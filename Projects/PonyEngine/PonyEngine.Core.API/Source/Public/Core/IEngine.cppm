/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core:IEngine;

import PonyBase.Core;

import PonyEngine.Log;

import :ISystemManager;

export namespace PonyEngine::Core
{
	/// @brief Engine.
	class IEngine
	{
	public:
		IEngine(const IEngine&) = delete;
		IEngine(IEngine&&) = delete;

		/// @brief Gets the current frame count.
		/// @return Current frame count.
		[[nodiscard("Pure function")]]
		virtual std::size_t FrameCount() const noexcept = 0;

		/// @brief Gets the engine logger.
		/// @return Engine logger.
		[[nodiscard("Pure function")]]
		virtual Log::ILogger& Logger() const noexcept = 0;
		/// @brief Gets the engine system manager.
		/// @return Engine system manager.
		[[nodiscard("Pure function")]]
		virtual ISystemManager& SystemManager() const noexcept = 0;

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

		/// @brief Gets the engine name.
		/// @return Engine name.
		[[nodiscard("Pure function")]]
		virtual const char* Name() const noexcept = 0;

		IEngine& operator =(const IEngine&) = delete;
		IEngine& operator =(IEngine&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IEngine() noexcept = default;

		~IEngine() noexcept = default;
	};
}
