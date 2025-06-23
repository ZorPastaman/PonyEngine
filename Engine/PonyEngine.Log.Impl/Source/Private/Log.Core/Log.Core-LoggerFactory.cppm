/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

#include "PonyEngine/Log/Log.h"

export module PonyEngine.Log.Core:LoggerFactory;

import std;

import PonyEngine.Application;
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
		virtual std::shared_ptr<PonyEngine::Core::ILogger> Create(const PonyEngine::Core::IModuleContext& context) override;

		LoggerFactory& operator =(const LoggerFactory&) = delete;
		LoggerFactory& operator =(LoggerFactory&&) = delete;

	private:
		/// @brief Creates sub-loggers.
		/// @param context Module context.
		/// @return Sub-loggers in the correct order.
		[[nodiscard("Pure function")]]
		static std::vector<std::shared_ptr<Extension::ISubLogger>> CreateSubLoggers(const PonyEngine::Core::IModuleContext& context);
	};
}

namespace PonyEngine::Log::Core
{
	std::shared_ptr<PonyEngine::Core::ILogger> LoggerFactory::Create(const PonyEngine::Core::IModuleContext& context)
	{
		const std::vector<std::shared_ptr<Extension::ISubLogger>> subLoggers = CreateSubLoggers(context);

		PONY_LOG(context.Application().Logger(), LogType::Info, "Constructing logger.");
		const auto logger = std::make_shared<Logger>();
		logger->Reserve(subLoggers.size());
		for (const std::shared_ptr<Extension::ISubLogger>& subLogger : subLoggers)
		{
			PONY_LOG(context.Application().Logger(), LogType::Info, "Adding '{}' sub-logger.", typeid(*subLogger).name());
			logger->AddSubLogger(subLogger);
		}

		return logger;
	}

	std::vector<std::shared_ptr<Extension::ISubLogger>> LoggerFactory::CreateSubLoggers(const PonyEngine::Core::IModuleContext& context)
	{
		PONY_LOG(context.Application().Logger(), LogType::Info, "Creating sub-loggers...");
		const std::size_t subLoggerCount = context.DataCount<Extension::ISubLoggerFactory>();
		std::vector<std::pair<std::shared_ptr<Extension::ISubLogger>, std::int32_t>> subLoggers;
		subLoggers.reserve(subLoggerCount);
		for (std::size_t i = 0Z; i < subLoggerCount; ++i)
		{
			const std::shared_ptr<Extension::ISubLoggerFactory> subLoggerFactory = context.GetData<Extension::ISubLoggerFactory>(i);
			try
			{
				PONY_LOG(context.Application().Logger(), LogType::Info, "Creating sub-logger... Factory: '{}'.", typeid(*subLoggerFactory).name());
				const std::shared_ptr<Extension::ISubLogger> subLogger = subLoggerFactory->CreateSubLogger(context);
				assert(subLogger && "The created sub-logger is nullptr!");
				subLoggers.emplace_back(subLogger, subLoggerFactory->Order());
				PONY_LOG(context.Application().Logger(), LogType::Info, "Creating sub-logger done. Sub-logger: '{}'.", typeid(*subLoggerFactory).name(), typeid(*subLogger).name());
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(context.Application().Logger(), e, "On creating sub-logger with '{}' factory.", typeid(*subLoggerFactory).name());
			}
		}
		PONY_LOG(context.Application().Logger(), LogType::Info, "Creating sub-loggers done.");

		PONY_LOG(context.Application().Logger(), LogType::Debug, "Sorting sub-loggers.");
		std::ranges::sort(subLoggers, [](const auto& lhs, const auto& rhs) { return lhs.second < rhs.second; });
		if constexpr (IsInMask(LogType::Warning, PONY_LOG_MASK))
		{
			for (std::size_t i = 0Z; i < subLoggers.size(); ++i)
			{
				for (std::size_t j = i + 1Z; j < subLoggers.size(); ++j)
				{
					PONY_LOG_IF(subLoggers[i].second == subLoggers[j].second, context.Application().Logger(), LogType::Warning, 
						"'{}' and '{}' sub-loggers have the same order. It may cause unpredictable results.", typeid(*subLoggers[i].first).name(), typeid(*subLoggers[j].first).name());
				}
			}
		}
		std::vector<std::shared_ptr<Extension::ISubLogger>> answer;
		answer.reserve(subLoggers.size());
		for (std::shared_ptr<Extension::ISubLogger>& subLogger : std::views::keys(subLoggers))
		{
			answer.push_back(subLogger);
		}

		return answer;
	}
}
