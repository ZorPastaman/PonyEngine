/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:D3D12BackendModule;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.RenderDevice.Ext;

import :D3D12Backend;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	class D3D12BackendModule final : public Application::IModule
	{
	public:
		[[nodiscard("Pure constructor")]]
		D3D12BackendModule() noexcept = default;
		D3D12BackendModule(const D3D12BackendModule&) = delete;
		D3D12BackendModule(D3D12BackendModule&&) = delete;

		~D3D12BackendModule() noexcept = default;

		virtual void StartUp(Application::IModuleContext& context) override;
		virtual void ShutDown(Application::IModuleContext& context) override;

		D3D12BackendModule& operator =(const D3D12BackendModule&) = delete;
		D3D12BackendModule& operator =(D3D12BackendModule&&) = delete;

	private:
		BackendHandle d3d12Handle;
	};
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	void D3D12BackendModule::StartUp(Application::IModuleContext& context)
	{
		IRenderDeviceModuleContext* renderDeviceModuleContext = context.GetData<IRenderDeviceModuleContext>();
#ifndef NDEBUG
		if (!renderDeviceModuleContext) [[unlikely]]
		{
			throw std::logic_error("Render device module context not found.");
		}
#endif

		d3d12Handle = renderDeviceModuleContext->AddBackend([](IRenderDeviceContext& renderDevice)
		{
			return std::make_shared<D3D12Backend>(renderDevice);
		});
	}

	void D3D12BackendModule::ShutDown(Application::IModuleContext& context)
	{
		IRenderDeviceModuleContext* renderDeviceModuleContext = context.GetData<IRenderDeviceModuleContext>();
#ifndef NDEBUG
		if (!renderDeviceModuleContext) [[unlikely]]
		{
			throw std::logic_error("Render device module context not found.");
		}
#endif

		renderDeviceModuleContext->RemoveBackend(d3d12Handle);
	}
}
