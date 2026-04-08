# PonyEngine.RawInput module

Raw input API module. Provides interfaces for a raw input service.

The idea is this. The raw input service has input devices. Each device has axes. Any axis is just an ID.
Every tick, the raw input service gathers input events. Each event contains an axis ID, a float value and an input type.
The input type can be either State or Delta. A state input is remembered by the service and can be changed only by another state input.
A delta input is added to a current delta input sum, and every tick delta inputs are zeroed.

Devices may have special features like vibration, for example. These features can be found via the raw input service interface.

## Dependencies

- [PonyEngine.Core](../Core)

## C\++ modules

### [PonyEngine.RawInput](Source/Public/Main.cppm)

Main sub-modules:

#### [IRawInputService](Source/Public/Main-IRawInputService.cppm)

Raw input service public interface.

#### [Axis](Source/Public/Main-Axis.cppm)

Input axis. It's a special string wrapper.

#### [AxisID](Source/Public/Main-AxisID.cppm)

Input axis ID. It's a hash value of the [Axis](Source/Public/Main-Axis.cppm). The engine uses this everywhere 'cause it's much faster to work with integers than with strings.

See [Axes](#axes) for details details.

#### [DeviceHandle](Source/Public/Main-DeviceHandle.cppm)

Device handle. It's an integer, and it's a special handle that is used to access an input device.

#### [DeviceType](Source/Public/Main-DeviceType.cppm)

Device type. It's a special string wrapper.

#### [DeviceTypeID](Source/Public/Main-DeviceTypeID.cppm)

Device type ID. It's a hash value of the [DeviceType](Source/Public/Main-DeviceType.cppm). The engine uses this everywhere 'cause it's much faster to work with integers than with strings.

See [Devices](#devices) for details details.

#### [IDeviceObserver](Source/Public/Main-IDeviceObserver.cppm)

Device observer interface. It can be added (and must be removed before the object destruction) to the [IRawInputService](Source/Public/Main-IRawInputService.cppm).
The added device observers receive different events on a device state change.

#### [IRawInputObserver](Source/Public/Main-IRawInputObserver.cppm)

Raw input observer interface. It can be added (and must be removed before the object destruction) to the [IRawInputService](Source/Public/Main-IRawInputService.cppm).
The added raw input observers receive raw input events.

#### [IVibrating](Source/Public/Main-IVibrating.cppm)

Device feature interface for vibration control.

## Axes

Axes are represented as string paths in the form `<something>/<something>/<something>`. The first segment defines a layout, while the following segments represent subtypes.
To make them easier to work with, the engine provides a wrapper class, [Axis](Source/Public/Main-Axis.cppm).
However, working directly with strings is inefficient, so axes are hashed internally. The [AxisID](Source/Public/Main-AxisID.cppm) wrapper simplifies working with these hash values.
The [IRawInputService](Source/Public/Main-IRawInputService.cppm) exposes functions for hashing axes, retrieving original strings from hash values, and validating those hashes. It also provides additional utility functions for working with axes.

Example of usage:

```
PonyEngine::RawInput::IRawInputService* rawInputService = GetRawInputService();
PonyEngine::RawInput::Axis axis = PonyEngine::RawInput::Axis("Gamepad/D-Pad/Up");
PonyEngine::RawInput::AxisID axisId = rawInputService->Hash(axis);
std::string axisOriginName = rawInputService->Unhash(axisId);
float value = rawInputService->Value(axisId);
```

## Devices

Devices are fully managed inside the raw input service. It exposes device handles only. The handles are unique for a device and never repeated.
The raw input service provides info about devices via different functions.

The devices may be enumerated via these functions: `IRawInputService.DeviceCount()` and `IRawInputService.Device(deviceIndex)`.

The devices have types that are represented as string paths in the form `<something>/<something>/<something>`. The first segment defines a base type, while the following segments represent subtypes.
To make them easier to work with, the engine provides a wrapper class, [DeviceType](Source/Public/Main-DeviceType.cppm).
However, working directly with strings is inefficient, so device types are hashed internally. The [DeviceTypeID](Source/Public/Main-DeviceTypeID.cppm) wrapper simplifies working with these hash values.
The [IRawInputService](Source/Public/Main-IRawInputService.cppm) exposes functions for hashing device types, retrieving original strings from hash values, and validating those hashes.

The devices may have custom features. Those may be accessed via `IRawInputService.FindFeature()` functions.

## String presets

The API provides default string for axes and device types. Use them wherever it's possible:

- [Layout](Source/Public/Main-Layout.cppm) - layout(axis) element names;
- [KeyboardDevice](Source/Public/Main-Keyboard.cppm) - keyboard device sub-type names;
- [KeyboardLayout](Source/Public/Main-Keyboard.cppm) - keyboard axis names;
- [MouseDevice](Source/Public/Main-Mouse.cppm) - mouse device sub-type names;
- [MouseLayout](Source/Public/Main-Mouse.cppm) - mouse axis names;
- [GamepadDevice](Source/Public/Main-Gamepad.cppm) - gamepad device sub-type names;
- [GamepadLayout](Source/Public/Main-Gamepad.cppm) - gamepad axis names;
