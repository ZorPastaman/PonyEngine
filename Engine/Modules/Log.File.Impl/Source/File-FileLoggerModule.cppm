/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Macro/Text.h"

export module PonyEngine.Log.File.Impl:FileLoggerModule;

import std;

import PonyEngine.Application;
import PonyEngine.Log.Ext;

import :FileLogger;

export namespace PonyEngine::Log::File
{
	/// @brief File logger module.
	class FileLoggerModule final : public Application::IModule
	{
	public:
		[[nodiscard("Pure constuctor")]]
		FileLoggerModule() noexcept = default;
		FileLoggerModule(const FileLoggerModule&) = delete;
		FileLoggerModule(FileLoggerModule&&) = delete;

		~FileLoggerModule() noexcept = default;

		virtual void StartUp(Application::IModuleContext& context) override;
		virtual void ShutDown(Application::IModuleContext& context) override;

		FileLoggerModule& operator =(const FileLoggerModule&) = delete;
		FileLoggerModule& operator =(FileLoggerModule&&) = delete;

	private:
		std::unique_ptr<FileLogger> logger; ///< File logger.
	};
}

namespace PonyEngine::Log::File
{
	void FileLoggerModule::StartUp(Application::IModuleContext& context)
	{
		ILogHub& logHub = context.Application().GetInterface<ILogHub>();

		const std::filesystem::path logPath = (context.Application().LocalDataDirectory() / PONY_STRINGIFY_VALUE(PONY_ENGINE_LOG_FILE_PATH)).lexically_normal();
		if (std::filesystem::exists(logPath)) [[likely]]
		{
			const std::filesystem::path prevLogPath = logPath.parent_path() / (logPath.stem().string() + "_prev" + logPath.extension().string());
			std::filesystem::copy_file(logPath, prevLogPath, std::filesystem::copy_options::overwrite_existing);
		}
		else [[unlikely]]
		{
			std::filesystem::create_directories(logPath.parent_path());
		}

		logger = std::make_unique<FileLogger>(logPath);
		try
		{
			logHub.AddLogger(*logger);
		}
		catch (...)
		{
			logger.reset();
			throw;
		}
	}

	void FileLoggerModule::ShutDown(Application::IModuleContext& context)
	{
		ILogHub& logHub = context.Application().GetInterface<ILogHub>();
		logHub.RemoveLogger(*logger);
		logger.reset();
	}
}
