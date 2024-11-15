/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core:EngineParams;

import :SystemFactoriesContainer;

export namespace PonyEngine::Core
{
	/// @brief Engine parameters.
	struct EngineParams final
	{
		// TODO: Use just span here instead. Inside SystemManager add a validation code.
		SystemFactoriesContainer systemFactories; ///< System factories.
	};
}
