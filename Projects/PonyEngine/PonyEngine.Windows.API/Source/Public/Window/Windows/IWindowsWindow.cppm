/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#define WIN32_LEAN_AND_MEAN 
#include <windows.h>

export module PonyEngine.Window.Windows:IWindowsWindow;

import PonyEngine.Window;

namespace PonyEngine::Window
{
	/// @brief Windows window interface.
	export class IWindowsWindow : public IWindow
	{
	public:
		/// @brief Gets a windows window handle.
		/// @details Use this handle only for readonly operations.
		/// @return Window handle.
		[[nodiscard("Pure function")]]
		virtual HWND GetWindowHandle() const noexcept = 0;

	protected:
		inline virtual ~IWindowsWindow() noexcept = default;
	};
}
