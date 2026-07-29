/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Object/Body.h"

export module PonyEngine.Application:IApplication;

import std;

import PonyEngine.Chrono;
import PonyEngine.Meta;

import :TempBuffer;

export namespace PonyEngine::Application
{
	/// @brief Application.
	class IApplication
	{
		PONY_INTERFACE_BODY(IApplication)

		/// @brief Gets the engine name.
		/// @return Engine name.
		/// @remark The name is a string to use in code. To get a fancy name for views, use @p EngineTitle().
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual std::string_view EngineName() const noexcept = 0;
		/// @brief Gets the engine version.
		/// @return Engine version.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual Meta::Version EngineVersion() const noexcept = 0;
		/// @brief Gets the engine title.
		/// @return Engine title.
		/// @remark The title is a string to use in views. To get a name for code, use @p EngineName().
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual std::string_view EngineTitle() const noexcept = 0;

		/// @brief Gets the company name.
		/// @return Company name.
		/// @remark The name is a string to use in code. To get a fancy name for views, use @p CompanyTitle().
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual std::string_view CompanyName() const noexcept = 0;
		/// @brief Gets the project name.
		/// @return Project name.
		/// @remark The name is a string to use in code. To get a fancy name for views, use @p ProjectTitle().
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual std::string_view ProjectName() const noexcept = 0;
		/// @brief Gets the project version.
		/// @return Project version.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual Meta::Version ProjectVersion() const noexcept = 0;
		/// @brief Gets the company title.
		/// @return Company title.
		/// @remark The title is a string to use in views. To get a name for code, use @p CompanyName().
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual std::string_view CompanyTitle() const noexcept = 0;
		/// @brief Gets the project title.
		/// @return Project title.
		/// @remark The title is a string to use in views. To get a name for code, use @p ProjectName().
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual std::string_view ProjectTitle() const noexcept = 0;

		/// @brief Gets a path to the executable.
		/// @return Path to the executable.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual const std::filesystem::path& ExecutableFile() const noexcept = 0;
		/// @brief Gets an executable directory.
		/// @return Executable directory.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual const std::filesystem::path& ExecutableDirectory() const noexcept = 0;
		/// @brief Gets a root directory.
		/// @return Root directory.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual const std::filesystem::path& RootDirectory() const noexcept = 0;
		/// @brief Gets a local data directory.
		/// @return Local data directory.
		/// @remark The directory isn't created automatically.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual const std::filesystem::path& LocalDataDirectory() const noexcept = 0;
		/// @brief Gets a user data directory.
		/// @return User data directory.
		/// @remark The directory isn't created automatically.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual const std::filesystem::path& UserDataDirectory() const noexcept = 0;
		/// @brief Gets a temporal data directory.
		/// @return Temporal data directory.
		/// @remark The directory isn't created automatically.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual const std::filesystem::path& TempDataDirectory() const noexcept = 0;

		/// @brief Gets the main thread ID.
		/// @return Main thread ID.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual std::thread::id MainThreadID() const noexcept = 0;
		/// @brief Gets the command line.
		/// @return Command line.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual std::span<const std::string_view> CommandLine() const noexcept = 0;

