/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window.Factory:WindowSystemParams;

import <string>;

import PonyEngine.Core.Factory;

import :WindowRect;

export namespace PonyEngine::Window
{
	/// @brief Window system parameters.
	struct WindowSystemParams : Core::SystemParams
	{
		WindowRect rect; ///< Window rect.
		std::wstring title = L"Pony Engine Window"; ///< Window title.
	};
}
