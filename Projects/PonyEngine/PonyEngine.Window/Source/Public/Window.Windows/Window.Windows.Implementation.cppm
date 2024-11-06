/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/Linking.h"

export module PonyEngine.Window.Windows.Implementation;

export import PonyEngine.Window.Windows.Factory;

import <utility>;

import PonyBase.Memory;

import PonyEngine.Core;

import :WindowsWindowSystemFactory;

export namespace PonyEngine::Window
{
	/// @brief Creates a window system for Windows factory.
	/// @param application Application.
	/// @param params Window system for Windows factory parameters.
	/// @return Created factory.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT WindowsWindowSystemFactoryData CreateWindowsWindowFactory(Core::IApplicationContext& application, const WindowsWindowSystemFactoryParams& params);
}

namespace PonyEngine::Window
{
	WindowsWindowSystemFactoryData CreateWindowsWindowFactory(Core::IApplicationContext& application, const WindowsWindowSystemFactoryParams& params)
	{
		auto factory = PonyBase::Memory::UniquePointer<WindowsWindowSystemFactory>::Create(application, params.windowsClassParams);

		return WindowsWindowSystemFactoryData{.systemFactory = PonyBase::Memory::UniquePointer<IWindowsWindowSystemFactory>(std::move(factory))};
	}
}
