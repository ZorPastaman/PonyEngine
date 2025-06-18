/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <typeinfo>

#include "PonyEngine/Log/Log.h"
#include "PonyEngine/Log/Console/ConsoleModule.h"
#include "PonyEngine/Utility/Macro.h"

export module PonyEngine.Log.Console:ConsoleSubLoggerModule;

import std;

import PonyEngine.Core;

import :ConsoleSubLoggerFactory;

export namespace PonyEngine::Log::Console
{
	/// @brief Console sub-logger module.
	class ConsoleSubLoggerModule final : public Core::IModule
	{
	public:
		[[nodiscard("Pure constructor")]]
		ConsoleSubLoggerModule() noexcept = default;
		ConsoleSubLoggerModule(const ConsoleSubLoggerModule&) = delete;
		ConsoleSubLoggerModule(ConsoleSubLoggerModule&&) = delete;

		~ConsoleSubLoggerModule() noexcept = default;

		virtual void StartUp(Core::IModuleContext& context) override;
		virtual void ShutDown(const Core::IModuleContext& context) override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;

		ConsoleSubLoggerModule& operator =(const ConsoleSubLoggerModule&) = delete;
		ConsoleSubLoggerModule& operator =(ConsoleSubLoggerModule&&) = delete;
	};
}

namespace PonyEngine::Log::Console
{
	void ConsoleSubLoggerModule::StartUp(Core::IModuleContext& context)
	{
		PONY_LOG(context.Application().Logger(), LogType::Debug, "Constructing '{}' and adding it to context as '{}'.", typeid(ConsoleSubLoggerFactory).name(), typeid(Extension::ISubLoggerFactory).name());
		context.AddData<Extension::ISubLoggerFactory>(std::make_shared<ConsoleSubLoggerFactory>());
	}

	void ConsoleSubLoggerModule::ShutDown(const Core::IModuleContext&)
	{
	}

	std::string_view ConsoleSubLoggerModule::Name() const noexcept
	{
		return PONY_STRINGIFY_VALUE(PONY_ENGINE_CONSOLE_SUBLOGGER_MODULE_NAME);
	}
}
