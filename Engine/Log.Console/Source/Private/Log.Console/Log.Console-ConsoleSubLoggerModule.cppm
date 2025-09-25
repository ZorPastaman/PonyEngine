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

export module PonyEngine.Log.Console:ConsoleSubLoggerModule;

import std;

import PonyEngine.Application;
import PonyEngine.Log;

import :ConsoleSubLoggerFactory;

export namespace PonyEngine::Log
{
	/// @brief Console sub-logger module.
	class ConsoleSubLoggerModule final : public Application::IModule
	{
	public:
		[[nodiscard("Pure constructor")]]
		ConsoleSubLoggerModule() noexcept = default;
		ConsoleSubLoggerModule(const ConsoleSubLoggerModule&) = delete;
		ConsoleSubLoggerModule(ConsoleSubLoggerModule&&) = delete;

		~ConsoleSubLoggerModule() noexcept = default;

		virtual void StartUp(Application::IModuleContext& context) override;
		virtual void ShutDown(const Application::IModuleContext& context) override;

		ConsoleSubLoggerModule& operator =(const ConsoleSubLoggerModule&) = delete;
		ConsoleSubLoggerModule& operator =(ConsoleSubLoggerModule&&) = delete;
	};
}

namespace PonyEngine::Log
{
	void ConsoleSubLoggerModule::StartUp(Application::IModuleContext& context)
	{
		PONY_LOG(context.Logger(), LogType::Debug, "Constructing '{}'...", typeid(ConsoleSubLoggerFactory).name());
		const auto consoleSubLoggerFactory = std::make_shared<ConsoleSubLoggerFactory>(context);
		PONY_LOG(context.Logger(), LogType::Debug, "Constructing '{}' done.", typeid(ConsoleSubLoggerFactory).name());
		PONY_LOG(context.Logger(), LogType::Debug, "Adding '{}' as data of type '{}'...", typeid(ConsoleSubLoggerFactory).name(), typeid(ISubLoggerFactory).name());
		context.AddData<ISubLoggerFactory>(consoleSubLoggerFactory);
		PONY_LOG(context.Logger(), LogType::Debug, "Adding '{}' as data of type '{}' done.", typeid(ConsoleSubLoggerFactory).name(), typeid(ISubLoggerFactory).name());
	}

	void ConsoleSubLoggerModule::ShutDown(const Application::IModuleContext&)
	{
	}
}
