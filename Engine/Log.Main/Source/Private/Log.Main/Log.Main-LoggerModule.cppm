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

import :LoggerFactory;

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
		PONY_LOG(context.Logger(), LogType::Debug, "Constructing '{}'...", typeid(LoggerFactory).name());
		const auto loggerFactory = std::make_shared<LoggerFactory>(context);
		PONY_LOG(context.Logger(), LogType::Debug, "Constructing '{}' done.", typeid(LoggerFactory).name());
		PONY_LOG(context.Logger(), Log::LogType::Debug, "Adding '{}' as service...", typeid(LoggerFactory).name());
		context.AddService(loggerFactory);
		PONY_LOG(context.Logger(), Log::LogType::Debug, "Adding '{}' as service done.", typeid(LoggerFactory).name());
	}

	void LoggerModule::ShutDown(const Application::IModuleContext&)
	{
	}
}
