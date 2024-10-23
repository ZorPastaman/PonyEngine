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

export module PonyEngine.Time.Implementation;

export import PonyEngine.Time.Factory;

import PonyEngine.Core;

import :FrameRateSystemFactory;
import :FrameRateSystemFactoryDestroyer;

export namespace PonyEngine::Time
{
	/// @brief Creates a frame rate system factory.
	/// @param application Application
	/// @param params Frame rate system factory parameters.
	/// @return Frame rate system factory.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT FrameRateSystemFactoryData CreateFrameRateSystemFactory(Core::IApplication& application, const FrameRateSystemFactoryParams& params);
}

namespace PonyEngine::Time
{
	auto DefaultFrameRateSystemFactoryDestroyer = FrameRateSystemFactoryDestroyer();

	FrameRateSystemFactoryData CreateFrameRateSystemFactory(Core::IApplication&, const FrameRateSystemFactoryParams&)
	{
		IFrameRateSystemFactory* const factory = new FrameRateSystemFactory();

		return FrameRateSystemFactoryData{.systemFactory = Core::SystemFactoryUniquePtr(*factory, DefaultFrameRateSystemFactoryDestroyer)};
	}
}
