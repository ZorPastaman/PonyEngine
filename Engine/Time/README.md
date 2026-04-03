# PonyEngine.Time module

Log API module. Provides interfaces for a time service.

The time service provides an engine time including real time, virtual time and fixed time steps.
The time service controls a frame frequency as well.

## C\++ modules

### [PonyEngine.Time](Source/Public/Main.cppm)

Main sub-modules:

#### [ITimeService](Source/Public/Main-ITimeService.cppm)

Time service public interface. It provides different types of time and has function to control their calculations.
The time service gets a current real time in its tick and calculates all the properties using current parameters.
The calculated properties stay the same till a next tick. The only exception is `NowTime()` - it's calculated on every call.
The real time is always a real time returned by a platform while the virtual types of time are calculated as a sum of their deltas per frame.

Time types:

- Real - real time that is returned from a platform;
- Virtual - real time which a scale and a delta time cap is applied to;
- Unscaled virtual time - real time which a delta time camp is applied to.

All the time types are provided in an accumulated form (since the application start) and delta form (difference between frames).

Parameters:

- Delta time cap - upper limit of a virtual delta time;
- Scale - virtual time multiplier.

The service supports fixed time steps as well. The fixed time step period may be controlled via the service functions.
The fixed steps are calculated for all the time types in both overall and delta forms.

The time service can control a frame pacing. There's a function `TargetFrameTime()` that sets a target frame time. 
The service will wait in its tick till the frame time is equal or greater than that value.

#### [ConversionUtility](Source/Public/Main-ConversionUtility.cppm)

Utility functions that convert durations in defferent formats.
