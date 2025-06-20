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

import PonyEngine.Log.Extension;

import :FileSubLogger;

export namespace PonyEngine::Log::File
{
	/// @brief File sub-logger factory.
	class FileSubLoggerFactory final : public Extension::ISubLoggerFactory
	{
	public:
		[[nodiscard("Pure constructor")]]
		FileSubLoggerFactory() noexcept = default;
		FileSubLoggerFactory(const FileSubLoggerFactory&) = delete;
		FileSubLoggerFactory(FileSubLoggerFactory&&) = delete;

		~FileSubLoggerFactory() noexcept = default;

		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<Extension::ISubLogger> CreateSubLogger(const Core::IModuleContext& context) override;

		[[nodiscard("Pure function")]]
		virtual std::int32_t Order() const noexcept override;

		FileSubLoggerFactory& operator =(const FileSubLoggerFactory&) = delete;
		FileSubLoggerFactory& operator =(FileSubLoggerFactory&&) = delete;
	};
}

namespace PonyEngine::Log::File
{
	std::shared_ptr<Extension::ISubLogger> FileSubLoggerFactory::CreateSubLogger(const Core::IModuleContext& context)
	{
		PONY_LOG(context.Application().Logger(), LogType::Debug, "Preparing log files.");
		const std::filesystem::path logPath = (context.Application().Paths().localData / PONY_STRINGIFY_VALUE(PONY_ENGINE_LOG_FILE_PATH)).lexically_normal();
		if (std::filesystem::exists(logPath))
		{
			const std::filesystem::path prevLogPath = logPath.parent_path() / (logPath.stem().string() + "_prev" + logPath.extension().string());
			std::filesystem::copy_file(logPath, prevLogPath, std::filesystem::copy_options::overwrite_existing);
		}
		else
		{
			std::filesystem::create_directories(logPath.parent_path());
		}

		PONY_LOG(context.Application().Logger(), LogType::Debug, "Constructing file sub-logger. Log path: '{}'.", logPath.string());
		return std::make_shared<FileSubLogger>(logPath);
	}

	std::int32_t FileSubLoggerFactory::Order() const noexcept
	{
		return PONY_ENGINE_LOG_FILE_ORDER;
	}
}
