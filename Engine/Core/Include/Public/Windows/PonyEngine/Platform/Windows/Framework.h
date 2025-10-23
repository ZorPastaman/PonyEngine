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
#define NTDDI_VERSION 0x0A00000D
#include <sdkddkver.h>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <wrl/client.h>

#include <windowsx.h>
#include <hidusage.h>
#include <shlobj.h>
