# PonyEngine.Application module for Windows

Platform independent module: [PonyEngine.Application](../../../Modules/Application).

In GUI mode, the application has a message pump on all hwnd. It's called right in the beginning of a frame.
On WM_QUIT the application sets an exit code and exits after the end of frame.

In Console mode, the application listens to CTRL+C combination and sets the application to stop so that it can exit in a correct way.
Other stop combinations aren't handled.

## C\++ modules

### [PonyEngine.Application.Windows](Source/Main.cppm)

#### [IMainData](Source/Main-IMainData.cppm)

Provides the data that was passed into `WinMain()`. 

Exits only in GUI mode.

#### [IMessagePump](Source/Main-IMessagePump.cppm)

Provides the message data that was gotten in the message pump function.
The data is updated before dispathing. So, you can use it in your message handlers.

Exits only in GUI mode.
