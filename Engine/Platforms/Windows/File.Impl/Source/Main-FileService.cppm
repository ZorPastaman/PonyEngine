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

export module PonyEngine.File.Impl.Windows:FileService;

import std;

import PonyEngine.Application;
import PonyEngine.File;
import PonyEngine.Log;

import :File;
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
		const Log::ILogService* logService; ///< Log service.
		Worker worker; ///< Worker.

#ifndef NDEBUG
		std::atomic_size_t fileCount;
#endif

		static_assert(std::atomic_size_t::is_always_lock_free, "std::size_t isn't lock-free.");
	};
}

namespace PonyEngine::File
{
	FileService::FileService(Application::IApplication& application) :
#ifndef NDEBUG
		fileCount(0uz),
#endif
		logService{application.FindInterface<Log::ILogService>()},
		worker(application)
	{
	}

	FileService::~FileService() noexcept
	{
#ifndef NDEBUG
		assert(fileCount.load(std::memory_order::relaxed) == 0uz && "Some files are still open.");
#endif
	}

	std::shared_ptr<IFile> FileService::OpenFile(const std::filesystem::path& path, const FileParams params)
	{
#ifndef NDEBUG
		const auto file = std::shared_ptr<File>(new File(logService, worker, path, params), [this](const File* const fileToDelete) noexcept
		{
			fileCount.fetch_sub(1uz, std::memory_order::relaxed);
			delete fileToDelete;
		});
		fileCount.fetch_add(1uz, std::memory_order::relaxed);
		return file;
#else
		return std::make_shared<File>(logService, worker, path, params);
#endif
	}
}
