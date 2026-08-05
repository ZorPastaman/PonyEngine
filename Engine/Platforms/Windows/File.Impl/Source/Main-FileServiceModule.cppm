/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Log/Log.h"

export module PonyEngine.File.Impl.Windows:FileServiceModule;

import std;

import :FileService;

export namespace PonyEngine::File
{
	/// @brief Windows file service module.
	class FileServiceModule final : public Application::IModule
	{
	public:
		[[nodiscard("Pure constuctor")]]
		FileServiceModule() noexcept = default;
		FileServiceModule(const FileServiceModule&) = delete;
		FileServiceModule(FileServiceModule&&) = delete;

		~FileServiceModule() noexcept = default;

		virtual void StartUp(Application::IModuleContext& context) override;
		virtual void ShutDown(Application::IModuleContext& context) override;

		FileServiceModule& operator =(const FileServiceModule&) = delete;
		FileServiceModule& operator =(FileServiceModule&&) = delete;

	private:
		std::unique_ptr<FileService> fileService; ///< File service.
	};
}

namespace PonyEngine::File
{
	void FileServiceModule::StartUp(Application::IModuleContext& context)
	{
		fileService = std::make_unique<FileService>(context.Application());
		try
		{
			context.AddInterface<IFileService>(*fileService);
		}
		catch (...)
		{
			fileService.reset();
			throw;
		}
	}

	void FileServiceModule::ShutDown(Application::IModuleContext& context)
	{
		context.RemoveInterface<IFileService>(*fileService);
		fileService.reset();
	}
}
