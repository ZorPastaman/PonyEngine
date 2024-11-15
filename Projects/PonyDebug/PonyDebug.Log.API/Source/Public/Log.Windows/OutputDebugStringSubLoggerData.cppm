/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyDebug.Log.Windows:OutputDebugStringSubLoggerData;

import <memory>;

import PonyDebug.Log;

export namespace PonyDebug::Log
{
	/// @brief Output debug string sub-logger data.
	struct OutputDebugStringSubLoggerData final
	{
		std::unique_ptr<SubLogger> subLogger; ///< Sub-logger.
	};
}
