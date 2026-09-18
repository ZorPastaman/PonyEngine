# PonyEngine.RawInput.Mouse.Impl.WinAPI modification module

Adds WinAPI implementation to [PonyEngine.RawInput.Mouse.Impl](../RawInput.Mouse.Impl).

Modifies `PonyEngine.RawInput.Mouse.Impl` target.

## Dependencies

- [PonyEngine.Application](../Application)
- [PonyEngine.Log](../Log)
- [PonyEngine.RawInput.Mouse.Impl](../RawInput.Mouse.Impl)
- [PonyEngine.WinInput](../WinInput)
- Windows SDK 10.0.26100.0

## CMake variables

These variables are used to configure the build of the module:

| Variable name                       | Default value | Description                                                 |
|:------------------------------------|:-------------:|:------------------------------------------------------------|
| `PONY_ENGINE_RAW_INPUT_MOUSE_ORDER` | p             | PonyEngine.RawInput.Mouse.Impl module initialization order. |

## For Pony Engine developers

Main submodules:

- [MouseProvider](Source/Mouse-MouseProvider.cppm) - mouse provider;
- [MouseProviderModule](Source/Mouse-MouseProviderModule.cppm) - mouse provider module.
