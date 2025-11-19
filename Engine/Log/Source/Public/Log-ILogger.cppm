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
	class ILogger
	{
		INTERFACE_BODY(ILogger)

		virtual void Log(LogType logType, std::string_view message) const noexcept = 0;
		virtual void Log(LogType logType, std::string_view format, std::format_args formatArgs) const noexcept = 0;
		virtual void Log(LogType logType, std::string_view message, const std::stacktrace& stacktrace) const noexcept = 0;
		virtual void Log(LogType logType, std::string_view format, std::format_args formatArgs, const std::stacktrace& stacktrace) const noexcept = 0;

		virtual void Log(const std::exception_ptr& exception) const noexcept = 0;
		virtual void Log(const std::exception_ptr& exception, std::string_view message) const noexcept = 0;
		virtual void Log(const std::exception_ptr& exception, std::string_view format, std::format_args formatArgs) const noexcept = 0;
		virtual void Log(const std::exception_ptr& exception, const std::stacktrace& stacktrace) const noexcept = 0;
		virtual void Log(const std::exception_ptr& exception, std::string_view message, const std::stacktrace& stacktrace) const noexcept = 0;
		virtual void Log(const std::exception_ptr& exception, std::string_view format, std::format_args formatArgs, const std::stacktrace& stacktrace) const noexcept = 0;
	};
}
