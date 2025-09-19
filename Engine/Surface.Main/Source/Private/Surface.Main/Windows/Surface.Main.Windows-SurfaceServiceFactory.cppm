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
import PonyEngine.Surface.Windows;
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
		[[nodiscard("Pure function")]]
		SurfaceParams GetParams() const;
		[[nodiscard("Pure function")]]
		SurfaceParams AssembleParams() const;

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
		const SurfaceParams params = GetParams();

		PONY_LOG(context->Logger(), Log::LogType::Info, "Constructing Windows window class.");
		const HBRUSH backgroundBrush = CreateSolidBrush(RGB(params.backgroundColor.R(), params.backgroundColor.G(), params.backgroundColor.B()));
		if (!backgroundBrush) [[unlikely]]
		{
			throw std::runtime_error(Utility::SafeFormat("Failed to create background brush. Error code: '0x{:X}'.", GetLastError()));
		}
		const auto windowClass = std::make_shared<WindowClass>(application, params.icon, params.smallIcon, params.cursor, backgroundBrush);

		PONY_LOG(context->Logger(), Log::LogType::Info, "Constructing Windows surface service.");
		const auto surfaceService = std::make_shared<SurfaceService>(application, windowClass, params.title, params.rect, params.minimalSize, params.style);

		Application::ServiceData data;
		data.service = std::static_pointer_cast<Application::ITickableService>(surfaceService);
		data.publicInterfaces.AddInterface<Surface::ISurfaceService>(surfaceService->PublicSurfaceService());
		data.publicInterfaces.AddInterface<ISurfaceService>(surfaceService->PublicSurfaceService());
		data.tickOrder = PONY_ENGINE_SURFACE_MAIN_TICK_ORDER;

		return data;
	}

	SurfaceParams SurfaceServiceFactory::GetParams() const
	{
		if (context->DataCount(typeid(SurfaceParams)))
		{
			PONY_LOG(context->Logger(), Log::LogType::Info, "Getting preset surface parameters.");
			return *context->GetData<SurfaceParams>(0uz);
		}
		else
		{
			PONY_LOG(context->Logger(), Log::LogType::Info, "Assembling surface parameters.");
			return AssembleParams();
		}
	}

	SurfaceParams SurfaceServiceFactory::AssembleParams() const
	{
		// TODO: Fill data including different sources like command line, configs etc.
		return SurfaceParams();
	}
}
