/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window.Windows.Factories.Implementation;

import <string>;

import PonyEngine.Window.Windows.Factories;

import :WindowsWindowFactory;

namespace PonyEngine::Window
{
	export __declspec(dllexport) IWindowsWindowFactory* CreateWindowsWindowFactory(std::string title);
	export __declspec(dllexport) void DestroyWindowsWindowFactory(IWindowsWindowFactory* factory);

	IWindowsWindowFactory* CreateWindowsWindowFactory(std::string title)
	{
		return new WindowsWindowFactory(title);
	}

	void DestroyWindowsWindowFactory(IWindowsWindowFactory* factory)
	{
		delete static_cast<WindowsWindowFactory*>(factory);
	}
}
