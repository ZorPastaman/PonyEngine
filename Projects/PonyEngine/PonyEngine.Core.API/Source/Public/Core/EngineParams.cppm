/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core:EngineParams;

import <cstdint>;
import <span>;
import <utility>;

import :ISystemFactory;

export namespace PonyEngine::Core
{
	/// @brief Engine parameters.
	struct EngineParams final
	{
		std::span<const std::pair<ISystemFactory*, std::int32_t>> systemFactories; ///< Pairs of system factories and tick orders. System factories must be unique.
	};
}
