# PonyEngine.Resource.Text.Impl feature module

Text resource loader module. It supports `PonyText` resource type.

Adds `PonyEngine.Resource.Text.Impl` target as a static library.

## Dependencies

- [PonyEngine.Application](../Application)
- [PonyEngine.Core](../Core)
- [PonyEngine.Log](../Log)
- [PonyEngine.Resource](../Resource)
- [PonyEngine.Resource.Ext](../Resource.Ext)

## CMake variables

These variables are used to configure the build of the module:

| Variable name                            | Default value | Description                                                |
|:-----------------------------------------|:-------------:|:-----------------------------------------------------------|
| `PONY_ENGINE_RESOURCE_TEXT_ORDER`        | p             | PonyEngine.Resource.Text.Impl module initialization order. |

## For Pony Engine developers

Main sub-modules:

- [TextLoader](Source/Text-TextLoader.cppm) - text resource loader;
- [TextLoaderModule](Source/Text-TextLoaderModule.cppm) - text resource loader module.
