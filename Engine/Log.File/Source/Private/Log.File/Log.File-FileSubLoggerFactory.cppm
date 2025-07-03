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
import PonyEngine.Core;
import PonyEngine.Log.Extension;

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
		explicit FileSubLoggerFactory(Core::IModuleContext& context) noexcept;
		FileSubLoggerFactory(const FileSubLoggerFactory&) = delete;
		FileSubLoggerFactory(FileSubLoggerFactory&&) = delete;

		~FileSubLoggerFactory() noexcept = default;

		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<ISubLogger> CreateSubLogger(ILoggerContext& logger) override;

		[[nodiscard("Pure function")]]
		virtual std::int32_t Order() const noexcept override;

		FileSubLoggerFactory& operator =(const FileSubLoggerFactory&) = delete;
		FileSubLoggerFactory& operator =(FileSubLoggerFactory&&) = delete;

	private:
		Core::IModuleContext* context; ///< Module context.
	};
}

namespace PonyEngine::Log
{
	FileSubLoggerFactory::FileSubLoggerFactory(Core::IModuleContext& context) noexcept :
		context{&context}
	{
	}

	std::shared_ptr<ISubLogger> FileSubLoggerFactory::CreateSubLogger(ILoggerContext&)
	{
		PONY_LOG(context->Logger(), LogType::Debug, "Preparing log files.");
		const std::filesystem::path logPath = (context->Application().Paths().localData / PONY_STRINGIFY_VALUE(PONY_ENGINE_LOG_FILE_PATH)).lexically_normal();
		if (std::filesystem::exists(logPath))
		{
			const std::filesystem::path prevLogPath = logPath.parent_path() / (logPath.stem().string() + "_prev" + logPath.extension().string());
			std::filesystem::copy_file(logPath, prevLogPath, std::filesystem::copy_options::overwrite_existing);
		}
		else
		{
			std::filesystem::create_directories(logPath.parent_path());
		}

		PONY_LOG(context->Logger(), LogType::Debug, "Constructing file sub-logger. Log path: '{}'.", logPath.string());
		return std::make_shared<FileSubLogger>(logPath);
	}

	std::int32_t FileSubLoggerFactory::Order() const noexcept
	{
		return PONY_ENGINE_LOG_FILE_ORDER;
	}
}
