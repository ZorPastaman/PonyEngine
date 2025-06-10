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

import :LogInput;
import :LogType;

export namespace PonyEngine::Log
{
	/// @brief Logger.
	class ILogger
	{
		INTERFACE_BODY(ILogger)

		/// @brief Logs the message.
		/// @param logType Log type.
		/// @param logInput Log input.
		virtual void Log(LogType logType, const LogInput& logInput) const noexcept = 0;
		/// @brief Logs the exception.
		/// @param exception Exception to log.
		/// @param logInput Log input.
		virtual void LogException(const std::exception& exception, const LogInput& logInput) const noexcept = 0;
	};
}
