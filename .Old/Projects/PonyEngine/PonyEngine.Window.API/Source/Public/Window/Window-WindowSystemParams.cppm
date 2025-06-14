/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window:WindowSystemParams;

import <string>;

import :CursorParams;
import :WindowRect;

export namespace PonyEngine::Window
{
	/// @brief Window system parameters.
	struct WindowSystemParams
	{
		WindowRect rect; ///< Window rect.
		CursorParams cursorParams; ///< Cursor parameters.
		std::string title = "Pony Engine Window"; ///< Window title.
	};
}
