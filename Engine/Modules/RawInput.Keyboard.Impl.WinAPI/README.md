# PonyEngine.RawInput.Keyboard.Impl.WinAPI modification module

Adds WinAPI implementation to [PonyEngine.RawInput.Keyboard.Impl](../RawInput.Keyboard.Impl).

Modifies `PonyEngine.RawInput.Keyboard.Impl` target.

## Dependencies

- [PonyEngine.Application](../Application)
- [PonyEngine.Core](../Core)
- [PonyEngine.Log](..//Log)
- [PonyEngine.RawInput.Keyboard.Impl](../RawInput.Keyboard.Impl)
- [PonyEngine.WinAPIInput](../WinAPIInput)
- Windows SDK 10.0.26100.0
 
## CMake variables

These variables are used to configure the build of the module:

| Variable name                          | Default value | Description                                                    |
|:---------------------------------------|:-------------:|:---------------------------------------------------------------|
| `PONY_ENGINE_RAW_INPUT_KEYBOARD_ORDER` | p             | PonyEngine.RawInput.Keyboard.Impl module initialization order. |

## For Pony Engine developers

Main submodules:

- [KeyboardAxisMap](Source/Keyboard-KeyboardAxisMap.cppm) - maps Windows scan codes to engine axes;
- [KeyboardProvider](Source/Keyboard-KeyboardProvider.cppm) - keyboard provider;
- [KeyboardProviderModule](Source/Keyboard-KeyboardProviderModule.cppm) - keyboard provider module.
