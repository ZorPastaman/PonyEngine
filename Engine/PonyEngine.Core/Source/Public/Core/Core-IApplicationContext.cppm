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

export module PonyEngine.Core:IApplicationContext;

import PonyEngine.Log;

import :ApplicationPaths;
import :IEngine;

export namespace PonyEngine::Core
{
	/// @brief Application context. It exists for the whole life of an application.
	class IApplicationContext
	{
		INTERFACE_BODY(IApplicationContext)

		/// @brief Gets the logger.
		/// @return Logger.
		[[nodiscard("Pure function")]]
		virtual Log::ILogger& Logger() noexcept = 0;
		/// @brief Gets the logger.
		/// @return Logger.
		[[nodiscard("Pure function")]]
		virtual const Log::ILogger& Logger() const noexcept = 0;

		/// @brief Gets the engine.
		/// @return Engine. It's nullptr before the engine module phase, and non-nullptr after it.
		[[nodiscard("Pure function")]]
		virtual const IEngine* Engine() const noexcept = 0;

		/// @brief Gets the application paths.
		/// @return Application paths.
		[[nodiscard("Pure function")]]
		virtual const ApplicationPaths& Paths() const noexcept = 0;
	};
}
