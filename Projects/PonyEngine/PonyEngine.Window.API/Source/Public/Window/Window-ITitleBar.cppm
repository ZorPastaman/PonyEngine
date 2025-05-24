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

		/// @brief Gets the title.
		/// @return Title.
		[[nodiscard("Pure function")]]
		virtual std::string_view Title() const noexcept = 0;
		/// @brief Sets the title.
		/// @param title Title to set.
		virtual void Title(std::string_view title) = 0;
	};
}
