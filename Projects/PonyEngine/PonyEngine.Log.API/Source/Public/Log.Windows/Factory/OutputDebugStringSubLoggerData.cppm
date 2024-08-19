/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Log.Windows.Factory:OutputDebugStringSubLoggerData;

import PonyEngine.Log.Factory;

export namespace PonyEngine::Log
{
	/// @brief Output debug string sub-logger data.
	struct OutputDebugStringSubLoggerData final
	{
		SubLoggerUniquePtr subLogger; ///< Sub-logger.
	};
}
