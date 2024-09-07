/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyDebug.Log.Factory:LoggerData;

import :LoggerUniquePtr;

export namespace PonyDebug::Log
{
	/// @brief Logger data.
	struct LoggerData final
	{
		LoggerUniquePtr logger; ///< Logger unique_ptr.
	};
}