/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyDebug.Log.Factory:FileSubLoggerData;

import PonyBase.Memory;

import PonyDebug.Log;

export namespace PonyDebug::Log
{
	/// @brief File sub-logger data.
	struct FileSubLoggerData final
	{
		PonyBase::Memory::UniquePointer<ISubLogger> subLogger; ///< Sub-logger.
	};
}
