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

export module PonyEngine.Window.Windows.Detail:IWindowsWindowSystemContext;

import PonyDebug.Log;

export namespace PonyEngine::Window
{
	/// @brief Windows window system context.
	class IWindowsWindowSystemContext
	{
		INTERFACE_BODY(IWindowsWindowSystemContext)

		/// @brief Gets the logger.
		/// @return Logger.
		[[nodiscard("Pure function")]]
		virtual PonyDebug::Log::ILogger& Logger() noexcept = 0;
		/// @brief Gets the logger.
		/// @return Logger.
		[[nodiscard("Pure function")]]
		virtual const PonyDebug::Log::ILogger& Logger() const noexcept = 0;

		/// @brief Gets the window handle.
		/// @return Window handle.
		[[nodiscard("Pure function")]]
		virtual HWND WindowHandle() const noexcept = 0;
	};
}
