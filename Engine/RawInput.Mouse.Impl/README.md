# PonyEngine.RawInput.Mouse.Impl module

Raw input mouse provider module. It reads mouse input and pushes it into a raw input service.

The module requires a platform specific implementation.

## For Pony Engine developers

The module contains some utilities that can be useful for mouse implementations on any platform:

- [MouseAxis](Source/Private/Main-MouseAxis.cppm);
- [MouseAxisMap](Source/Private/Main-MouseAxisMap.cppm);
- [MouseContainer](Source/Private/Main-MouseContainer.cppm);
- [MouseEvent](Source/Private/Main-MouseEvent.cppm);
- [MouseEventQueue](Source/Private/Main-MouseEventQueue.cppm).
