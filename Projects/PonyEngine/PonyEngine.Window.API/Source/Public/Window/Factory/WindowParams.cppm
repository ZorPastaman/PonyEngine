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

export namespace PonyEngine::Window
{
	/// @brief Platform-independent window parameters.
	struct WindowParams final
	{
		std::wstring title; ///< Window title.
		int horizontalPosition; ///< Window horizontal position.
		int verticalPosition; ///< Window vertical position.
		int width; ///< Window width.
		int height; ///< Window height.
	};
}
