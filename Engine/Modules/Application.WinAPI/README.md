# PonyEngine.Application.WinAPI modification module

Adds WinAPI application interfaces to [PonyEngine.Application](../Application).

In GUI mode, the application has a message pump on all hwnd. It's called right in the beginning of a frame.
On WM_QUIT the application sets an exit code and exits after the end of a frame.

In Console mode, the application listens to CTRL+C combination and sets the application to stop so that it can exit in a correct way.
Other stop combinations aren't handled.

Modifies `PonyEngine.Application` target.

## Dependencies

- [PonyEngine.Application](../Application)
- Windows SDK 10.0.26100.0

## C\++ modules

### [PonyEngine.Application.WinAPI](Source/Application.cppm)

#### [IMainData](Source/Application-IMainData.cppm)

Provides the data that was passed into `WinMain()`. 

Exits only in GUI mode.

#### [IMessagePump](Source/Application-IMessagePump.cppm)

Provides the message data that was gotten in the message pump function.
The data is updated before dispathing. So, you can use it in your message handlers.

Exits only in GUI mode.
