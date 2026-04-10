# PonyEngine.Surface module for Windows

Platform independent module: [PonyEngine.Surface](../../../Engine/Surface).

## C\++ modules

### [PonyEngine.Surface.Windows](Source/Main.cppm)

Main interfaces:

#### [ISurfaceService](Source/Main-ISurfaceService.cppm)

Windows specific surface service public interface, inherits the platform independent interface.
The surface implementation on Windows must implement this interface.

Provides `HWND` of the game window, raw input and some other functions. 

#### [IRawInputObserver](Source/Main-IRawInputObserver.cppm)

Interface for an object that observers a raw input from Windows.
To receive it, add an observer to the [ISurfaceService](Source/Main-ISurfaceService.cppm).
