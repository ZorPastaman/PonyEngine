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

import PonyEngine.Application.Ext;
import PonyEngine.File;

import :File;
import :Worker;

export namespace PonyEngine::File::Windows
{
	/// @brief File service.
	class FileService final : public Application::IService, private IFileService
	{
	public:
		/// @brief Creates a file service.
		/// @param application Application context.
		[[nodiscard("Pure constructor")]]
		explicit FileService(const Application::IApplicationContext& application);
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
		virtual std::shared_ptr<IFile> OpenFile(const FileParams& params) override;

		const Application::IApplicationContext* application; ///< Application context.

		Worker worker; ///< Worker.
	};
}

namespace PonyEngine::File::Windows
{
	FileService::FileService(const Application::IApplicationContext& application) :
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

	std::shared_ptr<IFile> FileService::OpenFile(const FileParams& params)
	{
		return std::make_shared<File>(*application, worker, params);
	}
}
