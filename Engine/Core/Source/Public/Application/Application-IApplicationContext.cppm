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

#if PONY_WINDOWS
#include "PonyEngine/Platform/Windows/Framework.h"
#endif

export module PonyEngine.Application:IApplicationContext;

import std;

import PonyEngine.Log;

import :IMessageObserver;

export namespace PonyEngine::Application
{
#if PONY_WINDOWS
	namespace Windows
	{
		/// @brief Windows application context.
		class IApplicationContext;
	}

	/// @brief Windows application context.
	using INativeApplicationContext = Windows::IApplicationContext;
#else
#error "Unsupported platform!"
#endif

	/// @brief Application context. It exists for the whole life of an application.
	class IApplicationContext
	{
		INTERFACE_BODY(IApplicationContext)

		/// @brief Gets the company name.
		/// @return Company name.
		/// @remark The name is a string to use in code. To get a fancy name for views, use @p CompanyTitle().
		[[nodiscard("Pure function")]]
		virtual std::string_view CompanyName() const noexcept = 0;
		/// @brief Gets the project name.
		/// @return Project name.
		/// @remark The name is a string to use in code. To get a fancy name for views, use @p ProjectTitle().
		[[nodiscard("Pure function")]]
		virtual std::string_view ProjectName() const noexcept = 0;
		/// @brief Gets the project version.
		/// @return Project version.
		[[nodiscard("Pure function")]]
		virtual std::string_view ProjectVersion() const noexcept = 0;
		/// @brief Gets the company title.
		/// @return Company title.
		/// @remark The title is a string to use in views. To get a name for code, use @p CompanyName().
		[[nodiscard("Pure function")]]
		virtual std::string_view CompanyTitle() const noexcept = 0;
		/// @brief Gets the project title.
		/// @return Project title.
		/// @remark The title is a string to use in views. To get a name for code, use @p ProjectName().
		[[nodiscard("Pure function")]]
		virtual std::string_view ProjectTitle() const noexcept = 0;

		/// @brief Gets a path to the executable.
		/// @return Path to the executable.
		[[nodiscard("Pure function")]]
		virtual const std::filesystem::path& ExecutableFile() const noexcept = 0;
		/// @brief Gets an executable directory.
		/// @return Executable directory.
		[[nodiscard("Pure function")]]
		virtual const std::filesystem::path& ExecutableDirectory() const noexcept = 0;
		/// @brief Gets a root directory.
		/// @return Root directory.
		[[nodiscard("Pure function")]]
		virtual const std::filesystem::path& RootDirectory() const noexcept = 0;
		/// @brief Gets a local data directory.
		/// @return Local data directory.
		[[nodiscard("Pure function")]]
		virtual const std::filesystem::path& LocalDataDirectory() const noexcept = 0;
		/// @brief Gets a user data directory.
		/// @return User data directory.
		[[nodiscard("Pure function")]]
		virtual const std::filesystem::path& UserDataDirectory() const noexcept = 0;
		/// @brief Gets a temporal data directory.
		/// @return Temporal data directory.
		[[nodiscard("Pure function")]]
		virtual const std::filesystem::path& TempDataDirectory() const noexcept = 0;

		/// @brief Gets the command line excluding an executable name.
		/// @return Command line.
		[[nodiscard("Pure function")]]
		virtual std::string_view CommandLine() const noexcept = 0;

		/// @brief Gets the logger.
		/// @return Logger.
		[[nodiscard("Pure function")]]
		virtual Log::ILogger& Logger() noexcept = 0;
		/// @brief Gets the logger.
		/// @return Logger.
		[[nodiscard("Pure function")]]
		virtual const Log::ILogger& Logger() const noexcept = 0;
		/// @brief Log to console.
		/// @param logType Log type.
		/// @param message Log message.
		virtual void LogToConsole(Log::LogType logType, std::string_view message) const noexcept = 0;

		/// @brief Tries to find a service by its type.
		/// @param type Service type. Must be a public service interface.
		/// @return Pointer to the service if it's found; nullptr if it's not found.
		[[nodiscard("Pure function")]]
		virtual void* FindService(const std::type_info& type) noexcept = 0;
		/// @brief Tries to find a service by its type.
		/// @tparam T Service type. Must be a public service interface.
		/// @return Pointer to the service if it's found; nullptr if it's not found.
		template<typename T> [[nodiscard("Pure function")]]
		T* FindService() noexcept;
		/// @brief Tries to find a service by its type.
		/// @param type Service type. Must be a public service interface.
		/// @return Pointer to the service if it's found; nullptr if it's not found.
		[[nodiscard("Pure function")]]
		virtual const void* FindService(const std::type_info& type) const noexcept = 0;
		/// @brief Tries to find a service by its type.
		/// @tparam T Service type. Must be a public service interface.
		/// @return Pointer to the service if it's found; nullptr if it's not found.
		template<typename T> [[nodiscard("Pure function")]]
		const T* FindService() const noexcept;

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

