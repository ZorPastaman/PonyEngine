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

export module PonyEngine.Log.Core:LoggerFactory;

import std;

import PonyEngine.Core;
import PonyEngine.Log.Extension;

import :Logger;

export namespace PonyEngine::Log::Core
{
	/// @brief Logger factory.
	class LoggerFactory final : public PonyEngine::Core::ILoggerFactory
	{
	public:
		[[nodiscard("Pure constructor")]]
		LoggerFactory() noexcept = default;
		LoggerFactory(const LoggerFactory&) = delete;
		LoggerFactory(LoggerFactory&&) = delete;

		~LoggerFactory() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<ILogger> Create(const PonyEngine::Core::IModuleContext& context) override;

		LoggerFactory& operator =(const LoggerFactory&) = delete;
		LoggerFactory& operator =(LoggerFactory&&) = delete;
	};
}

namespace PonyEngine::Log::Core
{
	std::shared_ptr<ILogger> LoggerFactory::Create(const PonyEngine::Core::IModuleContext& context)
	{
		const auto logger = std::make_shared<Logger>();
		const std::size_t subLoggerCount = context.DataCount<Extension::ISubLoggerFactory>();
		for (std::size_t i = 0Z; i < subLoggerCount; ++i)
		{
			const std::shared_ptr<Extension::ISubLoggerFactory> subLoggerFactory = context.GetData<Extension::ISubLoggerFactory>(i);
			try
			{
				PONY_LOG(context.Application().Logger(), LogType::Info, "Creates sub-logger with '{}' factory.", typeid(*subLoggerFactory).name());
				const std::shared_ptr<Extension::ISubLogger> subLogger = subLoggerFactory->CreateSubLogger(context);
				PONY_LOG(context.Application().Logger(), LogType::Info, "Adds '{}' sub-logger.", typeid(*subLogger).name());
				logger->AddSubLogger(subLogger);
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(context.Application().Logger(), e, "On creating a sub-logger with '{}' factory.", typeid(*subLoggerFactory).name());
			}
		}

		return logger;
	}
}
