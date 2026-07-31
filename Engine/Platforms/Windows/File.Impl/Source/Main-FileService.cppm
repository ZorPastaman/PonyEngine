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
import :Worker;

export namespace PonyEngine::File
{
	/// @brief File service.
	class FileService final : public Application::IService, private IFileService
	{
	public:
		/// @brief Creates a file service.
		/// @param application Application.
		[[nodiscard("Pure constructor")]]
		explicit FileService(const Application::IApplication& application);
		FileService(const FileService&) = delete;
		FileService(FileService&&) = delete;

		~FileService() noexcept = default;

		virtual void Begin() override;
		virtual void End() override;

		virtual void AddInterfaces(Application::IServiceInterfaceAdder& adder) override;

		FileService& operator =(const FileService&) = delete;
		FileService& operator =(FileService&&) = delete;

	private:
		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<IFile> OpenFile(const std::filesystem::path& path, FileParams params) override;

		const Application::IApplication* application; ///< Application.

		Worker worker; ///< Worker.
	};
}

namespace PonyEngine::File
{
	FileService::FileService(const Application::IApplication& application) :
		application{&application},
		worker(*this->application)
	{
	}

	void FileService::Begin()
	{
	}

	void FileService::End()
	{
	}

	void FileService::AddInterfaces(Application::IServiceInterfaceAdder& adder)
	{
		adder.AddInterface<IFileService>(*this);
	}

	std::shared_ptr<IFile> FileService::OpenFile(const std::filesystem::path& path, const FileParams params)
	{
		return std::make_shared<File>(*application, worker, path, params);
	}
}
