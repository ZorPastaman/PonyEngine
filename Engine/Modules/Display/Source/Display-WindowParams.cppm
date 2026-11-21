/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Display:WindowParams;

import std;

import :WindowMode;

export namespace PonyEngine::Display
{
	struct WindowParams final
	{
		WindowMode mode;
		std::optional<std::string_view> title;
		bool hidden = false;
		bool quitOnDestroy = false;
	};
}
