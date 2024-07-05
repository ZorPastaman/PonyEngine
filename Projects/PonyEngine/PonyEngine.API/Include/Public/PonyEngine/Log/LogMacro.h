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
#define PONY_LOG_VERBOSE_MASK PonyEngine::Log::LogType::Verbose
#else
#define PONY_LOG_VERBOSE_MASK PonyEngine::Log::LogType::None
#endif

#if PONY_LOG_DEBUG
#define PONY_LOG_DEBUG_MASK PonyEngine::Log::LogType::Debug
#else
#define PONY_LOG_DEBUG_MASK PonyEngine::Log::LogType::None
#endif

#if PONY_LOG_INFO
#define PONY_LOG_INFO_MASK PonyEngine::Log::LogType::Info
#else
#define PONY_LOG_INFO_MASK PonyEngine::Log::LogType::None
#endif

#if PONY_LOG_WARNING
#define PONY_LOG_WARNING_MASK PonyEngine::Log::LogType::Warning
#else
#define PONY_LOG_WARNING_MASK PonyEngine::Log::LogType::None
#endif

#if PONY_LOG_ERROR
#define PONY_LOG_ERROR_MASK PonyEngine::Log::LogType::Error
#else
#define PONY_LOG_ERROR_MASK PonyEngine::Log::LogType::None
#endif

#if PONY_LOG_EXCEPTION
#define PONY_LOG_EXCEPTION_MASK PonyEngine::Log::LogType::Exception
#else
#define PONY_LOG_EXCEPTION_MASK PonyEngine::Log::LogType::None
#endif

#define PONY_LOG_MASK (PONY_LOG_VERBOSE_MASK | PONY_LOG_DEBUG_MASK | PONY_LOG_INFO_MASK | PONY_LOG_WARNING_MASK | PONY_LOG_ERROR_MASK)

#if PONY_CONSOLE_LOG
#define PONY_CONSOLE_LOG_MASK PonyEngine::Log::LogType::All
#else
#define PONY_CONSOLE_LOG_MASK PonyEngine::Log::LogType::None
#endif

#define PONY_COUT_MASK ((PONY_LOG_VERBOSE_MASK | PONY_LOG_DEBUG_MASK | PONY_LOG_INFO_MASK) & PONY_CONSOLE_LOG_MASK)
#define PONY_CLOG_MASK (PONY_LOG_WARNING_MASK & PONY_CONSOLE_LOG_MASK)
#define PONY_CERR_MASK (PONY_LOG_ERROR_MASK & PONY_CONSOLE_LOG_MASK)
#define PONY_CEXC_MASK (PONY_LOG_EXCEPTION_MASK & PONY_CONSOLE_LOG_MASK)

#if PONY_TERMINATE_ON_LOG_EXCEPTION
#define PONY_ON_LOG_EXCEPTION_ACTION std::terminate()
#else
#define PONY_ON_LOG_EXCEPTION_ACTION
#endif

#define PONY_LOG_TRY_CATCH(expression) \
	try \
	{ \
		expression; \
	} \
	catch (...) \
	{ \
		PONY_ON_LOG_EXCEPTION_ACTION; \
	}

#define PONY_LOG_CONDITIONAL(condition, expression) \
	if (condition) \
	{ \
		expression; \
	}

/// @brief Log macro that calls the log function if it's enabled with the preprocessors; otherwise it's empty.
/// @param engine PonyEngine::Core::IEngine pointer.
/// @param logType PonyEngine::Log::LogType value.
/// @param message const char* as a message.
#define PONY_LOG(engine, logType, message) \
	if constexpr (((logType) & PONY_LOG_MASK) != PonyEngine::Log::LogType::None) \
	{ \
		PONY_LOG_TRY_CATCH((engine)->GetLogger().Log(logType, PonyEngine::Log::LogInput(message, (engine)->GetTimeManager().GetFrameCount()))); \
	}

