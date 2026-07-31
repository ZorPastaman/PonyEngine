/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Log/Log.h"
#include "PonyEngine/Platform/Windows/Framework.h"

export module PonyEngine.File.Impl.Windows:Worker;

import std;

import PonyEngine.Application;
import PonyEngine.File.Impl;
import PonyEngine.Log;

import :OverlappedRequest;

export namespace PonyEngine::File
{
	/// @brief Worker. Manages an io thread, creates requests and updates them on their completion.
	class Worker final
	{
	public:
		/// @brief Creates a worker.
		/// @param application Application.
		[[nodiscard("Pure constructor")]]
		explicit Worker(const Application::IApplication& application);
		Worker(const Worker&) = delete;
		Worker(Worker&&) = delete;

		~Worker() noexcept;

		/// @brief Associates the file handle with the worker iocp.
		/// @param fileHandle File handle.
		/// @param file File.
		void AssociateFile(HANDLE fileHandle, const IFile& file) const;

		/// @brief Makes a read request.
		/// @param fileHandle File handle. Must be associated with the worker.
		/// @param params Read parameters.
		/// @param callback Read callback. Can be nullptr.
		/// @return Overlapped read request.
		[[nodiscard("Must be used")]]
		std::shared_ptr<OverlappedRequest> MakeRequest(HANDLE fileHandle, const ReadParams& params, const std::function<void(const IReadRequest&)>& callback) const;
		/// @brief Makes a write request.
		/// @param fileHandle File handle. Must be associated with the worker.
		/// @param params Write parameters.
		/// @param callback Write callback. Can be nullptr.
		/// @return Overlapped write request.
		[[nodiscard("Must be used")]]
		std::shared_ptr<OverlappedRequest> MakeRequest(HANDLE fileHandle, const WriteParams& params, const std::function<void(const IWriteRequest&)>& callback) const;

		Worker& operator =(const Worker&) = delete;
		Worker& operator =(Worker&&) = delete;

	private:
		/// @brief Work function.
		void Work() const noexcept;

		const Application::IApplication* application; ///< Application.

		HANDLE iocp; ///< IO completion port.
		std::atomic_bool running; ///< Should the worker run?

		std::pmr::synchronized_pool_resource requestPool; ///< Request pool.
		std::pmr::polymorphic_allocator<OverlappedRequest> requestAllocator; ///< Request allocator.

		std::thread thread; ///< Worker thread.

		static_assert(sizeof(std::size_t) >= sizeof(DWORD), "std::size_t is less than DWORD.");
		static_assert(std::atomic_bool::is_always_lock_free, "bool is not lock-free.");
	};
}

