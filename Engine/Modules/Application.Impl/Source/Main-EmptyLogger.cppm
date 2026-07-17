/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Application.Impl:EmptyLogger;

import std;

import PonyEngine.Log;

export namespace PonyEngine::Application
{
	class EmptyLogger final : public Log::ILogger
	{
	public:
		virtual void Log(Log::LogType logType, std::string_view message) const noexcept override {}
		virtual void Log(Log::LogType logType, std::string_view format, std::format_args formatArgs) const noexcept override {}
		virtual void Log(Log::LogType logType, std::string_view message, const std::stacktrace& stacktrace) const noexcept override {}
		virtual void Log(Log::LogType logType, std::string_view format, std::format_args formatArgs, const std::stacktrace& stacktrace) const noexcept override {}

		virtual void Log(Log::LogType logType, const std::exception_ptr& exception) const noexcept override {}
		virtual void Log(Log::LogType logType, const std::exception_ptr& exception, std::string_view message) const noexcept override {}
		virtual void Log(Log::LogType logType, const std::exception_ptr& exception, std::string_view format, std::format_args formatArgs) const noexcept override {}
		virtual void Log(Log::LogType logType, const std::exception_ptr& exception, const std::stacktrace& stacktrace) const noexcept override {}
		virtual void Log(Log::LogType logType, const std::exception_ptr& exception, std::string_view message, const std::stacktrace& stacktrace) const noexcept override {}
		virtual void Log(Log::LogType logType, const std::exception_ptr& exception, std::string_view format, std::format_args formatArgs, const std::stacktrace& stacktrace) const noexcept override {}
	};
}
