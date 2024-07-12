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

export module PonyEngine.Window.Windows.Factory:WindowsWindowParams;

export namespace PonyEngine::Window
{
	/// @brief Windows window parameters.
	struct WindowsWindowParams final
	{
		[[nodiscard("Pure constructor")]]
		WindowsWindowParams() noexcept = default;
		[[nodiscard("Pure constructor")]]
		WindowsWindowParams(const WindowsWindowParams& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		WindowsWindowParams(WindowsWindowParams&& other) noexcept = default;

		~WindowsWindowParams() noexcept = default;

		WindowsWindowParams& operator =(const WindowsWindowParams& other) noexcept = default;
		WindowsWindowParams& operator =(WindowsWindowParams&& other) noexcept = default;

		DWORD style; ///< Window style.
		DWORD extendedStyle; ///< Extended window style.
		int cmdShow = SW_NORMAL; ///< Window cmdShow.
	};
}
