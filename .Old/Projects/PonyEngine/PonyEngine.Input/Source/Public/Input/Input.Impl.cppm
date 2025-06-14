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

export module PonyEngine.Input.Impl;

export import PonyEngine.Input;

import <memory>;

import PonyEngine.Core;
import PonyEngine.Input.Detail;

export namespace PonyEngine::Input
{
	/// @brief Creates an input system factory.
	/// @param application Application context.
	/// @param factoryParams Input system factory parameters.
	/// @param systemParams Input system parameters.
	/// @return Input system factory.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT InputSystemFactoryData CreateInputSystemFactory(Core::IApplicationContext& application, const InputSystemFactoryParams& factoryParams, const InputSystemParams& systemParams);
}

namespace PonyEngine::Input
{
	InputSystemFactoryData CreateInputSystemFactory(Core::IApplicationContext& application, const InputSystemFactoryParams& factoryParams, const InputSystemParams& systemParams)
	{
		return InputSystemFactoryData{.systemFactory = std::make_shared<InputSystemFactoryImpl>(application, factoryParams, systemParams)};
	}
}
