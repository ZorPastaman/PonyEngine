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

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

export module PonyEngine.File.Impl.WinAPI:Worker;

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
		std::shared_ptr<IReadRequest> MakeRequest(const ReadParams& params, std::move_only_function<void(const IReadRequest&) noexcept> callback, HANDLE file) const;
		/// @brief Makes a write request.
		/// @param params Write parameters.
		/// @param callback Callback.
		/// @param file File that created this request.
		/// @return Write request.
		[[nodiscard("Must be used")]]
		std::shared_ptr<IWriteRequest> MakeRequest(const WriteParams& params, std::move_only_function<void(const IWriteRequest&) noexcept> callback, HANDLE file) const;

		Worker& operator =(const Worker&) = delete;
		Worker& operator =(Worker&&) = delete;

	private:
		/// @brief Adds the ongoing request.
		/// @param request Request to add.
		void AddOngoingRequest(const std::shared_ptr<OverlappedRequest>& request) const;
		/// @brief Removes the ongoing request.
		/// @param overlapped Request overlapped.
		/// @return Ongoing request.
		std::shared_ptr<OverlappedRequest> RemoveOngoingRequest(const OVERLAPPED* overlapped) const noexcept;

		/// @brief Increment the ongoing request count.
		void IncrementOngoingRequestCount() const noexcept;
		/// @brief Decrement the ongoing request count.
		void DecrementOngoingRequestCount() const noexcept;
		/// @brief Wait till the ongoing request count reaches 0.
		void WaitForOngoingRequestCountToFinish() const noexcept;

		/// @brief Work function.
		void Work() const noexcept;

		Log::ILogService* logService; ///< Log service.

		HANDLE iocp; ///< IO completion port.

		mutable std::pmr::synchronized_pool_resource requestPool; ///< Request pool.
		mutable std::pmr::polymorphic_allocator<OverlappedRequest> requestAllocator; ///< Request allocator.

		mutable std::unordered_map<const OVERLAPPED*, std::shared_ptr<OverlappedRequest>> ongoingRequests; ///< Ongoing requests.
		mutable std::mutex ongoingRequestMutex; ///< Ongoing request mutex.
		mutable std::atomic_size_t ongoingRequestCount; ///< Ongoing request count.

		std::thread thread; ///< Worker thread.
		std::atomic_bool running; ///< Should the worker run?

#ifndef NDEBUG
		mutable std::atomic_size_t requestCount;
#endif

		static_assert(std::atomic_bool::is_always_lock_free, "bool is not lock-free.");
		static_assert(std::atomic_size_t::is_always_lock_free, "std::size_t isn't lock-free.");
	};
}

