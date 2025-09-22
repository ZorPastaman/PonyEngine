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
#include "PonyEngine/Platform/Windows/Framework.h"
#include "PonyEngine/Utility/Macro.h"

export module PonyEngine.Surface.Configurator.Windows:SurfaceConfiguratorModule;

import std;

import PonyEngine.Application;
import PonyEngine.Log;
import PonyEngine.Platform.Windows;
import PonyEngine.Surface.Extension.Windows;

export namespace PonyEngine::Surface::Windows
{
	/// @brief Windows surface configurator module.
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

namespace PonyEngine::Surface::Windows
{
	void SurfaceConfiguratorModule::StartUp(Application::IModuleContext& context)
	{
		PONY_LOG(context.Logger(), Log::LogType::Debug, "Constructing '{}' and adding it to context as data.", typeid(SurfaceParams).name());
		const auto params = std::make_shared<SurfaceParams>();
		params->title = PONY_STRINGIFY_VALUE(PONY_PROJECT_NAME);
		params->cursor = Platform::Windows::DefaultCursor();
		context.AddData<SurfaceParams>(params);
		context.AddData<Surface::SurfaceParams>(params);
		// TODO: Add other data.
	}

	void SurfaceConfiguratorModule::ShutDown(const Application::IModuleContext&)
	{
	}
}
