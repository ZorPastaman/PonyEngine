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
#include "PonyBase/Utility/Interface.h"

export module PonyEngine.Window.Windows:IWindowsWindowSystem;

import PonyEngine.Window;

export namespace PonyEngine::Window
{
	/// @brief Window system for Windows.
	class IWindowsWindowSystem : public IWindowSystem
	{
		INTERFACE_BODY(IWindowsWindowSystem)

		/// @brief Gets the window handle.
		/// @return Window handle.
		[[nodiscard("Pure function")]]
		virtual HWND WindowHandle() const noexcept = 0;
	};
}
