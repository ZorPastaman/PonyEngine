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
import PonyEngine.Utility;
import PonyEngine.Window;

import :ISystem;
import :ISystemManager;
import :ITimeManager;

export namespace PonyEngine::Core
{
	/// @brief Main Pony Engine interface.
	class IEngine : public Utility::INamed
	{
	public:
		/// @brief Gets an engine logger.
		/// @return Engine logger.
		[[nodiscard("Pure function")]]
		virtual Log::ILogger& GetLogger() const noexcept = 0;
		/// @brief Gets an engine time manager.
		/// @return Engine time manager.
		[[nodiscard("Pure function")]]
		virtual ITimeManager& GetTimeManager() const noexcept = 0;
		/// @brief Gets an engine system manager.
		/// @return Engine system manager.
		[[nodiscard("Pure function")]]
		virtual ISystemManager& GetSystemManager() const noexcept = 0;

		/// @brief Checks if the engine received an exit code.
		/// @details Exit code can be gotten via @p GetExitCode().
		/// @return @a False if the engine received an exit code; @a true otherwise;
		[[nodiscard("Pure function")]]
		virtual bool IsRunning() const noexcept = 0;
		/// @brief Gets an exit code of the engine.
		/// @details Mustn't be called if @p IsRunning() returns @a true.
		/// @return Exit code.
		[[nodiscard("Pure function")]]
		virtual int GetExitCode() const noexcept = 0;
		/// @brief Stops the engine with the @p exitCode.
		/// @details If the engine is already stopped, the invocation of this function is ignored.
		/// @param exitCode Exit code.
		virtual void Stop(int exitCode = 0) noexcept = 0;

		/// @brief Ticks the engine and increments its frame count.
		virtual void Tick() = 0;

	protected:
		~IEngine() noexcept = default;
	};
}
