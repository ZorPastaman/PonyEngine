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
		[[nodiscard("Pure function")]]
		virtual Application::IApplicationContext& Application() noexcept = 0;
		/// @brief Gets the application context.
		/// @return Application context.
		[[nodiscard("Pure function")]]
		virtual const Application::IApplicationContext& Application() const noexcept = 0;

		virtual void LogToConsole(LogType logType, std::string_view message) const noexcept = 0;
		virtual void LogToConsole(LogType logType, std::string_view format, std::format_args formatArgs) const noexcept = 0;
		virtual void LogToConsole(LogType logType, std::string_view message, const std::stacktrace& stacktrace) const noexcept = 0;
		virtual void LogToConsole(LogType logType, std::string_view format, std::format_args formatArgs, const std::stacktrace& stacktrace) const noexcept = 0;

		virtual void LogToConsole(const std::exception_ptr& exception) const noexcept = 0;
		virtual void LogToConsole(const std::exception_ptr& exception, std::string_view message) const noexcept = 0;
		virtual void LogToConsole(const std::exception_ptr& exception, std::string_view format, std::format_args formatArgs) const noexcept = 0;
		virtual void LogToConsole(const std::exception_ptr& exception, const std::stacktrace& stacktrace) const noexcept = 0;
		virtual void LogToConsole(const std::exception_ptr& exception, std::string_view message, const std::stacktrace& stacktrace) const noexcept = 0;
		virtual void LogToConsole(const std::exception_ptr& exception, std::string_view format, std::format_args formatArgs, const std::stacktrace& stacktrace) const noexcept = 0;
	};
}
