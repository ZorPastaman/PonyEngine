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
import <typeinfo>;

import PonyEngine.Log;
import PonyEngine.Window;

import :ISystem;

export namespace PonyEngine::Core
{
	/// @brief Main Pony Engine interface.
	class IEngine
	{
	public:
		/// @brief Gets current frame count.
		/// @return Current frame count.
		[[nodiscard("Pure function")]]
		virtual std::size_t GetFrameCount() const noexcept = 0;

		/// @brief Gets an engine logger.
		/// @return Engine logger.
		[[nodiscard("Pure function")]]
		virtual Log::ILogger& GetLogger() const noexcept = 0;

		/// @brief Tries to find a system of the type described by the @p typeInfo.
		/// @param typeInfo System type info.
		/// @return Pointer to the system if it's found; nullptr if it's not found.
		[[nodiscard("Pure function")]]
		virtual void* FindSystem(const std::type_info& typeInfo) const noexcept = 0;
		/// @brief Tries to find a system of the type @p T.
		/// @tparam T System type.
		/// @return Pointer to the system if it's found; nullptr if it's not found.
		template<typename T> [[nodiscard("Pure function")]]
		T* FindSystem() const noexcept;

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

namespace PonyEngine::Core
{
	template<typename T>
	T* IEngine::FindSystem() const noexcept
	{
		return static_cast<T*>(FindSystem(typeid(T)));
	}
}
