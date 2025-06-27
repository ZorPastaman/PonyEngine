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

export module PonyEngine.Log.Core:LoggerModule;

import std;

import PonyEngine.Core;
import PonyEngine.Log;

import :LoggerFactory;

export namespace PonyEngine::Log
{
	/// @brief Logger module.
	class LoggerModule final : public Core::IModule
	{
	public:
		[[nodiscard("Pure constructor")]]
		LoggerModule() noexcept = default;
		LoggerModule(const LoggerModule&) = delete;
		LoggerModule(LoggerModule&&) = delete;

		~LoggerModule() noexcept = default;

		virtual void StartUp(Core::IModuleContext& context) override;
		virtual void ShutDown(const Core::IModuleContext& context) override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;

		LoggerModule& operator =(const LoggerModule&) = delete;
		LoggerModule& operator =(LoggerModule&&) = delete;
	};
}

namespace PonyEngine::Log
{
	void LoggerModule::StartUp(Core::IModuleContext& context)
	{
		PONY_LOG(context.Logger(), LogType::Debug, "Constructing '{}' and adding it to context as '{}'.", typeid(LoggerFactory).name(), typeid(PonyEngine::Core::ILoggerFactory).name());
		context.AddData<Core::ILoggerFactory>(std::make_shared<LoggerFactory>(context));
	}

	void LoggerModule::ShutDown(const Core::IModuleContext&)
	{
	}

	std::string_view LoggerModule::Name() const noexcept
	{
		return "PonyEngineLogger";
	}
}
