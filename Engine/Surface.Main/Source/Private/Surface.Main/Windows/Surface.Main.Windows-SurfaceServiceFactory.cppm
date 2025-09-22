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

export module PonyEngine.Surface.Main.Windows:SurfaceServiceFactory;

import std;

import PonyEngine.Application;
import PonyEngine.Log;
import PonyEngine.Surface.Extension.Windows;
import PonyEngine.Utility;

import :SurfaceService;

export namespace PonyEngine::Surface::Windows
{
	class SurfaceServiceFactory final : public Application::IServiceFactory
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit SurfaceServiceFactory(Application::IModuleContext& context) noexcept;
		SurfaceServiceFactory(const SurfaceServiceFactory&) = delete;
		SurfaceServiceFactory(SurfaceServiceFactory&&) = delete;

		~SurfaceServiceFactory() noexcept = default;

		[[nodiscard("Redundant call")]]
		virtual Application::ServiceData Create(Application::IApplicationContext& application) override;

		SurfaceServiceFactory& operator =(const SurfaceServiceFactory&) = delete;
		SurfaceServiceFactory& operator =(SurfaceServiceFactory&&) = delete;

	private:
		Application::IModuleContext* context;
	};
}

namespace PonyEngine::Surface::Windows
{
	SurfaceServiceFactory::SurfaceServiceFactory(Application::IModuleContext& context) noexcept :
		context{&context}
	{
	}

	Application::ServiceData SurfaceServiceFactory::Create(Application::IApplicationContext& application)
	{
		PONY_LOG(context->Logger(), Log::LogType::Info, "Getting surface parameters.");
		if (context->DataCount<SurfaceParams>() == 0) [[unlikely]]
		{
			throw std::runtime_error("Surface parameters not found.");
		}
		PONY_LOG_IF(context->DataCount<SurfaceParams>() > 1uz, context->Logger(), Log::LogType::Warning, "Multiple surface parameters found. First one will be used.");
		const auto params = context->GetData<SurfaceParams>(0uz);
		if (!params) [[unlikely]]
		{
			throw std::runtime_error("Surface parameters is nullptr.");
		}

		PONY_LOG(context->Logger(), Log::LogType::Info, "Constructing Windows window class.");
		const auto windowClass = std::make_shared<WindowClass>(application, params->icon, params->smallIcon, params->cursor, params->backgroundColor);

		PONY_LOG(context->Logger(), Log::LogType::Info, "Constructing Windows surface service.");
		const auto surfaceService = std::make_shared<SurfaceService>(application, windowClass, params->title, params->rect, params->minimalSize, params->style);

		Application::ServiceData data;
		data.service = std::static_pointer_cast<Application::ITickableService>(surfaceService);
		data.publicInterfaces.AddInterface<Surface::ISurfaceService>(surfaceService->PublicSurfaceService());
		data.publicInterfaces.AddInterface<ISurfaceService>(surfaceService->PublicSurfaceService());
		data.tickOrder = PONY_ENGINE_SURFACE_MAIN_TICK_ORDER;

		return data;
	}
}
