# Third-Party Software

This repo uses the following third-party libraries:

## Catch2
- Version: v3.8.1
- Repo: https://github.com/catchorg/Catch2/tree/v3.8.1
- License: https://github.com/catchorg/Catch2/blob/v3.8.1/LICENSE.txt
- Integration: CMake Git dependency.
- Modules that use it: none, only unit tests use it.

## TOML++
- Version: v3.4.0
- Repo: https://github.com/marzer/tomlplusplus/tree/v3.4.0
- License: https://github.com/marzer/tomlplusplus/blob/v3.4.0/LICENSE
- Integration: CMake Git dependency.
- Modules that use it:
	- [PonyTools.FileResourceManifestCompiler](Tools/FileResourceManifestCompiler)
	- [PonyTools.FileResourceManifestGenerator](Tools/FileResourceManifestGenerator)
	- [PonyTools.PackResourceManifestCompiler](Tools/PackResourceManifestCompiler)
	- [PonyTools.PackResourceManifestGenerator](Tools/PackResourceManifestGenerator)