/// @brief Log macro that calls the log function if it's enabled with the preprocessors; otherwise it's empty.
/// @param engine PonyEngine::Core::IEngine reference.
/// @param logType PonyEngine::Log::LogType value.
/// @param message const char* as a message.
#define PONY_LOG_REF(engine, logType, message) \
	if constexpr (((logType) & PONY_LOG_MASK) != PonyEngine::Log::LogType::None) \
	{ \
		PONY_LOG_TRY_CATCH((engine).GetLogger().Log(logType, PonyEngine::Log::LogInput(message, (engine).GetTimeManager().GetFrameCount()))); \
	}

/// @brief Log macro that calls the log function if it's enabled with the preprocessors; otherwise it's empty.
/// @param logger PonyEngine::Log::ILogger reference.
/// @param logType PonyEngine::Log::LogType value.
/// @param message const char* as a message.
#define PONY_LOG_GENERAL(logger, logType, message) \
	if constexpr (((logType) & PONY_LOG_MASK) != PonyEngine::Log::LogType::None) \
	{ \
		PONY_LOG_TRY_CATCH((logger).Log(logType, PonyEngine::Log::LogInput(message, 0))); \
	}

/// @brief Log macro that calls the log function if it's enabled with the preprocessors; otherwise it's empty.
/// @param logger PonyEngine::Log::ILogger pointer.
/// @param logType PonyEngine::Log::LogType value.
/// @param message const char* as a message.
#define PONY_LOG_GENERAL_PTR(logger, logType, message) \
	if constexpr (((logType) & PONY_LOG_MASK) != PonyEngine::Log::LogType::None) \
	{ \
		PONY_LOG_TRY_CATCH((logger)->Log(logType, PonyEngine::Log::LogInput(message, 0))); \
	}

/// @brief Log macro that conditionally calls the log function if it's enabled with the preprocessors; otherwise it's empty.
/// @param condition Log condition.
/// @param engine PonyEngine::Core::IEngine pointer.
/// @param logType PonyEngine::Log::LogType value.
/// @param message const char* as a message.
#define PONY_LOG_IF(condition, engine, logType, message) \
	if constexpr (((logType) & PONY_LOG_MASK) != PonyEngine::Log::LogType::None) \
	{ \
		PONY_LOG_TRY_CATCH(PONY_LOG_CONDITIONAL(condition, (engine)->GetLogger().Log(logType, PonyEngine::Log::LogInput(message, (engine)->GetTimeManager().GetFrameCount())))); \
	}

/// @brief Log macro that conditionally calls the log function if it's enabled with the preprocessors; otherwise it's empty.
/// @param condition Log condition.
/// @param engine PonyEngine::Core::IEngine reference.
/// @param logType PonyEngine::Log::LogType value.
/// @param message const char* as a message.
#define PONY_LOG_IF_REF(condition, engine, logType, message) \
	if constexpr (((logType) & PONY_LOG_MASK) != PonyEngine::Log::LogType::None) \
	{ \
		PONY_LOG_TRY_CATCH(PONY_LOG_CONDITIONAL(condition, (engine).GetLogger().Log(logType, PonyEngine::Log::LogInput(message, (engine).GetTimeManager().GetFrameCount())))); \
	}

/// @brief Log macro that conditionally calls the log function if it's enabled with the preprocessors; otherwise it's empty.
/// @param condition Log condition.
/// @param logger PonyEngine::Log::ILogger reference.
/// @param logType PonyEngine::Log::LogType value.
/// @param message const char* as a message.
#define PONY_LOG_IF_GENERAL(condition, logger, logType, message) \
	if constexpr (((logType) & PONY_LOG_MASK) != PonyEngine::Log::LogType::None) \
	{ \
		PONY_LOG_TRY_CATCH(PONY_LOG_CONDITIONAL(condition, (logger).Log(logType, PonyEngine::Log::LogInput(message, 0)))); \
	}

/// @brief Log macro that conditionally calls the log function if it's enabled with the preprocessors; otherwise it's empty.
/// @param condition Log condition.
/// @param logger PonyEngine::Log::ILogger pointer.
/// @param logType PonyEngine::Log::LogType value.
/// @param message const char* as a message.
#define PONY_LOG_IF_GENERAL_PTR(condition, logger, logType, message) \
	if constexpr (((logType) & PONY_LOG_MASK) != PonyEngine::Log::LogType::None) \
	{ \
		PONY_LOG_TRY_CATCH(PONY_LOG_CONDITIONAL(condition, (logger)->Log(logType, PonyEngine::Log::LogInput(message, 0)))); \
	}

