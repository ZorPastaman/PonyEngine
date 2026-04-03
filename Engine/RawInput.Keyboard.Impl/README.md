# PonyEngine.RawInput.Keyboard.Impl module

Raw input keyboard provider module. It reads keyboard input and pushes it into a raw input service.

The module requires a platform specific implementation.

## For Pony Engine developers

The module contains some utilities that can be useful for keyboard implementations on any platform:

- [KeyboardContainer](Source/Private/Main-KeyboardContainer.cppm);
- [KeyboardEvent](Source/Private/Main-KeyboardEvent.cppm);
- [KeyboardEventQueue](Source/Private/Main-KeyboardEventQueue.cppm).
