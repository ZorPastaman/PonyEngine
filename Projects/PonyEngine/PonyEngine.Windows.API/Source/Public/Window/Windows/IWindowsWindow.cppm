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
	/// @brief Windows window interface.
	class IWindowsWindow : public IWindow
	{
	public:
		/// @brief Gets a windows window handle.
		/// @return Window handle.
		[[nodiscard("Pure function")]]
		virtual HWND GetWindowHandle() const noexcept = 0;

	protected:
		~IWindowsWindow() noexcept = default;
	};
}
