/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

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

		FileSubLoggerFactory& operator =(const FileSubLoggerFactory&) = delete;
		FileSubLoggerFactory& operator =(FileSubLoggerFactory&&) = delete;
	};
}

namespace PonyEngine::Log::File
{
	std::shared_ptr<Extension::ISubLogger> FileSubLoggerFactory::CreateSubLogger(const Core::IModuleContext& context)
	{
		const std::filesystem::path logPath = (context.Application().Paths().localData / PONY_STRINGIFY_VALUE(PONY_ENGINE_LOG_FILE_PATH)).lexically_normal();
		if (std::filesystem::exists(logPath))
		{
			const std::filesystem::path prevLogPath = logPath.parent_path() / (logPath.stem().string() + "_prev" + logPath.extension().string());
			std::filesystem::copy_file(logPath, prevLogPath, std::filesystem::copy_options::overwrite_existing);
		}
		std::filesystem::create_directories(logPath.parent_path());

		return std::make_shared<FileSubLogger>(logPath);
	}
}
