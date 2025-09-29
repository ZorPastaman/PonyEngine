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

export module PonyEngine.Log.Main:LoggerFactory;

import std;

import PonyEngine.Application;
import PonyEngine.Log.Extension;

import :Logger;

export namespace PonyEngine::Log
{
	/// @brief Logger factory.
	class LoggerFactory final : public Application::IServiceFactory
	{
	public:
		/// @brief Creates a logger factory.
		/// @param context Module context.
		[[nodiscard("Pure constructor")]]
		explicit LoggerFactory(Application::IModuleContext& context) noexcept;
		LoggerFactory(const LoggerFactory&) = delete;
		LoggerFactory(LoggerFactory&&) = delete;

		~LoggerFactory() noexcept = default;

		[[nodiscard("Redundant call")]]
		virtual Application::ServiceData Create(Application::IApplicationContext& application) override;

		LoggerFactory& operator =(const LoggerFactory&) = delete;
		LoggerFactory& operator =(LoggerFactory&&) = delete;

	private:
		Application::IModuleContext* context; ///< Module context.
	};
}

namespace PonyEngine::Log
{
	LoggerFactory::LoggerFactory(Application::IModuleContext& context) noexcept :
		context{&context}
	{
	}

	Application::ServiceData LoggerFactory::Create(Application::IApplicationContext& application)
	{
		PONY_LOG(context->Logger(), LogType::Debug, "Getting sub-logger factories...");
		const std::size_t subLoggerFactoryCount = context->DataCount<ISubLoggerFactory>();
		std::vector<ISubLoggerFactory*> subLoggerFactories;
		subLoggerFactories.reserve(subLoggerFactoryCount);
		for (std::size_t i = 0uz; i < subLoggerFactoryCount; ++i)
		{
			const auto factory = context->GetData<ISubLoggerFactory>(i);
			if (!factory) [[unlikely]]
			{
				throw std::logic_error("Sub-logger factory is nullptr.");
			}
			subLoggerFactories.push_back(factory.get());
		}
		PONY_LOG(context->Logger(), LogType::Debug, "Getting sub-logger factories done.");

		PONY_LOG(context->Logger(), LogType::Info, "Constructing '{}'...", typeid(Logger).name());
		const auto logger = std::make_shared<Logger>(context->Application(), subLoggerFactories);
		Application::ServiceData data;
		data.service = logger;
		data.publicInterfaces.AddInterface<ILogger>(logger->PublicLogger());
		PONY_LOG(context->Logger(), LogType::Info, "Constructing '{}' done.", typeid(Logger).name());

		return data;
	}
}
