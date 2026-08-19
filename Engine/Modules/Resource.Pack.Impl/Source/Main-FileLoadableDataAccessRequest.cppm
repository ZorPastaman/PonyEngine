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

export module PonyEngine.Resource.Pack.Impl:FileLoadableDataAccessRequest;

import std;

import PonyEngine.File;
import PonyEngine.Resource.Ext;

export namespace PonyEngine::Resource::Pack
{
	class FileLoadableDataAccessRequest final : public ILoadableDataAccessRequest, private File::IReadRequestObserver
	{
	public:
		[[nodiscard("Pure constructor")]]
		FileLoadableDataAccessRequest(File::IFile& dataFile, std::size_t offset, std::span<std::byte> buffer, ILoadableDataAccessRequestObserver* observer);
		FileLoadableDataAccessRequest(const FileLoadableDataAccessRequest&) = delete;
		FileLoadableDataAccessRequest(FileLoadableDataAccessRequest&&) = delete;

		~FileLoadableDataAccessRequest() noexcept;

		[[nodiscard("Pure function")]]
		virtual LoadableRequestStatus Status() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::size_t ByteCount() const override;
		[[nodiscard("Pure function")]]
		virtual const std::exception_ptr& Exception() const override;

		virtual void Cancel() override;

		virtual void Wait() const noexcept override;

		FileLoadableDataAccessRequest& operator =(const FileLoadableDataAccessRequest&) = delete;
		FileLoadableDataAccessRequest& operator =(FileLoadableDataAccessRequest&&) = delete;

	private:
		virtual void OnSuccess(std::size_t byteCount) noexcept override;
		virtual void OnFailure(const std::exception_ptr& exception) noexcept override;
		virtual void OnCancel() noexcept override;

		ILoadableDataAccessRequestObserver* observer;

		std::atomic<LoadableRequestStatus> status;

		std::shared_ptr<File::IReadRequest> fileRequest;

		static_assert(std::atomic<LoadableRequestStatus>::is_always_lock_free, "LoadableRequestStatus isn't lock-free.");
		static_assert(std::atomic_bool::is_always_lock_free, "bool isn't lock-free.");
	};
}

namespace PonyEngine::Resource::Pack
{
	FileLoadableDataAccessRequest::FileLoadableDataAccessRequest(File::IFile& dataFile, const std::size_t offset,
		const std::span<std::byte> buffer, ILoadableDataAccessRequestObserver* const observer) :
		observer{observer},
		status(LoadableRequestStatus::Pending),
		isFinished(false),
		fileRequest(dataFile.Read(File::ReadParams{.buffer = buffer, .offset = offset}, this))
	{
	}

	FileLoadableDataAccessRequest::~FileLoadableDataAccessRequest() noexcept
	{
		if (status.load(std::memory_order::relaxed) == LoadableRequestStatus::Pending)
		{
			Cancel();
		}

		while (!isFinished.load(std::memory_order::relaxed))
		{
			isFinished.wait(false, std::memory_order::relaxed);
		}
	}

	LoadableRequestStatus FileLoadableDataAccessRequest::Status() const noexcept
	{
		return status.load(std::memory_order::acquire);
	}

	std::size_t FileLoadableDataAccessRequest::ByteCount() const
	{
		return fileRequest->ByteCount();
	}

	const std::exception_ptr& FileLoadableDataAccessRequest::Exception() const
	{
		return fileRequest->Exception();
	}

	void FileLoadableDataAccessRequest::Cancel()
	{
		fileRequest->Cancel();
	}

	void FileLoadableDataAccessRequest::Wait() const noexcept
	{
		while (status.load(std::memory_order::acquire) == LoadableRequestStatus::Pending)
		{
			status.wait(LoadableRequestStatus::Pending, std::memory_order::acquire);
		}
	}

	void FileLoadableDataAccessRequest::OnSuccess(const std::size_t byteCount) noexcept
	{
		status.store(LoadableRequestStatus::Success, std::memory_order::release);
		status.notify_all();

		if (observer)
		{
			observer->OnSuccess(byteCount);
		}

		isFinished.store(true, std::memory_order::relaxed);
		isFinished.notify_one();
	}

	void FileLoadableDataAccessRequest::OnFailure(const std::exception_ptr& exception) noexcept
	{
		status.store(LoadableRequestStatus::Failure, std::memory_order::release);
		status.notify_all();

		if (observer)
		{
			observer->OnFailure(exception);
		}

		isFinished.store(true, std::memory_order::relaxed);
		isFinished.notify_one();
	}

	void FileLoadableDataAccessRequest::OnCancel() noexcept
	{
		status.store(LoadableRequestStatus::Canceled, std::memory_order::release);
		status.notify_all();

		if (observer)
		{
			observer->OnCancel();
		}

		isFinished.store(true, std::memory_order::relaxed);
		isFinished.notify_one();
	}
}
