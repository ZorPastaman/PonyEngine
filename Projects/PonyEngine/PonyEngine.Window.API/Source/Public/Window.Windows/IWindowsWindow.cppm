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

export module PonyEngine.Window.Windows:IWindowsWindow;

import PonyEngine.Window;

export namespace PonyEngine::Window
{
	/// @brief Windows window.
	class IWindowsWindow : public IWindow
	{
	public:
		IWindowsWindow(const IWindowsWindow&) = delete;
		IWindowsWindow(IWindowsWindow&&) = delete;

		/// @brief Gets the windows window handle.
		/// @return Window handle.
		[[nodiscard("Pure function")]]
		virtual HWND WindowHandle() const noexcept = 0;

		IWindowsWindow& operator =(const IWindowsWindow&) = delete;
		IWindowsWindow& operator =(IWindowsWindow&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IWindowsWindow() noexcept = default;

		~IWindowsWindow() noexcept = default;
	};
}
