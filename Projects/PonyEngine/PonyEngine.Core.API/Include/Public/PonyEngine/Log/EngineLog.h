/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#pragma once

#include "PonyEngine/Log/Log.h"

/// @brief Log macro that calls the log function if it's enabled with the preprocessors; otherwise it's empty.
/// @param engine PonyEngine::Core::IEngine pointer.
/// @param logType PonyEngine::Log::LogType value.
/// @param logMessage const char* as a message.
#define PONY_LOG(engine, logType, logMessage) \
	if constexpr (((logType) & PONY_LOG_MASK) != PonyEngine::Log::LogType::None) \
	{ \
		PONY_LOG_TRY_CATCH((engine)->GetLogger().Log(logType, PonyEngine::Log::LogInput{.message = (logMessage), .frameCount = (engine)->GetTimeManager().GetFrameCount()})); \
	}

/// @brief Log macro that conditionally calls the log function if it's enabled with the preprocessors; otherwise it's empty.
/// @param condition Log condition.
/// @param engine PonyEngine::Core::IEngine pointer.
/// @param logType PonyEngine::Log::LogType value.
/// @param logMessage const char* as a message.
#define PONY_LOG_IF(condition, engine, logType, logMessage) \
	if constexpr (((logType) & PONY_LOG_MASK) != PonyEngine::Log::LogType::None) \
	{ \
		PONY_LOG_TRY_CATCH(PONY_LOG_CONDITIONAL(condition, (engine)->GetLogger().Log(logType, PonyEngine::Log::LogInput{.message = (logMessage), .frameCount = (engine)->GetTimeManager().GetFrameCount()}))); \
	}

/// @brief Log exception macro that calls the log exception function if it's enabled with the preprocessors; otherwise it's empty.
/// @param engine PonyEngine::Core::IEngine pointer.
/// @param exception std::exception reference.
/// @param logMessage const char* as a message.
#define PONY_LOG_E(engine, exception, logMessage) \
	if constexpr (PONY_LOG_EXCEPTION_MASK != PonyEngine::Log::LogType::None) \
	{ \
		PONY_LOG_TRY_CATCH((engine)->GetLogger().LogException(exception, PonyEngine::Log::LogInput{.message = (logMessage), .frameCount = (engine)->GetTimeManager().GetFrameCount()})); \
	}

/// @brief Log exception macro that conditionally calls the log exception function if it's enabled with the preprocessors; otherwise it's empty.
/// @param condition Log condition.
/// @param engine PonyEngine::Core::IEngine pointer.
/// @param exception std::exception reference.
/// @param logMessage const char* as a message.
#define PONY_LOG_E_IF(condition, engine, exception, logMessage) \
	if constexpr (PONY_LOG_EXCEPTION_MASK != PonyEngine::Log::LogType::None) \
	{ \
		PONY_LOG_TRY_CATCH(PONY_LOG_CONDITIONAL(condition, (engine)->GetLogger().LogException(exception, PonyEngine::Log::LogInput{.message = (logMessage), .frameCount = (engine)->GetTimeManager().GetFrameCount()}))); \
	}