/// @brief Log exception macro that calls the log exception function if it's enabled with the preprocessors; otherwise it's empty.
/// @param engine PonyEngine::Core::IEngine pointer.
/// @param exception std::exception reference.
/// @param message const char* as a message.
#define PONY_LOG_E(engine, exception, message) \
	if constexpr (PONY_LOG_EXCEPTION_MASK != PonyEngine::Log::LogType::None) \
	{ \
		PONY_LOG_TRY_CATCH((engine)->GetLogger().LogException(exception, PonyEngine::Log::LogInput(message, (engine)->GetTimeManager().GetFrameCount()))); \
	}

/// @brief Log exception macro that calls the log exception function if it's enabled with the preprocessors; otherwise it's empty.
/// @param engine PonyEngine::Core::IEngine reference.
/// @param exception std::exception reference.
/// @param message const char* as a message.
#define PONY_LOG_E_REF(engine, exception, message) \
	if constexpr (PONY_LOG_EXCEPTION_MASK != PonyEngine::Log::LogType::None) \
	{ \
		PONY_LOG_TRY_CATCH((engine).GetLogger().LogException(exception, PonyEngine::Log::LogInput(message, (engine).GetTimeManager().GetFrameCount()))); \
	}

/// @brief Log exception macro that calls the log exception function if it's enabled with the preprocessors; otherwise it's empty.
/// @param logger PonyEngine::Log::ILogger reference.
/// @param exception std::exception reference.
/// @param message const char* as a message.
#define PONY_LOG_E_GENERAL(logger, exception, message) \
	if constexpr (PONY_LOG_EXCEPTION_MASK != PonyEngine::Log::LogType::None) \
	{ \
		PONY_LOG_TRY_CATCH((logger).LogException(exception, PonyEngine::Log::LogInput(message, 0))); \
	}

/// @brief Log exception macro that calls the log exception function if it's enabled with the preprocessors; otherwise it's empty.
/// @param logger PonyEngine::Log::ILogger pointer.
/// @param exception std::exception reference.
/// @param message const char* as a message.
#define PONY_LOG_E_GENERAL_PTR(logger, exception, message) \
	if constexpr (PONY_LOG_EXCEPTION_MASK != PonyEngine::Log::LogType::None) \
	{ \
		PONY_LOG_TRY_CATCH((logger)->LogException(exception, PonyEngine::Log::LogInput(message, 0))); \
	}

/// @brief Log exception macro that conditionally calls the log exception function if it's enabled with the preprocessors; otherwise it's empty.
/// @param condition Log condition.
/// @param engine PonyEngine::Core::IEngine pointer.
/// @param exception std::exception reference.
/// @param message const char* as a message.
#define PONY_LOG_E_IF(condition, engine, exception, message) \
	if constexpr (PONY_LOG_EXCEPTION_MASK != PonyEngine::Log::LogType::None) \
	{ \
		PONY_LOG_TRY_CATCH(PONY_LOG_CONDITIONAL(condition, (engine).GetLogger().LogException(exception, PonyEngine::Log::LogInput(message, (engine).GetTimeManager().GetFrameCount())))); \
	}

