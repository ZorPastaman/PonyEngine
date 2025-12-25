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

export module PonyEngine.RenderDevice.Impl:RenderDeviceServiceModule;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.Log;
import PonyEngine.RenderDevice.Ext;

import :RenderDeviceService;

export namespace PonyEngine::Render
{
	/// @brief Render service module.
	class RenderDeviceServiceModule final : public Application::IModule
	{
	public:
		[[nodiscard("Pure constructor")]]
		RenderDeviceServiceModule() noexcept = default;
		RenderDeviceServiceModule(const RenderDeviceServiceModule&) = delete;
		RenderDeviceServiceModule(RenderDeviceServiceModule&&) = delete;

		~RenderDeviceServiceModule() noexcept = default;

		virtual void StartUp(Application::IModuleContext& context) override;
		virtual void ShutDown(Application::IModuleContext& context) override;

		RenderDeviceServiceModule& operator =(const RenderDeviceServiceModule&) = delete;
		RenderDeviceServiceModule& operator =(RenderDeviceServiceModule&&) = delete;

	private:
		Application::ModuleDataHandle renderServiceModuleHandle; ///< Render service module handle.
		Application::ServiceHandle renderServiceHandle; ///< Render service handle.
	};
}

namespace PonyEngine::Render
{
	void RenderDeviceServiceModule::StartUp(Application::IModuleContext& context)
	{
		PONY_LOG(context.Logger(), Log::LogType::Info, "Constructing '{}'...", typeid(RenderDeviceService).name());
		try
		{
			renderServiceHandle = context.ServiceModuleContext().AddService([&](Application::IApplicationContext& application)
			{
				const auto render = std::make_shared<RenderDeviceService>(application);
				renderServiceModuleHandle = context.AddData(std::shared_ptr<IRenderDeviceModuleContext>(render, render.get()));

				return render;
			});
		}
		catch (...)
		{
			if (renderServiceModuleHandle.IsValid())
			{
				context.RemoveData(renderServiceModuleHandle);
			}
			throw;
		}
		PONY_LOG(context.Logger(), Log::LogType::Info, "Constructing '{}' done.", typeid(RenderDeviceService).name());
	}

	void RenderDeviceServiceModule::ShutDown(Application::IModuleContext& context)
	{
		PONY_LOG(context.Logger(), Log::LogType::Info, "Releasing '{}'...", typeid(RenderDeviceService).name());
		context.ServiceModuleContext().RemoveService(renderServiceHandle);
		context.RemoveData(renderServiceModuleHandle);
		PONY_LOG(context.Logger(), Log::LogType::Info, "Releasing '{}' done.", typeid(RenderDeviceService).name());
	}
}
