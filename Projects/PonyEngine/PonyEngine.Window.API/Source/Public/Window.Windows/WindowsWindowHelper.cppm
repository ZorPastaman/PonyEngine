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
import PonyBase.Screen;

export namespace PonyEngine::Window // TODO: Add tests and docs.
{
	constexpr UINT DefaultClassStyle = CS_OWNDC;

	constexpr DWORD DefaultWindowedStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
	constexpr DWORD DefaultWindowedExtendedStyle = WS_EX_OVERLAPPEDWINDOW;
	constexpr DWORD DefaultBorderlessWindowedStyle = WS_POPUP;
	constexpr DWORD DefaultBorderlessWindowedExtendedStyle = 0;

	[[nodiscard("Pure function")]]
	PonyBase::Screen::Resolution<unsigned int> GetDisplaySize() noexcept;

	[[nodiscard("Pure function")]]
	PonyBase::Math::Vector2<int> CalculateCenteredWindowPosition(const PonyBase::Screen::Resolution<unsigned int>& windowSize) noexcept;

	[[nodiscard("Pure function")]]
	PonyBase::Screen::Resolution<unsigned int> GetWindowClientSize(HWND hWnd) noexcept;
}

namespace PonyEngine::Window
{
	PonyBase::Screen::Resolution<unsigned int> GetDisplaySize() noexcept
	{
		return PonyBase::Screen::Resolution<unsigned int>(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	}

	PonyBase::Math::Vector2<int> CalculateCenteredWindowPosition(const PonyBase::Screen::Resolution<unsigned int>& windowSize) noexcept
	{
		const PonyBase::Screen::Resolution<unsigned int> displaySize = GetDisplaySize();

		PonyBase::Math::Vector2<int> position;
		position.X() = displaySize.Width() / 2 - windowSize.Width() / 2;
		position.Y() = displaySize.Height() / 2 - windowSize.Height() / 2;

		return position;
	}

	PonyBase::Screen::Resolution<unsigned int> GetWindowClientSize(const HWND hWnd) noexcept
	{
		RECT rect;
		GetClientRect(hWnd, &rect);

		PonyBase::Screen::Resolution<unsigned int> size;
		size.Width() = rect.right - rect.left;
		size.Height() = rect.bottom - rect.top;

		return size;
	}
}
