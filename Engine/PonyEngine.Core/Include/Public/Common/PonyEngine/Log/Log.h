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

#if defined(PONY_CONSOLE_LOG) || defined(PONY_PLATFORM_CONSOLE_LOG)
/// @brief Console log mask.
#define PONY_CONSOLE_LOG_MASK PONY_LOG_MASK
#else
/// @brief Console log mask.
#define PONY_CONSOLE_LOG_MASK PonyEngine::Log::LogTypeMask::None
#endif

/// @brief Pushes the log without a level a check.
/// @param logger PonyEngine::Log::ILogger reference.
/// @param type PonyEngine::Log::LogType value.
/// @param message std::string_view as a message or format string.
/// @param ... Format arguments.
#define PONY_LOG_PUSH(logger, type, message, ...) \
	PonyEngine::Log::LogData PonyEngineLogData; \
	if constexpr (PonyEngine::Log::IsInMask(type, PONY_LOG_STACKTRACE_MASK)) \
	{ \
		PonyEngineLogData.stacktrace = std::stacktrace::current(); \
	} \
	PonyEngine::Log::LogToLogger(logger, type, PonyEngineLogData, message __VA_OPT__(,) __VA_ARGS__); \

/// @brief Pushes the exception log without a level a check.
/// @param logger PonyEngine::Log::ILogger reference.
/// @param exception std::exception reference.
#define PONY_LOG_PUSH_E_S(logger, exception) \
	PonyEngine::Log::LogData PonyEngineLogData; \
	if constexpr (PonyEngine::Log::IsInMask(PonyEngine::Log::LogType::Exception, PONY_LOG_STACKTRACE_MASK)) \
	{ \
		PonyEngineLogData.stacktrace = std::stacktrace::current(); \
	} \
	PonyEngine::Log::LogToLogger(logger, exception, PonyEngineLogData); \

/// @brief Pushes the exception log without a level a check.
/// @param logger PonyEngine::Log::ILogger reference.
/// @param exception std::exception reference.
/// @param message std::string_view as a message or format string.
/// @param ... Format arguments.
#define PONY_LOG_PUSH_E(logger, exception, message, ...) \
	PonyEngine::Log::LogData PonyEngineLogData; \
	if constexpr (PonyEngine::Log::IsInMask(PonyEngine::Log::LogType::Exception, PONY_LOG_STACKTRACE_MASK)) \
	{ \
		PonyEngineLogData.stacktrace = std::stacktrace::current(); \
	} \
	PonyEngine::Log::LogToLogger(logger, exception, PonyEngineLogData, message __VA_OPT__(,) __VA_ARGS__); \

/// @brief Pushes the log without a level a check.
/// @param type PonyEngine::Log::LogType value.
/// @param message std::string_view as a message or format string.
/// @param ... Format arguments.
#define PONY_LOG_CONSOLE_PUSH(type, message, ...) \
	PonyEngine::Log::LogData PonyEngineLogData; \
	if constexpr (PonyEngine::Log::IsInMask(type, PONY_LOG_STACKTRACE_MASK)) \
	{ \
		PonyEngineLogData.stacktrace = std::stacktrace::current(); \
	} \
	PonyEngine::Log::LogToConsole(type, PonyEngineLogData, message __VA_OPT__(,) __VA_ARGS__); \

/// @brief Pushes the exception log without a level a check.
/// @param exception std::exception reference.
#define PONY_LOG_CONSOLE_PUSH_E_S(exception) \
	PonyEngine::Log::LogData PonyEngineLogData; \
	if constexpr (PonyEngine::Log::IsInMask(PonyEngine::Log::LogType::Exception, PONY_LOG_STACKTRACE_MASK)) \
	{ \
		PonyEngineLogData.stacktrace = std::stacktrace::current(); \
	} \
	PonyEngine::Log::LogToConsole(exception, PonyEngineLogData); \

