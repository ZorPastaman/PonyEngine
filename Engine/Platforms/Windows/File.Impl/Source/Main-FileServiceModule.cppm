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
		Application::ServiceHandle fileServiceHandle; ///< File service handle.
	};
}

namespace PonyEngine::File
{
	void FileServiceModule::StartUp(Application::IModuleContext& context)
	{
		PONY_LOG(context.Logger(), Log::LogType::Info, "Constructing '{}'...", typeid(FileService).name());
		fileServiceHandle = context.ServiceModuleContext().AddService([](Application::IApplication& application)
		{
			return std::make_shared<FileService>(application);
		});
		PONY_LOG(context.Logger(), Log::LogType::Info, "Constructing '{}' done.", typeid(FileService).name());
	}

	void FileServiceModule::ShutDown(Application::IModuleContext& context)
	{
		PONY_LOG(context.Logger(), Log::LogType::Info, "Releasing '{}'...", typeid(FileService).name());
		context.ServiceModuleContext().RemoveService(fileServiceHandle);
		PONY_LOG(context.Logger(), Log::LogType::Info, "Releasing '{}' done.", typeid(FileService).name());
	}
}
