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

#include "PonyEngine/Log/Log.h"
#include "PonyEngine/Macro/Text.h"
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
		explicit Worker(Application::IApplication& application);
		Worker(const Worker&) = delete;
		Worker(Worker&&) = delete;

		~Worker() noexcept;

		/// @brief Associates the file handle with the worker iocp.
		/// @param file File.
		void AssociateFile(HANDLE file) const;

		/// @brief Makes a read request.
		/// @param params Read parameters.
		/// @param callback Callback.
		/// @param file File that created this request.
		/// @return Read request.
		[[nodiscard("Must be used")]]
		std::shared_ptr<IReadRequest> MakeRequest(const ReadParams& params, std::move_only_function<void(const IReadRequest&)> callback, HANDLE file) const;
		/// @brief Makes a write request.
		/// @param params Write parameters.
		/// @param callback Callback.
		/// @param file File that created this request.
		/// @return Write request.
		[[nodiscard("Must be used")]]
		std::shared_ptr<IWriteRequest> MakeRequest(const WriteParams& params, std::move_only_function<void(const IWriteRequest&)> callback, HANDLE file) const;

		Worker& operator =(const Worker&) = delete;
		Worker& operator =(Worker&&) = delete;

	private:
		/// @brief Adds the ongoing request.
		/// @param request Request to add.
		void AddOngoingRequest(const std::shared_ptr<OverlappedRequest>& request) const;
		/// @brief Removes the ongoing request.
		/// @param overlapped Request overlapped.
		/// @return Ongoing request.
		std::shared_ptr<OverlappedRequest> RemoveOngoingRequest(const OVERLAPPED* overlapped) const;

		/// @brief Work function.
		void Work() const noexcept;

		Log::ILogService* logService; ///< Log service.

		HANDLE iocp; ///< IO completion port.

		std::pmr::synchronized_pool_resource requestPool; ///< Request pool.
		std::pmr::polymorphic_allocator<OverlappedRequest> requestAllocator; ///< Request allocator.

		mutable std::unordered_map<const OVERLAPPED*, std::shared_ptr<OverlappedRequest>> ongoingRequests; ///< Ongoing requests.
		mutable std::mutex ongoingRequestMutex; ///< Ongoing request mutex.

		std::thread thread; ///< Worker thread.
		std::shared_ptr<Application::IThreadControl> threadControl; ///< Thread control.
		std::atomic_bool running; ///< Should the worker run?

		static_assert(std::atomic_bool::is_always_lock_free, "bool is not lock-free.");
	};
}

