/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#pragma once

 // To use this header, you have to import PonyDebug.Log and PonyEngine.Core as well.

#include "PonyDebug/Log/Log.h"

/// @brief Log macro that calls the log function if it's enabled with the preprocessors; otherwise it's empty.
/// @param engine PonyEngine::Core::IEngine pointer.
/// @param logType PonyDebug::Log::LogType value.
/// @param logMessage const char* as a message or format string.
/// @param ... Format arguments.
#define PONY_LOG(engine, logType, logMessage, ...) \
	if constexpr (((logType) & PONY_LOG_MASK) != PonyDebug::Log::LogType::None) \
	{ \
		PonyEngine::Core::LogToLogger(*(engine), logType, logMessage __VA_OPT__(,) __VA_ARGS__); \
	}

/// @brief Log macro that conditionally calls the log function if it's enabled with the preprocessors; otherwise it's empty.
/// @param condition Log condition. Must evaluate to bool.
/// @param engine PonyEngine::Core::IEngine pointer.
/// @param logType PonyDebug::Log::LogType value.
/// @param logMessage const char* as a message or format string.
/// @param ... Format arguments.
#define PONY_LOG_IF(condition, engine, logType, logMessage, ...) \
	if constexpr (((logType) & PONY_LOG_MASK) != PonyDebug::Log::LogType::None) \
	{ \
		PONY_LOG_CONDITIONAL(condition, PonyEngine::Core::LogToLogger(*(engine), logType, logMessage __VA_OPT__(,) __VA_ARGS__)); \
	}

/// @brief Log exception macro that calls the log exception function if it's enabled with the preprocessors; otherwise it's empty.
/// @param engine PonyEngine::Core::IEngine pointer.
/// @param exception std::exception reference.
#define PONY_LOG_E_S(engine, exception) \
	if constexpr (PONY_LOG_EXCEPTION_MASK != PonyDebug::Log::LogType::None) \
	{ \
		PonyEngine::Core::LogExceptionToLogger(*(engine), exception); \
	}

/// @brief Log exception macro that conditionally calls the log exception function if it's enabled with the preprocessors; otherwise it's empty.
/// @param condition Log condition. Must evaluate to bool.
/// @param engine PonyEngine::Core::IEngine pointer.
/// @param exception std::exception reference.
#define PONY_LOG_E_S_IF(condition, engine, exception) \
	if constexpr (PONY_LOG_EXCEPTION_MASK != PonyDebug::Log::LogType::None) \
	{ \
		PONY_LOG_CONDITIONAL(condition, PonyEngine::Core::LogExceptionToLogger(*(engine), exception)); \
	}

/// @brief Log exception macro that calls the log exception function if it's enabled with the preprocessors; otherwise it's empty.
/// @param engine PonyEngine::Core::IEngine pointer.
/// @param exception std::exception reference.
/// @param logMessage const char* as a message or format string.
/// @param ... Format arguments.
#define PONY_LOG_E(engine, exception, logMessage, ...) \
	if constexpr (PONY_LOG_EXCEPTION_MASK != PonyDebug::Log::LogType::None) \
	{ \
		PonyEngine::Core::LogExceptionToLogger(*(engine), exception, logMessage __VA_OPT__(,) __VA_ARGS__); \
	}

/// @brief Log exception macro that conditionally calls the log exception function if it's enabled with the preprocessors; otherwise it's empty.
/// @param condition Log condition. Must evaluate to bool.
/// @param engine PonyEngine::Core::IEngine pointer.
/// @param exception std::exception reference.
/// @param logMessage const char* as a message or format string.
/// @param ... Format arguments.
#define PONY_LOG_E_IF(condition, engine, exception, logMessage, ...) \
	if constexpr (PONY_LOG_EXCEPTION_MASK != PonyDebug::Log::LogType::None) \
	{ \
		PONY_LOG_CONDITIONAL(condition, PonyEngine::Core::LogExceptionToLogger(*(engine), exception, logMessage __VA_OPT__(,) __VA_ARGS__)); \
	}
