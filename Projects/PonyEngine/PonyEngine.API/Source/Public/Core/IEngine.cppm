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
import <functional>;

import PonyEngine.Debug.Log;
import PonyEngine.Window;

import :ISystem;

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

		/// @brief Finds a system by the @p predicate.
		/// @param predicate Predicate.
		/// @return Found system. It's nullptr if no system is found.
		[[nodiscard("Pure function")]]
		virtual ISystem* FindSystem(const std::function<bool(const ISystem*)>& predicate) const = 0;
		/// @brief Finds a system of the type @p T.
		/// @tparam T System type to find.
		/// @return Found system. It's nullptr if no system is found.
		template<typename T> [[nodiscard("Pure function")]]
		T* FindSystem() const;

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
		inline virtual ~IEngine() noexcept = default;
	};

	template<typename T>
	T* IEngine::FindSystem() const
	{
		ISystem* const system = FindSystem([](const ISystem* const system) { return dynamic_cast<const T*>(system) != nullptr; });

		return dynamic_cast<T*>(system);
	}
}
