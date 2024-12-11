/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/Interface.h"

export module PonyEngine.Window:IWindowSystem;

import <cstdint>;

import PonyMath.Core;
import PonyMath.Utility;

import :IWindowTitleBar;

export namespace PonyEngine::Window
{
	/// @brief Window system.
	class IWindowSystem
	{
		INTERFACE_BODY(IWindowSystem)

		/// @brief Gets the window title bar.
		/// @return Window title bar.
		[[nodiscard("Pure function")]]
		virtual IWindowTitleBar& TitleBar() noexcept = 0;
		/// @brief Gets the window title bar.
		/// @return Window title bar.
		[[nodiscard("Pure function")]]
		virtual const IWindowTitleBar& TitleBar() const noexcept = 0;

		/// @brief Checks if the window is visible.
		/// @return @a True if it's visible; @a false otherwise.
		[[nodiscard("Pure function")]]
		virtual bool IsVisible() const noexcept = 0;
		/// @brief Shows the window.
		virtual void ShowWindow() = 0;
		/// @brief Hides the window.
		virtual void HideWindow() = 0;

		/// @brief Gets the window position.
		/// @return Window position.
		[[nodiscard("Pure function")]]
		virtual PonyMath::Core::Vector2<std::int32_t> Position() const noexcept = 0;
		/// @brief Gets the window resolution.
		/// @return Window resolution.
		[[nodiscard("Pure function")]]
		virtual PonyMath::Utility::Resolution<std::uint32_t> Resolution() const noexcept = 0;
	};
}
