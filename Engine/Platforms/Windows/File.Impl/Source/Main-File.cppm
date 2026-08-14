/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.File.Impl.Windows:File;

import std;

import PonyEngine.File.Impl;

import :FileHandle;
import :ServiceContext;
import :Worker;

export namespace PonyEngine::File
{
	/// @brief File.
	class File final : public IFile
	{
	public:
		/// @brief Opens a file.
		/// @param worker Worker.
		/// @param context Context.
		/// @param path File path
		/// @param params File parameters.
		[[nodiscard("Pure constructor")]]
		File(Worker& worker, const ServiceContext& context, const std::filesystem::path& path, FileParams params);
		File(const File&) = delete;
		File(File&&) = delete;

		~File() noexcept = default;

		[[nodiscard("Pure function")]] 
		virtual const std::filesystem::path& Path() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual FileAccess Access() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual FileFlag Flags() const noexcept override;

		[[nodiscard("Must be used")]] 
		virtual std::shared_ptr<IReadRequest> Read(const ReadParams& params, IReadRequestObserver* observer) override;
		[[nodiscard("Must be used")]] 
		virtual std::shared_ptr<IWriteRequest> Write(const WriteParams& params, IWriteRequestObserver* observer) override;

		File& operator =(const File&) = delete;
		File& operator =(File&&) = delete;

	private:
		Worker* worker; ///< Worker.

		FileInfo fileInfo; ///< File info.
		std::shared_ptr<const FileHandle> fileHandle; ///< File handle.
	};
}

namespace PonyEngine::File
{
	File::File(Worker& worker, const ServiceContext& context, const std::filesystem::path& path, const FileParams params) :
		worker{&worker},
		fileInfo(path, params.access, params.flags),
		fileHandle(std::make_shared<FileHandle>(context, path, params))
	{
		this->worker->AssociateFile(fileHandle);
	}

	const std::filesystem::path& File::Path() const noexcept
	{
		return fileInfo.Path();
	}

	FileAccess File::Access() const noexcept
	{
		return fileInfo.Access();
	}

	FileFlag File::Flags() const noexcept
	{
		return fileInfo.Flags();
	}

	std::shared_ptr<IReadRequest> File::Read(const ReadParams& params, IReadRequestObserver* const observer)
	{
		fileInfo.ValidateRead();
		return worker->MakeRequest(fileHandle, params, observer);
	}

	std::shared_ptr<IWriteRequest> File::Write(const WriteParams& params, IWriteRequestObserver* const observer)
	{
		fileInfo.ValidateWrite();
		return worker->MakeRequest(fileHandle, params, observer);
	}
}
