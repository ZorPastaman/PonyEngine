/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/ObjectBody.h"

export module PonyEngine.Core:IEngineContext;

import <cstdint>;

import PonyBase.Core;

import PonyDebug.Log;

import :ISystemManager;

export namespace PonyEngine::Core
{
	/// @brief Engine context.
	class IEngineContext
	{
		INTERFACE_BODY(IEngineContext)

		/// @brief Gets the current frame count.
		/// @return Current frame count.
		[[nodiscard("Pure function")]]
		virtual std::uint64_t FrameCount() const noexcept = 0;

		/// @brief Gets the engine logger.
		/// @return Engine logger.
		[[nodiscard("Pure function")]]
		virtual PonyDebug::Log::ILogger& Logger() noexcept = 0;
		/// @brief Gets the engine logger.
		/// @return Engine logger.
		[[nodiscard("Pure function")]]
		virtual const PonyDebug::Log::ILogger& Logger() const noexcept = 0;
		/// @brief Gets the engine system manager.
		/// @return Engine system manager.
		[[nodiscard("Pure function")]]
		virtual ISystemManager& SystemManager() noexcept = 0;
		/// @brief Gets the engine system manager.
		/// @return Engine system manager.
		[[nodiscard("Pure function")]]
		virtual const ISystemManager& SystemManager() const noexcept = 0;

		/// @brief Did the engine receive an exit code?
		/// @remark Exit code can be gotten via @p ExitCode().
		/// @return @a False if the engine received an exit code; @a true otherwise;
		[[nodiscard("Pure function")]]
		virtual bool IsRunning() const noexcept = 0;
		/// @brief Gets the exit code.
		/// @note Mustn't be called if @p IsRunning() returns @a true.
		/// @return Exit code.
		[[nodiscard("Pure function")]]
		virtual int ExitCode() const noexcept = 0;
		/// @brief Stops the engine with the @p exitCode.
		/// @remark If the engine is already stopped, the invocation of this function is ignored.
		/// @param exitCode Exit code.
		virtual void Stop(int exitCode = static_cast<int>(PonyBase::Core::ExitCodes::Success)) noexcept = 0;
	};
}
