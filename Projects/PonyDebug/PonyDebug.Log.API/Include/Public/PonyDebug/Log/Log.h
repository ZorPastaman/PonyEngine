/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#pragma once

// To use this header, you have to import PonyDebug.Log as well.

#ifdef PONY_LOG_VERBOSE
/// @brief Verbose log mask.
#define PONY_LOG_VERBOSE_MASK PonyDebug::Log::LogType::Verbose
#else
/// @brief Verbose log mask.
#define PONY_LOG_VERBOSE_MASK PonyDebug::Log::LogType::None
#endif

#ifdef PONY_LOG_DEBUG
/// @brief Debug log mask.
#define PONY_LOG_DEBUG_MASK PonyDebug::Log::LogType::Debug
#else
/// @brief Debug log mask.
#define PONY_LOG_DEBUG_MASK PonyDebug::Log::LogType::None
#endif

#ifdef PONY_LOG_INFO
/// @brief Info log mask.
#define PONY_LOG_INFO_MASK PonyDebug::Log::LogType::Info
#else
/// @brief Info log mask.
#define PONY_LOG_INFO_MASK PonyDebug::Log::LogType::None
#endif

#ifdef PONY_LOG_WARNING
/// @brief Warning log mask.
#define PONY_LOG_WARNING_MASK PonyDebug::Log::LogType::Warning
#else
/// @brief Warning log mask.
#define PONY_LOG_WARNING_MASK PonyDebug::Log::LogType::None
#endif

#ifdef PONY_LOG_ERROR
/// @brief Error log mask.
#define PONY_LOG_ERROR_MASK PonyDebug::Log::LogType::Error
#else
/// @brief Error log mask.
#define PONY_LOG_ERROR_MASK PonyDebug::Log::LogType::None
#endif

#ifdef PONY_LOG_EXCEPTION
/// @brief Exception log mask.
#define PONY_LOG_EXCEPTION_MASK PonyDebug::Log::LogType::Exception
#else
/// @brief Exception log mask.
#define PONY_LOG_EXCEPTION_MASK PonyDebug::Log::LogType::None
#endif

/// @brief Log mask. It contains a mask of all possible log types.
#define PONY_LOG_MASK (PONY_LOG_VERBOSE_MASK | PONY_LOG_DEBUG_MASK | PONY_LOG_INFO_MASK | PONY_LOG_WARNING_MASK | PONY_LOG_ERROR_MASK | PONY_LOG_EXCEPTION_MASK)

#if defined(PONY_CONSOLE_LOG) || defined(PONY_SYSTEM_CONSOLE_LOG)
/// @brief Console log mask.
#define PONY_CONSOLE_LOG_MASK PONY_LOG_MASK
#else
/// @brief Console log mask.
#define PONY_CONSOLE_LOG_MASK PonyDebug::Log::LogType::None
#endif

/// @brief If wrapper.
/// @param condition If condition.
/// @param expression If statement-true.
#define PONY_LOG_CONDITIONAL(condition, expression) \
	if (condition) \
	{ \
		expression; \
	}

/// @brief Log macro that calls the log function if it's enabled with the preprocessors; otherwise it's empty.
/// @param logger PonyDebug::Log::ILogger reference.
/// @param logType PonyDebug::Log::LogType value.
/// @param logMessage const char* as a message or format string.
/// @param ... Format arguments.
#define PONY_LOG(logger, logType, logMessage, ...) \
	if constexpr (((logType) & PONY_LOG_MASK) != PonyDebug::Log::LogType::None) \
	{ \
		PonyDebug::Log::LogToLogger(logger, logType, logMessage __VA_OPT__(,) __VA_ARGS__); \
	}

/// @brief Log macro that conditionally calls the log function if it's enabled with the preprocessors; otherwise it's empty.
/// @param condition Log condition.
/// @param logger PonyDebug::Log::ILogger reference.
/// @param logType PonyDebug::Log::LogType value.
/// @param logMessage const char* as a message or format string.
/// @param ... Format arguments.
#define PONY_LOG_IF(condition, logger, logType, logMessage, ...) \
	if constexpr (((logType) & PONY_LOG_MASK) != PonyDebug::Log::LogType::None) \
	{ \
		PONY_LOG_CONDITIONAL(condition, PonyDebug::Log::LogToLogger(logger, logType, logMessage __VA_OPT__(,) __VA_ARGS__)); \
	}

/// @brief Log exception macro that calls the log exception function if it's enabled with the preprocessors; otherwise it's empty.
/// @param logger PonyDebug::Log::ILogger reference.
/// @param exception std::exception reference.
/// @param ... Format arguments.
#define PONY_LOG_E_S(logger, exception) \
	if constexpr (PONY_LOG_EXCEPTION_MASK != PonyDebug::Log::LogType::None) \
	{ \
		PonyDebug::Log::LogExceptionToLogger(logger, exception); \
	}

/// @brief Log exception macro that conditionally calls the log exception function if it's enabled with the preprocessors; otherwise it's empty.
/// @param condition Log condition.
/// @param logger PonyDebug::Log::ILogger reference.
/// @param exception std::exception reference.
/// @param ... Format arguments.
#define PONY_LOG_E_S_IF(condition, logger, exception, logMessage, ...) \
	if constexpr (PONY_LOG_EXCEPTION_MASK != PonyDebug::Log::LogType::None) \
	{ \
		PONY_LOG_CONDITIONAL(condition, PonyDebug::Log::LogExceptionToLogger(logger, exception)); \
	}

