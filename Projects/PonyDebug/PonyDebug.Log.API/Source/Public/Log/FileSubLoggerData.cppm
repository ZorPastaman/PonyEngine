/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyDebug.Log:FileSubLoggerData;

import <memory>;

import :SubLogger;

export namespace PonyDebug::Log
{
	/// @brief File sub-logger data.
	struct FileSubLoggerData final
	{
		std::unique_ptr<SubLogger> subLogger; ///< Sub-logger.
	};
}
