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

export module PonyEngine.Resource.Pack.Impl:FilePackMountRequest;

import std;

import PonyEngine.File;
import PonyEngine.Resource.Pack;

import :PackMountRequest;

export namespace PonyEngine::Resource::Pack
{
	/// @brief File pack mount request.
	class FilePackMountRequest final : public PackMountRequest
	{
	public:
		/// @brief Creates a file pack mount request.
		/// @param manifestFile Manifest file.
		/// @param dataFile Data file.
		/// @param accessType Access type.
		/// @param manifestBuffer Manifest buffer.
		/// @param manifestSize Manifest size in bytes.
		/// @param dataBuffer Data buffer.
		/// @param dataSize Data size in bytes.
		/// @param callback Request callback.
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

		/// @brief Gets the manifest file.
		/// @return Manifest file.
		[[nodiscard("Pure function")]]
		const std::shared_ptr<File::IFile>& ManifestFile() const noexcept;
		/// @brief Gets the writable manifest buffer.
		/// @return Writable manifest buffer.
		[[nodiscard("Pure function")]]
		std::span<std::byte> ManifestTarget() const noexcept;
		/// @brief Gets the manifest file read request.
		/// @return Manifest file read request.
		[[nodiscard("Pure function")]]
		const std::shared_ptr<File::IReadRequest>& ManifestReadRequest() const noexcept;
		/// @brief Sets the manifest file read request.
		/// @param request Manifest file read request.
		void ManifestReadRequest(std::shared_ptr<File::IReadRequest> request) noexcept;

		/// @brief Gets the data file.
		/// @return Data file.
		[[nodiscard("Pure function")]]
		const std::shared_ptr<File::IFile>& DataFile() const noexcept;
		/// @brief Gets the data file read request.
		/// @return Data file read request.
		[[nodiscard("Pure function")]]
		const std::shared_ptr<File::IReadRequest>& DataReadRequest() const noexcept;
		/// @brief Sets the data file read request.
		/// @param request Data file read request.
		void DataReadRequest(std::shared_ptr<File::IReadRequest> request) noexcept;

		FilePackMountRequest& operator =(const FilePackMountRequest&) = delete;
		FilePackMountRequest& operator =(FilePackMountRequest&&) = delete;

	private:
		std::unique_ptr<std::byte[]> manifestBuffer; ///< Writable manifest buffer.
		std::shared_ptr<File::IFile> manifestFile; ///< Manifest file.
		std::shared_ptr<File::IReadRequest> manifestReadRequest; ///< Manifest read request.
		std::shared_ptr<File::IFile> dataFile; ///< Data file.
		std::shared_ptr<File::IReadRequest> dataReadRequest; ///< Data read request.
	};
}

namespace PonyEngine::Resource::Pack
{
	FilePackMountRequest::FilePackMountRequest(std::shared_ptr<File::IFile> manifestFile, std::shared_ptr<File::IFile> dataFile, const enum AccessType accessType,
		std::unique_ptr<std::byte[]> manifestBuffer, const std::size_t manifestSize, std::shared_ptr<std::byte[]> dataBuffer, const std::size_t dataSize, 
		std::move_only_function<void(const IPackMountRequest&) noexcept> callback) noexcept :
		PackMountRequest(accessType, manifestBuffer.get(), manifestSize, std::move(dataBuffer), dataSize, std::move(callback)),
		manifestBuffer(std::move(manifestBuffer)),
		manifestFile(std::move(manifestFile)),
		dataFile(std::move(dataFile))
	{
		assert(this->manifestFile && "Manifest file is nullptr.");
		assert(this->dataFile && "Data file is nullptr.");
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

	std::span<std::byte> FilePackMountRequest::ManifestTarget() const noexcept
	{
		return std::span<std::byte>(manifestBuffer.get(), ManifestSize());
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
