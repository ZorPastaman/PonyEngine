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

export module PonyEngine.Log.Impl:LoggerModule;

import std;

import PonyEngine.Application.Ext;
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
		virtual void ShutDown(Application::IModuleContext& context) override;

		LoggerModule& operator =(const LoggerModule&) = delete;
		LoggerModule& operator =(LoggerModule&&) = delete;

	private:
		Application::ModuleDataHandle loggerModuleHandle; ///< Logger module handle.
		Application::LoggerHandle loggerHandle; ///< Logger handle.
	};
}

namespace PonyEngine::Log
{
	void LoggerModule::StartUp(Application::IModuleContext& context)
	{
		PONY_LOG(context.Logger(), LogType::Info, "Constructing '{}'...", typeid(Logger).name());
		try
		{
			loggerHandle = context.LoggerModuleContext().SetLogger([&](Application::ILoggerContext& loggerContext)
			{
				const auto logger = std::make_shared<Logger>(loggerContext);
				loggerModuleHandle = context.AddData(std::shared_ptr<ILoggerModuleContext>(logger, &logger->PublicLoggerModule()));
				return std::shared_ptr<ILogger>(logger, &logger->PublicLogger());
			});
		}
		catch (...)
		{
			if (loggerModuleHandle.IsValid())
			{
				context.RemoveData(loggerModuleHandle);
			}
			throw;
		}
		PONY_LOG(context.Logger(), LogType::Info, "Constructing '{}' done.", typeid(Logger).name());
	}

	void LoggerModule::ShutDown(Application::IModuleContext& context)
	{
		PONY_LOG(context.Logger(), LogType::Info, "Releasing '{}'...", typeid(Logger).name());
		context.LoggerModuleContext().UnsetLogger(loggerHandle);
		context.RemoveData(loggerModuleHandle);
		PONY_LOG(context.Logger(), LogType::Info, "Releasing '{}' done.", typeid(Logger).name());
	}
}
