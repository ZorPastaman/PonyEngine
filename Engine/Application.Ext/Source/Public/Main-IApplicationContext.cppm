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

export module PonyEngine.Application.Ext:IApplicationContext;

import std;

import PonyEngine.Log;
import PonyEngine.Meta;

import :FlowState;

export namespace PonyEngine::Application
{
	/// @brief Application context.
	class IApplicationContext
	{
		PONY_INTERFACE_BODY(IApplicationContext)

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

		/// @brief Gets the command line excluding an executable name.
		/// @return Command line.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual std::string_view CommandLine() const noexcept = 0;

		/// @brief Gets the logger.
		/// @return Logger.
		/// @note The function is thread-safe between Begin() and End() of the engine but must be accessed only from a main thread before Begin() and after End().
		[[nodiscard("Pure function")]]
		virtual Log::ILogger& Logger() noexcept = 0;
		/// @brief Gets the logger.
		/// @return Logger.
		/// @note The function is thread-safe between Begin() and End() of the engine but must be accessed only from a main thread before Begin() and after End().
		[[nodiscard("Pure function")]]
		virtual const Log::ILogger& Logger() const noexcept = 0;

		/// @brief Tries to find a service by its type.
		/// @param type Service type. Must be a public service interface.
		/// @return Pointer to the service if it's found; nullptr if it's not found.
		/// @note The function is thread-safe between Begin() and End() of the engine but must be accessed only from a main thread before Begin() and after End().
		[[nodiscard("Pure function")]]
		virtual void* FindService(std::type_index type) noexcept = 0;
		/// @brief Tries to find a service by its type.
		/// @tparam T Service type. Must be a public service interface.
		/// @return Pointer to the service if it's found; nullptr if it's not found.
		/// @note The function is thread-safe between Begin() and End() of the engine but must be accessed only from a main thread before Begin() and after End().
		template<typename T> [[nodiscard("Pure function")]]
		T* FindService() noexcept;
		/// @brief Tries to find a service by its type.
		/// @param type Service type. Must be a public service interface.
		/// @return Pointer to the service if it's found; nullptr if it's not found.
		/// @note The function is thread-safe between Begin() and End() of the engine but must be accessed only from a main thread before Begin() and after End().
		[[nodiscard("Pure function")]]
		virtual const void* FindService(std::type_index type) const noexcept = 0;
		/// @brief Tries to find a service by its type.
		/// @tparam T Service type. Must be a public service interface.
		/// @return Pointer to the service if it's found; nullptr if it's not found.
		/// @note The function is thread-safe between Begin() and End() of the engine but must be accessed only from a main thread before Begin() and after End().
		template<typename T> [[nodiscard("Pure function")]]
		const T* FindService() const noexcept;
		/// @brief Gets a service by its type or throws an exception.
		/// @tparam T Service type. Must be a public service interface.
		/// @return Reference to the service.
		/// @note The function is thread-safe between Begin() and End() of the engine but must be accessed only from a main thread before Begin() and after End().
		template<typename T> [[nodiscard("Pure function")]]
		T& GetService();
		/// @brief Gets a service by its type or throws an exception.
		/// @tparam T Service type. Must be a public service interface.
		/// @return Reference to the service.
		/// @note The function is thread-safe between Begin() and End() of the engine but must be accessed only from a main thread before Begin() and after End().
		template<typename T> [[nodiscard("Pure function")]]
		const T& GetService() const;

		/// @brief Gets the flow state.
		/// @return Flow state.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual FlowState FlowState() const noexcept = 0;
		/// @brief Gets the exit code.
		/// @note Mustn't be called if @p FlowState() returns Running or less.
		/// @return Exit code.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual int ExitCode() const noexcept = 0;
		/// @brief Stops the application with the @p exitCode.
		/// @remark If the application is already stopped, the invocation of this function is ignored.
		/// @param exitCode Exit code.
		/// @note Must be called on a main thread only.
		virtual void Stop(int exitCode = 0) = 0;

		/// @brief Gets the current frame count.
		/// @return Current frame count.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual std::uint64_t FrameCount() const noexcept = 0;
	};
}

namespace PonyEngine::Application
{
	template<typename T>
	T* IApplicationContext::FindService() noexcept
	{
		return static_cast<T*>(FindService(typeid(T)));
	}

	template<typename T>
	const T* IApplicationContext::FindService() const noexcept
	{
		return static_cast<const T*>(FindService(typeid(T)));
	}

	template<typename T>
	T& IApplicationContext::GetService()
	{
		T* const service = FindService<T>();
#ifndef NDEBUG
		if (!service) [[unlikely]]
		{
			throw std::logic_error("Service not found");
		}
#endif

		return *service;
	}

	template<typename T>
	const T& IApplicationContext::GetService() const
	{
		const T* const service = FindService<T>();
#ifndef NDEBUG
		if (!service) [[unlikely]]
		{
			throw std::logic_error("Service not found");
		}
#endif

		return *service;
	}
}
