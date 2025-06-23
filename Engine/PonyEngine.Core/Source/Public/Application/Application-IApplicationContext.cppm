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

export module PonyEngine.Application:IApplicationContext;

import PonyEngine.Engine;
import PonyEngine.Log;

import :ApplicationPaths;

export namespace PonyEngine::Application
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
		/// @return Engine.
		[[nodiscard("Pure function")]]
		virtual Engine::IEngine* Engine() noexcept = 0;
		/// @brief Gets the engine.
		/// @return Engine.
		[[nodiscard("Pure function")]]
		virtual const Engine::IEngine* Engine() const noexcept = 0;

		/// @brief Gets the application paths.
		/// @return Application paths.
		[[nodiscard("Pure function")]]
		virtual const ApplicationPaths& Paths() const noexcept = 0;
	};
}
