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

#if PONY_CONSOLE_LOG
#define PONY_CONSOLE_LOG_MASK PonyEngine::Debug::Log::LogType::All
#else
#define PONY_CONSOLE_LOG_MASK PonyEngine::Debug::Log::LogType::None
#endif

#define PONY_COUT_MASK ((PONY_LOG_VERBOSE_MASK | PONY_LOG_DEBUG_MASK | PONY_LOG_INFO_MASK) & PONY_CONSOLE_LOG_MASK)
#define PONY_CLOG_MASK (PONY_LOG_WARNING_MASK & PONY_CONSOLE_LOG_MASK)
#define PONY_CERR_MASK (PONY_LOG_ERROR_MASK & PONY_CONSOLE_LOG_MASK)
#define PONY_CEXC_MASK (PONY_LOG_EXCEPTION_MASK & PONY_CONSOLE_LOG_MASK)

/// @brief Log macro that calls the log function if it's enabled with the preprocessors; otherwise it's empty.
/// @param engine PonyEngine::Core::IEngine reference.
/// @param logType PonyEngine::Debug::Log::LogType value.
/// @param message const char* as a message.
#define PONY_LOG(engine, logType, message) \
{ \
	if constexpr ((logType & PONY_LOG_MASK) != PonyEngine::Debug::Log::LogType::None) \
	{ \
		engine.GetLogger().Log(logType, PonyEngine::Debug::Log::LogInput(message, engine.GetFrameCount())); \
	} \
}

/// @brief Log macro that calls the log function if it's enabled with the preprocessors; otherwise it's empty.
/// @param engine PonyEngine::Core::IEngine pointer.
/// @param logType PonyEngine::Debug::Log::LogType value.
/// @param message const char* as a message.
#define PONY_LOG_PTR(engine, logType, message) \
{ \
	if constexpr ((logType & PONY_LOG_MASK) != PonyEngine::Debug::Log::LogType::None) \
	{ \
		engine->GetLogger().Log(logType, PonyEngine::Debug::Log::LogInput(message, engine->GetFrameCount())); \
	} \
}

/// @brief Log macro that calls the log function if it's enabled with the preprocessors; otherwise it's empty.
/// @param logger PonyEngine::Debug::Log::ILogger reference.
/// @param logType PonyEngine::Debug::Log::LogType value.
/// @param message const char* as a message.
#define PONY_LOG_GENERAL(logger, logType, message) \
{ \
	if constexpr ((logType & PONY_LOG_MASK) != PonyEngine::Debug::Log::LogType::None) \
	{ \
		logger.Log(logType, PonyEngine::Debug::Log::LogInput(message, 0)); \
	} \
}

/// @brief Log macro that conditionally calls the log function if it's enabled with the preprocessors; otherwise it's empty.
/// @param condition Log condition.
/// @param engine PonyEngine::Core::IEngine reference.
/// @param logType PonyEngine::Debug::Log::LogType value.
/// @param message const char* as a message.
#define PONY_LOG_IF(condition, engine, logType, message) \
{ \
	if constexpr ((logType & PONY_LOG_MASK) != PonyEngine::Debug::Log::LogType::None) \
	{ \
		if (condition) \
		{ \
			engine.GetLogger().Log(logType, PonyEngine::Debug::Log::LogInput(message, engine.GetFrameCount())); \
		} \
	} \
}

/// @brief Log macro that conditionally calls the log function if it's enabled with the preprocessors; otherwise it's empty.
/// @param condition Log condition.
/// @param engine PonyEngine::Core::IEngine pointer.
/// @param logType PonyEngine::Debug::Log::LogType value.
/// @param message const char* as a message.
#define PONY_LOG_IF_PTR(condition, engine, logType, message) \
{ \
	if constexpr ((logType & PONY_LOG_MASK) != PonyEngine::Debug::Log::LogType::None) \
	{ \
		if (condition) \
		{ \
			engine->GetLogger().Log(logType, PonyEngine::Debug::Log::LogInput(message, engine->GetFrameCount())); \
		} \
	} \
}

