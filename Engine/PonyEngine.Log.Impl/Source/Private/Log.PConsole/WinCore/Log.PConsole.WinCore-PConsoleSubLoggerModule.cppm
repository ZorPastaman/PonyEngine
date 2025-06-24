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
#include "PonyEngine/Log/WinCore/PlatformConsoleModule.h"

export module PonyEngine.Log.PlatformConsole.WinCore:PlatformConsoleSubLoggerModule;

import std;

import PonyEngine.Core;
import PonyEngine.Log;

import :PlatformConsoleSubLoggerFactory;

export namespace PonyEngine::Log::WinCore
{
	/// @brief WinCore platform console sub-logger module.
	class PlatformConsoleSubLoggerModule final : public Core::IModule
	{
	public:
		[[nodiscard("Pure constructor")]]
		PlatformConsoleSubLoggerModule() noexcept = default;
		PlatformConsoleSubLoggerModule(const PlatformConsoleSubLoggerModule&) = delete;
		PlatformConsoleSubLoggerModule(PlatformConsoleSubLoggerModule&&) = delete;

		~PlatformConsoleSubLoggerModule() noexcept = default;

		virtual void StartUp(Core::IModuleContext& context) override;
		virtual void ShutDown(const Core::IModuleContext& context) override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;

		PlatformConsoleSubLoggerModule& operator =(const PlatformConsoleSubLoggerModule&) = delete;
		PlatformConsoleSubLoggerModule& operator =(PlatformConsoleSubLoggerModule&&) = delete;
	};
}

namespace PonyEngine::Log::WinCore
{
	void PlatformConsoleSubLoggerModule::StartUp(Core::IModuleContext& context)
	{
		PONY_LOG(context.Logger(), LogType::Debug, "Constructing '{}' and adding it to context as '{}'.", typeid(PlatformConsoleSubLoggerFactory).name(), typeid(ISubLoggerFactory).name());
		context.AddData<ISubLoggerFactory>(std::make_shared<PlatformConsoleSubLoggerFactory>(context));
	}

	void PlatformConsoleSubLoggerModule::ShutDown(const Core::IModuleContext&)
	{
	}

	std::string_view PlatformConsoleSubLoggerModule::Name() const noexcept
	{
		return PONY_STRINGIFY_VALUE(PONY_ENGINE_WINCORE_PLATFORM_CONSOLE_SUBLOGGER_MODULE_NAME);
	}
}
