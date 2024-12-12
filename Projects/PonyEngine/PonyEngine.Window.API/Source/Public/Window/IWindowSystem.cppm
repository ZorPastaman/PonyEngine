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
import <utility>;

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

		/// @brief Gets window rect.
		/// @return Left-upper point as position and resolution of the window rect.
		[[nodiscard("Pure function")]]
		virtual std::pair<PonyMath::Core::Vector2<std::int32_t>, PonyMath::Utility::Resolution<std::uint32_t>> WindowRect() const = 0;
		/// @brief Gets window client rect.
		/// @return Left-upper point as position and resolution of the window client rect.
		[[nodiscard("Pure function")]]
		virtual std::pair<PonyMath::Core::Vector2<std::int32_t>, PonyMath::Utility::Resolution<std::uint32_t>> WindowClientRect() const = 0;
	};
}
