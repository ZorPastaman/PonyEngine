/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Log/PlatformConsole/WinCore/PlatformConsoleModule.h"

export module PonyEngine.Log.PlatformConsole.WinCore:PlatformConsoleSubLoggerModule;

import std;

import PonyEngine.Core;

import :PlatformConsoleSubLoggerFactory;

export namespace PonyEngine::Log::PlatformConsole::WinCore
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

namespace PonyEngine::Log::PlatformConsole::WinCore
{
	void PlatformConsoleSubLoggerModule::StartUp(Core::IModuleContext& context)
	{
		context.AddData<Extension::ISubLoggerFactory>(std::make_shared<PlatformConsoleSubLoggerFactory>());
	}

	void PlatformConsoleSubLoggerModule::ShutDown(const Core::IModuleContext& context)
	{
	}

	std::string_view PlatformConsoleSubLoggerModule::Name() const noexcept
	{
		return PONY_STRINGIFY_VALUE(PONY_WINCORE_PLATFORM_CONSOLE_MODULE_NAME);
	}
}
