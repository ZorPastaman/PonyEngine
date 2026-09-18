# PonyEngine.RawInput.WinInput feature module

The module provides interfaces to register for WinAPI raw input events.

The module requires WinAPI support.

Adds `PonyEngine.WinInput` target as a static library.

## Dependencies

- [PonyEngine.Core](../Core)
- Windows SDK 10.0.26100.0

## C\++ modules

### [PonyEngine.WinInput](Source/WinInput.cppm)

#### [IRawInputObserver](Source/WinInput-IRawInputObserver.cppm)

WinAPI raw input observer.

#### [IInputDispatcher](Source/WinInput-IInputDispatcher.cppm)

The main interface where observers are registered for events.