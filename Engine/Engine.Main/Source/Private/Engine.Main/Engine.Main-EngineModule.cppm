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

export module PonyEngine.Engine.Main:EngineModule;

import PonyEngine.Application;
import PonyEngine.Log;

import :EngineFactory;

export namespace PonyEngine::Engine
{
	/// @brief Engine module.
	class EngineModule final : public Application::IModule
	{
	public:
		[[nodiscard("Pure constructor")]]
		EngineModule() noexcept = default;
		EngineModule(const EngineModule&) = delete;
		EngineModule(EngineModule&&) = delete;

		~EngineModule() noexcept = default;

		virtual void StartUp(Application::IModuleContext& context) override;
		virtual void ShutDown(const Application::IModuleContext& context) override;

		EngineModule& operator =(const EngineModule&) = delete;
		EngineModule& operator =(EngineModule&&) = delete;
	};
}

namespace PonyEngine::Engine
{
	void EngineModule::StartUp(Application::IModuleContext& context)
	{
		PONY_LOG(context.Logger(), Log::LogType::Debug, "Constructing '{}'...", typeid(EngineFactory).name());
		const auto engineFactory = std::make_shared<EngineFactory>(context);
		PONY_LOG(context.Logger(), Log::LogType::Debug, "Constructing '{}' done.", typeid(EngineFactory).name());
		PONY_LOG(context.Logger(), Log::LogType::Debug, "Adding '{}' as service.", typeid(EngineFactory).name());
		context.AddService(engineFactory);
	}

	void EngineModule::ShutDown(const Application::IModuleContext&)
	{
	}
}
