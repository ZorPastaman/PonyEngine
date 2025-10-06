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
import :SurfaceService;

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
		MessageHandlerApp = &context.Application();

		PONY_LOG(context.Logger(), Log::LogType::Debug, "Getting surface parameters.");
		if (context.DataCount<SurfaceParams>() == 0) [[unlikely]]
		{
			throw std::runtime_error("Surface parameters not found.");
		}
		PONY_LOG_IF(context.DataCount<SurfaceParams>() > 1uz, context.Logger(), Log::LogType::Warning, "Multiple surface parameters found. First one will be used.");
		const auto params = context.GetData<SurfaceParams>(0uz);
		if (!params) [[unlikely]]
		{
			throw std::runtime_error("Surface parameters is nullptr.");
		}
		const HICON mainIcon = context.Application().Native().AppIcon();
		const HCURSOR mainCursor = context.Application().Native().AppCursor() ? context.Application().Native().AppCursor() : GetDefaultCursor();

		PONY_LOG(context.Logger(), Log::LogType::Info, "Constructing Windows window class...");
		const auto windowClass = std::make_shared<WindowClass>(context.Application(), mainIcon, nullptr, mainCursor, params->backgroundColor);
		PONY_LOG(context.Logger(), Log::LogType::Info, "Constructing Windows window class done. Class: '0x{:X}'.", windowClass->ClassHandle());

		PONY_LOG(context.Logger(), Log::LogType::Info, "Constructing Windows surface service...");
		const auto surfaceService = std::make_shared<SurfaceService>(context.Application(), windowClass, params->title, params->clientRect, params->minimalClientSize, params->style,
			params->showCursor, params->cursorClippingRect);
		Application::ServiceData data;
		data.service = surfaceService;
		data.publicInterfaces.push_back(Memory::TypedPtr(static_cast<Surface::ISurfaceService*>(&surfaceService->PublicSurfaceService())));
		data.publicInterfaces.push_back(Memory::TypedPtr(&surfaceService->PublicSurfaceService()));
		PONY_LOG(context.Logger(), Log::LogType::Info, "Constructing Windows surface service done.");
		PONY_LOG(context.Logger(), Log::LogType::Debug, "Adding '{}' as service.", typeid(SurfaceService).name());
		context.AddService(data);
	}

	void SurfaceServiceModule::ShutDown(const Application::IModuleContext&)
	{
		MessageHandlerApp = nullptr;
	}
}
