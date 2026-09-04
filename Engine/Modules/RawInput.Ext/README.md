# PonyEngine.RawInput.Ext feature module

Raw input extension API module. Provides interfaces for a raw input controller that can be added to a raw input device hub.

The raw input service doesn't know about specific devices, it's just a middle service that aggregates input from different input controller and exposes it to other services.

Adds `PonyEngine.RawInput.Ext` target as a static library.

## Dependencies

- [PonyEngine.Core](../Core)
- [PonyEngine.RawInput](../RawInput)

## C\++ modules

### [PonyEngine.RawInput.Ext](Source/Main.cppm)

#### [IDeviceController](Source/Main-IDeviceController.cppm)

Interface that receives requests about its devices.

#### [IDeviceHub](Source/Main-IDeviceHub.cppm)

Interface that provides API to register and unregister devices.

#### [IInputRegistry](Source/Main-IInputRegistry.cppm)

Interface that's used to report input including connection changes.
