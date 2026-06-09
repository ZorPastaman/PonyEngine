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

import PonyEngine.Application.Ext;
import PonyEngine.File.Impl;
import PonyEngine.Log;

import :OverlappedRequest;

export namespace PonyEngine::File::Windows
{
	class Worker final
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit Worker(const Application::IApplicationContext& application);
		Worker(const Worker&) = delete;
		Worker(Worker&&) = delete;

		~Worker() noexcept;

		[[nodiscard("Must be used")]]
		std::shared_ptr<OverlappedRequest> MakeRequest(HANDLE fileHandle, const ReadParams& params, const std::function<void(const IReadRequest&)>& callback) const;
		[[nodiscard("Must be used")]]
		std::shared_ptr<OverlappedRequest> MakeRequest(HANDLE fileHandle, const WriteParams& params, const std::function<void(const IWriteRequest&)>& callback) const;

		Worker& operator =(const Worker&) = delete;
		Worker& operator =(Worker&&) = delete;

	private:
		void Work() const noexcept;

		const Application::IApplicationContext* application;

		HANDLE iocp;
		std::atomic_bool running;

		std::thread thread;

		static_assert(sizeof(std::size_t) >= sizeof(DWORD), "std::size_t is less than DWORD.");
		static_assert(std::atomic_bool::is_always_lock_free, "bool is not lock-free.");
	};
}

namespace PonyEngine::File::Windows
{
	Worker::Worker(const Application::IApplicationContext& application) :
		application{&application},
		iocp(CreateIoCompletionPort(INVALID_HANDLE_VALUE, nullptr, 0, 0)),
		running(true)
	{
		if (!iocp) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to create iocp: Error code = '0x{:X}'", GetLastError()));
		}

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
	}

	Worker::~Worker() noexcept
	{
		running.store(false, std::memory_order::relaxed);
		if (!PostQueuedCompletionStatus(iocp, 0, 0, nullptr)) [[unlikely]]
		{
			PONY_LOG(application->Logger(), Log::LogType::Error, "Failed to post queued io completion status. Error code: '0x{:X}'.", GetLastError());
		}
		thread.join();
		if (!CloseHandle(iocp)) [[unlikely]]
		{
			PONY_LOG(application->Logger(), Log::LogType::Error, "Failed to close iocp. Error code: '0x{:X}'.", GetLastError());
		}
	}

	std::shared_ptr<OverlappedRequest> Worker::MakeRequest(const HANDLE fileHandle, const ReadParams& params, const std::function<void(const IReadRequest&)>& callback) const
	{
#ifndef NDEBUG
		if (params.buffer.size() > std::numeric_limits<DWORD>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Too great buffer");
		}
#endif

		const auto request = std::make_shared<OverlappedRequest>(params, callback);

		if (!CreateIoCompletionPort(fileHandle, iocp, reinterpret_cast<ULONG_PTR>(request.get()), 0)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to create file iocp: Error code = '0x{:X}'", GetLastError()));
		}

		if (!ReadFile(fileHandle, params.buffer.data(), static_cast<DWORD>(params.buffer.size()), nullptr, &request->Overlapped())) [[unlikely]]
		{
			if (const DWORD error = GetLastError(); error != ERROR_IO_PENDING)
			{
				throw std::runtime_error(std::format("Failed to create file read task: Error code = '0x{:X}'", error));
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

		const auto request = std::make_shared<OverlappedRequest>(params, callback);

		if (!CreateIoCompletionPort(fileHandle, iocp, reinterpret_cast<ULONG_PTR>(request.get()), 0)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to create file iocp: Error code = '0x{:X}'", GetLastError()));
		}

		if (!WriteFile(fileHandle, params.buffer.data(), static_cast<DWORD>(params.buffer.size()), nullptr, &request->Overlapped())) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to create file write task: Error code = '0x{:X}'", GetLastError()));
		}

		return request;
	}

	void Worker::Work() const noexcept
	{
		while (running.load(std::memory_order::relaxed))
		{
			DWORD bytesTransferred = 0;
			ULONG_PTR completionKey = 0;
			OVERLAPPED* completedOverlapped = nullptr;

			if (GetQueuedCompletionStatus(iocp, &bytesTransferred, &completionKey, &completedOverlapped, INFINITE)) [[likely]]
			{
				if (completionKey) [[likely]]
				{
					const auto request = reinterpret_cast<OverlappedRequest*>(completionKey);
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
					PONY_LOG_X(application->Logger(), exception);

					if (completionKey)
					{
						const auto request = reinterpret_cast<OverlappedRequest*>(completionKey);
						request->Request().SetFailed(exception);
					}
				}
			}
		}
	}
}
