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

export import PonyEngine.Screen.Windows;

import <memory>;

import PonyEngine.Core;
import PonyEngine.Screen.Windows.Detail;

export namespace PonyEngine::Screen::Windows
{
	/// @brief Creates a screen system for Windows factory.
	/// @param application Application context.
	/// @param factoryParams Screen system for Windows factory parameters.
	/// @param systemParams Screen system for Windows parameters.
	/// @return Created factory.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT ScreenSystemFactoryData CreateScreenFactory(Core::IApplicationContext& application, const ScreenSystemFactoryParams& factoryParams, const ScreenSystemParams& systemParams);
}

namespace PonyEngine::Screen::Windows
{
	ScreenSystemFactoryData CreateScreenFactory(Core::IApplicationContext& application, const ScreenSystemFactoryParams& factoryParams, const ScreenSystemParams& systemParams)
	{
		return ScreenSystemFactoryData{.systemFactory = std::make_shared<ScreenSystemFactoryImpl>(application, factoryParams, systemParams)};
	}
}
