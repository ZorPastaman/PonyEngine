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

import PonyEngine.Log;

import :IServiceManager;

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

		/// @brief Gets the service manager.
		/// @return Service manager.
		[[nodiscard("Pure function")]]
		virtual IServiceManager& ServiceManager() noexcept = 0;
		/// @brief Gets the service manager.
		/// @return Service manager.
		[[nodiscard("Pure function")]]
		virtual const IServiceManager& ServiceManager() const noexcept = 0;

		/// @brief Did the application receive an exit code?
		/// @remark Exit code can be gotten via @p ExitCode().
		/// @return @a False if the application received an exit code; @a true otherwise;
		[[nodiscard("Pure function")]]
		virtual bool IsRunning() const noexcept = 0;
		/// @brief Gets the exit code.
		/// @note Mustn't be called if @p IsRunning() returns @a true.
		/// @return Exit code.
		[[nodiscard("Pure function")]]
		virtual int ExitCode() const noexcept = 0;
		/// @brief Stops the application with the @p exitCode.
		/// @remark If the application is already stopped, the invocation of this function is ignored.
		/// @param exitCode Exit code.
		virtual void Stop(int exitCode = 0) noexcept = 0;
	};
}
