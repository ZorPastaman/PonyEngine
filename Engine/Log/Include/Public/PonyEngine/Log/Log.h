/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#pragma once

// To use this header, you have to import PonyEngine.Log as well.
// All the macros here are thread-safe.

#ifdef PONY_LOG_VERBOSE
/// @brief Verbose log mask.
#define PONY_LOG_VERBOSE_MASK PonyEngine::Log::LogTypeMask::Verbose
#else
/// @brief Verbose log mask.
#define PONY_LOG_VERBOSE_MASK PonyEngine::Log::LogTypeMask::None
#endif

#ifdef PONY_LOG_DEBUG
/// @brief Debug log mask.
#define PONY_LOG_DEBUG_MASK PonyEngine::Log::LogTypeMask::Debug
#else
/// @brief Debug log mask.
#define PONY_LOG_DEBUG_MASK PonyEngine::Log::LogTypeMask::None
#endif

#ifdef PONY_LOG_INFO
/// @brief Info log mask.
#define PONY_LOG_INFO_MASK PonyEngine::Log::LogTypeMask::Info
#else
/// @brief Info log mask.
#define PONY_LOG_INFO_MASK PonyEngine::Log::LogTypeMask::None
#endif

#ifdef PONY_LOG_WARNING
/// @brief Warning log mask.
#define PONY_LOG_WARNING_MASK PonyEngine::Log::LogTypeMask::Warning
#else
/// @brief Warning log mask.
#define PONY_LOG_WARNING_MASK PonyEngine::Log::LogTypeMask::None
#endif

#ifdef PONY_LOG_ERROR
/// @brief Error log mask.
#define PONY_LOG_ERROR_MASK PonyEngine::Log::LogTypeMask::Error
#else
/// @brief Error log mask.
#define PONY_LOG_ERROR_MASK PonyEngine::Log::LogTypeMask::None
#endif

#ifdef PONY_LOG_EXCEPTION
/// @brief Exception log mask.
#define PONY_LOG_EXCEPTION_MASK PonyEngine::Log::LogTypeMask::Exception
#else
/// @brief Exception log mask.
#define PONY_LOG_EXCEPTION_MASK PonyEngine::Log::LogTypeMask::None
#endif

#ifdef PONY_LOG_STACKTRACE_VERBOSE
/// @brief Verbose log stacktrace mask.
#define PONY_LOG_STACKTRACE_VERBOSE_MASK PonyEngine::Log::LogTypeMask::Verbose
#else
/// @brief Verbose log stacktrace mask.
#define PONY_LOG_STACKTRACE_VERBOSE_MASK PonyEngine::Log::LogTypeMask::None
#endif

#ifdef PONY_LOG_STACKTRACE_DEBUG
/// @brief Debug log stacktrace mask.
#define PONY_LOG_STACKTRACE_DEBUG_MASK PonyEngine::Log::LogTypeMask::Debug
#else
/// @brief Debug log stacktrace mask.
#define PONY_LOG_STACKTRACE_DEBUG_MASK PonyEngine::Log::LogTypeMask::None
#endif

#ifdef PONY_LOG_STACKTRACE_INFO
/// @brief Info log stacktrace mask.
#define PONY_LOG_STACKTRACE_INFO_MASK PonyEngine::Log::LogTypeMask::Info
#else
/// @brief Info log stacktrace mask.
#define PONY_LOG_STACKTRACE_INFO_MASK PonyEngine::Log::LogTypeMask::None
#endif

#ifdef PONY_LOG_STACKTRACE_WARNING
/// @brief Warning log stacktrace mask.
#define PONY_LOG_STACKTRACE_WARNING_MASK PonyEngine::Log::LogTypeMask::Warning
#else
/// @brief Warning log stacktrace mask.
#define PONY_LOG_STACKTRACE_WARNING_MASK PonyEngine::Log::LogTypeMask::None
#endif

#ifdef PONY_LOG_STACKTRACE_ERROR
/// @brief Error log stacktrace mask.
#define PONY_LOG_STACKTRACE_ERROR_MASK PonyEngine::Log::LogTypeMask::Error
#else
/// @brief Error log stacktrace mask.
#define PONY_LOG_STACKTRACE_ERROR_MASK PonyEngine::Log::LogTypeMask::None
#endif

#ifdef PONY_LOG_STACKTRACE_EXCEPTION
/// @brief Exception log stacktrace mask.
#define PONY_LOG_STACKTRACE_EXCEPTION_MASK PonyEngine::Log::LogTypeMask::Exception
#else
/// @brief Exception log stacktrace mask.
#define PONY_LOG_STACKTRACE_EXCEPTION_MASK PonyEngine::Log::LogTypeMask::None
#endif

