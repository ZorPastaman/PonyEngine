/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Object/Body.h"

export module PonyEngine.Log:ILogger;

import std;

import :LogType;

export namespace PonyEngine::Log
{
	/// @brief Logger.
	/// @note All the functions here are thread-safe.
	class ILogger
	{
		PONY_INTERFACE_BODY(ILogger)

		/// @brief Logs a message.
		/// @param logType Log type.
		/// @param message Log message.
		virtual void Log(LogType logType, std::string_view message) const noexcept = 0;
		/// @brief Logs a formatted message.
		/// @param logType Log type.
		/// @param format Log message format.
		/// @param formatArgs Log message format arguments.
		virtual void Log(LogType logType, std::string_view format, std::format_args formatArgs) const noexcept = 0;
		/// @brief Logs a message with the stacktrace.
		/// @param logType Log type.
		/// @param message Log message.
		/// @param stacktrace Stacktrace.
		virtual void Log(LogType logType, std::string_view message, const std::stacktrace& stacktrace) const noexcept = 0;
		/// @brief Logs a formatted message with the stacktrace.
		/// @param logType Log type.
		/// @param format Log message format.
		/// @param formatArgs Log message format arguments.
		/// @param stacktrace Stacktrace.
		virtual void Log(LogType logType, std::string_view format, std::format_args formatArgs, const std::stacktrace& stacktrace) const noexcept = 0;

		/// @brief Logs the exception.
		/// @param exception Exception.
		virtual void Log(const std::exception_ptr& exception) const noexcept = 0;
		/// @brief Logs the exception with a message.
		/// @param exception Exception.
		/// @param message Log message.
		virtual void Log(const std::exception_ptr& exception, std::string_view message) const noexcept = 0;
		/// @brief Logs the exception with a formatted message.
		/// @param exception Exception.
		/// @param format Log message format.
		/// @param formatArgs Log message format arguments.
		virtual void Log(const std::exception_ptr& exception, std::string_view format, std::format_args formatArgs) const noexcept = 0;
		/// @brief Logs the exception with a stacktrace.
		/// @param exception Exception.
		/// @param stacktrace Stacktrace.
		virtual void Log(const std::exception_ptr& exception, const std::stacktrace& stacktrace) const noexcept = 0;
		/// @brief Logs the exception with a message and a stacktrace.
		/// @param exception Exception.
		/// @param message Log message.
		/// @param stacktrace Stacktrace.
		virtual void Log(const std::exception_ptr& exception, std::string_view message, const std::stacktrace& stacktrace) const noexcept = 0;
		/// @brief Logs the exception with a formatted message and a stacktrace.
		/// @param exception Exception.
		/// @param format Log message format.
		/// @param formatArgs Log message format arguments.
		/// @param stacktrace Stacktrace.
		virtual void Log(const std::exception_ptr& exception, std::string_view format, std::format_args formatArgs, const std::stacktrace& stacktrace) const noexcept = 0;
	};
}
