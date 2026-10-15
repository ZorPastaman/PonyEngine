# Tools build

Pony Engine uses several build tools during the project build process. 
Build these tools for a host platform first, then build the engine and your project for a target platform.

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
