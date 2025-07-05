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
import PonyEngine.Core;
import PonyEngine.Engine.Extension;
import PonyEngine.Log;

import :Engine;

export namespace PonyEngine::Engine
{
	/// @brief Engine factory.
	class EngineFactory final : public Core::IEngineFactory
	{
	public:
		/// @brief Creates an engine factory.
		/// @param context Module context.
		[[nodiscard("Pure constructor")]]
		explicit EngineFactory(Core::IModuleContext& context) noexcept;
		EngineFactory(const EngineFactory&) = delete;
		EngineFactory(EngineFactory&&) = delete;

		~EngineFactory() noexcept = default;

		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<Core::IEngine> Create() override;

		EngineFactory& operator =(const EngineFactory&) = delete;
		EngineFactory& operator =(EngineFactory&&) = delete;

	private:
		Core::IModuleContext* context; ///< Module context.
	};
}

namespace PonyEngine::Engine
{
	EngineFactory::EngineFactory(Core::IModuleContext& context) noexcept :
		context{&context}
	{
	}

	std::shared_ptr<Core::IEngine> EngineFactory::Create()
	{
		PONY_LOG(context->Logger(), Log::LogType::Info, "Getting engine system factories.");
		const std::size_t systemFactoryCount = context->DataCount<ISystemFactory>();
		std::vector<ISystemFactory*> systemFactories;
		systemFactories.reserve(systemFactoryCount);
		for (std::size_t i = 0uz; i < systemFactoryCount; ++i)
		{
			systemFactories.push_back(context->GetData<ISystemFactory>(i).get());
		}

		PONY_LOG(context->Logger(), Log::LogType::Info, "Constructing engine.");
		return std::make_shared<Engine>(context->Application(), systemFactories);
	}
}
