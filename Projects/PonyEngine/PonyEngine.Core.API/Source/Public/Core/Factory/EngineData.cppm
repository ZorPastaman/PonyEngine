/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core.Factory:EngineData;

import :EngineUniquePtr;

export namespace PonyEngine::Core
{
	/// @brief Engine data.
	struct EngineData final
	{
		EngineUniquePtr engine; ///< Engine.

		ITickableEngine* tickableEngine = nullptr; ///< Engine tickable interface.
	};
}
