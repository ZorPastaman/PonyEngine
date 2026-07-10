/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "cassert"

export module PonyEngine.Resource.File.Impl:LoadRequest;

import std;

import PonyEngine.File;
import PonyEngine.Resource.Ext;

export namespace PonyEngine::Resource::File
{
	/// @brief Load request.
	class LoadRequest final : public ILoadRequest
	{
	public:
		/// @brief Creates a load request.
		/// @param loadParams Load parameters.
		/// @param loadCallback Load callback.
		[[nodiscard("Pure constructor")]]
		LoadRequest(const LoadParams& loadParams, const std::function<void(const ILoadRequest&)>& loadCallback) noexcept;
		[[nodiscard("Pure constructor")]]
		LoadRequest(const LoadRequest& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		LoadRequest(LoadRequest&& other) noexcept = default;

		~LoadRequest() noexcept = default;

		/// @brief Gets the file request.
		/// @return File request.
		[[nodiscard("Pure function")]]
		const std::shared_ptr<PonyEngine::File::IReadRequest>& FileRequest() const noexcept;
		/// @brief Sets the file request.
		/// @param fileRequest File request.
		void FileRequest(const std::shared_ptr<PonyEngine::File::IReadRequest>& fileRequest) noexcept;
		/// @brief Sets the file request.
		/// @param fileRequest File request.
		void FileRequest(std::shared_ptr<PonyEngine::File::IReadRequest>&& fileRequest) noexcept;

		[[nodiscard("Pure function")]] 
		virtual const LoadParams& Params() const noexcept override;

		[[nodiscard("Pure function")]] 
		virtual RequestStatus Status() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::size_t ByteCount() const override;
		[[nodiscard("Pure function")]] 
		virtual const std::exception_ptr& Exception() const override;

		virtual void Wait() const noexcept override;

		/// @brief Gets the file callback.
		/// @return File callback.
		[[nodiscard("Pure function")]]
		const std::function<void(const PonyEngine::File::IReadRequest&)>& FileCallback() const noexcept;

		LoadRequest& operator =(const LoadRequest& other) noexcept = default;
		LoadRequest& operator =(LoadRequest&& other) noexcept = default;

	private:
		std::shared_ptr<PonyEngine::File::IReadRequest> fileRequest; ///< File request.
		LoadParams loadParams; ///< Load parameters.
		std::function<void(const ILoadRequest&)> loadCallback; ///< Load callback.
		std::function<void(const PonyEngine::File::IReadRequest&)> fileCallback; ///< File callback.
	};
}

namespace PonyEngine::Resource::File
{
	LoadRequest::LoadRequest(const LoadParams& loadParams, const std::function<void(const ILoadRequest&)>& loadCallback) noexcept :
		loadParams(loadParams),
		loadCallback(loadCallback),
		fileCallback(this->loadCallback 
			? [&](const PonyEngine::File::IReadRequest&) { this->loadCallback(*this); } 
			: std::function<void(const PonyEngine::File::IReadRequest&)>(nullptr))
	{
	}

	const std::shared_ptr<PonyEngine::File::IReadRequest>& LoadRequest::FileRequest() const noexcept
	{
		return fileRequest;
	}

	void LoadRequest::FileRequest(const std::shared_ptr<PonyEngine::File::IReadRequest>& fileRequest) noexcept
	{
		this->fileRequest = fileRequest;
	}

	void LoadRequest::FileRequest(std::shared_ptr<PonyEngine::File::IReadRequest>&& fileRequest) noexcept
	{
		this->fileRequest = std::move(fileRequest);
	}

	const LoadParams& LoadRequest::Params() const noexcept
	{
		return loadParams;
	}

	RequestStatus LoadRequest::Status() const noexcept
	{
		switch (fileRequest->Status())
		{
		case PonyEngine::File::RequestStatus::Pending:
			return RequestStatus::Pending;
		case PonyEngine::File::RequestStatus::Success:
			return RequestStatus::Success;
		case PonyEngine::File::RequestStatus::Failure:
			return RequestStatus::Failure;
		default:
			assert(false && "Unexpected request status.");
			return RequestStatus::Pending;
		}
	}

	std::size_t LoadRequest::ByteCount() const
	{
		return fileRequest->ByteCount();
	}

	const std::exception_ptr& LoadRequest::Exception() const
	{
		return fileRequest->Exception();
	}

	void LoadRequest::Wait() const noexcept
	{
		fileRequest->Wait();
	}

	const std::function<void(const PonyEngine::File::IReadRequest&)>& LoadRequest::FileCallback() const noexcept
	{
		return fileCallback;
	}
}
