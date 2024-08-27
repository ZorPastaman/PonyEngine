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

export module PonyEngine.Time.Implementation;

export import PonyEngine.Time.Factory;

import :FrameRateSystemFactory;
import :FrameRateSystemFactoryDestroyer;

export namespace PonyEngine::Time
{
	/// @brief Creates a frame rate system factory.
	/// @param params Frame rate system factory parameters.
	/// @return Frame rate system factory.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT FrameRateSystemFactoryData CreateFrameRateSystemFactory(const FrameRateSystemFactoryParams& params);
}

namespace PonyEngine::Time
{
	auto DefaultFrameRateSystemFactoryDestroyer = FrameRateSystemFactoryDestroyer();

	FrameRateSystemFactoryData CreateFrameRateSystemFactory(const FrameRateSystemFactoryParams&)
	{
		const auto factory = new FrameRateSystemFactory();
		const auto factoryDeleter = Core::SystemFactoryDeleter(DefaultFrameRateSystemFactoryDestroyer);

		return FrameRateSystemFactoryData
		{
			.systemFactory = Core::SystemFactoryUniquePtr(factory, factoryDeleter)
		};
	}
}
