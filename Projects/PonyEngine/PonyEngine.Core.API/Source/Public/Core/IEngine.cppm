/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core:IEngine;

import PonyEngine.Log;

import :ISystemManager;
import :ITimeManager;

export namespace PonyEngine::Core
{
	/// @brief Engine.
	class IEngine
	{
	public:
		IEngine(const IEngine&) = delete;
		IEngine(IEngine&&) = delete;

		/// @brief Gets the engine logger.
		/// @return Engine logger.
		[[nodiscard("Pure function")]]
		virtual Log::ILogger& GetLogger() const noexcept = 0;
		/// @brief Gets the engine time manager.
		/// @return Engine time manager.
		[[nodiscard("Pure function")]]
		virtual ITimeManager& GetTimeManager() const noexcept = 0;
		/// @brief Gets the engine system manager.
		/// @return Engine system manager.
		[[nodiscard("Pure function")]]
		virtual ISystemManager& GetSystemManager() const noexcept = 0;

		/// @brief Did the engine receive an exit code?
		/// @remark Exit code can be gotten via @p GetExitCode().
		/// @return @a False if the engine received an exit code; @a true otherwise;
		[[nodiscard("Pure function")]]
		virtual bool GetIsRunning() const noexcept = 0;
		/// @brief Gets the exit code.
		/// @note Mustn't be called if @p GetIsRunning() returns @a true.
		/// @return Exit code.
		[[nodiscard("Pure function")]]
		virtual int GetExitCode() const noexcept = 0;
		/// @brief Stops the engine with the @p exitCode.
		/// @remark If the engine is already stopped, the invocation of this function is ignored.
		/// @param exitCode Exit code.
		virtual void Stop(int exitCode = 0) noexcept = 0;

		/// @brief Gets the engine name.
		/// @return Engine name.
		[[nodiscard("Pure function")]]
		virtual const char* GetName() const noexcept = 0;

		IEngine& operator =(const IEngine&) = delete;
		IEngine& operator =(IEngine&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IEngine() noexcept = default;

		~IEngine() noexcept = default;
	};
}