# MSVC compiler support

MSVC compiler support module. It adds required compiler-dependent defines to [PonyEngine.Core](../../Engine/Core).

## C\++ headers

### [PonyEngine/Macro/MSVC/Compiler.h](Include/Public/PonyEngine/Macro/MSVC/Compiler.h)

Contains required compiler defines.

## Public defines

Sets public defines to [PonyEngine.Core](../../Engine/Core).

| Define                  | Value                              |
|:------------------------|:----------------------------------:|
| `PONY_COMPILER_INCLUDE` | "PonyEngine/Macro/MSVC/Compiler.h" |
| `PONY_MSVC`             | N/A                                |

## Build

Before building with MSVC using CMake, you must set up the MSVC build environment.
See details on [Microsoft Learn](https://learn.microsoft.com/en-us/cpp/build/building-on-the-command-line?view=msvc-170).
