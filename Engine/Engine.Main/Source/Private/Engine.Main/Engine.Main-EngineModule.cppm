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

import PonyEngine.Core;
import PonyEngine.Log;

import :EngineFactory;

export namespace PonyEngine::Engine
{
	/// @brief Engine module.
	class EngineModule final : public Core::IModule
	{
	public:
		[[nodiscard("Pure constructor")]]
		EngineModule() noexcept = default;
		EngineModule(const EngineModule&) = delete;
		EngineModule(EngineModule&&) = delete;

		~EngineModule() noexcept = default;

		virtual void StartUp(Core::IModuleContext& context) override;
		virtual void ShutDown(const Core::IModuleContext& context) override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;

		EngineModule& operator =(const EngineModule&) = delete;
		EngineModule& operator =(EngineModule&&) = delete;
	};
}

namespace PonyEngine::Engine
{
	void EngineModule::StartUp(Core::IModuleContext& context)
	{
		PONY_LOG(context.Logger(), Log::LogType::Debug, "Constructing '{}' and adding it to context as '{}'.", typeid(EngineFactory).name(), typeid(PonyEngine::Core::IEngineFactory).name());
		context.AddData<Core::IEngineFactory>(std::make_shared<EngineFactory>(context));
	}

	void EngineModule::ShutDown(const Core::IModuleContext& context)
	{
	}

	std::string_view EngineModule::Name() const noexcept
	{
		return "PonyEngineEngine";
	}
}
