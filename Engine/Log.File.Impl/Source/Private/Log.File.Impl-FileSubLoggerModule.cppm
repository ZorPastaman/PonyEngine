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
#include "PonyEngine/Macro/Text.h"

export module PonyEngine.Log.File.Impl:FileSubLoggerModule;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.Log.Ext;

import :FileSubLogger;

export namespace PonyEngine::Log
{
	/// @brief File sub-logger module.
	class FileSubLoggerModule final : public Application::IModule
	{
	public:
		[[nodiscard("Pure constuctor")]]
		FileSubLoggerModule() noexcept = default;
		FileSubLoggerModule(const FileSubLoggerModule&) = delete;
		FileSubLoggerModule(FileSubLoggerModule&&) = delete;

		~FileSubLoggerModule() noexcept = default;

		virtual void StartUp(Application::IModuleContext& context) override;
		virtual void ShutDown(Application::IModuleContext& context) override;

		FileSubLoggerModule& operator =(const FileSubLoggerModule&) = delete;
		FileSubLoggerModule& operator =(FileSubLoggerModule&&) = delete;

	private:
		SubLoggerHandle fileSubLoggerHandle; ///< File sub-logger handle.
	};
}

namespace PonyEngine::Log
{
	void FileSubLoggerModule::StartUp(Application::IModuleContext& context)
	{
		ILoggerModuleContext* const loggerModuleContext = context.GetData<ILoggerModuleContext>();
		if (!loggerModuleContext) [[unlikely]]
		{
			throw std::logic_error("Logger module context not found");
		}

		PONY_LOG(context.Logger(), LogType::Info, "Constructing '{}'...", typeid(FileSubLogger).name());
		fileSubLoggerHandle = loggerModuleContext->AddSubLogger([&](ILoggerContext& loggerContext)
		{
			PONY_LOG(context.Logger(), LogType::Info, "Preparing log files...");
			const std::filesystem::path logPath = (loggerContext.Application().LocalDataDirectory() / PONY_STRINGIFY_VALUE(PONY_ENGINE_LOG_FILE_PATH)).lexically_normal();
			if (std::filesystem::exists(logPath)) [[likely]]
			{
				const std::filesystem::path prevLogPath = logPath.parent_path() / (logPath.stem().string() + "_prev" + logPath.extension().string());
				std::filesystem::copy_file(logPath, prevLogPath, std::filesystem::copy_options::overwrite_existing);
				PONY_LOG(context.Logger(), LogType::Info, "Preparing log files done. New log file path: '{}'; Old log file path: '{}'.", logPath.string(), prevLogPath.string());
			}
			else [[unlikely]]
			{
				std::filesystem::create_directories(logPath.parent_path());
				PONY_LOG(context.Logger(), LogType::Info, "Preparing log files done. Log file path: '{}'.", logPath.string());
			}
			return std::make_shared<FileSubLogger>(loggerContext, logPath);
		});
		PONY_LOG(context.Logger(), LogType::Info, "Constructing '{}' done.", typeid(FileSubLogger).name());
	}

	void FileSubLoggerModule::ShutDown(Application::IModuleContext& context)
	{
		ILoggerModuleContext* const loggerModuleContext = context.GetData<ILoggerModuleContext>();
		if (!loggerModuleContext) [[unlikely]]
		{
			throw std::logic_error("Logger module context not found");
		}

		PONY_LOG(context.Logger(), LogType::Info, "Releasing '{}'...", typeid(FileSubLogger).name());
		loggerModuleContext->RemoveSubLogger(fileSubLoggerHandle);
		PONY_LOG(context.Logger(), LogType::Info, "Releasing '{}' done.", typeid(FileSubLogger).name());
	}
}
