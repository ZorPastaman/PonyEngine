/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#pragma once

#if PONY_LOG_VERBOSE
#define PONY_LOG_VERBOSE_MASK PonyEngine::Debug::Log::LogType::Verbose
#else
#define PONY_LOG_VERBOSE_MASK PonyEngine::Debug::Log::LogType::None
#endif

#if PONY_LOG_DEBUG
#define PONY_LOG_DEBUG_MASK PonyEngine::Debug::Log::LogType::Debug
#else
#define PONY_LOG_DEBUG_MASK PonyEngine::Debug::Log::LogType::None
#endif

#if PONY_LOG_INFO
#define PONY_LOG_INFO_MASK PonyEngine::Debug::Log::LogType::Info
#else
#define PONY_LOG_INFO_MASK PonyEngine::Debug::Log::LogType::None
#endif

#if PONY_LOG_WARNING
#define PONY_LOG_WARNING_MASK PonyEngine::Debug::Log::LogType::Warning
#else
#define PONY_LOG_WARNING_MASK PonyEngine::Debug::Log::LogType::None
#endif

#if PONY_LOG_ERROR
#define PONY_LOG_ERROR_MASK PonyEngine::Debug::Log::LogType::Error
#else
#define PONY_LOG_ERROR_MASK PonyEngine::Debug::Log::LogType::None
#endif

#if PONY_LOG_EXCEPTION
#define PONY_LOG_EXCEPTION_MASK PonyEngine::Debug::Log::LogType::Exception
#else
#define PONY_LOG_EXCEPTION_MASK PonyEngine::Debug::Log::LogType::None
#endif

#define PONY_LOG_MASK (PONY_LOG_VERBOSE_MASK | PONY_LOG_DEBUG_MASK | PONY_LOG_INFO_MASK | PONY_LOG_WARNING_MASK | PONY_LOG_ERROR_MASK)

#define PONY_COUT_MASK (PONY_LOG_VERBOSE_MASK | PONY_LOG_DEBUG_MASK | PONY_LOG_INFO_MASK)
#define PONY_CLOG_MASK PONY_LOG_WARNING_MASK
#define PONY_CERR_MASK PONY_LOG_ERROR_MASK
#define PONY_CEXC_MASK PONY_LOG_EXCEPTION_MASK

/// @brief Log macro that calls the log function if it's enabled with the preprocessors; otherwise it's empty.
/// @param logger PonyEngine::Debug::Log::ILogger reference.
/// @param logType PonyEngine::Debug::Log::LogType value.
/// @param message const char* as a message.
#define PONY_LOG(logger, logType, message) \
{ \
	if constexpr ((logType & PONY_LOG_MASK) != PonyEngine::Debug::Log::LogType::None) \
	{ \
		logger.Log(logType, message); \
	} \
}

/// @brief Log macro that conditionally calls the log function if it's enabled with the preprocessors; otherwise it's empty.
/// @param condition Log condition.
/// @param logger PonyEngine::Debug::Log::ILogger reference.
/// @param logType PonyEngine::Debug::Log::LogType value.
/// @param message const char* as a message.
#define PONY_LOG_IF(condition, logger, logType, message) \
{ \
	if constexpr ((logType & PONY_LOG_MASK) != PonyEngine::Debug::Log::LogType::None) \
	{ \
		if (condition) \
		{ \
			logger.Log(logType, message); \
		} \
	} \
}

/// @brief Log exception macro that calls the log exception function if it's enabled with the preprocessors; otherwise it's empty.
/// @param logger PonyEngine::Debug::Log::ILogger reference.
/// @param exception std::exception reference.
/// @param message const char* as a message.
#define PONY_LOG_E(logger, exception, message) \
{ \
	if constexpr (PONY_LOG_EXCEPTION_MASK != PonyEngine::Debug::Log::LogType::None) \
	{ \
		logger.LogException(exception, message); \
	} \
}

/// @brief Log exception macro that conditionally calls the log exception function if it's enabled with the preprocessors; otherwise it's empty.
/// @param condition Log condition.
/// @param logger PonyEngine::Debug::Log::ILogger reference.
/// @param exception std::exception reference.
/// @param message const char* as a message.
#define PONY_LOG_E_IF(condition, logger, exception, message) \
{ \
	if constexpr (PONY_LOG_EXCEPTION_MASK != PonyEngine::Debug::Log::LogType::None) \
	{ \
		if (condition) \
		{ \
			logger.LogException(exception, message); \
		} \
	} \
}

// TODO: Add console preposition to turn off logging to a console

/// @brief Log macro that puts a message into a corresponding console output if it's enabled with the preprocessors; otherwise it's empty.
/// @details std::cout corresponds to Verbose, Debug and Info log types; std::clog corresponds to Warning log type; std::cerr corresponds to Error log type.
/// @param logType Log type.
/// @param message Message that can be put into a std::cout.
#define PONY_CONSOLE(logType, message) \
{ \
	if constexpr ((logType & PONY_COUT_MASK) != PonyEngine::Debug::Log::LogType::None) \
	{ \
		std::cout << message << std::endl; \
	} \
	else if constexpr ((logType & PONY_CLOG_MASK) != PonyEngine::Debug::Log::LogType::None) \
	{ \
		std::clog << message << std::endl; \
	} \
	else if constexpr ((logType & PONY_CERR_MASK) != PonyEngine::Debug::Log::LogType::None) \
	{ \
		std::cerr << message << std::endl; \
	} \
	else if constexpr ((logType & PONY_CEXC_MASK) != PonyEngine::Debug::Log::LogType::None) \
	{ \
		std::cerr << message << std::endl; \
	} \
}

/// @brief Log macro that conditionally puts a message into a corresponding console output if it's enabled with the preprocessors; otherwise it's empty.
/// @details std::cout corresponds to Verbose, Debug and Info log types; std::clog corresponds to Warning log type; std::cerr corresponds to Error log type.
/// @param condition Log condition.
/// @param logType Log type.
/// @param message Message that can be put into a std::cout.
#define PONY_CONSOLE_IF(condition, logType, message) \
{ \
	if constexpr ((logType & PONY_COUT_MASK) != PonyEngine::Debug::Log::LogType::None) \
	{ \
		if (condition) \
		{ \
			std::cout << message << std::endl; \
		} \
	} \
	else if constexpr ((logType & PONY_CLOG_MASK) != PonyEngine::Debug::Log::LogType::None) \
	{ \
		if (condition) \
		{ \
			std::clog << message << std::endl; \
		} \
	} \
	else if constexpr ((logType & PONY_CERR_MASK) != PonyEngine::Debug::Log::LogType::None) \
	{ \
		if (condition) \
		{ \
			std::cerr << message << std::endl; \
		} \
	} \
	else if constexpr ((logType & PONY_CEXC_MASK) != PonyEngine::Debug::Log::LogType::None) \
	{ \
		if (condition) \
		{ \
			std::cerr << message << std::endl; \
		} \
	} \
}
