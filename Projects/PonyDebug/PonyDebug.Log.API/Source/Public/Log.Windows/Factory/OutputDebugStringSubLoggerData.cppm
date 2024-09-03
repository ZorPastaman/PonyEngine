/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyDebug.Log.Windows.Factory:OutputDebugStringSubLoggerData;

import PonyDebug.Log.Factory;

export namespace PonyDebug::Log
{
	/// @brief Output debug string sub-logger data.
	struct OutputDebugStringSubLoggerData final
	{
		SubLoggerUniquePtr subLogger; ///< Sub-logger.
	};
}
