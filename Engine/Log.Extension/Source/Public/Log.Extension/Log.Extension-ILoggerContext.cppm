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

export module PonyEngine.Log.Extension:ILoggerContext;

import PonyEngine.Application.Extension;
import PonyEngine.Log;

export namespace PonyEngine::Log
{
	/// @brief Logger context.
	class ILoggerContext
	{
		INTERFACE_BODY(ILoggerContext)

		/// @brief Gets the application context.
		/// @return Application context.
		[[nodiscard("Pure function")]]
		virtual Application::IApplicationContext& Application() noexcept = 0;
		/// @brief Gets the application context.
		/// @return Application context.
		[[nodiscard("Pure function")]]
		virtual const Application::IApplicationContext& Application() const noexcept = 0;

		/// @brief Logs to console.
		/// @param logType Log type.
		/// @param message Log message.
		virtual void LogToConsole(LogType logType, std::string_view message) const noexcept = 0;
	};
}
