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

import PonyEngine.Core;

import :InputSystemFactory;
import :InputSystemFactoryDestroyer;

export namespace PonyEngine::Input
{
	/// @brief Creates an input system factory.
	/// @param application Application.
	/// @param params Input system factory parameters.
	/// @return Input system factory.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT InputSystemFactoryData CreateInputSystemFactory(Core::IApplication& application, const InputSystemFactoryParams& params);
}

namespace PonyEngine::Input
{
	auto DefaultInputSystemFactoryDestroyer = InputSystemFactoryDestroyer(); ///< Default input system factory destroyer.

	InputSystemFactoryData CreateInputSystemFactory(Core::IApplication&, const InputSystemFactoryParams&)
	{
		IInputSystemFactory* const factory = new InputSystemFactory();

		return InputSystemFactoryData{.systemFactory = Core::SystemFactoryUniquePtr(*factory, DefaultInputSystemFactoryDestroyer)};
	}
}
