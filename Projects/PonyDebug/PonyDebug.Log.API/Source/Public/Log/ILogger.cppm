/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/ObjectBody.h"

export module PonyDebug.Log:ILogger;

import <exception>;

import :LogInput;
import :LogType;

export namespace PonyDebug::Log
{
	/// @brief Logger.
	/// @details The logger is an entry point for logs. It translates logs via its sub-loggers.
	class ILogger
	{
		INTERFACE_BODY(ILogger)

		/// @brief Logs via the current sub-loggers.
		/// @param logType Log type.
		/// @param logInput Log input.
		virtual void Log(LogType logType, const LogInput& logInput) const noexcept = 0;
		/// @brief Logs the exception via the current sub-loggers.
		/// @param exception Exception to log.
		/// @param logInput Log input.
		virtual void LogException(const std::exception& exception, const LogInput& logInput) const noexcept = 0;
	};
}
