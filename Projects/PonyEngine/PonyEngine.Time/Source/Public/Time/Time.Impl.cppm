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

export module PonyEngine.Time.Impl;

export import PonyEngine.Time.Factory;

import <utility>;

import PonyEngine.Core;

import :FrameRateSystemFactory;

export namespace PonyEngine::Time
{
	/// @brief Creates a frame rate system factory.
	/// @param application Application context.
	/// @param factoryParams Frame rate system factory parameters.
	/// @param systemParams Frame rate system parameters.
	/// @return Frame rate system factory.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT FrameRateSystemFactoryData CreateFrameRateSystemFactory(Core::IApplicationContext& application, const FrameRateSystemFactoryParams& factoryParams, const FrameRateSystemParams& systemParams);
}

namespace PonyEngine::Time
{
	FrameRateSystemFactoryData CreateFrameRateSystemFactory(Core::IApplicationContext& application, const FrameRateSystemFactoryParams& factoryParams, const FrameRateSystemParams& systemParams)
	{
		auto factory = PonyBase::Memory::UniquePointer<FrameRateSystemFactory>::Create(application, factoryParams, systemParams);

		return FrameRateSystemFactoryData{.systemFactory = PonyBase::Memory::UniquePointer<IFrameRateSystemFactory>(std::move(factory))};
	}
}
