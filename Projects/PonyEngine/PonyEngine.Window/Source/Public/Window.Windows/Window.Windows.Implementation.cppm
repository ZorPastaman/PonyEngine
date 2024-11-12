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

import <memory>;
import <utility>;

import PonyBase.Memory;

import PonyEngine.Core;

import :WindowsClass;
import :WindowsWindowSystemFactory;

export namespace PonyEngine::Window
{
	/// @brief Creates a Windows class.
	/// @param application Application context.
	/// @param params Windows class parameters.
	/// @return Windows class.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT std::shared_ptr<IWindowsClass> CreateWindowsClass(Core::IApplicationContext& application, const WindowsClassParams& params);

	/// @brief Creates a window system for Windows factory.
	/// @param application Application.
	/// @param params Window system for Windows factory parameters.
	/// @param systemParams Window system for Windows parameters.
	/// @return Created factory.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT WindowsWindowSystemFactoryData CreateWindowsWindowFactory(Core::IApplicationContext& application, const WindowsWindowSystemFactoryParams& params, const WindowsWindowSystemParams& systemParams);
}

namespace PonyEngine::Window
{
	std::shared_ptr<IWindowsClass> CreateWindowsClass(Core::IApplicationContext& application, const WindowsClassParams& params)
	{
		return std::make_shared<WindowsClass>(application, params);
	}

	WindowsWindowSystemFactoryData CreateWindowsWindowFactory(Core::IApplicationContext&, const WindowsWindowSystemFactoryParams&, const WindowsWindowSystemParams& systemParams)
	{
		auto factory = PonyBase::Memory::UniquePointer<WindowsWindowSystemFactory>::Create(systemParams);

		return WindowsWindowSystemFactoryData{.systemFactory = PonyBase::Memory::UniquePointer<IWindowsWindowSystemFactory>(std::move(factory))};
	}
}