/// @brief Log exception macro that conditionally calls the log exception function if it's enabled with the preprocessors; otherwise it's empty.
/// @param condition Log condition.
/// @param engine PonyEngine::Core::IEngine reference.
/// @param exception std::exception reference.
/// @param message const char* as a message.
#define PONY_LOG_E_IF_REF(condition, engine, exception, message) \
	if constexpr (PONY_LOG_EXCEPTION_MASK != PonyEngine::Log::LogType::None) \
	{ \
		PONY_LOG_TRY_CATCH(PONY_LOG_CONDITIONAL(condition, (engine).GetLogger().LogException(exception, (engine)->GetLogger().LogException(exception, PonyEngine::Log::LogInput(message, (engine)->GetTimeManager().GetFrameCount())))); \
	}

/// @brief Log exception macro that conditionally calls the log exception function if it's enabled with the preprocessors; otherwise it's empty.
/// @param condition Log condition.
/// @param logger PonyEngine::Log::ILogger reference.
/// @param exception std::exception reference.
/// @param message const char* as a message.
#define PONY_LOG_E_IF_GENERAL(condition, logger, exception, message) \
	if constexpr (PONY_LOG_EXCEPTION_MASK != PonyEngine::Log::LogType::None) \
	{ \
		PONY_LOG_TRY_CATCH(PONY_LOG_CONDITIONAL(condition, (logger).LogException(exception, PonyEngine::Log::LogInput(message, 0)))); \
	}

/// @brief Log exception macro that conditionally calls the log exception function if it's enabled with the preprocessors; otherwise it's empty.
/// @param condition Log condition.
/// @param logger PonyEngine::Log::ILogger pointer.
/// @param exception std::exception reference.
/// @param message const char* as a message.
#define PONY_LOG_E_IF_GENERAL_PTR(condition, logger, exception, message) \
	if constexpr (PONY_LOG_EXCEPTION_MASK != PonyEngine::Log::LogType::None) \
	{ \
		PONY_LOG_TRY_CATCH(PONY_LOG_CONDITIONAL(condition, (logger)->LogException(exception, PonyEngine::Log::LogInput(message, 0)))); \
	}

/// @brief Log macro that puts a message into a corresponding console output if it's enabled with the preprocessors; otherwise it's empty.
/// @details std::cout corresponds to Verbose, Debug and Info log types; std::clog corresponds to Warning log type; std::cerr corresponds to Error log type.
/// @param logType Log type.
/// @param message Message that can be put into a std::cout.
#define PONY_CONSOLE(logType, message) \
	if constexpr (((logType) & PONY_COUT_MASK) != PonyEngine::Log::LogType::None) \
	{ \
		PONY_LOG_TRY_CATCH(std::cout << (message) << std::endl); \
	} \
	else if constexpr (((logType) & PONY_CLOG_MASK) != PonyEngine::Log::LogType::None) \
	{ \
		PONY_LOG_TRY_CATCH(std::clog << (message) << std::endl); \
	} \
	else if constexpr (((logType) & PONY_CERR_MASK) != PonyEngine::Log::LogType::None) \
	{ \
		PONY_LOG_TRY_CATCH(std::cerr << (message) << std::endl); \
	} \
	else if constexpr (((logType) & PONY_CEXC_MASK) != PonyEngine::Log::LogType::None) \
	{ \
		PONY_LOG_TRY_CATCH(std::cerr << (message) << std::endl); \
	}

/// @brief Log macro that conditionally puts a message into a corresponding console output if it's enabled with the preprocessors; otherwise it's empty.
/// @details std::cout corresponds to Verbose, Debug and Info log types; std::clog corresponds to Warning log type; std::cerr corresponds to Error log type.
/// @param condition Log condition.
/// @param logType Log type.
/// @param message Message that can be put into a std::cout.
#define PONY_CONSOLE_IF(condition, logType, message) \
	if constexpr (((logType) & PONY_COUT_MASK) != PonyEngine::Log::LogType::None) \
	{ \
		PONY_LOG_TRY_CATCH(PONY_LOG_CONDITIONAL(condition, std::cout << (message) << std::endl)); \
	} \
	else if constexpr (((logType) & PONY_CLOG_MASK) != PonyEngine::Log::LogType::None) \
	{ \
		PONY_LOG_TRY_CATCH(PONY_LOG_CONDITIONAL(condition, std::clog << (message) << std::endl)); \
	} \
	else if constexpr (((logType) & PONY_CERR_MASK) != PonyEngine::Log::LogType::None) \
	{ \
		PONY_LOG_TRY_CATCH(PONY_LOG_CONDITIONAL(condition, std::cerr << (message) << std::endl)); \
	} \
	else if constexpr (((logType) & PONY_CEXC_MASK) != PonyEngine::Log::LogType::None) \
	{ \
		PONY_LOG_TRY_CATCH(PONY_LOG_CONDITIONAL(condition, std::cerr << (message) << std::endl)); \
	}
