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

export module PonyEngine.Log.Ext:ILoggerContext;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.Log;

export namespace PonyEngine::Log
{
	/// @brief Logger context.
	class ILoggerContext
	{
		INTERFACE_BODY(ILoggerContext)

		/// @brief Gets the application context.
		/// @return Application context.
		/// @note Don't call the logger of the application context.
		[[nodiscard("Pure function")]]
		virtual Application::IApplicationContext& Application() noexcept = 0;
		/// @brief Gets the application context.
		/// @return Application context.
		/// @note Don't call the logger of the application context.
		[[nodiscard("Pure function")]]
		virtual const Application::IApplicationContext& Application() const noexcept = 0;

		/// @brief Logs a message to a console.
		/// @param logType Log type.
		/// @param message Log message.
		virtual void LogToConsole(LogType logType, std::string_view message) const noexcept = 0;
		/// @brief Logs a formatted message to a console.
		/// @param logType Log type.
		/// @param format Log message format.
		/// @param formatArgs Log message format arguments.
		virtual void LogToConsole(LogType logType, std::string_view format, std::format_args formatArgs) const noexcept = 0;
		/// @brief Logs a message to a console with a stacktrace.
		/// @param logType Log type.
		/// @param message Log message.
		/// @param stacktrace Stacktrace.
		virtual void LogToConsole(LogType logType, std::string_view message, const std::stacktrace& stacktrace) const noexcept = 0;
		/// @brief Logs a formatted message to a console with a stacktrace.
		/// @param logType Log type.
		/// @param format Log message format.
		/// @param formatArgs Log message format arguments.
		/// @param stacktrace Stacktrace.
		virtual void LogToConsole(LogType logType, std::string_view format, std::format_args formatArgs, const std::stacktrace& stacktrace) const noexcept = 0;

		/// @brief Logs the exception to a console.
		/// @param exception Exception.
		virtual void LogToConsole(const std::exception_ptr& exception) const noexcept = 0;
		/// @brief Logs the exception to a console with a message.
		/// @param exception Exception.
		/// @param message Log message.
		virtual void LogToConsole(const std::exception_ptr& exception, std::string_view message) const noexcept = 0;
		/// @brief Logs the exception to a console with a formatted message.
		/// @param exception Exception.
		/// @param format Log message format.
		/// @param formatArgs Log message format arguments.
		virtual void LogToConsole(const std::exception_ptr& exception, std::string_view format, std::format_args formatArgs) const noexcept = 0;
		/// @brief Logs the exception to a console with a stacktrace.
		/// @param exception Exception.
		/// @param stacktrace Stacktrace.
		virtual void LogToConsole(const std::exception_ptr& exception, const std::stacktrace& stacktrace) const noexcept = 0;
		/// @brief Logs the exception to a console with a message and a stacktrace.
		/// @param exception Exception.
		/// @param message Log message.
		/// @param stacktrace Stacktrace.
		virtual void LogToConsole(const std::exception_ptr& exception, std::string_view message, const std::stacktrace& stacktrace) const noexcept = 0;
		/// @brief Logs the exception to a console with a formatted message and a stacktrace.
		/// @param exception Exception.
		/// @param format Log message format.
		/// @param formatArgs Log message format arguments.
		/// @param stacktrace Stacktrace.
		virtual void LogToConsole(const std::exception_ptr& exception, std::string_view format, std::format_args formatArgs, const std::stacktrace& stacktrace) const noexcept = 0;
	};
}
