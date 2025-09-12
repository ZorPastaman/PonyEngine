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

export module PonyEngine.Log.PlatformConsole.WinCore:PlatformConsoleSubLoggerModule;

import std;

import PonyEngine.Application;
import PonyEngine.Log;

import :PlatformConsoleSubLoggerFactory;

export namespace PonyEngine::Log::WinCore
{
	/// @brief WinCore platform console sub-logger module.
	class PlatformConsoleSubLoggerModule final : public Application::IModule
	{
	public:
		[[nodiscard("Pure constructor")]]
		PlatformConsoleSubLoggerModule() noexcept = default;
		PlatformConsoleSubLoggerModule(const PlatformConsoleSubLoggerModule&) = delete;
		PlatformConsoleSubLoggerModule(PlatformConsoleSubLoggerModule&&) = delete;

		~PlatformConsoleSubLoggerModule() noexcept = default;

		virtual void StartUp(Application::IModuleContext& context) override;
		virtual void ShutDown(const Application::IModuleContext& context) override;

		PlatformConsoleSubLoggerModule& operator =(const PlatformConsoleSubLoggerModule&) = delete;
		PlatformConsoleSubLoggerModule& operator =(PlatformConsoleSubLoggerModule&&) = delete;
	};
}

namespace PonyEngine::Log::WinCore
{
	void PlatformConsoleSubLoggerModule::StartUp(Application::IModuleContext& context)
	{
		PONY_LOG(context.Logger(), LogType::Debug, "Constructing '{}' and adding it to context as '{}'.", typeid(PlatformConsoleSubLoggerFactory).name(), typeid(ISubLoggerFactory).name());
		context.AddData<ISubLoggerFactory>(std::make_shared<PlatformConsoleSubLoggerFactory>(context));
	}

	void PlatformConsoleSubLoggerModule::ShutDown(const Application::IModuleContext&)
	{
	}
}
