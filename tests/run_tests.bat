@echo off
setlocal EnableDelayedExpansion

REM --- Clear or create the test_result directory ---
if exist test_result (
    rmdir /s /q test_result
)
mkdir test_result

REM --- Create (or clear) overall log files ---
type nul > test_result\full_log.txt
type nul > test_result\summary.txt

@echo on
"../scripts/concat-header.py" ../src/ostd.h ../ostd_single_header.h
@echo off

echo.
echo Starting tests...
echo.

REM --- Loop through each .c file in the current directory ---
for %%F in (*.c) do (
    set "fname=%%~nF"
    set "testFailed=0"
    
    REM --- Minimal console output for this test ---
    REM It will be a single line with the test name and OK/ERROR.
    
    echo ==== Running test: %%F ====
    
    REM --- Debug compile ---
    clang -o "test_result\!fname!-debug.exe" "!fname!.c" -O0 -std=c99 -pedantic -nodefaultlibs -Wall -Werror -Weverything -DDEBUG -I../vendors -L./../. -DRUNNING_TESTS -DTESTING_DURATION=1 -mavx -mavx2> "test_result\!fname!-debug_compile.log" 2>&1
    set "debugCompileError=!ERRORLEVEL!"
    echo. >> test_result\full_log.txt
    echo ===== !fname!-debug compile output ===== >> test_result\full_log.txt
    type "test_result\!fname!-debug_compile.log" >> test_result\full_log.txt

    if !debugCompileError! neq 0 (
        set "testFailed=1"
    ) else (
        REM --- Debug run ---
        pushd ..
        "tests\test_result\!fname!-debug.exe" > "tests\test_result\!fname!-debug_run.log" 2>&1
        popd
        set "debugRunError=!ERRORLEVEL!"
        echo. >> test_result\full_log.txt
        echo ===== !fname!-debug run output ===== >> test_result\full_log.txt
        type "test_result\!fname!-debug_run.log" >> test_result\full_log.txt
        if !debugRunError! neq 0 (
            set "testFailed=1"
        )
    )

    REM --- Release compile ---
    clang -o "test_result\!fname!-release.exe" "!fname!.c" -O2 -std=c23 -pedantic -nodefaultlibs -Wall -Werror -Weverything -Wno-pre-c23-compat -I../vendors -L./../. -DRUNNING_TESTS -DTESTING_DURATION=1 -mavx -mavx2 > "test_result\!fname!-release_compile.log" 2>&1
    set "releaseCompileError=!ERRORLEVEL!"
    echo. >> test_result\full_log.txt
    echo ===== !fname!-release compile output ===== >> test_result\full_log.txt
    type "test_result\!fname!-release_compile.log" >> test_result\full_log.txt
    if !releaseCompileError! neq 0 (
        set "testFailed=1"
    ) else (
    	pushd ..
        REM --- Release run ---
        "tests\test_result\!fname!-release.exe" > "tests\test_result\!fname!-release_run.log" 2>&1
        popd
        set "releaseRunError=!ERRORLEVEL!"
        echo. >> test_result\full_log.txt
        echo ===== !fname!-release run output ===== >> test_result\full_log.txt
        type "test_result\!fname!-release_run.log" >> test_result\full_log.txt
        if !releaseRunError! neq 0 (
            set "testFailed=1"
        )
    )

    REM --- Print minimal test result to console ---
    if !testFailed! equ 0 (
       powershell "Write-Host 'PASSED' -ForegroundColor Green"
    ) else (
       powershell "Write-Host 'ERROR' -ForegroundColor Red"

        REM --- Append details to summary for any failed test ---
        (
         echo.
         echo.
         echo =============================
         echo Test: %%F FAILED
         echo =============================
         echo.
         if !debugCompileError! neq 0 (
            echo --- Debug Compile Log:
            type "test_result\!fname!-debug_compile.log"
         ) else if !debugRunError! neq 0 (
            echo --- Debug Run Log:
            type "test_result\!fname!-debug_run.log"
         )
         if !releaseCompileError! neq 0 (
            echo --- Release Compile Log:
            type "test_result\!fname!-release_compile.log"
         ) else if !releaseRunError! neq 0 (
            echo --- Release Run Log:
            type "test_result\!fname!-release_run.log"
         )
        ) >> test_result\summary.txt
    )
)

echo.
echo ===============================
echo TEST SUMMARY:
echo ===============================
type test_result\summary.txt
echo.
echo Full log is available in test_result\full_log.txt
pause
endlocal