		/// @brief Gets the current frame count.
		/// @return Current frame count.
		[[nodiscard("Pure function")]]
		virtual std::uint64_t FrameCount() const noexcept = 0;

		/// @brief Gets the native application context.
		/// @return Native application context.
		[[nodiscard("Pure function")]]
		INativeApplicationContext& Native() noexcept;
		/// @brief Gets the native application context.
		/// @return Native application context.
		[[nodiscard("Pure function")]]
		const INativeApplicationContext& Native() const noexcept;
		/// @brief Gets the native application context.
		/// @return Native application context.
		[[nodiscard("Pure function")]]
		INativeApplicationContext* NativePtr() noexcept;
		/// @brief Gets the native application context.
		/// @return Native application context.
		[[nodiscard("Pure function")]]
		const INativeApplicationContext* NativePtr() const noexcept;
	};
}

#if PONY_WINDOWS
export namespace PonyEngine::Application::Windows
{
	/// @brief Windows application context.
	class IApplicationContext : public Application::IApplicationContext
	{
		INTERFACE_BODY(IApplicationContext)

		/// @brief Gets the instance handle of the application.
		/// @return Instance handle of the application.
		[[nodiscard("Pure function")]]
		virtual HINSTANCE Instance() const noexcept = 0;
		/// @brief Gets the previous instance handle of the application.
		/// @return Previous instance handle of the application.
		[[nodiscard("Pure function")]]
		virtual HINSTANCE PrevInstance() const noexcept = 0;
		/// @brief Gets the show command for the application.
		/// @return Show command.
		[[nodiscard("Pure function")]]
		virtual int ShowCommand() const noexcept = 0;

		/// @brief Gets the application icon.
		/// @return Application icon.
		[[nodiscard("Pure function")]]
		virtual HICON AppIcon() const noexcept = 0;
		/// @brief Gets the application cursor.
		/// @return Application cursor.
		[[nodiscard("Pure function")]]
		virtual HCURSOR AppCursor() const noexcept = 0;

		/// @brief Adds the message observer.
		/// @param observer Observer to add.
		/// @param messageType Message type to observe. Example: WM_QUIT.
		/// @remark It observes only global messages, not window-specific messages.
		virtual void AddMessageObserver(IMessageObserver& observer, UINT messageType) = 0;
		/// @brief Adds the message observer.
		/// @param observer Observer to add.
		/// @param messageTypes Message types to observe. Example: WM_QUIT.
		/// @remark It observes only global messages, not window-specific messages.
		virtual void AddMessageObserver(IMessageObserver& observer, std::span<const UINT> messageTypes) = 0;
		/// @brief Removes the message observer from the specified message type.
		/// @param observer Observer to remove.
		/// @param messageType Message type to observe. Example: WM_QUIT.
		virtual void RemoveMessageObserver(IMessageObserver& observer, UINT messageType) noexcept = 0;
		/// @brief Removes the message observer from the specified message types.
		/// @param observer Observer to remove.
		/// @param messageTypes Message types to observe. Example: WM_QUIT.
		virtual void RemoveMessageObserver(IMessageObserver& observer, std::span<const UINT> messageTypes) noexcept = 0;
		/// @brief Removes the message observer from all the message types.
		/// @param observer Observer to remove.
		virtual void RemoveMessageObserver(IMessageObserver& observer) noexcept = 0;
	};
}
#endif

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

	INativeApplicationContext& IApplicationContext::Native() noexcept
	{
		return static_cast<INativeApplicationContext&>(*this);
	}

	const INativeApplicationContext& IApplicationContext::Native() const noexcept
	{
		return static_cast<const INativeApplicationContext&>(*this);
	}

	INativeApplicationContext* IApplicationContext::NativePtr() noexcept
	{
		return static_cast<INativeApplicationContext*>(this);
	}

	const INativeApplicationContext* IApplicationContext::NativePtr() const noexcept
	{
		return static_cast<const INativeApplicationContext*>(this);
	}
}
