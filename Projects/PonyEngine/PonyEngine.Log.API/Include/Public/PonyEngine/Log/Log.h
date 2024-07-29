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

#if PONY_LOG_VERBOSE
/// @brief Verbose log mask.
#define PONY_LOG_VERBOSE_MASK PonyEngine::Log::LogType::Verbose
#else
/// @brief Verbose log mask.
#define PONY_LOG_VERBOSE_MASK PonyEngine::Log::LogType::None
#endif

#if PONY_LOG_DEBUG
/// @brief Debug log mask.
#define PONY_LOG_DEBUG_MASK PonyEngine::Log::LogType::Debug
#else
/// @brief Debug log mask.
#define PONY_LOG_DEBUG_MASK PonyEngine::Log::LogType::None
#endif

#if PONY_LOG_INFO
/// @brief Info log mask.
#define PONY_LOG_INFO_MASK PonyEngine::Log::LogType::Info
#else
/// @brief Info log mask.
#define PONY_LOG_INFO_MASK PonyEngine::Log::LogType::None
#endif

#if PONY_LOG_WARNING
/// @brief Warning log mask.
#define PONY_LOG_WARNING_MASK PonyEngine::Log::LogType::Warning
#else
/// @brief Warning log mask.
#define PONY_LOG_WARNING_MASK PonyEngine::Log::LogType::None
#endif

#if PONY_LOG_ERROR
/// @brief Error log mask.
#define PONY_LOG_ERROR_MASK PonyEngine::Log::LogType::Error
#else
/// @brief Error log mask.
#define PONY_LOG_ERROR_MASK PonyEngine::Log::LogType::None
#endif

#if PONY_LOG_EXCEPTION
/// @brief Exception log mask.
#define PONY_LOG_EXCEPTION_MASK PonyEngine::Log::LogType::Exception
#else
/// @brief Exception log mask.
#define PONY_LOG_EXCEPTION_MASK PonyEngine::Log::LogType::None
#endif

/// @brief Log mask. It contains a mask of all possible log types except Exception.
#define PONY_LOG_MASK (PONY_LOG_VERBOSE_MASK | PONY_LOG_DEBUG_MASK | PONY_LOG_INFO_MASK | PONY_LOG_WARNING_MASK | PONY_LOG_ERROR_MASK | PONY_LOG_EXCEPTION_MASK)

#if PONY_CONSOLE_LOG || PONY_SYSTEM_CONSOLE_LOG
/// @brief Console log mask.
#define PONY_CONSOLE_LOG_MASK PONY_LOG_MASK
#else
/// @brief Console log mask.
#define PONY_CONSOLE_LOG_MASK PonyEngine::Log::LogType::None
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
/// @param logger PonyEngine::Log::ILogger pointer.
/// @param logType PonyEngine::Log::LogType value.
/// @param logMessage const char* as a message.
#define PONY_LOG_GENERAL(logger, logType, logMessage) \
	if constexpr (((logType) & PONY_LOG_MASK) != PonyEngine::Log::LogType::None) \
	{ \
		PonyEngine::Log::LogToLogger(*(logger), logType, logMessage); \
	}

/// @brief Log macro that conditionally calls the log function if it's enabled with the preprocessors; otherwise it's empty.
/// @param condition Log condition.
/// @param logger PonyEngine::Log::ILogger pointer.
/// @param logType PonyEngine::Log::LogType value.
/// @param logMessage const char* as a message.
#define PONY_LOG_IF_GENERAL(condition, logger, logType, logMessage) \
	if constexpr (((logType) & PONY_LOG_MASK) != PonyEngine::Log::LogType::None) \
	{ \
		PONY_LOG_CONDITIONAL(condition, PonyEngine::Log::LogToLogger(*(logger), logType, logMessage)); \
	}

/// @brief Log exception macro that calls the log exception function if it's enabled with the preprocessors; otherwise it's empty.
/// @param logger PonyEngine::Log::ILogger pointer.
/// @param exception std::exception reference.
/// @param logMessage const char* as a message.
#define PONY_LOG_E_GENERAL(logger, exception, logMessage) \
	if constexpr (PONY_LOG_EXCEPTION_MASK != PonyEngine::Log::LogType::None) \
	{ \
		PonyEngine::Log::LogExceptionToLogger(*(logger), exception, logMessage); \
	}

