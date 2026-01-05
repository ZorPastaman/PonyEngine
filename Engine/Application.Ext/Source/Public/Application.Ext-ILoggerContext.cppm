/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Object/Body.h"

export module PonyEngine.Application.Ext:ILoggerContext;

import PonyEngine.Log;

import :IApplicationContext;

export namespace PonyEngine::Application
{
	/// @brief Logger context.
	class ILoggerContext
	{
		PONY_INTERFACE_BODY(ILoggerContext)

		/// @brief Gets the application context.
		/// @return Application.
		[[nodiscard("Pure function")]]
		virtual IApplicationContext& Application() noexcept = 0;
		/// @brief Gets the application context.
		/// @return Application.
		[[nodiscard("Pure function")]]
		virtual const IApplicationContext& Application() const noexcept = 0;

		/// @brief Logs to console.
		/// @param logType Log type.
		/// @param message Log message.
		virtual void LogToConsole(Log::LogType logType, std::string_view message) const noexcept = 0;
	};
}
