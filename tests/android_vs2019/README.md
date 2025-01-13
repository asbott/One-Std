# Teapot Sample

This project demonstrates Windows and Android sharing C++ code. This sample uses the Ninja backend, which enables building APKs/AABs with multiple ABIs.

## Building Multi-ABI APKs and App Bundles
You can build multi-ABI APKs and App Bundles with this sample by building with Gradle from the command-line.

### Build Using MSBuild

Build a multi-ABI APK:

```
msbuild Teapot.sln /t:Gradle/Assemble /p:Configuration=Debug
```

Build a multi-ABI App Bundle:

```
msbuild Teapot.sln /t:Gradle/Bundle /p:Configuration=Release
```

You can also execute an arbitrary Gradle task. This example builds APKs for all known Gradle variants.

```
msbuild Teapot.sln /t:Gradle/Task /p:GradleTaskName=assemble
```

### Build Using Gradle
You can also directly build a multi-ABI APK or App Bundle with Gradle.

First, set up an environment variable for the version of MSBuild your project requires. For example,

```
set MSBUILD_TOOLS_PATH=C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\bin
```

Then, you can build all configured APKs:

```
gradlew :GameApplication:assembleDebug
dir *.apk /s/b
```

Alternatively, you can build an App Bundle like this:

```
gradlew :GameApplication:bundleDebug
dir *.aab /s/b
```

The APKs and App Bundles built this way will contain all targetted ABIs. The set of ABIs is defined in build.gradle here:

```
experimentalProperties["ninja.abiFilters"] = ["x86_64", "arm64-v8a" ]
```

### Build Using Android Studio
Lastly, you can open build.gradle in this folder in Android Studio. From there, you can build, edit, and debug the project.
Mixed mode Native/Java debugging is available this way. The recommended Android Studio version is 2022.3.1 (Giraffe Patch 1) or higher.

## Windows Setup

In order to build run this sample on Windows you will need libraries 'freeglut' and 'glew'.

One way to get these is to use vcpkg:

```
./vcpkg install freeglut:x64-windows
./vcpkg install glew:x64-windows
./vcpkg install freeglut:x86-windows
./vcpkg install glew:x86-windows
```

The vcpkg tool can be installed using these instructions: https://vcpkg.io/en/getting-started.html 