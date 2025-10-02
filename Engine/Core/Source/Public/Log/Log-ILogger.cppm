/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Utility/ObjectBody.h"

export module PonyEngine.Log:ILogger;

import std;

import :LogData;
import :LogType;

export namespace PonyEngine::Log
{
	/// @brief Logger.
	class ILogger
	{
		INTERFACE_BODY(ILogger)

		/// @brief Logs the message.
		/// @param logType Log type.
		/// @param message Log message.
		/// @param logData Log data.
		virtual void Log(LogType logType, std::string_view message, const LogData& logData = LogData()) const noexcept = 0;
		/// @brief Logs the exception.
		/// @param exception Exception to log.
		/// @param message Log message.
		/// @param logData Log data.
		virtual void Log(const std::exception& exception, std::string_view message, const LogData& logData = LogData()) const noexcept = 0;
	};
}
