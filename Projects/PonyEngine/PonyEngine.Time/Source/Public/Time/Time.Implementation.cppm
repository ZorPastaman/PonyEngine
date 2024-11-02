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

import <utility>;

import PonyEngine.Core;

import :FrameRateSystemFactory;

export namespace PonyEngine::Time
{
	/// @brief Creates a frame rate system factory.
	/// @param application Application context.
	/// @param params Frame rate system factory parameters.
	/// @return Frame rate system factory.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT FrameRateSystemFactoryData CreateFrameRateSystemFactory(Core::IApplicationContext& application, const FrameRateSystemFactoryParams& params);
}

namespace PonyEngine::Time
{
	FrameRateSystemFactoryData CreateFrameRateSystemFactory(Core::IApplicationContext&, const FrameRateSystemFactoryParams&)
	{
		auto factory = PonyBase::Memory::UniquePointer<FrameRateSystemFactory>::Create();

		return FrameRateSystemFactoryData{.systemFactory = PonyBase::Memory::UniquePointer<IFrameRateSystemFactory>(std::move(factory))};
	}
}
