/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

#include "PonyEngine/Object/Body.h"

export module PonyEngine.Application:IApplication;

import std;

import PonyEngine.Log;
import PonyEngine.Meta;

import :FlowState;
import :TempBuffer;

export namespace PonyEngine::Application
{
	/// @brief Temporary buffer that is released automatically when this struct goes out of scope.
	class ScopedTempBuffer;

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

		/// @brief Acquires a temporary buffer.
		/// @param requiredSize Required size.
		/// @param requiredAlignment Required alignment. Must be a valid alignment value and at least alignof(std::max_align_t).
		/// @return Temporary buffer.
		/// @note Each thread has its own pool of buffers.
		[[nodiscard("Pure function")]]
		virtual TempBuffer AcquireTempBuffer(std::size_t requiredSize, std::size_t requiredAlignment = alignof(std::max_align_t)) = 0;
		/// @brief Releases the temporary buffer.
		/// @param buffer Temporary buffer.
		/// @note The buffer must be returned on the same thread it was acquired.
		virtual void ReleaseTempBuffer(TempBuffer buffer) noexcept = 0;
		/// @brief Acquires a scoped temporary buffer.
		/// @param requiredSize Required size.
		/// @param requiredAlignment Required alignment. Must be a valid alignment value and at least alignof(std::max_align_t).
		/// @return Scoped temporary buffer.
		/// @note Each thread has its own pool of buffers.
		/// @note The buffer must be destroyed on the same thread it was acquired.
		[[nodiscard("Pure function")]]
		ScopedTempBuffer AcquiredScopedTempBuffer(std::size_t requiredSize, std::size_t requiredAlignment = alignof(std::max_align_t));
	};

	class ScopedTempBuffer final
	{
	public:
		/// @brief Creates an empty scoped temporary buffer.
		[[nodiscard("Pure constructor")]]
		ScopedTempBuffer() noexcept;
		/// @brief Creates a scoped temporary buffer.
		/// @param buffer Temporary buffer. Must be an alive buffer.
		/// @param application Application.
		[[nodiscard("Pure constructor")]]
		ScopedTempBuffer(TempBuffer buffer, IApplication& application) noexcept;
		ScopedTempBuffer(const ScopedTempBuffer&) = delete;
		[[nodiscard("Pure constructor")]]
		ScopedTempBuffer(ScopedTempBuffer&& other) noexcept;

		~ScopedTempBuffer() noexcept;

		/// @brief Releases the temporary buffer.
		void Release() noexcept;
		/// @brief Forgets the temporary buffer.
		void Forget() noexcept;

		/// @brief Gets the buffer.
		/// @return Buffer.
		[[nodiscard("Pure function")]]
		const std::span<std::byte>* Get() const noexcept;
		/// @brief Gets the temp buffer.
		/// @return Temp buffer.
		[[nodiscard("Pure function")]]
		const TempBuffer& Buffer() const noexcept;
		/// @brief Gets the application.
		/// @return Application.
		[[nodiscard("Pure function")]]
		IApplication* Application() const noexcept;

		/// @brief Checks if it has a valid buffer.
		[[nodiscard("Pure operator")]]
		explicit operator bool() const noexcept;

		[[nodiscard("Pure operator")]]
		const std::span<std::byte>& operator *() const noexcept;
		[[nodiscard("Pure operator")]]
		const std::span<std::byte>* operator ->() const noexcept;

		ScopedTempBuffer& operator =(const ScopedTempBuffer&) = delete;
		ScopedTempBuffer& operator =(ScopedTempBuffer&& other) noexcept;

	private:
		TempBuffer buffer; ///< Temporary buffer.
		IApplication* application; ///< Application.
	};
}

namespace PonyEngine::Application
{
	template<typename T>
	T* IApplication::FindService() noexcept
	{
		return static_cast<T*>(FindService(typeid(T)));
	}

	template<typename T>
	const T* IApplication::FindService() const noexcept
	{
		return static_cast<const T*>(FindService(typeid(T)));
	}

	template<typename T>
	T& IApplication::GetService()
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
	const T& IApplication::GetService() const
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

	ScopedTempBuffer IApplication::AcquiredScopedTempBuffer(const std::size_t requiredSize, const std::size_t requiredAlignment)
	{
		return ScopedTempBuffer(AcquireTempBuffer(requiredSize, requiredAlignment), *this);
	}

	ScopedTempBuffer::ScopedTempBuffer() noexcept :
		application{nullptr}
	{
	}

	ScopedTempBuffer::ScopedTempBuffer(const TempBuffer buffer, IApplication& application) noexcept :
		buffer(buffer),
		application{&application}
	{
		assert(this->buffer.buffer.data() && "Invalid buffer.");
	}

	ScopedTempBuffer::ScopedTempBuffer(ScopedTempBuffer&& other) noexcept :
		buffer(other.buffer),
		application{other.application}
	{
		other.Forget();
	}

	ScopedTempBuffer::~ScopedTempBuffer() noexcept
	{
		Release();
	}

	void ScopedTempBuffer::Release() noexcept
	{
		if (application)
		{
			application->ReleaseTempBuffer(buffer);
			Forget();
		}
	}

	void ScopedTempBuffer::Forget() noexcept
	{
		buffer = TempBuffer{};
		application = nullptr;
	}

	const std::span<std::byte>* ScopedTempBuffer::Get() const noexcept
	{
		return application ? &buffer.buffer : nullptr;
	}

	const TempBuffer& ScopedTempBuffer::Buffer() const noexcept
	{
		return buffer;
	}

	IApplication* ScopedTempBuffer::Application() const noexcept
	{
		return application;
	}

	ScopedTempBuffer::operator bool() const noexcept
	{
		return application;
	}

	const std::span<std::byte>& ScopedTempBuffer::operator *() const noexcept
	{
		return *Get();
	}

	const std::span<std::byte>* ScopedTempBuffer::operator ->() const noexcept
	{
		return Get();
	}

	ScopedTempBuffer& ScopedTempBuffer::operator =(ScopedTempBuffer&& other) noexcept
	{
		Release();
		buffer = other.buffer;
		application = other.application;
		other.Forget();

		return *this;
	}
}
