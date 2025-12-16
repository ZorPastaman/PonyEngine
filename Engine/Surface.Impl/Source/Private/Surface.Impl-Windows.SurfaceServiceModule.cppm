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

export module PonyEngine.Surface.Impl:Windows.SurfaceServiceModule;

import PonyEngine.Application.Ext;
import PonyEngine.Log;
import PonyEngine.Platform;
import PonyEngine.Surface;

import :Windows.MessageHandler;
import :Windows.SurfaceService;

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
		virtual void ShutDown(Application::IModuleContext& context) override;

		SurfaceServiceModule& operator =(const SurfaceServiceModule&) = delete;
		SurfaceServiceModule& operator =(SurfaceServiceModule&&) = delete;

	private:
		Application::ServiceHandle surfaceServiceHandle; ///< Surface service handle.
	};
}

namespace PonyEngine::Surface::Windows
{
	void SurfaceServiceModule::StartUp(Application::IModuleContext& context)
	{
		PONY_LOG(context.Logger(), Log::LogType::Info, "Constructing '{}'...", typeid(SurfaceService).name());
		surfaceServiceHandle = context.ServiceModuleContext().AddService([&](Application::IApplicationContext& application)
		{
			PONY_LOG(context.Logger(), Log::LogType::Debug, "Getting surface parameters.");
			auto& nativeApplication = static_cast<Application::Windows::IApplicationContext&>(application);
			const std::string_view title = application.ProjectTitle();
			const HICON mainIcon = nativeApplication.AppIcon();
			const HCURSOR mainCursor = nativeApplication.AppCursor() ? nativeApplication.AppCursor() : Platform::Windows::GetDefaultCursor();

			PONY_LOG(context.Logger(), Log::LogType::Info, "Constructing Windows window class...");
			const auto windowClass = std::make_shared<WindowClass>(application, mainIcon, nullptr, mainCursor);
			PONY_LOG(context.Logger(), Log::LogType::Info, "Constructing Windows window class done. Class: '0x{:X}'.", windowClass->ClassHandle());

			const auto surfaceService = std::make_shared<SurfaceService>(nativeApplication, windowClass, title);
			Application::ServiceData data;
			data.SetService(surfaceService);
			data.AddInterface(&surfaceService->PublicSurfaceService());
			data.AddInterface(static_cast<Surface::ISurfaceService*>(&surfaceService->PublicSurfaceService()));

			return data;
		});
		PONY_LOG(context.Logger(), Log::LogType::Info, "Constructing '{}' done.", typeid(SurfaceService).name());
	}

	void SurfaceServiceModule::ShutDown(Application::IModuleContext& context)
	{
		PONY_LOG(context.Logger(), Log::LogType::Info, "Releasing '{}'...", typeid(SurfaceService).name());
		context.ServiceModuleContext().RemoveService(surfaceServiceHandle);
		PONY_LOG(context.Logger(), Log::LogType::Info, "Releasing '{}' done.", typeid(SurfaceService).name());
	}
}
