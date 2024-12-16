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

export import PonyEngine.Time;

import <memory>;

import PonyEngine.Core;
import PonyEngine.Time.Detail;

export namespace PonyEngine::Time
{
	/// @brief Creates a frame rate system factory.
	/// @param application Application context.
	/// @param factoryParams Frame rate system factory parameters.
	/// @param systemParams Frame rate system parameters.
	/// @return Frame rate system factory.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT FrameRateSystemFactoryData CreateFrameRateSystemFactory(Core::IApplicationContext& application, const FrameRateSystemFactoryParams& factoryParams, const FrameRateSystemParams& systemParams);
	/// @brief Creates a time system factory.
	/// @param application Application context.
	/// @param factoryParams Time system factory parameters.
	/// @param systemParams Time system parameters.
	/// @return Time system factory.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT TimeSystemFactoryData CreateTimeSystemFactory(Core::IApplicationContext& application, const TimeSystemFactoryParams& factoryParams, const TimeSystemParams& systemParams);

}

namespace PonyEngine::Time
{
	FrameRateSystemFactoryData CreateFrameRateSystemFactory(Core::IApplicationContext& application, const FrameRateSystemFactoryParams& factoryParams, const FrameRateSystemParams& systemParams)
	{
		return FrameRateSystemFactoryData{.systemFactory = std::make_unique<FrameRateSystemFactoryImpl>(application, factoryParams, systemParams)};
	}

	TimeSystemFactoryData CreateTimeSystemFactory(Core::IApplicationContext& application, const TimeSystemFactoryParams& factoryParams, const TimeSystemParams& systemParams)
	{
		return TimeSystemFactoryData{.systemFactory = std::make_unique<TimeSystemFactoryImpl>(application, factoryParams, systemParams)};
	}
}
