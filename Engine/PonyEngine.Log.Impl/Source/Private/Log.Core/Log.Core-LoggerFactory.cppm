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

export namespace PonyEngine::Log
{
	/// @brief Logger factory.
	class LoggerFactory final : public Core::ILoggerFactory
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit LoggerFactory(Core::IModuleContext& context) noexcept;
		LoggerFactory(const LoggerFactory&) = delete;
		LoggerFactory(LoggerFactory&&) = delete;

		~LoggerFactory() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<Core::ILogger> Create() override;

		LoggerFactory& operator =(const LoggerFactory&) = delete;
		LoggerFactory& operator =(LoggerFactory&&) = delete;

	private:
		/// @brief Creates sub-loggers.
		/// @param logger Logger context.
		/// @return Sub-loggers in the correct order.
		[[nodiscard("Pure function")]]
		std::vector<std::shared_ptr<ISubLogger>> CreateSubLoggers(ILoggerContext& logger) const;

		Core::IModuleContext* context; ///< Module context.
	};
}

namespace PonyEngine::Log
{
	LoggerFactory::LoggerFactory(Core::IModuleContext& context) noexcept :
		context{&context}
	{
	}

	std::shared_ptr<Core::ILogger> LoggerFactory::Create()
	{
		PONY_LOG(context->Logger(), LogType::Info, "Constructing logger.");
		const auto logger = std::make_shared<Logger>(context->Application());

		std::vector<std::shared_ptr<ISubLogger>> subLoggers = CreateSubLoggers(logger->Context());
		PONY_LOG(context->Logger(), LogType::Info, "Setting sub-loggers.");
		logger->SubLoggers(std::move(subLoggers));

		return logger;
	}

	std::vector<std::shared_ptr<ISubLogger>> LoggerFactory::CreateSubLoggers(ILoggerContext& logger) const
	{
		PONY_LOG(context->Logger(), LogType::Info, "Creating sub-loggers...");
		const std::size_t subLoggerCount = context->DataCount<ISubLoggerFactory>();
		std::vector<std::pair<std::shared_ptr<ISubLogger>, std::int32_t>> subLoggers;
		subLoggers.reserve(subLoggerCount);
		for (std::size_t i = 0Z; i < subLoggerCount; ++i)
		{
			const std::shared_ptr<ISubLoggerFactory> subLoggerFactory = context->GetData<ISubLoggerFactory>(i);
			try
			{
				PONY_LOG(context->Logger(), LogType::Info, "Creating sub-logger... Factory: '{}'.", typeid(*subLoggerFactory).name());
				const std::shared_ptr<ISubLogger> subLogger = subLoggerFactory->CreateSubLogger(logger);
				assert(subLogger && "The created sub-logger is nullptr!");
				subLoggers.emplace_back(subLogger, subLoggerFactory->Order());
				PONY_LOG(context->Logger(), LogType::Info, "Creating sub-logger done. Sub-logger: '{}'.", typeid(*subLoggerFactory).name(), typeid(*subLogger).name());
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(context->Logger(), e, "On creating sub-logger with '{}' factory.", typeid(*subLoggerFactory).name());

				throw;
			}
			catch (...)
			{
				PONY_LOG(context->Logger(), LogType::Error, "Unknown exception on creating sub-logger with '{}' factory.", typeid(*subLoggerFactory).name());

				throw;
			}
		}
		PONY_LOG(context->Logger(), LogType::Info, "Creating sub-loggers done.");

		PONY_LOG(context->Logger(), LogType::Info, "Sorting sub-loggers...");
		std::ranges::sort(subLoggers, [](const auto& lhs, const auto& rhs) { return lhs.second < rhs.second; });
		if constexpr (IsInMask(LogType::Warning, PONY_LOG_MASK))
		{
			for (std::size_t i = 0Z; i < subLoggers.size(); ++i)
			{
				for (std::size_t j = i + 1Z; j < subLoggers.size(); ++j)
				{
					PONY_LOG_IF(subLoggers[i].second == subLoggers[j].second, context->Logger(), LogType::Warning, 
						"'{}' and '{}' sub-loggers have the same order. It may cause unpredictable results.", typeid(*subLoggers[i].first).name(), typeid(*subLoggers[j].first).name());
				}
			}
		}
		std::vector<std::shared_ptr<ISubLogger>> answer;
		answer.reserve(subLoggers.size());
		for (std::shared_ptr<ISubLogger>& subLogger : std::views::keys(subLoggers))
		{
			PONY_LOG(context->Logger(), LogType::Info, typeid(*subLogger).name());
			answer.push_back(subLogger);
		}
		PONY_LOG(context->Logger(), LogType::Info, "Sorting sub-loggers done.");

		return answer;
	}
}