/// @brief Pushes the exception log without a level a check.
/// @param exception std::exception reference.
/// @param message std::string_view as a message or format string.
/// @param ... Format arguments.
#define PONY_LOG_CONSOLE_PUSH_E(exception, message, ...) \
	PonyEngine::Log::LogData PonyEngineLogData; \
	if constexpr (PonyEngine::Log::IsInMask(PonyEngine::Log::LogType::Exception, PONY_LOG_STACKTRACE_MASK)) \
	{ \
		PonyEngineLogData.stacktrace = std::stacktrace::current(); \
	} \
	PonyEngine::Log::LogToConsole(exception, PonyEngineLogData, message __VA_OPT__(,) __VA_ARGS__); \

/// @brief Log macro that calls the log function if it's enabled with the preprocessors; otherwise it's empty.
/// @param logger PonyEngine::Log::ILogger reference.
/// @param type PonyEngine::Log::LogType value.
/// @param message std::string_view as a message or format string.
/// @param ... Format arguments.
#define PONY_LOG(logger, type, message, ...) \
	if constexpr (PonyEngine::Log::IsInMask(type, PONY_LOG_MASK)) \
	{ \
		PONY_LOG_PUSH(logger, type, message __VA_OPT__(,) __VA_ARGS__) \
	}

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
	}

/// @brief Log exception macro that calls the log exception function if it's enabled with the preprocessors; otherwise it's empty.
/// @param logger PonyEngine::Log::ILogger reference.
/// @param exception std::exception reference.
/// @param ... Format arguments.
#define PONY_LOG_E_S(logger, exception) \
	if constexpr (PONY_LOG_EXCEPTION_MASK != PonyEngine::Log::LogTypeMask::None) \
	{ \
		PONY_LOG_PUSH_E_S(logger, exception) \
	}

/// @brief Log exception macro that conditionally calls the log exception function if it's enabled with the preprocessors; otherwise it's empty.
/// @param condition Log condition.
/// @param logger PonyEngine::Log::ILogger reference.
/// @param exception std::exception reference.
/// @param ... Format arguments.
#define PONY_LOG_E_S_IF(condition, logger, exception) \
	if constexpr (PONY_LOG_EXCEPTION_MASK != PonyEngine::Log::LogTypeMask::None) \
	{ \
		if (condition) \
		{ \
			PONY_LOG_PUSH_E_S(logger, exception) \
		} \
	}

/// @brief Log exception macro that calls the log exception function if it's enabled with the preprocessors; otherwise it's empty.
/// @param logger PonyEngine::Log::ILogger reference.
/// @param exception std::exception reference.
/// @param logMessage std::string_view as a message or format string.
/// @param ... Format arguments.
#define PONY_LOG_E(logger, exception, logMessage, ...) \
	if constexpr (PONY_LOG_EXCEPTION_MASK != PonyEngine::Log::LogTypeMask::None) \
	{ \
		PONY_LOG_PUSH_E(logger, exception, logMessage __VA_OPT__(,) __VA_ARGS__); \
	}

/// @brief Log exception macro that conditionally calls the log exception function if it's enabled with the preprocessors; otherwise it's empty.
/// @param condition Log condition.
/// @param logger PonyEngine::Log::ILogger reference.
/// @param exception std::exception reference.
/// @param logMessage std::string_view as a message or format string.
/// @param ... Format arguments.
#define PONY_LOG_E_IF(condition, logger, exception, logMessage, ...) \
	if constexpr (PONY_LOG_EXCEPTION_MASK != PonyEngine::Log::LogTypeMask::None) \
	{ \
		if (condition) \
		{ \
			PONY_LOG_PUSH_E(logger, exception, logMessage __VA_OPT__(,) __VA_ARGS__); \
		} \
	}

/// @brief Log macro that puts a message into a corresponding console output if it's enabled with the preprocessors; otherwise it's empty.
/// @details std::cout corresponds to Verbose, Debug and Info log types; std::clog corresponds to Warning log type; std::cerr corresponds to Error and Exception log type.
/// @param logType Log type.
/// @param logMessage std::string_view as a message or format string.
/// @param ... Format arguments.
#define PONY_CONSOLE(logType, logMessage, ...) \
	if constexpr (PonyEngine::Log::IsInMask(logType, PONY_CONSOLE_LOG_MASK)) \
	{ \
		PONY_LOG_CONSOLE_PUSH(logType, logMessage __VA_OPT__(,) __VA_ARGS__); \
	}

