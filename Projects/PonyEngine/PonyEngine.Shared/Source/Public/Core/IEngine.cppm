/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core:IEngine;

import <cstddef>;

import PonyEngine.Debug.Log;
import PonyEngine.Window;

import :IServiceManager;
import :ISystemManager;

namespace PonyEngine::Core
{
	/// @brief Main Pony Engine interface.
	export class IEngine
	{
	public:
		/// @brief Gets current frame count.
		/// @return Current frame count.
		[[nodiscard("Pure function")]]
		virtual std::size_t GetFrameCount() const noexcept = 0;

		/// @brief Gets an engine logger.
		/// @return Engine logger.
		[[nodiscard("Pure function")]]
		virtual Debug::Log::ILogger& GetLogger() const noexcept = 0;
		/// @brief Gets an engine window. The window is optional.
		/// @return Engine window. Can be @a nullptr.
		[[nodiscard("Pure function")]]
		virtual Window::IWindow* GetWindow() const noexcept = 0;

		[[nodiscard("Pure function")]]
		virtual IServiceManager& GetServiceManager() noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual ISystemManager& GetSystemManager() noexcept = 0;

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
		/// @details If the engine is already stopped, the invocation of this functions is ignored.
		/// @param exitCode Exit code.
		virtual void Stop(int exitCode = 0) noexcept = 0;

		/// @brief Ticks the engine and increments its frame count.
		virtual void Tick() = 0;

	protected:
		virtual ~IEngine() noexcept = default;
	};
}