/// @brief Log macro that conditionally calls the log function if it's enabled with the preprocessors; otherwise it's empty.
/// @param condition Log condition.
/// @param logger PonyEngine::Debug::Log::ILogger reference.
/// @param logType PonyEngine::Debug::Log::LogType value.
/// @param message const char* as a message.
#define PONY_LOG_IF_GENERAL(condition, logger, logType, message) \
{ \
	if constexpr ((logType & PONY_LOG_MASK) != PonyEngine::Debug::Log::LogType::None) \
	{ \
		if (condition) \
		{ \
			logger.Log(logType, PonyEngine::Debug::Log::LogInput(message, 0)); \
		} \
	} \
}

/// @brief Log exception macro that calls the log exception function if it's enabled with the preprocessors; otherwise it's empty.
/// @param engine PonyEngine::Core::IEngine reference.
/// @param exception std::exception reference.
/// @param message const char* as a message.
#define PONY_LOG_E(engine, exception, message) \
{ \
	if constexpr (PONY_LOG_EXCEPTION_MASK != PonyEngine::Debug::Log::LogType::None) \
	{ \
		engine.GetLogger().LogException(exception, PonyEngine::Debug::Log::LogInput(message, engine.GetFrameCount())); \
	} \
}

/// @brief Log exception macro that calls the log exception function if it's enabled with the preprocessors; otherwise it's empty.
/// @param engine PonyEngine::Core::IEngine pointer.
/// @param exception std::exception reference.
/// @param message const char* as a message.
#define PONY_LOG_E_PTR(engine, exception, message) \
{ \
	if constexpr (PONY_LOG_EXCEPTION_MASK != PonyEngine::Debug::Log::LogType::None) \
	{ \
		engine->GetLogger().LogException(exception, PonyEngine::Debug::Log::LogInput(message, engine->GetFrameCount())); \
	} \
}

/// @brief Log exception macro that calls the log exception function if it's enabled with the preprocessors; otherwise it's empty.
/// @param logger PonyEngine::Debug::Log::ILogger reference.
/// @param exception std::exception reference.
/// @param message const char* as a message.
#define PONY_LOG_E_GENERAL(logger, exception, message) \
{ \
	if constexpr (PONY_LOG_EXCEPTION_MASK != PonyEngine::Debug::Log::LogType::None) \
	{ \
		logger.LogException(exception, PonyEngine::Debug::Log::LogInput(message, 0)); \
	} \
}

/// @brief Log exception macro that conditionally calls the log exception function if it's enabled with the preprocessors; otherwise it's empty.
/// @param condition Log condition.
/// @param engine PonyEngine::Core::IEngine reference.
/// @param exception std::exception reference.
/// @param message const char* as a message.
#define PONY_LOG_E_IF(condition, engine, exception, message) \
{ \
	if constexpr (PONY_LOG_EXCEPTION_MASK != PonyEngine::Debug::Log::LogType::None) \
	{ \
		if (condition) \
		{ \
			engine.GetLogger().LogException(exception, PonyEngine::Debug::Log::LogInput(message, engine.GetFrameCount())); \
		} \
	} \
}

/// @brief Log exception macro that conditionally calls the log exception function if it's enabled with the preprocessors; otherwise it's empty.
/// @param condition Log condition.
/// @param engine PonyEngine::Core::IEngine pointer.
/// @param exception std::exception reference.
/// @param message const char* as a message.
#define PONY_LOG_E_IF_PTR(condition, engine, exception, message) \
{ \
	if constexpr (PONY_LOG_EXCEPTION_MASK != PonyEngine::Debug::Log::LogType::None) \
	{ \
		if (condition) \
		{ \
			engine->GetLogger().LogException(exception, PonyEngine::Debug::Log::LogInput(message, engine->GetFrameCount())); \
		} \
	} \
}

/// @brief Log exception macro that conditionally calls the log exception function if it's enabled with the preprocessors; otherwise it's empty.
/// @param condition Log condition.
/// @param logger PonyEngine::Debug::Log::ILogger reference.
/// @param exception std::exception reference.
/// @param message const char* as a message.
#define PONY_LOG_E_IF_GENERAL(condition, logger, exception, message) \
{ \
	if constexpr (PONY_LOG_EXCEPTION_MASK != PonyEngine::Debug::Log::LogType::None) \
	{ \
		if (condition) \
		{ \
			logger.LogException(exception, PonyEngine::Debug::Log::LogInput(message, 0)); \
		} \
	} \
}

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
