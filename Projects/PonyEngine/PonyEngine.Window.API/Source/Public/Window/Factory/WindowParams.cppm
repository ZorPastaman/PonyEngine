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
		std::wstring title = L"Pony Engine Window"; ///< Window title.
		int horizontalPosition = 0; ///< Window horizontal position.
		int verticalPosition = 0; ///< Window vertical position.
		int width = 800; ///< Window width.
		int height = 600; ///< Window height.
	};
}
