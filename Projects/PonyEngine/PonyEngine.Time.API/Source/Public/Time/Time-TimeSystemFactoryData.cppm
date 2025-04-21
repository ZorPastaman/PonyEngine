/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Time:TimeSystemFactoryData;

import <memory>;

import :TimeSystemFactory;

export namespace PonyEngine::Time
{
	/// @brief Time system factory data.
	struct TimeSystemFactoryData final
	{
		std::shared_ptr<TimeSystemFactory> systemFactory; ///< System factory.
	};
}
