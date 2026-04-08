# PonyEngine.RawInput.Keyboard.Impl module for Windows

Platform independent module: [PonyEngine.RawInput.Keyboard.Impl](../../../Engine/RawInput.Keyboard.Impl).

## Dependencies

- [PonyEngine.Log](../../../Engine/Log)
- [PonyEngine.Application.Ext](../Application.Ext)
- [PonyEngine.Surface](../Surface)

## CMake variables

These variables are used to configure the build of the module:

| Variable name                          | Default value | Description                                                    |
|:---------------------------------------|:-------------:|:---------------------------------------------------------------|
| `PONY_ENGINE_RAW_INPUT_KEYBOARD_ORDER` | p             | PonyEngine.RawInput.Keyboard.Impl module initialization order. |

## For Pony Engine developers

Main submodules:

- [KeyboardAxisMap](Source/Private/Main-KeyboardAxisMap.cppm) - maps Windows scan codes to engine axes;
- [KeyboardProvider](Source/Private/Main-KeyboardProvider.cppm) - keyboard provider;
- [KeyboardProviderModule](Source/Private/Main-KeyboardProviderModule.cppm) - keyboard provider module.