namespace PonyEngine::File
{
	Worker::Worker(const Application::IApplication& application) :
		application{&application},
		running(true),
		requestAllocator(&requestPool)
	{
		PONY_LOG(this->application->Logger(), Log::LogType::Info, "Creating IOCP...");
		iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, nullptr, 0, 0);
		if (!iocp) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to create iocp: Error code = '0x{:X}'", GetLastError()));
		}
		PONY_LOG(this->application->Logger(), Log::LogType::Info, "Creating IOCP done. Handle: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(iocp));

		PONY_LOG(this->application->Logger(), Log::LogType::Info, "Creating io work thread...");
		try
		{
			thread = std::thread(&Worker::Work, this);
		}
		catch (...)
		{
			if (!CloseHandle(iocp)) [[unlikely]]
			{
				PONY_LOG(this->application->Logger(), Log::LogType::Error, "Failed to close iocp. Error code: '0x{:X}'.", GetLastError());
			}
			throw;
		}
		PONY_LOG(this->application->Logger(), Log::LogType::Info, "Creating io work thread done.");
	}

	Worker::~Worker() noexcept
	{
		PONY_LOG(this->application->Logger(), Log::LogType::Info, "Closing io work thread...");
		running.store(false, std::memory_order::relaxed);
		if (!PostQueuedCompletionStatus(iocp, 0, 0, nullptr)) [[unlikely]]
		{
			PONY_LOG(application->Logger(), Log::LogType::Error, "Failed to post queued io completion status. Error code: '0x{:X}'.", GetLastError());
		}
		thread.join();
		PONY_LOG(this->application->Logger(), Log::LogType::Info, "Closing io work thread done.");

		PONY_LOG(this->application->Logger(), Log::LogType::Info, "Closing IOCP... Handle: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(iocp));
		if (!CloseHandle(iocp)) [[unlikely]]
		{
			PONY_LOG(application->Logger(), Log::LogType::Error, "Failed to close iocp. Error code: '0x{:X}'.", GetLastError());
		}
		PONY_LOG(this->application->Logger(), Log::LogType::Info, "Closing IOCP done.");
	}

	void Worker::AssociateFile(const HANDLE fileHandle, const IFile& file) const
	{
		PONY_LOG(this->application->Logger(), Log::LogType::Info, "Associating file with iocp... File handle: '0x{:X}'; IOCP: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(fileHandle), reinterpret_cast<std::uintptr_t>(iocp));
		if (!CreateIoCompletionPort(fileHandle, iocp, reinterpret_cast<ULONG_PTR>(&file), 0)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to create file iocp association: Error code = '0x{:X}'", GetLastError()));
		}
		PONY_LOG(this->application->Logger(), Log::LogType::Info, "Associating file with iocp done. Handle: '0x{:X}; IOCP: '0x{:X}''.", reinterpret_cast<std::uintptr_t>(fileHandle), reinterpret_cast<std::uintptr_t>(iocp));
	}

	std::shared_ptr<OverlappedRequest> Worker::MakeRequest(const HANDLE fileHandle, const ReadParams& params, const std::function<void(const IReadRequest&)>& callback) const
	{
#ifndef NDEBUG
		if (params.buffer.size() > std::numeric_limits<DWORD>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Too great buffer");
		}
#endif

		const auto request = std::allocate_shared<OverlappedRequest>(requestAllocator, params, callback);

		if (ReadFile(fileHandle, params.buffer.data(), static_cast<DWORD>(params.buffer.size()), nullptr, &request->Overlapped())) [[unlikely]]
		{
			DWORD bytesTransferred = 0;
			if (GetOverlappedResult(fileHandle, &request->Overlapped(), &bytesTransferred, FALSE)) [[likely]]
			{
				request->Request().SetSuccess(static_cast<std::size_t>(bytesTransferred));
			}
			else [[unlikely]]
			{
				throw std::runtime_error(std::format("Failed to create file read request: Error code = '0x{:X}'", GetLastError()));
			}
		}
		else [[likely]]
		{
			if (const DWORD error = GetLastError(); error != ERROR_IO_PENDING) [[unlikely]]
			{
				throw std::runtime_error(std::format("Failed to create file read request: Error code = '0x{:X}'", error));
			}
		}

		return request;
	}

	std::shared_ptr<OverlappedRequest> Worker::MakeRequest(const HANDLE fileHandle, const WriteParams& params, const std::function<void(const IWriteRequest&)>& callback) const
	{
#ifndef NDEBUG
		if (params.buffer.size() > std::numeric_limits<DWORD>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Too great buffer");
		}
#endif

		const auto request = std::allocate_shared<OverlappedRequest>(requestAllocator, params, callback);

		if (WriteFile(fileHandle, params.buffer.data(), static_cast<DWORD>(params.buffer.size()), nullptr, &request->Overlapped())) [[unlikely]]
		{
			DWORD bytesTransferred = 0;
			if (GetOverlappedResult(fileHandle, &request->Overlapped(), &bytesTransferred, FALSE)) [[likely]]
			{
				request->Request().SetSuccess(static_cast<std::size_t>(bytesTransferred));
			}
			else [[unlikely]]
			{
				throw std::runtime_error(std::format("Failed to create file write request: Error code = '0x{:X}'", GetLastError()));
			}
		}
		else [[likely]]
		{
			if (const DWORD error = GetLastError(); error != ERROR_IO_PENDING) [[unlikely]]
			{
				throw std::runtime_error(std::format("Failed to create file write request: Error code = '0x{:X}'", error));
			}
		}

		return request;
	}

	void Worker::Work() const noexcept
	{
		while (running.load(std::memory_order::relaxed))
		{
			DWORD bytesTransferred = 0;
			ULONG_PTR completionKey = 0;
			OVERLAPPED* overlapped = nullptr;

			if (GetQueuedCompletionStatus(iocp, &bytesTransferred, &completionKey, &overlapped, INFINITE)) [[likely]]
			{
				if (overlapped) [[likely]]
				{
					const auto request = reinterpret_cast<OverlappedRequest*>(overlapped);
					request->Request().SetSuccess(static_cast<std::size_t>(bytesTransferred));
				}
			}
			else [[unlikely]]
			{
				try
				{
					throw std::runtime_error(std::format("Failed to get queued io completion status: Error code = '0x{:X}'", GetLastError()));
				}
				catch (...)
				{
					const std::exception_ptr exception = std::current_exception();
					PONY_LOG(application->Logger(), Log::LogType::Error, exception);

					if (overlapped) [[likely]]
					{
						const auto request = reinterpret_cast<OverlappedRequest*>(overlapped);
						request->Request().SetFailed(exception);
					}
				}
			}
		}
	}
}
