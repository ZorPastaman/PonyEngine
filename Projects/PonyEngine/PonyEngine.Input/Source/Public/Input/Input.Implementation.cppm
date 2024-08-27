/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Compiler/Linking.h"

export module PonyEngine.Input.Implementation;

export import PonyEngine.Input.Factory;

import :InputSystemFactory;
import :InputSystemFactoryDestroyer;

export namespace PonyEngine::Input
{
	/// @brief Creates an input system factory.
	/// @param params Input system factory parameters.
	/// @return Input system factory.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT InputSystemFactoryData CreateInputSystemFactory(const InputSystemFactoryParams& params);
}

namespace PonyEngine::Input
{
	auto DefaultInputSystemFactoryDestroyer = InputSystemFactoryDestroyer(); ///< Default input system factory destroyer.

	InputSystemFactoryData CreateInputSystemFactory(const InputSystemFactoryParams&)
	{
		const auto factory = new InputSystemFactory();
		const auto factoryDeleter = Core::SystemFactoryDeleter(DefaultInputSystemFactoryDestroyer);

		return InputSystemFactoryData
		{
			.systemFactory = Core::SystemFactoryUniquePtr(factory, factoryDeleter)
		};
	}
}