/// @brief Log macro that conditionally puts a message into a corresponding console output if it's enabled with the preprocessors; otherwise it's empty.
/// @details std::cout corresponds to Verbose, Debug and Info log types; std::clog corresponds to Warning log type; std::cerr corresponds to Error and Exception log type.
/// @param condition Log condition.
/// @param logType Log type.
/// @param logMessage std::string_view as a message or format string.
/// @param ... Format arguments.
#define PONY_CONSOLE_IF(condition, logType, logMessage, ...) \
	if constexpr (PonyEngine::Log::IsInMask(logType, PONY_CONSOLE_LOG_MASK)) \
	{ \
		if (condition) \
		{ \
			PONY_LOG_CONSOLE_PUSH(logType, logMessage __VA_OPT__(,) __VA_ARGS__); \
		} \
	}

/// @brief Log macro that puts an exception into a corresponding console output if it's enabled with the preprocessors; otherwise it's empty.
/// @details std::cout corresponds to Verbose, Debug and Info log types; std::clog corresponds to Warning log type; std::cerr corresponds to Error and Exception log type.
/// @param exception std::exception reference.
#define PONY_CONSOLE_E_S(exception) \
	if constexpr ((PONY_LOG_EXCEPTION_MASK & PONY_CONSOLE_LOG_MASK) != PonyEngine::Log::LogTypeMask::None) \
	{ \
		PONY_LOG_CONSOLE_PUSH_E_S(exception); \
	}

/// @brief Log macro that conditionally puts an exception into a corresponding console output if it's enabled with the preprocessors; otherwise it's empty.
/// @details std::cout corresponds to Verbose, Debug and Info log types; std::clog corresponds to Warning log type; std::cerr corresponds to Error and Exception log type.
/// @param condition Log condition.
/// @param exception std::exception reference.
#define PONY_CONSOLE_E_S_IF(condition, exception) \
	if constexpr ((PONY_LOG_EXCEPTION_MASK & PONY_CONSOLE_LOG_MASK) != PonyEngine::Log::LogTypeMask::None) \
	{ \
		if (condition) \
		{ \
			PONY_LOG_CONSOLE_PUSH_E_S(exception); \
		} \
	}


/// @brief Log macro that puts an exception and a message into a corresponding console output if it's enabled with the preprocessors; otherwise it's empty.
/// @details std::cout corresponds to Verbose, Debug and Info log types; std::clog corresponds to Warning log type; std::cerr corresponds to Error and Exception log type.
/// @param exception std::exception reference.
/// @param logMessage std::string_view as a message or format string.
/// @param ... Format arguments.
#define PONY_CONSOLE_E(exception, logMessage, ...) \
	if constexpr ((PONY_LOG_EXCEPTION_MASK & PONY_CONSOLE_LOG_MASK) != PonyEngine::Log::LogTypeMask::None) \
	{ \
		PONY_LOG_CONSOLE_PUSH_E(exception, logMessage __VA_OPT__(,) __VA_ARGS__); \
	}

/// @brief Log macro that conditionally puts an exception and a message into a corresponding console output if it's enabled with the preprocessors; otherwise it's empty.
/// @details std::cout corresponds to Verbose, Debug and Info log types; std::clog corresponds to Warning log type; std::cerr corresponds to Error and Exception log type.
/// @param condition Log condition.
/// @param exception std::exception reference.
/// @param logMessage std::string_view as a message or format string.
/// @param ... Format arguments.
#define PONY_CONSOLE_E_IF(condition, exception, logMessage, ...) \
	if constexpr ((PONY_LOG_EXCEPTION_MASK & PONY_CONSOLE_LOG_MASK) != PonyEngine::Log::LogTypeMask::None) \
	{ \
		if (condition) \
		{ \
			PONY_LOG_CONSOLE_PUSH_E(exception, logMessage __VA_OPT__(,) __VA_ARGS__); \
		} \
	}
