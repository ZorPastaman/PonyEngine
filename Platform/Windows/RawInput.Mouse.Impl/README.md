# PonyEngine.RawInput.Mouse.Impl module for Windows

Platform independent module: [PonyEngine.RawInput.Mouse.Impl](../../../Engine/RawInput.Mouse.Impl).

## Dependencies

- [PonyEngine.Log](../../../Engine/Log)
- [PonyEngine.Application.Ext](../Application.Ext)
- [PonyEngine.Surface](../Surface)

## CMake variables

These variables are used to configure the build of the module:

| Variable name                       | Default value | Description                                                 |
|:------------------------------------|:-------------:|:------------------------------------------------------------|
| `PONY_ENGINE_RAW_INPUT_MOUSE_ORDER` | p             | PonyEngine.RawInput.Mouse.Impl module initialization order. |

## For Pony Engine developers

Main submodules:

- [MouseProvider](Source/Main-MouseProvider.cppm) - mouse provider;
- [MouseProviderModule](Source/Main-MouseProviderModule.cppm) - mouse provider module.
