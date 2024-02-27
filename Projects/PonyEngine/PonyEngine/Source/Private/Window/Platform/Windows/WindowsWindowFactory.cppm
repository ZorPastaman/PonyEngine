/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window.Implementation:WindowFactory;

import <stdexcept>;
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
		HMODULE hModule;
		GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, reinterpret_cast<LPCWSTR>(&CreateEngineWindow), &hModule);
		if (hModule == nullptr)
		{
			throw std::logic_error("Couldn't find a dll module to create a window.");
		}

		return new WindowsWindow(title, engine, hModule, SW_NORMAL);
	}
}
