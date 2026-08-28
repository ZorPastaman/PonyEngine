/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.Pack.Impl:FileLoadableDataAccessRequest;

import std;

import PonyEngine.File;

import :LoadableDataAccessRequest;

export namespace PonyEngine::Resource::Pack
{
	class FileLoadableDataAccessRequest final : public LoadableDataAccessRequest
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit FileLoadableDataAccessRequest(const LoadParams& params, std::move_only_function<void(const ILoadableDataAccessRequest&) noexcept> callback) noexcept;
		FileLoadableDataAccessRequest(const FileLoadableDataAccessRequest&) = delete;
		FileLoadableDataAccessRequest(FileLoadableDataAccessRequest&&) = delete;

		virtual ~FileLoadableDataAccessRequest() noexcept override = default;

		virtual void Cancel() override;

		void FileRequest(std::shared_ptr<File::IReadRequest> fileRequest) noexcept;

		FileLoadableDataAccessRequest& operator =(const FileLoadableDataAccessRequest&) = delete;
		FileLoadableDataAccessRequest& operator =(FileLoadableDataAccessRequest&&) = delete;

	private:
		std::shared_ptr<File::IReadRequest> fileRequest;
	};
}

namespace PonyEngine::Resource::Pack
{
	FileLoadableDataAccessRequest::FileLoadableDataAccessRequest(const LoadParams& params, 
		std::move_only_function<void(const ILoadableDataAccessRequest&) noexcept> callback) noexcept :
		LoadableDataAccessRequest(params, std::move(callback))
	{
	}

	void FileLoadableDataAccessRequest::Cancel()
	{
		fileRequest->Cancel();
	}

	void FileLoadableDataAccessRequest::FileRequest(std::shared_ptr<File::IReadRequest> fileRequest) noexcept
	{
		this->fileRequest = std::move(fileRequest);
	}
}