namespace PonyEngine::File
{
	Worker::Worker(Application::IApplication& application) :
#ifndef NDEBUG
		requestCount(0uz),
#endif
		logService{application.FindInterface<Log::ILogService>()},
		requestAllocator(&requestPool),
		ongoingRequestCount(0uz),
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
			thread = application.CreateThread([this] { Work(); }, Application::ThreadParams
			{
				.role = role,
				.onBeginException = [ls = logService](const std::exception_ptr& exception) noexcept
				{
					PONY_LOG(ls, Log::LogType::Error, exception, "On beginning IO thread. ID: '{}'.", std::this_thread::get_id());
					return true;
				},
				.onEndException = [ls = logService](const std::exception_ptr& exception) noexcept
				{
					PONY_LOG(ls, Log::LogType::Error, exception, "On ending IO thread. ID: '{}'.", std::this_thread::get_id());
				}
			});
		}
		catch (...)
		{
			if (!CloseHandle(iocp)) [[unlikely]]
			{
				PONY_LOG(logService, Log::LogType::Error, "Failed to close iocp. Error code: '0x{:X}'.", GetLastError());
			}
			throw;
		}
		PONY_LOG(logService, Log::LogType::Info, "Creating io work thread done.");
	}

	Worker::~Worker() noexcept
	{
		WaitForOngoingRequestCountToFinish();

#ifndef NDEBUG
		assert(requestCount.load(std::memory_order::relaxed) == 0uz && "Some file requests are still alive.");
#endif

		PONY_LOG(logService, Log::LogType::Info, "Closing io work thread...");
		running.store(false, std::memory_order::relaxed);
		if (!PostQueuedCompletionStatus(iocp, 0, 0, nullptr)) [[unlikely]]
		{
			PONY_LOG(logService, Log::LogType::Error, "Failed to post queued io completion status. Error code: '0x{:X}'.", GetLastError());
		}
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

	std::shared_ptr<IReadRequest> Worker::MakeRequest(const ReadParams& params, std::move_only_function<void(const IReadRequest&) noexcept> callback, const HANDLE file) const
	{
		if (!params.buffer.data()) [[unlikely]]
		{
			throw std::invalid_argument("Buffer is nullptr");
		}
		if (params.buffer.size() > std::numeric_limits<DWORD>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Too great buffer");
		}

#ifndef NDEBUG
		const auto overlappedRequest = requestAllocator.new_object<OverlappedRequest>(params, std::move(callback), file);
		requestCount.fetch_add(1uz, std::memory_order::relaxed);
		std::shared_ptr<OverlappedRequest> request;
		try
		{
			request = std::shared_ptr<OverlappedRequest>(overlappedRequest, [this](OverlappedRequest* const req)
			{
				requestAllocator.delete_object(req);
				requestCount.fetch_sub(1uz, std::memory_order::relaxed);
			}, requestAllocator);
		}
		catch (...)
		{
			requestAllocator.delete_object(overlappedRequest);
			requestCount.fetch_sub(1uz, std::memory_order::relaxed);
			throw;
		}
#else
		std::shared_ptr<OverlappedRequest> request = std::allocate_shared<OverlappedRequest>(requestAllocator, params, std::move(callback), file);
#endif
		IncrementOngoingRequestCount();
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
					DecrementOngoingRequestCount();
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
			DecrementOngoingRequestCount();
			throw;
		}

		return std::shared_ptr<IReadRequest>(std::move(request), &request->Read());
	}

	std::shared_ptr<IWriteRequest> Worker::MakeRequest(const WriteParams& params, std::move_only_function<void(const IWriteRequest&) noexcept> callback, HANDLE file) const
	{
		if (!params.buffer.data()) [[unlikely]]
		{
			throw std::invalid_argument("Buffer is nullptr");
		}
		if (params.buffer.size() > std::numeric_limits<DWORD>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Too great buffer");
		}

#ifndef NDEBUG
		const auto overlappedRequest = requestAllocator.new_object<OverlappedRequest>(params, std::move(callback), file);
		requestCount.fetch_add(1uz, std::memory_order::relaxed);
		std::shared_ptr<OverlappedRequest> request;
		try
		{
			request = std::shared_ptr<OverlappedRequest>(overlappedRequest, [this](OverlappedRequest* const req)
			{
				requestAllocator.delete_object(req);
				requestCount.fetch_sub(1uz, std::memory_order::relaxed);
			}, requestAllocator);
		}
		catch (...)
		{
			requestAllocator.delete_object(overlappedRequest);
			requestCount.fetch_sub(1uz, std::memory_order::relaxed);
			throw;
		}
#else
		std::shared_ptr<OverlappedRequest> request = std::allocate_shared<OverlappedRequest>(requestAllocator, params, std::move(callback), file);
#endif
		IncrementOngoingRequestCount();
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
					DecrementOngoingRequestCount();
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
			DecrementOngoingRequestCount();
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

	std::shared_ptr<OverlappedRequest> Worker::RemoveOngoingRequest(const OVERLAPPED* const overlapped) const noexcept
	{
		const auto lock = std::lock_guard(ongoingRequestMutex);
		const auto position = ongoingRequests.find(overlapped);
		assert(position != ongoingRequests.cend() && "Request wasn't added.");

		std::shared_ptr<OverlappedRequest> request = std::move(position->second);
		ongoingRequests.erase(position);
		
		return request;
	}

	void Worker::IncrementOngoingRequestCount() const noexcept
	{
		ongoingRequestCount.fetch_add(1uz, std::memory_order::release);
	}

	void Worker::DecrementOngoingRequestCount() const noexcept
	{
		ongoingRequestCount.fetch_sub(1uz, std::memory_order::release);
		ongoingRequestCount.notify_one();
	}

	void Worker::WaitForOngoingRequestCountToFinish() const noexcept
	{
		for (std::size_t requestCount = ongoingRequestCount.load(std::memory_order::acquire);
			requestCount > 0uz;
			requestCount = ongoingRequestCount.load(std::memory_order::acquire))
		{
			ongoingRequestCount.wait(requestCount, std::memory_order::acquire);
		}
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
							throw std::runtime_error(std::format("Failed to do file async operation: Error code = '0x{:X}'", error));
						}
						catch (...)
						{
							std::exception_ptr exception = std::current_exception();
							request->SetFailure(std::move(exception));
						}
					}
				}
				else [[unlikely]]
				{
					PONY_LOG(logService, Log::LogType::Error, "Failed to get queued io completion status. Error code: '0x{:X}'.", error);
				}
			}

			if (overlapped) [[likely]]
			{
				DecrementOngoingRequestCount();
			}
		}
	}
}
