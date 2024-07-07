/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Platform/Windows/Framework.h"

export module PonyEngine.Window.Windows.Factories:WindowsWindowParams;

export namespace PonyEngine::Window
{
	struct WindowsWindowParams final
	{
		WindowsWindowParams() noexcept = default;
		WindowsWindowParams(const WindowsWindowParams& other) = default;
		WindowsWindowParams(WindowsWindowParams&& other) noexcept = default;

		~WindowsWindowParams() noexcept = default;

		WindowsWindowParams& operator =(const WindowsWindowParams& other) = default;
		WindowsWindowParams& operator =(WindowsWindowParams&& other) noexcept = default;

		DWORD style; ///< Window style.
		DWORD extendedStyle; ///< Extended window style.
		int cmdShow = SW_NORMAL; ///< Window cmdShow.
	};
}
