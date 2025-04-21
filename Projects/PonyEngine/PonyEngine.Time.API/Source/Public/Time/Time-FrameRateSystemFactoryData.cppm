/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Time:FrameRateSystemFactoryData;

import <memory>;

import :FrameRateSystemFactory;

export namespace PonyEngine::Time
{
	/// @brief Frame rate system factory data.
	struct FrameRateSystemFactoryData final
	{
		std::unique_ptr<FrameRateSystemFactory> systemFactory; ///< System factory.
	};
}
