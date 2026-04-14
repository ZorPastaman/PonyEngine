/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#pragma once

// To use this header, you have to import PonyEngine.Log.Ext as well.

#include "PonyEngine/Log/Log.h"

/// @brief Pushes the log to a console without a level a check.
/// @param logger PonyEngine::Log::ILoggerContext reference.
/// @param type PonyEngine::Log::LogType value.
/// @param message std::string_view as a message or format string.
/// @param ... Format arguments.
/// @note The function is thread-safe.
#define PONY_CONSOLE_PUSH(logger, type, message, ...) \
	if constexpr (PonyEngine::Log::IsInMask(type, PONY_LOG_STACKTRACE_MASK)) \
	{ \
		const std::stacktrace stacktrace = std::stacktrace::current(); \
		PonyEngine::Log::LogToConsole(logger, type, stacktrace, message __VA_OPT__(,) __VA_ARGS__); \
	} \
	else \
	{ \
		PonyEngine::Log::LogToConsole(logger, type, message __VA_OPT__(,) __VA_ARGS__); \
	} \

/// @brief Pushes the exception log to a console without a level a check.
/// @param logger PonyEngine::Log::ILoggerContext reference.
/// @param exception std::exception_ptr reference.
/// @param ... Message or format and format arguments.
/// @note The function is thread-safe.
#define PONY_CONSOLE_PUSH_X(logger, exception, ...) \
	if constexpr (PonyEngine::Log::IsInMask(PonyEngine::Log::LogType::Exception, PONY_LOG_STACKTRACE_MASK)) \
	{ \
		const std::stacktrace stacktrace = std::stacktrace::current(); \
		PonyEngine::Log::LogToConsole(logger, exception, stacktrace __VA_OPT__(,) __VA_ARGS__); \
	} \
	else \
	{ \
		PonyEngine::Log::LogToConsole(logger, exception __VA_OPT__(,) __VA_ARGS__); \
	} \

/// @brief Log macro that calls the log to a console function if it's enabled with the preprocessors; otherwise it's empty.
/// @param logger PonyEngine::Log::ILoggerContext reference.
/// @param type PonyEngine::Log::LogType value.
/// @param message std::string_view as a message or format string.
/// @param ... Format arguments.
/// @note The function is thread-safe.
#define PONY_CONSOLE(logger, type, message, ...) \
	if constexpr (PonyEngine::Log::IsInMask(type, PONY_LOG_MASK)) \
	{ \
		PONY_CONSOLE_PUSH(logger, type, message __VA_OPT__(,) __VA_ARGS__) \
	} \

/// @brief Log macro that conditionally calls the log to a console function if it's enabled with the preprocessors; otherwise it's empty.
/// @param condition Log condition.
/// @param logger PonyEngine::Log::ILoggerContext reference.
/// @param type PonyEngine::Log::LogType value.
/// @param message std::string_view as a message or format string.
/// @param ... Format arguments.
/// @note The function is thread-safe.
#define PONY_CONSOLE_IF(condition, logger, type, message, ...) \
	if constexpr (PonyEngine::Log::IsInMask(type, PONY_LOG_MASK)) \
	{ \
		if (condition) \
		{ \
			PONY_CONSOLE_PUSH(logger, type, message __VA_OPT__(,) __VA_ARGS__) \
		} \
	} \

/// @brief Log exception macro that calls the log exception to a console function if it's enabled with the preprocessors; otherwise it's empty.
/// @param logger PonyEngine::Log::ILoggerContext reference.
/// @param exception std::exception reference.
/// @param logMessage std::string_view as a message or format string.
/// @param ... Message or format and format arguments.
/// @note The function is thread-safe.
#define PONY_CONSOLE_X(logger, exception, ...) \
	if constexpr (PONY_LOG_EXCEPTION_MASK != PonyEngine::Log::LogTypeMask::None) \
	{ \
		PONY_CONSOLE_PUSH_X(logger, exception __VA_OPT__(,) __VA_ARGS__); \
	} \

/// @brief Log exception macro that conditionally calls the log exception to a console function if it's enabled with the preprocessors; otherwise it's empty.
/// @param condition Log condition.
/// @param logger PonyEngine::Log::ILoggerContext reference.
/// @param exception std::exception reference.
/// @param logMessage std::string_view as a message or format string.
/// @param ... Message or format and format arguments.
/// @note The function is thread-safe.
#define PONY_CONSOLE_X_IF(condition, logger, exception, ...) \
	if constexpr (PONY_LOG_EXCEPTION_MASK != PonyEngine::Log::LogTypeMask::None) \
	{ \
		if (condition) \
		{ \
			PONY_CONSOLE_PUSH_X(logger, exception __VA_OPT__(,) __VA_ARGS__); \
		} \
	} \