/// @brief Log exception macro that calls the log exception function if it's enabled with the preprocessors; otherwise it's empty.
/// @param logger PonyDebug::Log::ILogger reference.
/// @param exception std::exception reference.
/// @param logMessage const char* as a message or format string.
/// @param ... Format arguments.
#define PONY_LOG_E(logger, exception, logMessage, ...) \
	if constexpr (PONY_LOG_EXCEPTION_MASK != PonyDebug::Log::LogType::None) \
	{ \
		PonyDebug::Log::LogExceptionToLogger(logger, exception, logMessage __VA_OPT__(,) __VA_ARGS__); \
	}

/// @brief Log exception macro that conditionally calls the log exception function if it's enabled with the preprocessors; otherwise it's empty.
/// @param condition Log condition.
/// @param logger PonyDebug::Log::ILogger reference.
/// @param exception std::exception reference.
/// @param logMessage const char* as a message or format string.
/// @param ... Format arguments.
#define PONY_LOG_E_IF(condition, logger, exception, logMessage, ...) \
	if constexpr (PONY_LOG_EXCEPTION_MASK != PonyDebug::Log::LogType::None) \
	{ \
		PONY_LOG_CONDITIONAL(condition, PonyDebug::Log::LogExceptionToLogger(logger, exception, logMessage __VA_OPT__(,) __VA_ARGS__)); \
	}

/// @brief Log macro that puts a message into a corresponding console output if it's enabled with the preprocessors; otherwise it's empty.
/// @details std::cout corresponds to Verbose, Debug and Info log types; std::clog corresponds to Warning log type; std::cerr corresponds to Error and Exception log type.
/// @param logType Log type.
/// @param logMessage const char* as a message or format string.
/// @param ... Format arguments.
#define PONY_CONSOLE(logType, logMessage, ...) \
	if constexpr (((logType) & PONY_CONSOLE_LOG_MASK) != PonyDebug::Log::LogType::None) \
	{ \
		PonyDebug::Log::LogToConsole(logType, logMessage __VA_OPT__(,) __VA_ARGS__); \
	}

/// @brief Log macro that conditionally puts a message into a corresponding console output if it's enabled with the preprocessors; otherwise it's empty.
/// @details std::cout corresponds to Verbose, Debug and Info log types; std::clog corresponds to Warning log type; std::cerr corresponds to Error and Exception log type.
/// @param condition Log condition.
/// @param logType Log type.
/// @param logMessage const char* as a message or format string.
/// @param ... Format arguments.
#define PONY_CONSOLE_IF(condition, logType, logMessage, ...) \
	if constexpr (((logType) & PONY_CONSOLE_LOG_MASK) != PonyDebug::Log::LogType::None) \
	{ \
		PONY_LOG_CONDITIONAL(condition, PonyDebug::Log::LogToConsole(logType, logMessage __VA_OPT__(,) __VA_ARGS__)); \
	}

/// @brief Log macro that puts an exception into a corresponding console output if it's enabled with the preprocessors; otherwise it's empty.
/// @details std::cout corresponds to Verbose, Debug and Info log types; std::clog corresponds to Warning log type; std::cerr corresponds to Error and Exception log type.
/// @param exception std::exception reference.
#define PONY_CONSOLE_E_S(exception) \
	if constexpr ((PONY_LOG_EXCEPTION_MASK & PONY_CONSOLE_LOG_MASK) != PonyDebug::Log::LogType::None) \
	{ \
		PonyDebug::Log::LogExceptionToConsole(exception); \
	}

/// @brief Log macro that conditionally puts an exception into a corresponding console output if it's enabled with the preprocessors; otherwise it's empty.
/// @details std::cout corresponds to Verbose, Debug and Info log types; std::clog corresponds to Warning log type; std::cerr corresponds to Error and Exception log type.
/// @param condition Log condition.
/// @param exception std::exception reference.
#define PONY_CONSOLE_E_S_IF(condition, exception) \
	if constexpr ((PONY_LOG_EXCEPTION_MASK & PONY_CONSOLE_LOG_MASK) != PonyDebug::Log::LogType::None) \
	{ \
		PONY_LOG_CONDITIONAL(condition, PonyDebug::Log::LogExceptionToConsole(exception)); \
	}


/// @brief Log macro that puts an exception and a message into a corresponding console output if it's enabled with the preprocessors; otherwise it's empty.
/// @details std::cout corresponds to Verbose, Debug and Info log types; std::clog corresponds to Warning log type; std::cerr corresponds to Error and Exception log type.
/// @param exception std::exception reference.
/// @param logMessage const char* as a message or format string.
/// @param ... Format arguments.
#define PONY_CONSOLE_E(exception, logMessage, ...) \
	if constexpr ((PONY_LOG_EXCEPTION_MASK & PONY_CONSOLE_LOG_MASK) != PonyDebug::Log::LogType::None) \
	{ \
		PonyDebug::Log::LogExceptionToConsole(exception, logMessage __VA_OPT__(,) __VA_ARGS__); \
	}

/// @brief Log macro that conditionally puts an exception and a message into a corresponding console output if it's enabled with the preprocessors; otherwise it's empty.
/// @details std::cout corresponds to Verbose, Debug and Info log types; std::clog corresponds to Warning log type; std::cerr corresponds to Error and Exception log type.
/// @param condition Log condition.
/// @param exception std::exception reference.
/// @param logMessage const char* as a message or format string.
/// @param ... Format arguments.
#define PONY_CONSOLE_E_IF(condition, exception, logMessage, ...) \
	if constexpr ((PONY_LOG_EXCEPTION_MASK & PONY_CONSOLE_LOG_MASK) != PonyDebug::Log::LogType::None) \
	{ \
		PONY_LOG_CONDITIONAL(condition, PonyDebug::Log::LogExceptionToConsole(exception, logMessage __VA_OPT__(,) __VA_ARGS__)); \
	}
