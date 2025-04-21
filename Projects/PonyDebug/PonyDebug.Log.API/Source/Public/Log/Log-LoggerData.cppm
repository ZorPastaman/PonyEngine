/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyDebug.Log:LoggerData;

import <memory>;

import :Logger;

export namespace PonyDebug::Log
{
	/// @brief Logger data.
	struct LoggerData final
	{
		std::shared_ptr<Logger> logger; ///< Logger.
	};
}
