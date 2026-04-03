# PonyEngine.Surface module

Surface API module. Provides interfaces for a surface service.

The surface service manages an output surface, for example a display and primitive objects on it.
The surface service always has a display and a main output rectangle.

## C\++ modules

### [PonyEngine.Surface](Source/Public/Main.cppm)

Main sub-modules:

#### [ISurfaceService](Source/Public/Main-ISurfaceService.cppm)

Surface service public interface. Provides different functions to manipulate an output surface and to get info about it.

The availability of different functions depend on a runtime environment. So, it's critically important to check supported functions via `ISurfaceService.SupportedFeatures()`.

#### [ISurfaceObserver](Source/Public/Main-ISurfaceObserver.cppm)

Surface observer interface. They can be added and removed to [ISurfaceService](Source/Public/Main-ISurfaceService.cppm).
If added, they will receive different events that happen to a surface.

#### [MathUtility](Source/Public/Main-MathUtility.cppm)

Math utility functions.
