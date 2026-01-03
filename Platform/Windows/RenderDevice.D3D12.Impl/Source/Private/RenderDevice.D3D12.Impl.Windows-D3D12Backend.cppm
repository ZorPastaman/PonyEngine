/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice.D3D12.Impl.Windows:D3D12Backend;

import std;

import PonyEngine.RenderDevice.Ext;

import :DXGIFactory;
import :D3D12Device;

export namespace PonyEngine::Render::Windows
{
	class D3D12Backend final : public IBackend
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit D3D12Backend(IRenderDeviceContext& renderDevice) noexcept;
		D3D12Backend(const D3D12Backend&) = delete;
		D3D12Backend(D3D12Backend&&) = delete;

		~D3D12Backend() noexcept = default;

		[[nodiscard("Pure function")]] 
		virtual std::string_view RenderApiName() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual Meta::Version RenderApiVersion() const noexcept override;

		virtual void Activate() override;
		virtual void Deactivate() override;

		D3D12Backend& operator =(const D3D12Backend&) = delete;
		D3D12Backend& operator =(D3D12Backend&&) = delete;

	private:
		IRenderDeviceContext* renderDevice;

		std::unique_ptr<DXGIFactory> factory;
		std::unique_ptr<D3D12Device> device;
	};
}

namespace PonyEngine::Render::Windows
{
	D3D12Backend::D3D12Backend(IRenderDeviceContext& renderDevice) noexcept :
		renderDevice{&renderDevice}
	{
	}

	std::string_view D3D12Backend::RenderApiName() const noexcept
	{
		return D3D12Device::ApiName;
	}

	Meta::Version D3D12Backend::RenderApiVersion() const noexcept
	{
		return D3D12Device::ApiVersion;
	}

	void D3D12Backend::Activate()
	{
		factory = std::make_unique<DXGIFactory>(*renderDevice);
		device = std::make_unique<D3D12Device>(*renderDevice);
	}

	void D3D12Backend::Deactivate()
	{
		device.reset();
		factory.reset();
	}
}
