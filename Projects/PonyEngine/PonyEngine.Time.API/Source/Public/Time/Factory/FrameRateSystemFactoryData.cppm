/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Time.Factory:FrameRateSystemFactoryData;

import PonyEngine.Core.Factory;

import :IFrameRateSystemFactory;

export namespace PonyEngine::Time
{
	/// @brief Frame rate system factory data.
	struct FrameRateSystemFactoryData final
	{
		Core::SystemFactoryUniquePtr systemFactory; ///< Frame rate system factory.

		IFrameRateSystemFactory* frameRateSystemFactory = nullptr; ///< Frame rate system factory.
	};
}
