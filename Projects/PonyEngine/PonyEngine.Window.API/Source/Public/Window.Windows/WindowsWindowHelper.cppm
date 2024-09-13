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

import PonyBase.Math;

export namespace PonyEngine::Window
{
	constexpr UINT DefaultClassStyle = CS_OWNDC;

	constexpr DWORD DefaultWindowedStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
	constexpr DWORD DefaultWindowedExtendedStyle = WS_EX_OVERLAPPEDWINDOW;
	constexpr DWORD DefaultBorderlessWindowedStyle = WS_POPUP;
	constexpr DWORD DefaultBorderlessWindowedExtendedStyle = 0;

	[[nodiscard("Pure function")]]
	PonyBase::Math::Vector2<int> GetDisplaySize() noexcept;

	[[nodiscard("Pure function")]]
	PonyBase::Math::Vector2<int> CalculateCenteredWindowPosition(const PonyBase::Math::Vector2<int>& windowSize) noexcept;

	[[nodiscard("Pure function")]]
	PonyBase::Math::Vector2<int> GetWindowClientSize(HWND hWnd) noexcept;
}

namespace PonyEngine::Window
{
	PonyBase::Math::Vector2<int> GetDisplaySize() noexcept
	{
		return PonyBase::Math::Vector2<int>(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	}

	PonyBase::Math::Vector2<int> CalculateCenteredWindowPosition(const PonyBase::Math::Vector2<int>& windowSize) noexcept
	{
		PonyBase::Math::Vector2<int> displaySize = GetDisplaySize();

		PonyBase::Math::Vector2<int> position;
		position.X() = displaySize.X() / 2 - windowSize.X() / 2;
		position.Y() = displaySize.Y() / 2 - windowSize.Y() / 2;

		return position;
	}

	PonyBase::Math::Vector2<int> GetWindowClientSize(const HWND hWnd) noexcept
	{
		RECT rect;
		GetClientRect(hWnd, &rect);

		PonyBase::Math::Vector2<int> size;
		size.X() = rect.right - rect.left;
		size.Y() = rect.bottom - rect.top;

		return size;
	}
}
