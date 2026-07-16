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

export module PonyEngine.Log.Ext:ILoggerContext;

import std;

import PonyEngine.Application;
import PonyEngine.Log;

export namespace PonyEngine::Log
{
	/// @brief Logger context.
	class ILoggerContext
	{
		PONY_INTERFACE_BODY(ILoggerContext)

		/// @brief Gets the application.
		/// @return Application.
		/// @note Don't call the logger of the application.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual Application::IApplication& Application() noexcept = 0;
		/// @brief Gets the application.
		/// @return Application.
		/// @note Don't call the logger of the application.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual const Application::IApplication& Application() const noexcept = 0;
	};
}
