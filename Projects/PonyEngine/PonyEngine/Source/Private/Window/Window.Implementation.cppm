/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window.Implementation;

import <string>;

import PonyEngine.Core;

export import :IEngineWindow;
export import :WindowFactory;

namespace PonyEngine::Window
{
	/// @brief Creates an engine window.
	/// @param title Window title.
	/// @param engine Engine that owns the window.
	/// @return Created window.
	export [[nodiscard]]
	IEngineWindow* CreateEngineWindow(const std::string& title, Core::IEngine& engine);
}
