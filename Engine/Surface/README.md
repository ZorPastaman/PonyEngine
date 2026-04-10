# PonyEngine.Surface module

Surface API module. Provides interfaces for a surface service.

The surface service manages an output surface, for example a display and primitive objects on it.
The surface service always has a display and a main output rectangle.

## Dependencies

- [PonyEngine.Core](../Core)

## C\++ modules

### [PonyEngine.Surface](Source/Main.cppm)

Main sub-modules:

#### [ISurfaceService](Source/Main-ISurfaceService.cppm)

Surface service public interface. Provides different functions to manipulate an output surface and to get info about it.

The availability of different functions depend on a runtime environment. So, it's critically important to check supported functions via `ISurfaceService.SupportedFeatures()`.

#### [ISurfaceObserver](Source/Main-ISurfaceObserver.cppm)

Surface observer interface. They can be added and removed to [ISurfaceService](Source/Main-ISurfaceService.cppm).
If added, they will receive different events that happen to a surface.

#### [MathUtility](Source/Main-MathUtility.cppm)

Math utility functions.
