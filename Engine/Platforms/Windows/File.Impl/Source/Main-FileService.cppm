/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.File.Impl.Windows:FileService;

import std;

import PonyEngine.Application;
import PonyEngine.File;

import :File;
import :ServiceContext;
import :Worker;

export namespace PonyEngine::File
{
	/// @brief File service.
	class FileService final : public IFileService
	{
	public:
		/// @brief Creates a file service.
		/// @param application Application.
		[[nodiscard("Pure constructor")]]
		explicit FileService(Application::IApplication& application);
		FileService(const FileService&) = delete;
		FileService(FileService&&) = delete;

		~FileService() noexcept;

		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<IFile> OpenFile(const std::filesystem::path& path, FileParams params) override;

		FileService& operator =(const FileService&) = delete;
		FileService& operator =(FileService&&) = delete;

	private:
		ServiceContext context; ///< Context.
		Worker worker; ///< Worker.
	};
}

namespace PonyEngine::File
{
	FileService::FileService(Application::IApplication& application) :
		context(application),
		worker(context)
	{
	}

	FileService::~FileService() noexcept
	{
		context.EnsureZeroCounts();
	}

	std::shared_ptr<IFile> FileService::OpenFile(const std::filesystem::path& path, const FileParams params)
	{
		return std::make_shared<File>(worker, context, path, params);
	}
}
