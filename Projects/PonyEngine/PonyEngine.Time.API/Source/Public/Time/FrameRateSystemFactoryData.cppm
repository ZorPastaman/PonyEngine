/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Time:FrameRateSystemFactoryData;

import PonyBase.Memory;

import :IFrameRateSystemFactory;

export namespace PonyEngine::Time
{
	/// @brief Frame rate system factory data.
	struct FrameRateSystemFactoryData final
	{
		PonyBase::Memory::UniquePointer<IFrameRateSystemFactory> systemFactory; ///< Frame rate system factory.
	};
}
