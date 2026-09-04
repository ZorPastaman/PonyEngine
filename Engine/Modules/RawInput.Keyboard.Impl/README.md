# PonyEngine.RawInput.Keyboard.Impl feature module

Raw input keyboard provider module. It reads keyboard input and pushes it into a raw input service.

Adds `PonyEngine.RawInput.Keyboard.Impl` target as a static library.

The module requires a platform specific implementation.

## Dependencies

- [PonyEngine.RawInput](../RawInput)
- [PonyEngine.RawInput.Ext](../RawInput.Ext)

## For Pony Engine developers

Main modules:

### [PonyEngine.RawInput.Keyboard.Impl](Source/Main.cppm)

#### [KeyboardController](Source/Main-KeyboardController.cppm)

Platform independent keyboard controller.
