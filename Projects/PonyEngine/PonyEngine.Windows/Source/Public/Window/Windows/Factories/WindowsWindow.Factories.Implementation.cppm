/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window.Windows.Factories.Implementation;

// TODO: move cassert to global
import <cassert>;

import PonyEngine.Window.Windows.Factories;

import :WindowsWindowFactory;

namespace PonyEngine::Window
{
	/// @brief Creates a Windows window factory.
	/// @param classParams Class parameters.
	/// @return Created factory.
	export [[nodiscard("Pure function")]]
	__declspec(dllexport) IWindowsWindowFactory* CreateWindowsWindowFactory(const WindowClassParams& classParams);
	/// @brief Destroys a previously created Windows window factory.
	/// @param factory Previously created Windows window factory.
	export __declspec(dllexport) void DestroyWindowsWindowFactory(IWindowsWindowFactory* factory) noexcept;

	IWindowsWindowFactory* CreateWindowsWindowFactory(const WindowClassParams& classParams)
	{
		return new WindowsWindowFactory(classParams);
	}

	void DestroyWindowsWindowFactory(IWindowsWindowFactory* factory) noexcept
	{
		assert((dynamic_cast<WindowsWindowFactory*>(factory) != nullptr));
		delete static_cast<WindowsWindowFactory*>(factory);
	}
}
