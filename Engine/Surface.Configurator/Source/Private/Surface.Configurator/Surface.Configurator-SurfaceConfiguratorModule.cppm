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
#include "PonyEngine/Utility/Macro.h"

export module PonyEngine.Surface.Configurator:SurfaceConfigurator;

import std;

import PonyEngine.Application;
import PonyEngine.Log;
import PonyEngine.Surface.Extension;

export namespace PonyEngine::Surface
{
	/// @brief Surface configurator module.
	class SurfaceConfiguratorModule final : public Application::IModule
	{
	public:
		[[nodiscard("Pure constructor")]]
		SurfaceConfiguratorModule() noexcept = default;
		SurfaceConfiguratorModule(const SurfaceConfiguratorModule&) = delete;
		SurfaceConfiguratorModule(SurfaceConfiguratorModule&&) = delete;

		~SurfaceConfiguratorModule() noexcept = default;

		virtual void StartUp(Application::IModuleContext& context) override;
		virtual void ShutDown(const Application::IModuleContext& context) override;

		SurfaceConfiguratorModule& operator =(const SurfaceConfiguratorModule&) = delete;
		SurfaceConfiguratorModule& operator =(SurfaceConfiguratorModule&&) = delete;
	};
}

namespace PonyEngine::Surface
{
	void SurfaceConfiguratorModule::StartUp(Application::IModuleContext& context)
	{
		PONY_LOG(context.Logger(), Log::LogType::Debug, "Constructing '{}'...", typeid(SurfaceParams).name());
		const auto params = std::make_shared<SurfaceParams>();
		params->title = context.Application().ProjectTitle();
		PONY_LOG(context.Logger(), Log::LogType::Debug, "Constructing '{}' done. Title: {}.", typeid(SurfaceParams).name(), params->title);
		PONY_LOG(context.Logger(), Log::LogType::Debug, "Adding '{}' as data of type '{}'.", typeid(SurfaceParams).name(), typeid(SurfaceParams).name());
		context.AddData<SurfaceParams>(params);
	}

	void SurfaceConfiguratorModule::ShutDown(const Application::IModuleContext&)
	{
	}
}
