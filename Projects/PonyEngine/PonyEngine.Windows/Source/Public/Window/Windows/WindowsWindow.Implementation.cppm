/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

#include "Core/Linking.h"

export module PonyEngine.Window.Windows.Implementation;

import PonyEngine.Debug.Log;
import PonyEngine.Window.Windows.Factories;

import :WindowsWindowFactory;

export namespace PonyEngine::Window
{
	/// @brief Creates a Windows window factory.
	/// @param logger Logger.
	/// @param classParams Class parameters.
	/// @return Created factory.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT IWindowsWindowFactory* CreateWindowsWindowFactory(Debug::Log::ILogger& logger, const WindowClassParams& classParams);
	/// @brief Destroys a previously created Windows window factory.
	/// @param factory Previously created Windows window factory.
	PONY_DLL_EXPORT void DestroyWindowsWindowFactory(IWindowsWindowFactory* factory) noexcept;
}

namespace PonyEngine::Window
{
	IWindowsWindowFactory* CreateWindowsWindowFactory(Debug::Log::ILogger& logger, const WindowClassParams& classParams)
	{
		return new WindowsWindowFactory(logger, classParams);
	}

	void DestroyWindowsWindowFactory(IWindowsWindowFactory* const factory) noexcept
	{
		assert((dynamic_cast<WindowsWindowFactory*>(factory) != nullptr));
		delete static_cast<WindowsWindowFactory*>(factory);
	}
}
