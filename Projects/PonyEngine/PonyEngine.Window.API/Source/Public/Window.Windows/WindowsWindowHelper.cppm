/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/Windows/Framework.h"

export module PonyEngine.Window.Windows:WindowsWindowHelper;

import PonyMath.Core;

import PonyEngine.Screen;

export namespace PonyEngine::Window // TODO: Add tests and docs. And move to PonyEngine.Screen
{
	constexpr UINT DefaultClassStyle = CS_OWNDC;

	constexpr DWORD DefaultWindowedStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
	constexpr DWORD DefaultWindowedExtendedStyle = WS_EX_OVERLAPPEDWINDOW;
	constexpr DWORD DefaultBorderlessWindowedStyle = WS_POPUP;
	constexpr DWORD DefaultBorderlessWindowedExtendedStyle = 0;
}
