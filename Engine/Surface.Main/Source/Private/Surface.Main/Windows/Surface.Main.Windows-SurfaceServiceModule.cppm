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

export module PonyEngine.Surface.Main.Windows:SurfaceServiceModule;

import PonyEngine.Application;
import PonyEngine.Log;

import :MessageHandler;
import :SurfaceServiceFactory;

export namespace PonyEngine::Surface::Windows
{
	/// @brief Windows surface service module.
	class SurfaceServiceModule final : public Application::IModule
	{
	public:
		[[nodiscard("Pure constructor")]]
		SurfaceServiceModule() noexcept = default;
		SurfaceServiceModule(const SurfaceServiceModule&) = delete;
		SurfaceServiceModule(SurfaceServiceModule&&) = delete;

		~SurfaceServiceModule() noexcept = default;

		virtual void StartUp(Application::IModuleContext& context) override;
		virtual void ShutDown(const Application::IModuleContext& context) override;

		SurfaceServiceModule& operator =(const SurfaceServiceModule&) = delete;
		SurfaceServiceModule& operator =(SurfaceServiceModule&&) = delete;
	};
}

namespace PonyEngine::Surface::Windows
{
	void SurfaceServiceModule::StartUp(Application::IModuleContext& context)
	{
		messageHandlerApp = &context.Application();

		PONY_LOG(context.Logger(), Log::LogType::Debug, "Constructing '{}'...", typeid(SurfaceServiceFactory).name());
		const auto surfaceServiceFactory = std::make_shared<SurfaceServiceFactory>(context);
		PONY_LOG(context.Logger(), Log::LogType::Debug, "Constructing '{}' done.", typeid(SurfaceServiceFactory).name());
		PONY_LOG(context.Logger(), Log::LogType::Debug, "Adding '{}' as service.", typeid(SurfaceServiceFactory).name());
		context.AddService(surfaceServiceFactory);
	}

	void SurfaceServiceModule::ShutDown(const Application::IModuleContext&)
	{
		messageHandlerApp = nullptr;
	}
}
