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

export module PonyEngine.Surface.Main:SurfaceServiceModule;

import PonyEngine.Application.Extension;
import PonyEngine.Log;
import PonyEngine.Surface;

import :MessageHandler;
import :ParamProvider;
import :SurfaceService;

#if PONY_WINDOWS
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
#endif

#if PONY_WINDOWS
namespace PonyEngine::Surface::Windows
{
	void SurfaceServiceModule::StartUp(Application::IModuleContext& context)
	{
		ISurfaceService* surface;

		PONY_LOG(context.Logger(), Log::LogType::Info, "Constructing '{}'...", typeid(SurfaceService).name());
		try
		{
			surfaceServiceHandle = context.ServiceModuleContext().AddService([&](Application::IApplicationContext& application)
			{
				MessageHandlerApp = &application;

				PONY_LOG(context.Logger(), Log::LogType::Debug, "Getting surface parameters.");
				// TODO: Load some data via config service.
				const std::string_view title = application.ProjectTitle();
				constexpr Math::ColorRGB<std::uint8_t> backgroundColor = GetBackgroundColor();
				const HICON mainIcon = application.Native().AppIcon();
				const HCURSOR mainCursor = application.Native().AppCursor() ? application.Native().AppCursor() : GetDefaultCursor();

				PONY_LOG(context.Logger(), Log::LogType::Info, "Constructing Windows window class...");
				const auto windowClass = std::make_shared<WindowClass>(application, mainIcon, nullptr, mainCursor, backgroundColor);
				PONY_LOG(context.Logger(), Log::LogType::Info, "Constructing Windows window class done. Class: '0x{:X}'.", windowClass->ClassHandle());

				const auto surfaceService = std::make_shared<SurfaceService>(application, windowClass, title);
				Application::ServiceData data;
				data.SetService(surfaceService);
				data.AddInterface(&surfaceService->PublicSurfaceService());
				data.AddInterface(static_cast<Surface::ISurfaceService*>(&surfaceService->PublicSurfaceService()));
				surface = &surfaceService->PublicSurfaceService();

				return data;
			});
		}
		catch (...)
		{
			MessageHandlerApp = nullptr;
			throw;
		}
		PONY_LOG(context.Logger(), Log::LogType::Info, "Constructing '{}' done.", typeid(SurfaceService).name());

		//surface->RectStyle(WindowRectStyle{.hasFrame = true, .movable = true, .resizable = true, .closable = true, .maximizable = true, .minimizable = true, .alwaysOnTop = true});
		//surface->ClientRect(Rect<std::int32_t>{.position = Math::Vector2<std::int32_t>(100, 100), .size = Math::Vector2<std::int32_t>(640, 480)});
	}

	void SurfaceServiceModule::ShutDown(Application::IModuleContext& context)
	{
		try
		{
			context.ServiceModuleContext().RemoveService(surfaceServiceHandle);
		}
		catch (...)
		{
			MessageHandlerApp = nullptr;
			throw;
		}

		MessageHandlerApp = nullptr;
	}
}
#endif
