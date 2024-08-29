/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window.Factory:WindowParams;

import <string>;

import PonyEngine.Math;

export namespace PonyEngine::Window
{
	/// @brief Platform-independent window parameters.
	struct WindowParams
	{
		std::wstring title = L"Pony Engine Window"; ///< Window title.
		Math::Vector2<int> position = Math::Vector2<int>(10, 10); ///< Window position (horizontal, vertical).
		Math::Vector2<int> size = Math::Vector2<int>(800, 600); ///< Window size (width, height).
	};
}
