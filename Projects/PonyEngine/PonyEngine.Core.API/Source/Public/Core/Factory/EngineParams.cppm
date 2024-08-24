/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core.Factory:EngineParams;

import PonyEngine.Log;

import :SystemFactoriesContainer;

export namespace PonyEngine::Core
{
	/// @brief Engine parameters.
	struct EngineParams final
	{
		Log::ILogger* logger = nullptr; ///< Logger. Mustn't be nullptr.
		SystemFactoriesContainer systemFactories; ///< System factories.
	};
}
