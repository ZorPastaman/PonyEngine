# Tools build

Pony Engine uses several build tools during the game build process. 
Build these tools for a host platform first, then build the engine and your game for a target platform.

## Tools

Each tools is a separate cmake target that is built into an executable.

| Target                                                                   | Output name | Description                                                                                      |
|:-------------------------------------------------------------------------|:------------|:-------------------------------------------------------------------------------------------------|
| [PonyTools.FileResourceManifestCompiler](FileResourceManifestCompiler)   | `ponyfrmc`  | Compiles text file resource manifest to binary file resource manifest.                           |
| [PonyTools.FileResourceManifestGenerator](FileResourceManifestGenerator) | `ponyfrmg`  | Creates and modifies text file resource manifest.                                                |
| [PonyTools.PackResourceManifestCompiler](PackResourceManifestCompiler)   | `ponyprmc`  | Compiles text pack resource manifest to binary pack resource manifest and binary data container. |
| [PonyTools.PackResourceManifestGenerator](PackResourceManifestGenerator) | `ponyprmg`  | Creates and modifies text pack resource manifest.                                                |