namespace PonyEngine::File
{
	Worker::Worker(Application::IApplication& application) :
		logService{application.FindInterface<Log::ILogService>()},
		requestAllocator(&requestPool),
		running(true)
	{
		PONY_LOG(logService, Log::LogType::Info, "Creating IOCP...");
		iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, nullptr, 0, 0);
		if (!iocp) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to create iocp: Error code = '0x{:X}'", GetLastError()));
		}
		PONY_LOG(logService, Log::LogType::Info, "Creating IOCP done. Handle: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(iocp));

		constexpr std::string_view role = PONY_STRINGIFY_VALUE(PONY_ENGINE_FILE_THREAD_ROLE);
		PONY_LOG(logService, Log::LogType::Info, "Creating io work thread... Role: '{}'.", role);
		try
		{
			thread = std::thread(&Worker::Work, this);
		}
		catch (...)
		{
			if (!CloseHandle(iocp)) [[unlikely]]
			{
				PONY_LOG(logService, Log::LogType::Error, "Failed to close iocp. Error code: '0x{:X}'.", GetLastError());
			}
			throw;
		}
		try
		{
			threadControl = application.CreateThreadControl(thread);
			threadControl->Role(role);
		}
		catch (...)
		{
			PONY_LOG(logService, Log::LogType::Error, std::current_exception(), "Failed to set io thread role.");
		}
		PONY_LOG(logService, Log::LogType::Info, "Creating io work thread done.");
	}

	Worker::~Worker() noexcept
	{
		assert(ongoingRequests.empty() && "Some file requests are still ongoing.");

		PONY_LOG(logService, Log::LogType::Info, "Closing io work thread...");
		running.store(false, std::memory_order::relaxed);
		if (!PostQueuedCompletionStatus(iocp, 0, 0, nullptr)) [[unlikely]]
		{
			PONY_LOG(logService, Log::LogType::Error, "Failed to post queued io completion status. Error code: '0x{:X}'.", GetLastError());
		}
		threadControl.reset();
		thread.join();
		PONY_LOG(logService, Log::LogType::Info, "Closing io work thread done.");

		PONY_LOG(logService, Log::LogType::Info, "Closing IOCP... Handle: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(iocp));
		if (!CloseHandle(iocp)) [[unlikely]]
		{
			PONY_LOG(logService, Log::LogType::Error, "Failed to close iocp. Error code: '0x{:X}'.", GetLastError());
		}
		PONY_LOG(logService, Log::LogType::Info, "Closing IOCP done.");
	}

	void Worker::AssociateFile(const HANDLE file) const
	{
		PONY_LOG(logService, Log::LogType::Debug, "Associating file with iocp... File handle: '0x{:X}'; IOCP: '0x{:X}'.",
			reinterpret_cast<std::uintptr_t>(file), reinterpret_cast<std::uintptr_t>(iocp));

		if (!CreateIoCompletionPort(file, iocp, 0, 0)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to create file iocp association: Error code = '0x{:X}'", GetLastError()));
		}

		PONY_LOG(logService, Log::LogType::Debug, "Associating file with iocp done. Handle: '0x{:X}; IOCP: '0x{:X}''.",
			reinterpret_cast<std::uintptr_t>(file), reinterpret_cast<std::uintptr_t>(iocp));
	}

	std::shared_ptr<IReadRequest> Worker::MakeRequest(const ReadParams& params, std::move_only_function<void(const IReadRequest&)> callback, const HANDLE file) const
	{
		if (params.buffer.size() > std::numeric_limits<DWORD>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Too great buffer");
		}

		std::shared_ptr<OverlappedRequest> request = std::allocate_shared<OverlappedRequest>(requestAllocator, params, std::move(callback), file);
		AddOngoingRequest(request);

		try
		{
			if (ReadFile(file, params.buffer.data(), static_cast<DWORD>(params.buffer.size()), nullptr, &request->Overlapped())) [[unlikely]]
			{
				DWORD bytesTransferred = 0;
				if (GetOverlappedResult(file, &request->Overlapped(), &bytesTransferred, FALSE)) [[likely]]
				{
					RemoveOngoingRequest(&request->Overlapped());
					request->SetSuccess(static_cast<std::size_t>(bytesTransferred));
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
		}
		catch (...)
		{
			RemoveOngoingRequest(&request->Overlapped());
			throw;
		}

		return std::shared_ptr<IReadRequest>(std::move(request), &request->Read());
	}

	std::shared_ptr<IWriteRequest> Worker::MakeRequest(const WriteParams& params, std::move_only_function<void(const IWriteRequest&)> callback, HANDLE file) const
	{
		if (params.buffer.size() > std::numeric_limits<DWORD>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Too great buffer");
		}

		std::shared_ptr<OverlappedRequest> request = std::allocate_shared<OverlappedRequest>(requestAllocator, params, std::move(callback), file);
		AddOngoingRequest(request);

		try
		{
			if (WriteFile(file, params.buffer.data(), static_cast<DWORD>(params.buffer.size()), nullptr, &request->Overlapped())) [[unlikely]]
			{
				DWORD bytesTransferred = 0;
				if (GetOverlappedResult(file, &request->Overlapped(), &bytesTransferred, FALSE)) [[likely]]
				{
					RemoveOngoingRequest(&request->Overlapped());
					request->SetSuccess(static_cast<std::size_t>(bytesTransferred));
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
		}
		catch (...)
		{
			RemoveOngoingRequest(&request->Overlapped());
			throw;
		}

		return std::shared_ptr<IWriteRequest>(std::move(request), &request->Write());
	}

	void Worker::AddOngoingRequest(const std::shared_ptr<OverlappedRequest>& request) const
	{
		const auto lock = std::lock_guard(ongoingRequestMutex);
		assert(!ongoingRequests.contains(&request->Overlapped()) && "Double request addition.");

		ongoingRequests[&request->Overlapped()] = request;
	}

	std::shared_ptr<OverlappedRequest> Worker::RemoveOngoingRequest(const OVERLAPPED* const overlapped) const
	{
		const auto lock = std::lock_guard(ongoingRequestMutex);
		const auto position = ongoingRequests.find(overlapped);
		assert(position != ongoingRequests.cend() && "Request wasn't added.");

		std::shared_ptr<OverlappedRequest> request = std::move(position->second);
		ongoingRequests.erase(position);
		
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
					const std::shared_ptr<OverlappedRequest> request = RemoveOngoingRequest(overlapped);
					request->SetSuccess(static_cast<std::size_t>(bytesTransferred));
				}
			}
			else [[unlikely]]
			{
				const DWORD error = GetLastError();
				if (overlapped) [[likely]]
				{
					const std::shared_ptr<OverlappedRequest> request = RemoveOngoingRequest(overlapped);

					if (error == ERROR_OPERATION_ABORTED) [[likely]]
					{
						request->SetCanceled();
					}
					else [[unlikely]]
					{
						try
						{
							throw std::runtime_error(std::format("Failed to get queued io completion status: Error code = '0x{:X}'", error));
						}
						catch (...)
						{
							const std::exception_ptr exception = std::current_exception();
							PONY_LOG(logService, Log::LogType::Error, exception);
							request->SetFailure(exception);
						}
					}
				}
				else [[unlikely]]
				{
					PONY_LOG(logService, Log::LogType::Error, "Failed to get queued io completion status. Error code: '0x{:X}'.", error);
				}
			}
		}
	}
}
