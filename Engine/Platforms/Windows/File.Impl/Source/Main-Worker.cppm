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

import :FileHandle;
import :OverlappedRequest;
import :ServiceContext;

export namespace PonyEngine::File
{
	/// @brief Worker. Manages an io thread, creates requests and updates them on their completion.
	class Worker final
	{
	public:
		/// @brief Creates a worker.
		/// @param context Context.
		[[nodiscard("Pure constructor")]]
		explicit Worker(const ServiceContext& context);
		Worker(const Worker&) = delete;
		Worker(Worker&&) = delete;

		~Worker() noexcept;

		/// @brief Associates the file handle with the worker iocp.
		/// @param file File.
		void AssociateFile(const std::shared_ptr<const FileHandle>& file) const;

		/// @brief Makes a read request.
		/// @param file File that created this request.
		/// @param params Read parameters.
		/// @param observer Observer. Can be nullptr.
		/// @return Overlapped read request.
		[[nodiscard("Must be used")]]
		std::shared_ptr<IReadRequest> MakeRequest(const std::shared_ptr<const FileHandle>& file, const ReadParams& params, IReadRequestObserver* observer) const;
		/// @brief Makes a write request.
		/// @param file File that created this request.
		/// @param params Write parameters.
		/// @param observer Observer. Can be nullptr.
		/// @return Overlapped write request.
		[[nodiscard("Must be used")]]
		std::shared_ptr<IWriteRequest> MakeRequest(const std::shared_ptr<const FileHandle>& file, const WriteParams& params, IWriteRequestObserver* observer) const;

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

		const ServiceContext* context; ///< Context.

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
	Worker::Worker(const ServiceContext& context) :
		context{&context},
		requestAllocator(&requestPool),
		running(true)
	{
		PONY_LOG(this->context->LogService(), Log::LogType::Info, "Creating IOCP...");
		iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, nullptr, 0, 0);
		if (!iocp) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to create iocp: Error code = '0x{:X}'", GetLastError()));
		}
		PONY_LOG(this->context->LogService(), Log::LogType::Info, "Creating IOCP done. Handle: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(iocp));

		constexpr std::string_view role = PONY_STRINGIFY_VALUE(PONY_ENGINE_FILE_THREAD_ROLE);
		PONY_LOG(this->context->LogService(), Log::LogType::Info, "Creating io work thread... Role: '{}'.", role);
		try
		{
			thread = std::thread(&Worker::Work, this);
		}
		catch (...)
		{
			if (!CloseHandle(iocp)) [[unlikely]]
			{
				PONY_LOG(this->context->LogService(), Log::LogType::Error, "Failed to close iocp. Error code: '0x{:X}'.", GetLastError());
			}
			throw;
		}
		try
		{
			threadControl = this->context->Application().CreateThreadControl(thread);
			threadControl->Role(role);
		}
		catch (...)
		{
			PONY_LOG(this->context->LogService(), Log::LogType::Error, std::current_exception(), "Failed to set io thread role.");
		}
		PONY_LOG(this->context->LogService(), Log::LogType::Info, "Creating io work thread done.");
	}

