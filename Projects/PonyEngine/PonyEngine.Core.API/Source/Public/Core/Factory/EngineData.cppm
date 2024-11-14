/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core.Factory:EngineData;

import <memory>;

import PonyEngine.Core;

export namespace PonyEngine::Core
{
	/// @brief Engine data.
	struct EngineData final
	{
		std::unique_ptr<Engine> engine; ///< Engine.
	};
}
