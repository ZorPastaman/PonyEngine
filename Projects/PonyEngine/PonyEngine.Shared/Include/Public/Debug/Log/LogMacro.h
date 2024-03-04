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

/// @brief Log macro that calls the log function if it's enabled with the preprocessors; otherwise it's empty.
/// @param logger PonyEngine::Debug::Log::ILogger reference.
/// @param logType PonyEngine::Debug::Log::LogType value.
/// @param message std::string reference as a message.
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
/// @param message std::string reference as a message.
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

/// @brief Log macro that calls the log function if it's enabled with the preprocessors; otherwise it's empty.
/// @param logger PonyEngine::Debug::Log::ILogger pointer.
/// @param logType PonyEngine::Debug::Log::LogType value.
/// @param message std::string reference as a message.
#define PONY_LOG_PTR(logger, logType, message) \
{ \
	if constexpr ((logType & PONY_LOG_MASK) != PonyEngine::Debug::Log::LogType::None) \
	{ \
		logger->Log(logType, message); \
	} \
}

/// @brief Log macro that conditionally calls the log function if it's enabled with the preprocessors; otherwise it's empty.
/// @param condition Log condition.
/// @param logger PonyEngine::Debug::Log::ILogger pointer.
/// @param logType PonyEngine::Debug::Log::LogType value.
/// @param message std::string reference as a message.
#define PONY_LOG_PTR_IF(condition, logger, logType, message) \
{ \
	if constexpr ((logType & PONY_LOG_MASK) != PonyEngine::Debug::Log::LogType::None) \
	{ \
		if (condition) \
		{ \
			logger->Log(logType, message); \
		} \
	} \
}

/// @brief Log exception macro that calls the log exception function if it's enabled with the preprocessors; otherwise it's empty.
/// @param logger PonyEngine::Debug::Log::ILogger reference.
/// @param exception std::exception reference.
/// @param message std::string reference as a message.
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
/// @param message std::string reference as a message.
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

/// @brief Log exception macro that calls the log exception function if it's enabled with the preprocessors; otherwise it's empty.
/// @param logger PonyEngine::Debug::Log::ILogger pointer.
/// @param exception std::exception reference.
/// @param message std::string reference as a message.
#define PONY_LOG_E_PTR(logger, exception, message) \
{ \
	if constexpr (PONY_LOG_EXCEPTION_MASK != PonyEngine::Debug::Log::LogType::None) \
	{ \
		logger->LogException(exception, message); \
	} \
}

/// @brief Log exception macro that conditionally calls the log exception function if it's enabled with the preprocessors; otherwise it's empty.
/// @param condition Log condition.
/// @param logger PonyEngine::Debug::Log::ILogger pointer.
/// @param exception std::exception reference.
/// @param message std::string reference as a message.
#define PONY_LOG_E_PTR_IF(condition, logger, exception, message) \
{ \
	if constexpr (PONY_LOG_EXCEPTION_MASK != PonyEngine::Debug::Log::LogType::None) \
	{ \
		if (condition) \
		{ \
			logger->LogException(exception, message); \
		} \
	} \
}

/// @brief Logs to std::cout if the info log is enabled with the preprocessor.
/// @param message Log message.
#define PONY_COUT(message) \
{ \
	if constexpr (PONY_LOG_INFO_MASK != PonyEngine::Debug::Log::LogType::None) \
	{ \
		std::cout << message << std::endl; \
	} \
}

/// @brief Logs conditionally to std::cout if the info log is enabled with the preprocessor.
/// @param condition Condition.
/// @param message Log message.
#define PONY_COUT_IF(condition, message) \
{ \
	if constexpr (PONY_LOG_INFO_MASK != PonyEngine::Debug::Log::LogType::None) \
	{ \
		if (condition) \
		{ \
			std::cout << message << std::endl; \
		} \
	} \
}

/// @brief Logs to std::clog if the warning log is enabled with the preprocessor.
/// @param message Log message.
#define PONY_CLOG(message) \
{ \
	if constexpr (PONY_LOG_WARNING_MASK != PonyEngine::Debug::Log::LogType::None) \
	{ \
		std::clog << message << std::endl; \
	} \
}

/// @brief Logs conditionally to std::clog if the info log is enabled with the preprocessor.
/// @param condition Condition.
/// @param message Log message.
#define PONY_CLOG_IF(condition, message) \
{ \
	if constexpr (PONY_LOG_WARNING_MASK != PonyEngine::Debug::Log::LogType::None) \
	{ \
		if (condition) \
		{ \
			std::clog << message << std::endl; \
		} \
	} \
}

/// @brief Logs to std::cerr if the error log is enabled with the preprocessor.
/// @param message Log message.
#define PONY_CERR(message) \
{ \
	if constexpr (PONY_LOG_ERROR_MASK != PonyEngine::Debug::Log::LogType::None) \
	{ \
		std::cerr << message << std::endl; \
	} \
}

/// @brief Logs conditionally to std::cerr if the info log is enabled with the preprocessor.
/// @param condition Condition.
/// @param message Log message.
#define PONY_CERR_IF(condition, message) \
{ \
	if constexpr (PONY_LOG_ERROR_MASK != PonyEngine::Debug::Log::LogType::None) \
	{ \
		if (condition) \
		{ \
			std::cerr << message << std::endl; \
		} \
	} \
}

/// @brief Logs to std::cerr if the exception log is enabled with the preprocessor.
/// @param exception Exception.
/// @param message Log message.
#define PONY_CEXC(exception, message) \
{ \
	if constexpr (PONY_LOG_EXCEPTION_MASK != PonyEngine::Debug::Log::LogType::None) \
	{ \
		std::cerr << exception.what() << " - " << message << std::endl; \
	} \
}

/// @brief Logs conditionally to std::cerr if the exception log is enabled with the preprocessor.
/// @param condition Condition.
/// @param exception Exception.
/// @param message Log message.
#define PONY_CEXC_IF(condition, exception, message) \
{ \
	if constexpr (PONY_LOG_EXCEPTION_MASK != PonyEngine::Debug::Log::LogType::None) \
	{ \
		if (condition) \
		{ \
			std::cerr << exception.what() << " - " << message << std::endl; \
		} \
	} \
}
