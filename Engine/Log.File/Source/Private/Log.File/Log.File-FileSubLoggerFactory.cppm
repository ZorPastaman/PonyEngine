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
#include "PonyEngine/Utility/Macro.h"

export module PonyEngine.Log.File:FileSubLoggerFactory;

import std;

import PonyEngine.Application;
import PonyEngine.Log.Extension;
import PonyEngine.Path;

import :FileSubLogger;

export namespace PonyEngine::Log
{
	/// @brief File sub-logger factory.
	class FileSubLoggerFactory final : public ISubLoggerFactory
	{
	public:
		/// @brief Creates a file sub-logger factory.
		/// @param context Module context.
		[[nodiscard("Pure constructor")]]
		explicit FileSubLoggerFactory(Application::IModuleContext& context) noexcept;
		FileSubLoggerFactory(const FileSubLoggerFactory&) = delete;
		FileSubLoggerFactory(FileSubLoggerFactory&&) = delete;

		~FileSubLoggerFactory() noexcept = default;

		[[nodiscard("Redundant call")]]
		virtual SubLoggerData CreateSubLogger(ILoggerContext& logger) override;

		FileSubLoggerFactory& operator =(const FileSubLoggerFactory&) = delete;
		FileSubLoggerFactory& operator =(FileSubLoggerFactory&&) = delete;

	private:
		Application::IModuleContext* context; ///< Module context.
	};
}

namespace PonyEngine::Log
{
	FileSubLoggerFactory::FileSubLoggerFactory(Application::IModuleContext& context) noexcept :
		context{&context}
	{
	}

	SubLoggerData FileSubLoggerFactory::CreateSubLogger(ILoggerContext&)
	{
		PONY_LOG(context->Logger(), LogType::Debug, "Preparing log files.");
		const Path::IPathService* const pathService = context->FindService<Path::IPathService>();
		if (!pathService) [[unlikely]]
		{
			throw std::logic_error("Path service not found.");
		}

		const std::filesystem::path* const logFolderPath = pathService->FindPath(Path::PathIds::Log);
		if (!logFolderPath) [[unlikely]]
		{
			throw std::logic_error("Log folder path not found.");
		}

		const std::filesystem::path logPath = (*logFolderPath / PONY_STRINGIFY_VALUE(PONY_ENGINE_LOG_FILE_PATH)).lexically_normal();
		if (std::filesystem::exists(logPath)) [[likely]]
		{
			const std::filesystem::path prevLogPath = logPath.parent_path() / (logPath.stem().string() + "_prev" + logPath.extension().string());
			std::filesystem::copy_file(logPath, prevLogPath, std::filesystem::copy_options::overwrite_existing);
		}
		else [[unlikely]]
		{
			std::filesystem::create_directories(logPath.parent_path());
		}

		PONY_LOG(context->Logger(), LogType::Debug, "Constructing file sub-logger. Log path: '{}'.", logPath.string());
		return SubLoggerData{.subLogger = std::make_shared<FileSubLogger>(logPath)};
	}
}
