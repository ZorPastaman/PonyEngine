/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#pragma once

#include "PonyEngine/Log/Log.h"

 /// @brief Logs to console.
 /// @param type Log type.
 /// @param message Message.
#define PONY_APP_CONSOLE(type, message, ...) \
	if constexpr (PonyEngine::Log::IsInMask(type, PONY_LOG_MASK)) \
	{ \
		if constexpr (PonyEngine::Log::IsInMask(type, PONY_LOG_STACKTRACE_MASK)) \
		{ \
			const auto stacktrace = std::stacktrace::current(); \
			PonyEngine::Application::LogToConsole(type, PonyEngine::Log::LogFormat(type, PonyEngine::Log::LogString(message __VA_OPT__(,) __VA_ARGS__), stacktrace)); \
		} \
		else \
		{ \
			PonyEngine::Application::LogToConsole(type, PonyEngine::Log::LogFormat(type, PonyEngine::Log::LogString(message __VA_OPT__(,) __VA_ARGS__))); \
		} \
	} \

 /// @brief Logs to console.
 /// @param exception Exception.
 /// @param message Message.
#define PONY_APP_CONSOLE_E(exception, message, ...) \
	if constexpr (PonyEngine::Log::IsInMask(PonyEngine::Log::LogType::Exception, PONY_LOG_MASK)) \
	{ \
		if constexpr (PonyEngine::Log::IsInMask(PonyEngine::Log::LogType::Exception, PONY_LOG_STACKTRACE_MASK)) \
		{ \
			const auto stacktrace = std::stacktrace::current(); \
			PonyEngine::Application::LogToConsole(PonyEngine::Log::LogType::Exception, PonyEngine::Log::LogFormat(PonyEngine::Log::LogType::Exception, exception.what(), PonyEngine::Log::LogString(message __VA_OPT__(,) __VA_ARGS__), stacktrace)); \
		} \
		else \
		{ \
			PonyEngine::Application::LogToConsole(PonyEngine::Log::LogType::Exception, PonyEngine::Log::LogFormat(PonyEngine::Log::LogType::Exception, exception.what(), PonyEngine::Log::LogString(message __VA_OPT__(,) __VA_ARGS__))); \
		} \
	} \
