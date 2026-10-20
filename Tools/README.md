# Tools build

Pony Engine uses several build tools during the project build process. 
Build these tools for a host platform first, then build the engine and your project for a target platform.

Tools build includes engine build as well for different API classes and functions.
It means that you can activate different modules and build your own tools inside the same build.

## Tools

Each tools is a separate cmake target that is built into an executable.

| Target                                                       | Output name                   |
|:-------------------------------------------------------------|:------------------------------|
| [PonyTools.TextCompiler](TextCompiler)                       | `PonyTextCompiler`            |
| [PonyTools.WorldDefinitionCompiler](WorldDefinitionCompiler) | `PonyWorldDefinitionCompiler` |
| [PonyTools.ResourcePacker](ResourcePacker)                   | `PonyResourcePacker`          |

## Extensions

These are dlls that may be used by tools.

| Target                                               | Output name               |
|:-----------------------------------------------------|:--------------------------|
| [PonyTools.WorldDataSerializer](WorldDataSerializer) | `PonyWorldDataSerializer` |

## Utilities

Static libraries that are used by the tools.

- [PonyTools.Utility](Utility)
