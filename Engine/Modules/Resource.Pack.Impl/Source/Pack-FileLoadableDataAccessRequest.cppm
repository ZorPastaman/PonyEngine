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
	/// @brief File loadable data access request.
	class FileLoadableDataAccessRequest final : public LoadableDataAccessRequest
	{
	public:
		/// @brief Creates a file loadable data access request.
		/// @param params Load parameters.
		/// @param callback Callback.
		[[nodiscard("Pure constructor")]]
		explicit FileLoadableDataAccessRequest(const LoadParams& params, std::move_only_function<void(const ILoadableDataAccessRequest&) noexcept> callback) noexcept;
		FileLoadableDataAccessRequest(const FileLoadableDataAccessRequest&) = delete;
		FileLoadableDataAccessRequest(FileLoadableDataAccessRequest&&) = delete;

		virtual ~FileLoadableDataAccessRequest() noexcept override = default;

		virtual void Cancel() override;

		/// @brief Gets the file request.
		/// @return File request.
		[[nodiscard("Pure function")]]
		const std::shared_ptr<File::IReadRequest>& FileRequest() const noexcept;
		/// @brief Sets the file request.
		/// @param fileRequest File request.
		void FileRequest(std::shared_ptr<File::IReadRequest> fileRequest) noexcept;

		FileLoadableDataAccessRequest& operator =(const FileLoadableDataAccessRequest&) = delete;
		FileLoadableDataAccessRequest& operator =(FileLoadableDataAccessRequest&&) = delete;

	private:
		std::shared_ptr<File::IReadRequest> fileRequest; ///< File request.
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

	const std::shared_ptr<File::IReadRequest>& FileLoadableDataAccessRequest::FileRequest() const noexcept
	{
		return fileRequest;
	}

	void FileLoadableDataAccessRequest::FileRequest(std::shared_ptr<File::IReadRequest> fileRequest) noexcept
	{
		this->fileRequest = std::move(fileRequest);
	}
}
