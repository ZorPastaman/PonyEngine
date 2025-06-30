/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#pragma once

#include <winsdkver.h>
#define _WIN32_WINNT 0x0A00
#define WINVER _WIN32_WINNT
#define NTDDI_VERSION 0x0A000010
#include <sdkddkver.h>
#include "PonyEngine/Platform/WinCore/Framework.h"

#include <windowsx.h>
#include <shlobj.h>
