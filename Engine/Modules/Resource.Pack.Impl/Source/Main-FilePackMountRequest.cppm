/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.Pack.Impl:FilePackMountRequest;

import std;

import PonyEngine.File;
import PonyEngine.Resource.Pack;

import :PackMountRequest;

export namespace PonyEngine::Resource::Pack
{
	class FilePackMountRequest final : public PackMountRequest
	{
	public:
		[[nodiscard("Pure constructor")]]
		FilePackMountRequest(std::shared_ptr<File::IFile> manifestFile, std::shared_ptr<File::IFile> dataFile, enum AccessType accessType, 
			std::unique_ptr<std::byte[]> manifestBuffer, std::size_t manifestSize, std::shared_ptr<std::byte[]> dataBuffer, std::size_t dataSize, 
			std::move_only_function<void(const IPackMountRequest&) noexcept> callback) noexcept;
		FilePackMountRequest(const FilePackMountRequest&) = delete;
		FilePackMountRequest(FilePackMountRequest&&) = delete;

		virtual ~FilePackMountRequest() noexcept override = default;

		virtual void Cancel() override;

		[[nodiscard("Pure function")]] 
		virtual bool IsFileSource() const noexcept override;

		[[nodiscard("Pure function")]]
		const std::shared_ptr<File::IFile>& ManifestFile() const noexcept;
		[[nodiscard("Pure function")]]
		const std::shared_ptr<File::IReadRequest>& ManifestReadRequest() const noexcept;
		void ManifestReadRequest(std::shared_ptr<File::IReadRequest> request) noexcept;

		[[nodiscard("Pure function")]]
		const std::shared_ptr<File::IFile>& DataFile() const noexcept;
		[[nodiscard("Pure function")]]
		const std::shared_ptr<File::IReadRequest>& DataReadRequest() const noexcept;
		void DataReadRequest(std::shared_ptr<File::IReadRequest> request) noexcept;

		FilePackMountRequest& operator =(const FilePackMountRequest&) = delete;
		FilePackMountRequest& operator =(FilePackMountRequest&&) = delete;

	private:
		std::unique_ptr<std::byte[]> manifestBuffer;
		std::shared_ptr<File::IFile> manifestFile;
		std::shared_ptr<File::IReadRequest> manifestReadRequest;
		std::shared_ptr<File::IFile> dataFile;
		std::shared_ptr<File::IReadRequest> dataReadRequest;
	};
}

namespace PonyEngine::Resource::Pack
{
	FilePackMountRequest::FilePackMountRequest(std::shared_ptr<File::IFile> manifestFile, std::shared_ptr<File::IFile> dataFile, const enum AccessType accessType,
		std::unique_ptr<std::byte[]> manifestBuffer, const std::size_t manifestSize, std::shared_ptr<std::byte[]> dataBuffer, const std::size_t dataSize, 
		std::move_only_function<void(const IPackMountRequest&) noexcept> callback) noexcept :
		PackMountRequest(accessType, std::span(manifestBuffer.get(), manifestSize), std::move(dataBuffer), dataSize, std::move(callback)),
		manifestBuffer(std::move(manifestBuffer)),
		manifestFile(std::move(manifestFile)),
		dataFile(std::move(dataFile))
	{
	}

	void FilePackMountRequest::Cancel()
	{
		PackMountRequest::Cancel();

		if (manifestReadRequest)
		{
			manifestReadRequest->Cancel();
		}

		if (dataReadRequest)
		{
			dataReadRequest->Cancel();
		}
	}

	bool FilePackMountRequest::IsFileSource() const noexcept
	{
		return true;
	}

	const std::shared_ptr<File::IFile>& FilePackMountRequest::ManifestFile() const noexcept
	{
		return manifestFile;
	}

	const std::shared_ptr<File::IReadRequest>& FilePackMountRequest::ManifestReadRequest() const noexcept
	{
		return manifestReadRequest;
	}

	void FilePackMountRequest::ManifestReadRequest(std::shared_ptr<File::IReadRequest> request) noexcept
	{
		manifestReadRequest = std::move(request);
	}

	const std::shared_ptr<File::IFile>& FilePackMountRequest::DataFile() const noexcept
	{
		return dataFile;
	}

	const std::shared_ptr<File::IReadRequest>& FilePackMountRequest::DataReadRequest() const noexcept
	{
		return dataReadRequest;
	}

	void FilePackMountRequest::DataReadRequest(std::shared_ptr<File::IReadRequest> request) noexcept
	{
		dataReadRequest = std::move(request);
	}
}
