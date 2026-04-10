# PonyEngine.RawInput.Mouse.Impl module

Raw input mouse provider module. It reads mouse input and pushes it into a raw input service.

The module requires a platform specific implementation.

## Dependencies

- [PonyEngine.Core](../Core)
- [PonyEngine.RawInput](../RawInput)
- [PonyEngine.RawInput.Ext](../RawInput.Ext)

## For Pony Engine developers

The module contains some utilities that can be useful for mouse implementations on any platform:

- [MouseAxis](Source/Main-MouseAxis.cppm);
- [MouseAxisMap](Source/Main-MouseAxisMap.cppm);
- [MouseContainer](Source/Main-MouseContainer.cppm);
- [MouseEvent](Source/Main-MouseEvent.cppm);
- [MouseEventQueue](Source/Main-MouseEventQueue.cppm).