		/// @brief Gets the exit code.
		/// @return Exit code; @a std::nullopt if the application isn't stopped.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual std::optional<int> ExitCode() const = 0;
		/// @brief Stops the application with the @p exitCode.
		/// @remark If the application is already stopped, the invocation of this function is ignored.
		/// @param exitCode Exit code.
		/// @note The function must be called on a main thread.
		virtual void Stop(int exitCode = 0) = 0;
		/// @brief Gets the current frame count.
		/// @return Current frame count.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual std::uint64_t FrameCount() const = 0;
		/// @brief Gets a time point when the application started.
		/// @return Time point.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual std::chrono::time_point<std::chrono::steady_clock> StartTimePoint() const noexcept = 0;
		/// @brief Gets a time point when a previous frame started.
		/// @return Time point.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual std::chrono::time_point<std::chrono::steady_clock> PrevFrameTimePoint() const = 0;
		/// @brief Gets a time point when this frame started.
		/// @return Time point.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual std::chrono::time_point<std::chrono::steady_clock> ThisFrameTimePoint() const = 0;
		/// @brief Gets the earliest time point when a next frame will start.
		/// @return Time point.
		/// @note The function must be called on a main thread.
		/// @remark The value is evaluated based on a current target frame time.
		[[nodiscard("Pure function")]]
		virtual std::chrono::time_point<std::chrono::steady_clock> NextFrameTimePoint() const = 0;
		/// @brief Gets a now time point.
		/// @return Time point.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual std::chrono::time_point<std::chrono::steady_clock> NowTimePoint() const noexcept = 0;
		/// @brief Gets a time elapsed between the application start and a previous frame start.
		/// @return Time.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds PrevFrameTime() const = 0;
		/// @brief Gets a time elapsed between the application start and a previous frame start.
		/// @tparam T Return value type.
		/// @return Time in seconds.
		/// @note The function must be called on a main thread.
		template<std::floating_point T = double> [[nodiscard("Pure function")]]
		T PrevFrameTimeSeconds() const;
		/// @brief Gets a time elapsed between the application start and this frame start.
		/// @return Time.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds ThisFrameTime() const = 0;
		/// @brief Gets a time elapsed between the application start and this frame start.
		/// @tparam T Return value type.
		/// @return Time in seconds.
		/// @note The function must be called on a main thread.
		template<std::floating_point T = double> [[nodiscard("Pure function")]]
		T ThisFrameTimeSeconds() const;
		/// @brief Gets a minimal time that will elapse between the application start and a next frame start.
		/// @return Time.
		/// @note The function must be called on a main thread.
		/// @remark The value is evaluated based on a current target frame time.
		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds NextFrameTime() const = 0;
		/// @brief Gets a minimal time that will elapse between the application start and a next frame start.
		/// @tparam T Return value type.
		/// @return Time in seconds.
		/// @note The function must be called on a main thread.
		/// @remark The value is evaluated based on a current target frame time.
		template<std::floating_point T = double> [[nodiscard("Pure function")]]
		T NextFrameTimeSeconds() const;
		/// @brief Gets a time elapsed since the application start.
		/// @return Time.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds NowTime() const noexcept = 0;
		/// @brief Gets a time elapsed since the application start.
		/// @tparam T Return value type.
		/// @return Time in seconds.
		/// @note The function is thread-safe.
		template<std::floating_point T = double> [[nodiscard("Pure function")]]
		T NowTimeSeconds() const noexcept;
		/// @brief Gets a time elapsed between the previous frame and this frame start.
		/// @return Time.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds DeltaTime() const = 0;
		/// @brief Gets a time elapsed between the previous frame and this frame start.
		/// @tparam T Return value type.
		/// @return Time in seconds.
		/// @note The function must be called on a main thread.
		template<std::floating_point T = double> [[nodiscard("Pure function")]]
		T DeltaTimeSeconds() const;
		/// @brief Gets the target frame time.
		/// @return Target frame time. 0 or less means no target frame time (it's not restricted).
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds TargetFrameTime() const = 0;
		/// @brief Gets the target frame time.
		/// @tparam T Return value type.
		/// @return Target frame time in seconds.
		/// @note The function must be called on a main thread.
		template<std::floating_point T = double> [[nodiscard("Pure function")]]
		T TargetFrameTimeSeconds() const;
		/// @brief Sets the target frame time.
		/// @param frameTime Target frame time. 0 or less means no target frame time (it's not restricted).
		/// @note The function must be called on a main thread.
		virtual void TargetFrameTime(std::chrono::nanoseconds frameTime) = 0;
		/// @brief Sets the target frame time.
		/// @tparam T Second type.
		/// @param frameTime Target frame time. 0 or less means no target frame time (it's not restricted).
		/// @note The function must be called on a main thread.
		template<std::floating_point T> [[nodiscard("Pure function")]]
		void TargetFrameTimeSeconds(T frameTime);

		/// @brief Tries to find an interface by its type.
		/// @param type Interface type.
		/// @return Pointer to the interface if it's found; nullptr if it's not found.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual void* FindInterface(std::type_index type) const = 0;
		/// @brief Tries to find an interface by its type.
		/// @tparam T Interface type.
		/// @return Pointer to the interface if it's found; nullptr if it's not found.
		/// @note The function must be called on a main thread.
		template<typename T> [[nodiscard("Pure function")]]
		T* FindInterface() const;
		/// @brief Gets an interface by its type or throws an exception.
		/// @tparam T Interface type.
		/// @return Reference to the interface.
		/// @note The function must be called on a main thread.
		template<typename T> [[nodiscard("Pure function")]]
		T& GetInterface() const;

		/// @brief Acquires a temporary buffer.
		/// @param requiredSize Required size.
		/// @param requiredAlignment Required alignment. Must be a valid alignment value and at least alignof(std::max_align_t).
		/// @return Temporary buffer.
		/// @note Each thread has its own pool of buffers.
		[[nodiscard("Pure function")]]
		virtual TempBuffer AcquireTempBuffer(std::size_t requiredSize, std::size_t requiredAlignment = alignof(std::max_align_t)) = 0;
		/// @brief Releases the temporary buffer.
		/// @param tempBuffer Temporary buffer.
		/// @note The buffer must be returned on the same thread it was acquired.
		virtual void ReleaseTempBuffer(TempBuffer tempBuffer) noexcept = 0;
	};
}

namespace PonyEngine::Application
{
	template<std::floating_point T>
	T IApplication::PrevFrameTimeSeconds() const
	{
		return Chrono::ToSeconds<T>(PrevFrameTime());
	}

	template<std::floating_point T>
	T IApplication::ThisFrameTimeSeconds() const
	{
		return Chrono::ToSeconds<T>(ThisFrameTime());
	}

	template<std::floating_point T>
	T IApplication::NextFrameTimeSeconds() const
	{
		return Chrono::ToSeconds<T>(NextFrameTime());
	}

	template<std::floating_point T>
	T IApplication::NowTimeSeconds() const noexcept
	{
		return Chrono::ToSeconds<T>(NowTime());
	}

	template<std::floating_point T>
	T IApplication::DeltaTimeSeconds() const
	{
		return Chrono::ToSeconds<T>(DeltaTime());
	}

	template<std::floating_point T>
	T IApplication::TargetFrameTimeSeconds() const
	{
		return Chrono::ToSeconds<T>(TargetFrameTime());
	}

	template<std::floating_point T>
	void IApplication::TargetFrameTimeSeconds(const T frameTime)
	{
		TargetFrameTime(Chrono::ToDuration<std::chrono::nanoseconds>(frameTime));
	}

	template<typename T>
	T* IApplication::FindInterface() const
	{
		return static_cast<T*>(FindInterface(typeid(T)));
	}

	template<typename T>
	T& IApplication::GetInterface() const
	{
		T* const interface = FindInterface<T>();
		if (!interface) [[unlikely]]
		{
			throw std::logic_error("Interface not found");
		}

		return *interface;
	}
}
