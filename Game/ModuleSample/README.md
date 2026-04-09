# Module sample

Shows how to make an engine module and add it to the engine application.

## Supported platform/compiler

| Compiler \ Platform | Windows |
|:-------------------:|:-------:|
| MSVC                | &check; |

## CMake version

The sample uses an experimental CMake feature to build `std` module automatically.
If you use CMake 3.31, you don't need to do anything.
Otherwise, you have to replace the experiment ID in `CMakeLists.txt`.
Find the line `set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")` and replace the ID with a value for your version.
Refer to the CMake documentation for the correct value: https://github.com/Kitware/CMake/blob/v3.31.0/Help/dev/experimental.rst - change the version in the link to your CMake version.

## Presets

The sample uses cmake presets for configuration and building.
The preset name pattern is `<PLATFORM>-<COMPILER>-<BUILD_TYPE>`.
The build type here is not a standard CMake build type. The engine uses its own.

| Build type  | Description                                                                                                          |
|:------------|:---------------------------------------------------------------------------------------------------------------------|
| Debug       | Both the game and the engine are in debug mode with no optimization.                                                 |
| Development | Both the game and the engine are in debug mode. The game uses no optimization. The engine uses release optimization. |
| Optimized   | Both the game and the engine are in debug mode with release optimization.                                            |
| Release     | Both the game and the engine are in release with debug info mode with release optimization.                          |
| Shipping    | Both the game and the engine are in release without debug info mode with release optimization.                       |

The preset names are shortened. Refer to the tables below to find a correct name. The display names are full.

| Full platform name | Short platform name |
|:-------------------|:--------------------|
| Windows            | Win                 |

| Full compiler name | Short compiler name |
|:-------------------|:--------------------|
| MSVC               | MSVC                |

| Full build type name | Short build type name |
|:---------------------|:----------------------|
| Debug                | Deb                   |
| Development          | Dev                   |
| Optimized            | Opt                   |
| Release              | Rel                   |
| Shipping             | Shi                   |

## How to build and launch

### Windows/MSVC

#### Via Visual Studio

1. Open the project;
2. Wait till CMake configuration is finished;
3. Choose any `Windows MSVC - <BUILD_TYPE>` configuration;
4. Choose `PonyGame.exe (Install)` as a startup item;
5. Click `Start Debugging`.

#### Via console

1. Open the console in your project folder;
2. Apply `vcvars*.bat`. For example, enter `C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" amd64`;
Refer to Microsoft documentation: https://learn.microsoft.com/en-us/cpp/build/building-on-the-command-line?view=msvc-170 for details;
3. Enter `cmake --preset Win-MSVC-<BUILD_TYPE>`;
4. Enter `cmake --build --preset Win-MSVC-<BUILD_TYPE> --target install`;
5. Launch `<YOUR_PROJECT_FOLDER>/Install/Win-MSVC-<BUILD_TYPE>/PonyGame.exe`.

## Main files

### [Game](GameSample/Source/Private/Game.cppm)

Module sample.

### [Main](GameSample/Source/Main.cpp) & [Main.Impl](GameSample/Source/Main.Impl.cpp)

Creates the game module and adds it to the application.

It's divided into two files because CMake doesn't allow to use private C\++ modules in public .cpp files.
