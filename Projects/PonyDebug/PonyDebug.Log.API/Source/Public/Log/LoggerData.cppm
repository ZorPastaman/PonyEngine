/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyDebug.Log:LoggerData;

import PonyBase.Memory;

import :ILogger;

export namespace PonyDebug::Log
{
	/// @brief Logger data.
	struct LoggerData final
	{
		PonyBase::Memory::UniquePointer<ILogger> logger; ///< Logger unique_ptr.
	};
}
