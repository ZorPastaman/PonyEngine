# PonyEngine.Core module for Windows

Platform independent module: [PonyEngine.Core](../../../Engine/Core).

## C\++ modules

### [PonyEngine.Platform.Windows](Source/Public/Platform.Windows.cppm)

Utilities specific to the Windows platform.

Main sub-modules:

#### [ComPtr](Source/Public/Platform.Windows-ComPtr.cppm)

Smart COM pointer implementation.

#### [Device](Source/Public/Platform.Windows-Device.cppm)

Utilities for Windows devices.

#### [File](Source/Public/Platform.Windows-File.cppm)

Utilities for Windows file system.

#### [GUID](Source/Public/Platform.Windows-GUID.cppm)

Utilities for Windows GUID including a formatter for it.

#### [Text](Source/Public/Platform.Windows-Text.cppm)

Utilities for text and text strings on Windows. It has converters between UTF-8 and UTF-16 strings.

## C\++ headers

### [PonyEngine/Platform/Windows/Framework.h](Include/Public/PonyEngine/Platform/Windows/Framework.h)

Main Windows framework header. It contains `#include <windows.h>` with correct defines.

## Public defines

Sets public defines to [PonyEngine.Core](../../../Engine/Core).

| Define         | Value |
|:---------------|:-----:|
| `PONY_WINDOWS` | N/A   |
