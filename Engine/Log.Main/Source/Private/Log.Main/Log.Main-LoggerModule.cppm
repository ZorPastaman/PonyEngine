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

export module PonyEngine.Log.Main:LoggerModule;

import std;

import PonyEngine.Application;
import PonyEngine.Log;

import :Logger;

export namespace PonyEngine::Log
{
	/// @brief Logger module.
	class LoggerModule final : public Application::IModule
	{
	public:
		[[nodiscard("Pure constructor")]]
		LoggerModule() noexcept = default;
		LoggerModule(const LoggerModule&) = delete;
		LoggerModule(LoggerModule&&) = delete;

		~LoggerModule() noexcept = default;

		virtual void StartUp(Application::IModuleContext& context) override;
		virtual void ShutDown(const Application::IModuleContext& context) override;

		LoggerModule& operator =(const LoggerModule&) = delete;
		LoggerModule& operator =(LoggerModule&&) = delete;
	};
}

namespace PonyEngine::Log
{
	void LoggerModule::StartUp(Application::IModuleContext& context)
	{
		PONY_LOG(context.Logger(), LogType::Debug, "Getting sub-logger factories.");
		const std::size_t subLoggerFactoryCount = context.DataCount<ISubLoggerFactory>();
		std::vector<ISubLoggerFactory*> subLoggerFactories;
		subLoggerFactories.reserve(subLoggerFactoryCount);
		for (std::size_t i = 0uz; i < subLoggerFactoryCount; ++i)
		{
			const auto factory = context.GetData<ISubLoggerFactory>(i);
			if (!factory) [[unlikely]]
			{
				throw std::logic_error("Sub-logger factory is nullptr.");
			}
			subLoggerFactories.push_back(factory.get());
		}

		PONY_LOG(context.Logger(), LogType::Info, "Constructing '{}'...", typeid(Logger).name());
		const auto logger = std::make_shared<Logger>(context.Application(), subLoggerFactories);
		Application::ServiceData data;
		data.service = logger;
		data.publicInterfaces.push_back(Memory::TypedPtr(&logger->PublicLogger()));
		PONY_LOG(context.Logger(), LogType::Info, "Constructing '{}' done.", typeid(Logger).name());
		PONY_LOG(context.Logger(), Log::LogType::Debug, "Adding '{}' as service.", typeid(Logger).name());
		context.AddService(data);
	}

	void LoggerModule::ShutDown(const Application::IModuleContext&)
	{
	}
}
