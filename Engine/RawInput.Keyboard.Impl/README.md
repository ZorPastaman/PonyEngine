# PonyEngine.RawInput.Keyboard.Impl module

Raw input keyboard provider module. It reads keyboard input and pushes it into a raw input service.

The module requires a platform specific implementation.

## Dependencies

- [PonyEngine.Core](../Core)
- [PonyEngine.RawInput](../RawInput)
- [PonyEngine.RawInput.Ext](../RawInput.Ext)

## For Pony Engine developers

The module contains some utilities that can be useful for keyboard implementations on any platform:

- [KeyboardContainer](Source/Main-KeyboardContainer.cppm);
- [KeyboardEvent](Source/Main-KeyboardEvent.cppm);
- [KeyboardEventQueue](Source/Main-KeyboardEventQueue.cppm).