/// @brief Log mask. It contains a mask of all possible log types.
#define PONY_LOG_MASK (PONY_LOG_VERBOSE_MASK | PONY_LOG_DEBUG_MASK | PONY_LOG_INFO_MASK | PONY_LOG_WARNING_MASK | PONY_LOG_ERROR_MASK | PONY_LOG_EXCEPTION_MASK)
/// @brief Log stacktrace mask. It contains a mask of all possible log stacktrace types.
#define PONY_LOG_STACKTRACE_MASK (PONY_LOG_STACKTRACE_VERBOSE_MASK | PONY_LOG_STACKTRACE_DEBUG_MASK | PONY_LOG_STACKTRACE_INFO_MASK | PONY_LOG_STACKTRACE_WARNING_MASK | PONY_LOG_STACKTRACE_ERROR_MASK | PONY_LOG_STACKTRACE_EXCEPTION_MASK)

/// @brief Pushes the log without a level a check.
/// @param logger PonyEngine::Log::ILogger reference.
/// @param type PonyEngine::Log::LogType value.
/// @param message std::string_view as a message or format string.
/// @param ... Format arguments.
#define PONY_LOG_PUSH(logger, type, message, ...) \
	if constexpr (PonyEngine::Log::IsInMask(type, PONY_LOG_STACKTRACE_MASK)) \
	{ \
		const std::stacktrace stacktrace = std::stacktrace::current(); \
		PonyEngine::Log::LogToLogger(logger, type, stacktrace, message __VA_OPT__(,) __VA_ARGS__); \
	} \
	else \
	{ \
		PonyEngine::Log::LogToLogger(logger, type, message __VA_OPT__(,) __VA_ARGS__); \
	} \

/// @brief Pushes the exception log without a level a check.
/// @param logger PonyEngine::Log::ILogger reference.
/// @param exception std::exception_ptr reference.
/// @param ... Message or format and format arguments.
#define PONY_LOG_PUSH_X(logger, exception, ...) \
	if constexpr (PonyEngine::Log::IsInMask(PonyEngine::Log::LogType::Exception, PONY_LOG_STACKTRACE_MASK)) \
	{ \
		const std::stacktrace stacktrace = std::stacktrace::current(); \
		PonyEngine::Log::LogToLogger(logger, exception, stacktrace __VA_OPT__(,) __VA_ARGS__); \
	} \
	else \
	{ \
		PonyEngine::Log::LogToLogger(logger, exception __VA_OPT__(,) __VA_ARGS__); \
	} \

/// @brief Log macro that calls the log function if it's enabled with the preprocessors; otherwise it's empty.
/// @param logger PonyEngine::Log::ILogger reference.
/// @param type PonyEngine::Log::LogType value.
/// @param message std::string_view as a message or format string.
/// @param ... Format arguments.
#define PONY_LOG(logger, type, message, ...) \
	if constexpr (PonyEngine::Log::IsInMask(type, PONY_LOG_MASK)) \
	{ \
		PONY_LOG_PUSH(logger, type, message __VA_OPT__(,) __VA_ARGS__) \
	} \

/// @brief Log macro that conditionally calls the log function if it's enabled with the preprocessors; otherwise it's empty.
/// @param condition Log condition.
/// @param logger PonyEngine::Log::ILogger reference.
/// @param type PonyEngine::Log::LogType value.
/// @param message std::string_view as a message or format string.
/// @param ... Format arguments.
#define PONY_LOG_IF(condition, logger, type, message, ...) \
	if constexpr (PonyEngine::Log::IsInMask(type, PONY_LOG_MASK)) \
	{ \
		if (condition) \
		{ \
			PONY_LOG_PUSH(logger, type, message __VA_OPT__(,) __VA_ARGS__) \
		} \
	} \

/// @brief Log exception macro that calls the log exception function if it's enabled with the preprocessors; otherwise it's empty.
/// @param logger PonyEngine::Log::ILogger reference.
/// @param exception std::exception reference.
/// @param logMessage std::string_view as a message or format string.
/// @param ... Message or format and format arguments.
#define PONY_LOG_X(logger, exception, ...) \
	if constexpr (PONY_LOG_EXCEPTION_MASK != PonyEngine::Log::LogTypeMask::None) \
	{ \
		PONY_LOG_PUSH_X(logger, exception __VA_OPT__(,) __VA_ARGS__); \
	} \

/// @brief Log exception macro that conditionally calls the log exception function if it's enabled with the preprocessors; otherwise it's empty.
/// @param condition Log condition.
/// @param logger PonyEngine::Log::ILogger reference.
/// @param exception std::exception reference.
/// @param logMessage std::string_view as a message or format string.
/// @param ... Message or format and format arguments.
#define PONY_LOG_X_IF(condition, logger, exception, ...) \
	if constexpr (PONY_LOG_EXCEPTION_MASK != PonyEngine::Log::LogTypeMask::None) \
	{ \
		if (condition) \
		{ \
			PONY_LOG_PUSH_X(logger, exception __VA_OPT__(,) __VA_ARGS__); \
		} \
	} \
