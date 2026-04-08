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

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:BackendModule;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.Log;
import PonyEngine.RenderDevice.Ext;

import :Backend;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	/// @brief Direct3D12 backend module.
	class BackendModule final : public Application::IModule
	{
	public:
		[[nodiscard("Pure constructor")]]
		BackendModule() noexcept = default;
		BackendModule(const BackendModule&) = delete;
		BackendModule(BackendModule&&) = delete;

		~BackendModule() noexcept = default;

		virtual void StartUp(Application::IModuleContext& context) override;
		virtual void ShutDown(Application::IModuleContext& context) override;

		BackendModule& operator =(const BackendModule&) = delete;
		BackendModule& operator =(BackendModule&&) = delete;

	private:
		BackendHandle backendHandle; ///< Direct3D12 backend handle.
	};
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	void BackendModule::StartUp(Application::IModuleContext& context)
	{
		IRenderDeviceModuleContext* renderDeviceModuleContext = context.GetData<IRenderDeviceModuleContext>();
#ifndef NDEBUG
		if (!renderDeviceModuleContext) [[unlikely]]
		{
			throw std::logic_error("Render device module context not found.");
		}
#endif

		PONY_LOG(context.Logger(), Log::LogType::Info, "Constructing '{}'...", typeid(Backend).name());
		backendHandle = renderDeviceModuleContext->AddBackend([](IRenderDeviceContext& renderDevice)
		{
			return std::make_shared<Backend>(renderDevice);
		});
		PONY_LOG(context.Logger(), Log::LogType::Info, "Constructing '{}' done.", typeid(Backend).name());
	}

	void BackendModule::ShutDown(Application::IModuleContext& context)
	{
		IRenderDeviceModuleContext* renderDeviceModuleContext = context.GetData<IRenderDeviceModuleContext>();
#ifndef NDEBUG
		if (!renderDeviceModuleContext) [[unlikely]]
		{
			throw std::logic_error("Render device module context not found.");
		}
#endif

		PONY_LOG(context.Logger(), Log::LogType::Info, "Releasing '{}'...", typeid(Backend).name());
		renderDeviceModuleContext->RemoveBackend(backendHandle);
		PONY_LOG(context.Logger(), Log::LogType::Info, "Releasing '{}' done.", typeid(Backend).name());
	}
}