	Worker::~Worker() noexcept
	{
		PONY_LOG(context->LogService(), Log::LogType::Info, "Closing io work thread...");
		running.store(false, std::memory_order::relaxed);
		if (!PostQueuedCompletionStatus(iocp, 0, 0, nullptr)) [[unlikely]]
		{
			PONY_LOG(context->LogService(), Log::LogType::Error, "Failed to post queued io completion status. Error code: '0x{:X}'.", GetLastError());
		}
		threadControl.reset();
		thread.join();
		PONY_LOG(context->LogService(), Log::LogType::Info, "Closing io work thread done.");

		PONY_LOG(context->LogService(), Log::LogType::Info, "Closing IOCP... Handle: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(iocp));
		if (!CloseHandle(iocp)) [[unlikely]]
		{
			PONY_LOG(context->LogService(), Log::LogType::Error, "Failed to close iocp. Error code: '0x{:X}'.", GetLastError());
		}
		PONY_LOG(context->LogService(), Log::LogType::Info, "Closing IOCP done.");
	}

	void Worker::AssociateFile(const std::shared_ptr<const FileHandle>& file) const
	{
		PONY_LOG(context->LogService(), Log::LogType::Debug, "Associating file with iocp... File handle: '0x{:X}'; IOCP: '0x{:X}'.",
			reinterpret_cast<std::uintptr_t>(file->Handle()), reinterpret_cast<std::uintptr_t>(iocp));
		if (!CreateIoCompletionPort(file->Handle(), iocp, reinterpret_cast<ULONG_PTR>(file.get()), 0)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to create file iocp association: Error code = '0x{:X}'", GetLastError()));
		}
		PONY_LOG(context->LogService(), Log::LogType::Debug, "Associating file with iocp done. Handle: '0x{:X}; IOCP: '0x{:X}''.",
			reinterpret_cast<std::uintptr_t>(file->Handle()), reinterpret_cast<std::uintptr_t>(iocp));
	}

	std::shared_ptr<IReadRequest> Worker::MakeRequest(const std::shared_ptr<const FileHandle>& file, const ReadParams& params, IReadRequestObserver* const observer) const
	{
		if (params.buffer.size() > std::numeric_limits<DWORD>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Too great buffer");
		}

		std::shared_ptr<OverlappedRequest> request = std::allocate_shared<OverlappedRequest>(requestAllocator, file, params, observer);
		AddOngoingRequest(request);

		try
		{
			if (ReadFile(file->Handle(), params.buffer.data(), static_cast<DWORD>(params.buffer.size()), nullptr, &request->Overlapped())) [[unlikely]]
			{
				DWORD bytesTransferred = 0;
				if (GetOverlappedResult(file->Handle(), &request->Overlapped(), &bytesTransferred, FALSE)) [[likely]]
				{
					RemoveOngoingRequest(&request->Overlapped());
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
		}
		catch (...)
		{
			RemoveOngoingRequest(&request->Overlapped());
			throw;
		}

		return std::shared_ptr<IReadRequest>(std::move(request), &request->Request().Read());
	}

	std::shared_ptr<IWriteRequest> Worker::MakeRequest(const std::shared_ptr<const FileHandle>& file, const WriteParams& params, IWriteRequestObserver* const observer) const
	{
		if (params.buffer.size() > std::numeric_limits<DWORD>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Too great buffer");
		}

		std::shared_ptr<OverlappedRequest> request = std::allocate_shared<OverlappedRequest>(requestAllocator, file, params, observer);
		AddOngoingRequest(request);

		try
		{
			if (WriteFile(file->Handle(), params.buffer.data(), static_cast<DWORD>(params.buffer.size()), nullptr, &request->Overlapped())) [[unlikely]]
			{
				DWORD bytesTransferred = 0;
				if (GetOverlappedResult(file->Handle(), &request->Overlapped(), &bytesTransferred, FALSE)) [[likely]]
				{
					RemoveOngoingRequest(&request->Overlapped());
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
		}
		catch (...)
		{
			RemoveOngoingRequest(&request->Overlapped());
			throw;
		}

		return std::shared_ptr<IWriteRequest>(std::move(request), &request->Request().Write());
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
					request->Request().SetSuccess(static_cast<std::size_t>(bytesTransferred));
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
						request->Request().SetCanceled();
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
							PONY_LOG(context->LogService(), Log::LogType::Error, exception);
							request->Request().SetFailure(exception);
						}
					}
				}
				else [[unlikely]]
				{
					PONY_LOG(context->LogService(), Log::LogType::Error, "Failed to get queued io completion status. Error code: '0x{:X}'.", error);
				}
			}
		}
	}
}
