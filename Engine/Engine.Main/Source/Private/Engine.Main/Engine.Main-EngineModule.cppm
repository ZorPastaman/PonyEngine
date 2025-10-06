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

import :Engine;

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
		PONY_LOG(context.Logger(), Log::LogType::Debug, "Getting engine system factories.");
		const std::size_t systemFactoryCount = context.DataCount<ISystemFactory>();
		std::vector<ISystemFactory*> systemFactories;
		systemFactories.reserve(systemFactoryCount);
		for (std::size_t i = 0uz; i < systemFactoryCount; ++i)
		{
			const auto factory = context.GetData<ISystemFactory>(i);
			if (!factory) [[unlikely]]
			{
				throw std::logic_error("System factory is nullptr.");
			}
			systemFactories.push_back(factory.get());
		}

		PONY_LOG(context.Logger(), Log::LogType::Info, "Constructing '{}'...", typeid(Engine).name());
		const auto engine = std::make_shared<Engine>(context.Application(), systemFactories);
		Application::ServiceData data;
		data.service = std::static_pointer_cast<Application::ITickableService>(engine);
		data.tickOrder = PONY_ENGINE_ENGINE_MAIN_TICK_ORDER;
		PONY_LOG(context.Logger(), Log::LogType::Info, "Constructing '{}' done.", typeid(Engine).name());
		PONY_LOG(context.Logger(), Log::LogType::Debug, "Adding '{}' as service.", typeid(Engine).name());
		context.AddService(data);
	}

	void EngineModule::ShutDown(const Application::IModuleContext&)
	{
	}
}
