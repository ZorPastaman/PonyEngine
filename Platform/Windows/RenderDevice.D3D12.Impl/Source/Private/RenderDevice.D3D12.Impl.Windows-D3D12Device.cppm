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
#include "PonyEngine/Render/Windows/D3D12Framework.h"

export module PonyEngine.RenderDevice.D3D12.Impl.Windows:D3D12Device;

import std;

import PonyEngine.Log;
import PonyEngine.Meta;
import PonyEngine.Platform.Windows;
import PonyEngine.RenderDevice.Ext;

import :Utility;

export namespace PonyEngine::Render::Windows
{
	class D3D12Device final
	{
	public:
		static constexpr std::string_view ApiName = RenderAPI::Direct3D;
		static constexpr auto ApiVersion = Meta::Version(12, 2);
		static constexpr D3D_FEATURE_LEVEL FeatureLevel = D3D_FEATURE_LEVEL_12_2;

		[[nodiscard("Pure constructor")]]
		explicit D3D12Device(IRenderDeviceContext& renderDevice);
		D3D12Device(const D3D12Device&) = delete;
		D3D12Device(D3D12Device&&) = delete;

		~D3D12Device() noexcept;

		void SetName(std::string_view name);

		D3D12Device& operator =(const D3D12Device&) = delete;
		D3D12Device& operator =(D3D12Device&&) = delete;

	private:
		IRenderDeviceContext* renderDevice;

#ifndef NDEBUG
		Platform::Windows::ComPtr<ID3D12Debug6> debug; ///< Debug interface.
#endif
		Platform::Windows::ComPtr<ID3D12Device14> device; ///< Render device.
	};
}

namespace PonyEngine::Render::Windows
{
	D3D12Device::D3D12Device(IRenderDeviceContext& renderDevice) :
		renderDevice{&renderDevice}
	{
#ifndef NDEBUG
		PONY_LOG(this->renderDevice->Logger(), Log::LogType::Info, "Acquiring debug interface...");
		if (const HRESULT result = D3D12GetDebugInterface(IID_PPV_ARGS(debug.GetAddress())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to acquire debug interface: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->renderDevice->Logger(), Log::LogType::Info, "Acquiring debug interface done.");

		PONY_LOG(this->renderDevice->Logger(), Log::LogType::Debug, "Enabling debug layer.");
		debug->EnableDebugLayer();
#endif

		PONY_LOG(this->renderDevice->Logger(), Log::LogType::Info, "Acquiring d3d12 device...");
		if (const HRESULT result = D3D12CreateDevice(nullptr, FeatureLevel, IID_PPV_ARGS(device.GetAddress())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to acquire device: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->renderDevice->Logger(), Log::LogType::Info, "Acquiring d3d12 device done.");
	}

	D3D12Device::~D3D12Device() noexcept
	{
		PONY_LOG(this->renderDevice->Logger(), Log::LogType::Info, "Releasing d3d12 device...");
		device.Reset();
		PONY_LOG(this->renderDevice->Logger(), Log::LogType::Info, "Releasing d3d12 device done.");

#ifndef NDEBUG
		PONY_LOG(this->renderDevice->Logger(), Log::LogType::Info, "Releasing debug interface...");
		debug.Reset();
		PONY_LOG(this->renderDevice->Logger(), Log::LogType::Info, "Releasing debug interface done.");
#endif
	}

	void D3D12Device::SetName(const std::string_view name)
	{
		Windows::SetName(*device, name);
	}
}
