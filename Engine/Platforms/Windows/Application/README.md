# PonyEngine.Application module for Windows

Platform independent module: [PonyEngine.Application](../../../Modules/Application).

The application has a message pump on all hwnd. It's called right in the beginning of a frame.

## C\++ modules

### [PonyEngine.Application.Windows](Source/Main.cppm)

Main interfaces:

#### [IMainData](Source/Main-IMainData.cppm)

Provides the data that was passed into `WinMain()`.

#### [IMessagePump](Source/Main-IMessagePump.cppm)

Provides the message data that was gotten in message pump function.
The data is updated before dispathing. So, you can use it in your message handlers.

#### [IResourceProvider](Source/Main-IResourceProvider.cppm)

Provides data from .rc files.
