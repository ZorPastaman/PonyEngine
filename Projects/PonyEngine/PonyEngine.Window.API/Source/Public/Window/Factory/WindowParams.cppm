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
	struct WindowParams
	{
		std::wstring title = L"Pony Engine Window"; ///< Window title.
	};
}