/// @brief Log exception macro that conditionally calls the log exception function if it's enabled with the preprocessors; otherwise it's empty.
/// @param condition Log condition.
/// @param logger PonyEngine::Log::ILogger pointer.
/// @param exception std::exception reference.
/// @param logMessage const char* as a message.
#define PONY_LOG_E_IF_GENERAL(condition, logger, exception, logMessage) \
	if constexpr (PONY_LOG_EXCEPTION_MASK != PonyEngine::Log::LogType::None) \
	{ \
		PONY_LOG_CONDITIONAL(condition, PonyEngine::Log::LogExceptionToLogger(*(logger), exception, logMessage)); \
	}

/// @brief Log macro that puts a message into a corresponding console output if it's enabled with the preprocessors; otherwise it's empty.
/// @details std::cout corresponds to Verbose, Debug and Info log types; std::clog corresponds to Warning log type; std::cerr corresponds to Error log type.
/// @param logType Log type.
/// @param message Message that can be put into a std::cout.
#define PONY_CONSOLE(logType, message) \
	if constexpr (((logType) & PONY_CONSOLE_LOG_MASK) != PonyEngine::Log::LogType::None) \
	{ \
		PonyEngine::Log::LogToConsole(logType, message); \
	}

/// @brief Log macro that conditionally puts a message into a corresponding console output if it's enabled with the preprocessors; otherwise it's empty.
/// @details std::cout corresponds to Verbose, Debug and Info log types; std::clog corresponds to Warning log type; std::cerr corresponds to Error log type.
/// @param condition Log condition.
/// @param logType Log type.
/// @param message Message that can be put into a std::cout.
#define PONY_CONSOLE_IF(condition, logType, message) \
	if constexpr (((logType) & PONY_CONSOLE_LOG_MASK) != PonyEngine::Log::LogType::None) \
	{ \
		PONY_LOG_CONDITIONAL(condition, PonyEngine::Log::LogToConsole(logType, message)); \
	}

/// @brief Log macro that puts an exception into a corresponding console output if it's enabled with the preprocessors; otherwise it's empty.
/// @details std::cout corresponds to Verbose, Debug and Info log types; std::clog corresponds to Warning log type; std::cerr corresponds to Error log type.
/// @param exception std::exception reference.
#define PONY_CONSOLE_E_S(exception) \
	if constexpr ((PONY_LOG_EXCEPTION_MASK & PONY_CONSOLE_LOG_MASK) != PonyEngine::Log::LogType::None) \
	{ \
		PonyEngine::Log::LogExceptionToConsole(exception); \
	}

/// @brief Log macro that conditionally puts an exception into a corresponding console output if it's enabled with the preprocessors; otherwise it's empty.
/// @details std::cout corresponds to Verbose, Debug and Info log types; std::clog corresponds to Warning log type; std::cerr corresponds to Error log type.
/// @param condition Log condition.
/// @param exception std::exception reference.
#define PONY_CONSOLE_E_S_IF(condition, exception) \
	if constexpr ((PONY_LOG_EXCEPTION_MASK & PONY_CONSOLE_LOG_MASK) != PonyEngine::Log::LogType::None) \
	{ \
		PONY_LOG_CONDITIONAL(condition, PonyEngine::Log::LogExceptionToConsole(exception)); \
	}


/// @brief Log macro that puts an exception and a message into a corresponding console output if it's enabled with the preprocessors; otherwise it's empty.
/// @details std::cout corresponds to Verbose, Debug and Info log types; std::clog corresponds to Warning log type; std::cerr corresponds to Error log type.
/// @param exception std::exception reference.
/// @param message Message that can be put into a std::cout.
#define PONY_CONSOLE_E(exception, message) \
	if constexpr ((PONY_LOG_EXCEPTION_MASK & PONY_CONSOLE_LOG_MASK) != PonyEngine::Log::LogType::None) \
	{ \
		PonyEngine::Log::LogExceptionToConsole(exception, message); \
	}

/// @brief Log macro that conditionally puts an exception and a message into a corresponding console output if it's enabled with the preprocessors; otherwise it's empty.
/// @details std::cout corresponds to Verbose, Debug and Info log types; std::clog corresponds to Warning log type; std::cerr corresponds to Error log type.
/// @param condition Log condition.
/// @param exception std::exception reference.
/// @param message Message that can be put into a std::cout.
#define PONY_CONSOLE_E_IF(condition, exception, message) \
	if constexpr ((PONY_LOG_EXCEPTION_MASK & PONY_CONSOLE_LOG_MASK) != PonyEngine::Log::LogType::None) \
	{ \
		PONY_LOG_CONDITIONAL(condition, PonyEngine::Log::LogExceptionToConsole(exception, message)); \
	}
