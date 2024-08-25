/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core.Factory:EngineParams;

import <functional>;

import PonyEngine.Log;

import :SystemFactoriesContainer;

export namespace PonyEngine::Core
{
	/// @brief Engine parameters.
	struct EngineParams final
	{
		std::reference_wrapper<Log::ILogger> logger; ///< Logger.
		SystemFactoriesContainer systemFactories; ///< System factories.
	};
}
