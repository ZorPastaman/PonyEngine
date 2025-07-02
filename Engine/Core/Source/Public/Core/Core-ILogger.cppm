/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Utility/ObjectBody.h"

export module PonyEngine.Core:ILogger;

import std;

import PonyEngine.Log;

export namespace PonyEngine::Core
{
	/// @brief Application logger.
	class ILogger
	{
		INTERFACE_BODY(ILogger)

		/// @brief Gets a public logger.
		/// @return Public logger.
		/// @remark The function must return the same reference each time it is called.
		[[nodiscard("Pure function")]]
		virtual Log::ILogger& PublicLogger() noexcept = 0;
		/// @brief Gets a public logger.
		/// @return Public logger.
		/// @remark The function must return the same reference each time it is called.
		[[nodiscard("Pure function")]]
		virtual const Log::ILogger& PublicLogger() const noexcept = 0;

		/// @brief Logs the message.
		/// @param logType Log type.
		/// @param logInput Log input.
		virtual void Log(Log::LogType logType, const Log::LogInput& logInput) const noexcept = 0;
		/// @brief Logs the exception.
		/// @param exception Exception to log.
		/// @param logInput Log input.
		virtual void Log(const std::exception& exception, const Log::LogInput& logInput) const noexcept = 0;
	};
}
