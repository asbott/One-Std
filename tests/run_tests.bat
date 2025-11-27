clang run_tests.c -o run_tests.exe -O0 -w -fno-exceptions -fno-rtti -fno-stack-protector -g0 && run_tests.exe %*

if "%~1"=="" pause