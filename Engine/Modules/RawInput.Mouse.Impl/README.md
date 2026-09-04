# PonyEngine.RawInput.Mouse.Impl feature module

Raw input mouse provider module. It reads mouse input and pushes it into a raw input service.

Adds `PonyEngine.RawInput.Mouse.Impl` target as a static library.

The module requires a platform specific implementation.

## Dependencies

- [PonyEngine.Core](../Core)
- [PonyEngine.RawInput](../RawInput)
- [PonyEngine.RawInput.Ext](../RawInput.Ext)

## For Pony Engine developers

The module contains some utilities that can be useful for mouse implementations on any platform:

- [MouseAxis](Source/Main-MouseAxis.cppm);
- [MouseAxisMap](Source/Main-MouseAxisMap.cppm);
- [MouseController](Source/Main-MouseController.cppm).
