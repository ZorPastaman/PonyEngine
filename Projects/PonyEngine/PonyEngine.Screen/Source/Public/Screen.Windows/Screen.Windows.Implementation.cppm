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

export module PonyEngine.Screen.Windows.Implementation;

export import PonyEngine.Screen.Windows.Factory;

import <utility>;

import PonyBase.Memory;

import PonyEngine.Core.Factory;

import :WindowsScreenSystemFactory;

export namespace PonyEngine::Screen
{
	/// @brief Creates a screen system for Windows factory.
	/// @param application Application context.
	/// @param params Screen system for Windows factory parameters.
	/// @return Created factory.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT WindowsScreenSystemFactoryData CreateWindowsScreenFactory(Core::IApplicationContext& application, const WindowsScreenSystemFactoryParams& params);
}

namespace PonyEngine::Screen
{
	WindowsScreenSystemFactoryData CreateWindowsScreenFactory(Core::IApplicationContext&, const WindowsScreenSystemFactoryParams&)
	{
		auto factory = PonyBase::Memory::UniquePointer<WindowsScreenSystemFactory>::Create();

		return WindowsScreenSystemFactoryData{.systemFactory = PonyBase::Memory::UniquePointer<IWindowsScreenSystemFactory>(std::move(factory))};
	}
}
