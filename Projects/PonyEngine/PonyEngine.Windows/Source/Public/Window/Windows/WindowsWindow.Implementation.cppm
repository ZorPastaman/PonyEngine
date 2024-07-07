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

#include "PonyEngine/Compiler/Linking.h"

export module PonyEngine.Window.Windows.Implementation;

import <functional>;
import <memory>;

import PonyEngine.Log;
import PonyEngine.Window.Windows.Factories;

import :WindowsWindowFactory;

export namespace PonyEngine::Window
{
	using WindowsWindowUniquePtr = std::unique_ptr<IWindowsWindowFactory, std::function<void(IWindowsWindowFactory*)>>; ///< Windows window factory unique_ptr typedef.

	/// @brief Creates a Windows window factory.
	/// @param logger Logger.
	/// @param classParams Class parameters.
	/// @return Created factory.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT WindowsWindowUniquePtr CreateWindowsWindowFactory(Log::ILogger& logger, const WindowsClassParams& classParams);

}

namespace PonyEngine::Window
{
	/// @brief Destroys a previously created Windows window factory.
	/// @param factory Previously created Windows window factory.
	void DestroyWindowsWindowFactory(IWindowsWindowFactory* factory) noexcept;

	WindowsWindowUniquePtr CreateWindowsWindowFactory(Log::ILogger& logger, const WindowsClassParams& classParams)
	{
		return std::unique_ptr<IWindowsWindowFactory, std::function<void(IWindowsWindowFactory*)>>(new WindowsWindowFactory(logger, classParams), DestroyWindowsWindowFactory);
	}

	void DestroyWindowsWindowFactory(IWindowsWindowFactory* const factory) noexcept
	{
		assert((dynamic_cast<WindowsWindowFactory*>(factory) && "Tried to destroy a factory of the wrong type."));
		delete static_cast<WindowsWindowFactory*>(factory);
	}
}
