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

export module PonyEngine.Screen.Windows.Impl;

export import PonyEngine.Screen.Windows.Factory;

import <utility>;

import PonyBase.Memory;

import PonyEngine.Core.Factory;

import :WindowsScreenSystemFactory;

export namespace PonyEngine::Screen
{
	/// @brief Creates a screen system for Windows factory.
	/// @param application Application context.
	/// @param factoryParams Screen system for Windows factory parameters.
	/// @param systemParams Screen system for Windows parameters.
	/// @return Created factory.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT WindowsScreenSystemFactoryData CreateWindowsScreenFactory(Core::IApplicationContext& application, const WindowsScreenSystemFactoryParams& factoryParams, const WindowsScreenSystemParams& systemParams);
}

namespace PonyEngine::Screen
{
	WindowsScreenSystemFactoryData CreateWindowsScreenFactory(Core::IApplicationContext& application, const WindowsScreenSystemFactoryParams& factoryParams, const WindowsScreenSystemParams& systemParams)
	{
		auto factory = PonyBase::Memory::UniquePointer<WindowsScreenSystemFactory>::Create(application, factoryParams, systemParams);

		return WindowsScreenSystemFactoryData{.systemFactory = PonyBase::Memory::UniquePointer<IWindowsScreenSystemFactory>(std::move(factory))};
	}
}
