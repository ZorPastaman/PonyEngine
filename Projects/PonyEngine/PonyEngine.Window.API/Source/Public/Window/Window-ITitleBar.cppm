/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/ObjectBody.h"

export module PonyEngine.Window:ITitleBar;

import <string_view>;

export namespace PonyEngine::Window
{
	/// @brief Window title bar.
	class ITitleBar
	{
		INTERFACE_BODY(ITitleBar)

		/// @brief Gets the window title.
		/// @return Window title.
		[[nodiscard("Pure function")]]
		virtual std::string_view MainTitle() const noexcept = 0;
		/// @brief Sets the window title.
		/// @param title Window title to set.
		virtual void MainTitle(std::string_view title) = 0;

		/// @brief Gets the window title text.
		/// @return Window title text.
		[[nodiscard("Pure function")]]
		virtual std::string_view SecondaryTitle() const noexcept = 0;
		/// @brief Sets the window title text.
		/// @param title Window title text to set.
		virtual void SecondaryTitle(std::string_view title) = 0;
	};
}
