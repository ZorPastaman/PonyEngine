/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "Platform/Windows/Framework.h"

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

		/// @brief Checks if the system window is alive.
		/// @return @a True if it's alive; @a false otherwise.
		[[nodiscard("Pure function")]]
		virtual bool IsWindowAlive() const noexcept = 0;

	protected:
		inline virtual ~IWindowsWindow() noexcept = default;
	};
}
