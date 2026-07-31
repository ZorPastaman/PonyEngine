# PonyEngine.RawInput.XInput.Impl module for Windows

Platform independent module: [PonyEngine.RawInput.XInput.Impl](../../../Modules/RawInput.XInput.Impl).

## Dependencies

- [PonyEngine.Application](../Application)
- [PonyEngine.Core](../Core)
- [PonyEngine.Log](../../../Modules/Log)
- Xinput.lib (Windows SDK)

## CMake variables

These variables are used to configure the build of the module:

| Variable name                        | Default value | Description                                                  |
|:-------------------------------------|:-------------:|:-------------------------------------------------------------|
| `PONY_ENGINE_RAW_INPUT_XINPUT_ORDER` | p             | PonyEngine.RawInput.XInput.Impl module initialization order. |

## For Pony Engine developers

Main submodules:

- [XInputProvider](Source/Main-XInputProvider.cppm) - XInput provider;
- [XInputProviderModule](Source/Main-XInputProviderModule.cppm) - XInput provider module.
