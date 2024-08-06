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

import <memory>;

import PonyEngine.Log;
export import PonyEngine.Window.Windows.Factory;

import :WindowsWindowFactory;

export namespace PonyEngine::Window
{
	/// @brief Windows window factory deleter.
	struct PONY_DLL_EXPORT WindowsWindowFactoryDeleter final
	{
		/// @brief Deletes the @p factory.
		/// @param factory Windows window factory to delete.
		void operator ()(IWindowsWindowFactory* factory) const noexcept;
	};

	using WindowsWindowUniquePtr = std::unique_ptr<IWindowsWindowFactory, WindowsWindowFactoryDeleter>; ///< Windows window factory unique_ptr typedef.

	/// @brief Creates a Windows window factory.
	/// @param logger Logger.
	/// @param classParams Class parameters.
	/// @return Created factory.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT WindowsWindowUniquePtr CreateWindowsWindowFactory(Log::ILogger& logger, const WindowsClassParams& classParams);

}

namespace PonyEngine::Window
{
	void WindowsWindowFactoryDeleter::operator ()(IWindowsWindowFactory* const factory) const noexcept
	{
		assert((dynamic_cast<WindowsWindowFactory*>(factory) && "Tried to destroy a factory of the wrong type."));
		delete static_cast<WindowsWindowFactory*>(factory);
	}

	WindowsWindowUniquePtr CreateWindowsWindowFactory(Log::ILogger& logger, const WindowsClassParams& classParams)
	{
		return std::unique_ptr<IWindowsWindowFactory, WindowsWindowFactoryDeleter>(new WindowsWindowFactory(logger, classParams));
	}
}
