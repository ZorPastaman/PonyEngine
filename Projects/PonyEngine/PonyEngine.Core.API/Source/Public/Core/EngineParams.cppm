/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core:EngineParams;

import <vector>;

import :SystemFactoryEntry;

export namespace PonyEngine::Core
{
	/// @brief Engine parameters.
	struct EngineParams final
	{
		std::vector<SystemFactoryEntry> systemFactories; ///< System factory entries. The factories must be unique.
	};
}
