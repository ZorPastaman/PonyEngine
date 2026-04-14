# PonyEngine.RawInput.XInput.Impl module for Windows

Platform independent module: [PonyEngine.RawInput.XInput.Impl](../../../Engine/RawInput.XInput.Impl).

## Dependencies

- [PonyEngine.Core](../Core)
- [PonyEngine.Log](../../../Engine/Log)
- [PonyEngine.Application.Ext](../Application.Ext)
- [PonyEngine.Surface](../Surface)
- Xinput.lib (Windows SDK)

## CMake variables

These variables are used to configure the build of the module:

| Variable name                        | Default value | Description                                                  |
|:-------------------------------------|:-------------:|:-------------------------------------------------------------|
| `PONY_ENGINE_RAW_INPUT_XInput_ORDER` | p             | PonyEngine.RawInput.XInput.Impl module initialization order. |

## For Pony Engine developers

Main submodules:

- [GamepadAxisMap](Source/Main-GamepadAxisMap.cppm) - map of the XInput gamepad axes to the engine input axes;
- [XInputProvider](Source/Main-XInputProvider.cppm) - XInput provider;
- [XInputProviderModule](Source/Main-XInputProviderModule.cppm) - XInput provider module.
