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

export module PonyEngine.Input.Implementation;

export import PonyEngine.Input.Factory;

import <utility>;

import PonyBase.Memory;

import PonyEngine.Core;

import :InputSystemFactory;

export namespace PonyEngine::Input
{
	/// @brief Creates an input system factory.
	/// @param application Application context.
	/// @param params Input system factory parameters.
	/// @return Input system factory.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT InputSystemFactoryData CreateInputSystemFactory(Core::IApplicationContext& application, const InputSystemFactoryParams& params);
}

namespace PonyEngine::Input
{
	InputSystemFactoryData CreateInputSystemFactory(Core::IApplicationContext&, const InputSystemFactoryParams&)
	{
		auto factory = PonyBase::Memory::UniquePointer<InputSystemFactory>::Create();

		return InputSystemFactoryData{.systemFactory = PonyBase::Memory::UniquePointer<IInputSystemFactory>(std::move(factory))};
	}
}
