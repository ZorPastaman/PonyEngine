# PonyEngine.RawInput feature module

Raw input API module. Provides interfaces for a raw input service.

The idea is this. The raw input service has input devices. Each device has axes. Any axis is just an ID.
Every tick, the raw input service gathers input events. Each event contains an axis ID, a float value and an input type.
The input type can be either State or Delta. A state input is remembered by the service and can be changed only by another state input.
A delta input is added to a current delta input sum, and every tick delta inputs are zeroed.

Devices may have special features like vibration, for example. These features can be found via the raw input service interface.

Adds `PonyEngine.RawInput` target as a static library.

## Dependencies

- [PonyEngine.Core](../Core)

## C\++ modules

### [PonyEngine.RawInput](Source/RawInput.cppm)

#### [IRawInputService](Source/RawInput-IRawInputService.cppm)

Raw input service public interface.

#### [Axis](Source/RawInput-Axis.cppm)

Input axis. It's a hash value of a axis string representation. The engine uses this everywhere 'cause it's much faster to work with integers than with strings.

See [Axes](#axes) for details details.

#### [DeviceHandle](Source/RawInput-DeviceHandle.cppm)

Device handle. It's an integer, and it's a special handle that is used to access an input device.

#### [DeviceType](Source/RawInput-DeviceType.cppm)

Device type. It's a hash value of a device type string representation. The engine uses this everywhere 'cause it's much faster to work with integers than with strings.

See [Devices](#devices) for details details.

#### [IDeviceObserver](Source/RawInput-IDeviceObserver.cppm)

Device observer interface. It can be added (and must be removed before the object destruction) to the [IRawInputService](Source/Main-IRawInputService.cppm).
The added device observers receive different events on a device state change.

#### [IRawInputObserver](Source/RawInput-IRawInputObserver.cppm)

Raw input observer interface. It can be added (and must be removed before the object destruction) to the [IRawInputService](Source/Main-IRawInputService.cppm).
The added raw input observers receive raw input events.

#### [IVibrating](Source/RawInput-IVibrating.cppm)

Device feature interface for vibration control.

## Axes

Axes are represented as strings. That allows to add as many axes at runtime as possible.
However, working directly with strings is inefficient, so axes are hashed internally. The [Axis](Source/RawInput-Axis.cppm) wrapper simplifies working with these hash values.
The [IRawInputService](Source/RawInput-IRawInputService.cppm) exposes functions for hashing axes, retrieving original strings from hash values, and validating those hashes. It also provides additional utility functions for working with axes.

Example of usage:

```
PonyEngine::RawInput::IRawInputService* rawInputService = GetRawInputService();
PonyEngine::RawInput::Axis axis = rawInputService->MakeAxis("Gamepad/D-Pad/Up");
float value = rawInputService->Value(axis);
```

## Devices

Devices are fully managed inside the raw input service. It exposes device handles only. The handles are unique for a device and never repeated.
The raw input service provides info about devices via different functions.

The devices may be enumerated via these functions: `IRawInputService.DeviceCount()` and `IRawInputService.Device(deviceIndex)`.

The devices have types that are represented as strings. That allows to add as many device types at runtime as possible.
However, working directly with strings is inefficient, so device types are hashed internally. The [DeviceType](Source/RawInput-DeviceType.cppm) wrapper simplifies working with these hash values.
The [IRawInputService](Source/RawInput-IRawInputService.cppm) exposes functions for hashing device types, retrieving original strings from hash values, and validating those hashes.

The devices may have custom features. Those may be accessed via `IRawInputService.FindFeature()` functions.

## String presets

The API provides default string for axes and device types. Use them wherever it's possible:

- [Layout](Source/RawInput-Layout.cppm) - layout(axis) element names;
- [KeyboardLayout](Source/RawInput-Keyboard.cppm) - keyboard axis names;
- [MouseLayout](Source/RawInput-Mouse.cppm) - mouse axis names;
- [GamepadLayout](Source/RawInput-Gamepad.cppm) - gamepad axis names;
