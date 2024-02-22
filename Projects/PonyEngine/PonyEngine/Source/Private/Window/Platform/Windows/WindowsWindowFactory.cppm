/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window.Implementation:WindowFactory;

import <string>;

import <windows.h>;

import PonyEngine.Core;
import PonyEngine.Window;

import :IEngineWindow;
import :WindowsWindow;

namespace PonyEngine::Window
{
	IEngineWindow* CreateEngineWindow(const std::string& title, Core::IEngine& engine)
	{
		const HINSTANCE hInstance = GetModuleHandle(NULL);

		return new WindowsWindow(title, engine, hInstance, SW_NORMAL);
	}
}
