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

export module PonyEngine.Engine.Main:EngineFactory;

import std;

import PonyEngine.Application;
import PonyEngine.Engine.Extension;
import PonyEngine.Log;

import :Engine;

export namespace PonyEngine::Engine
{
	/// @brief Engine factory.
	class EngineFactory final : public Application::IServiceFactory
	{
	public:
		/// @brief Creates an engine factory.
		/// @param context Module context.
		[[nodiscard("Pure constructor")]]
		explicit EngineFactory(Application::IModuleContext& context) noexcept;
		EngineFactory(const EngineFactory&) = delete;
		EngineFactory(EngineFactory&&) = delete;

		~EngineFactory() noexcept = default;

		[[nodiscard("Redundant call")]]
		virtual Application::ServiceData Create(Application::IApplicationContext& application) override;

		EngineFactory& operator =(const EngineFactory&) = delete;
		EngineFactory& operator =(EngineFactory&&) = delete;

	private:
		Application::IModuleContext* context; ///< Module context.
	};
}

namespace PonyEngine::Engine
{
	EngineFactory::EngineFactory(Application::IModuleContext& context) noexcept :
		context{&context}
	{
	}

	Application::ServiceData EngineFactory::Create(Application::IApplicationContext& application)
	{
		PONY_LOG(context->Logger(), Log::LogType::Info, "Getting engine system factories...");
		const std::size_t systemFactoryCount = context->DataCount<ISystemFactory>();
		std::vector<ISystemFactory*> systemFactories;
		systemFactories.reserve(systemFactoryCount);
		for (std::size_t i = 0uz; i < systemFactoryCount; ++i)
		{
			const auto factory = context->GetData<ISystemFactory>(i);
			if (!factory) [[unlikely]]
			{
				throw std::logic_error("System factory is nullptr.");
			}
			systemFactories.push_back(factory.get());
		}
		PONY_LOG(context->Logger(), Log::LogType::Info, "Getting engine system factories done.");

		PONY_LOG(context->Logger(), Log::LogType::Info, "Constructing '{}'...", typeid(Engine).name());
		const auto engine = std::make_shared<Engine>(context->Application(), systemFactories);
		Application::ServiceData data;
		data.service = std::static_pointer_cast<Application::ITickableService>(engine);
		data.tickOrder = PONY_ENGINE_ENGINE_MAIN_TICK_ORDER;
		PONY_LOG(context->Logger(), Log::LogType::Info, "Constructing '{}' done.", typeid(Engine).name());

		return data;
	}
}
