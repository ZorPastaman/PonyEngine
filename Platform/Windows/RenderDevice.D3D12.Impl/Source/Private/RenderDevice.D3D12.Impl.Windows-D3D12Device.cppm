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

import :D3D12Utility;

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

		[[nodiscard("Pure function")]]
		D3D12_FEATURE_DATA_FORMAT_SUPPORT GetFormatSupport(DXGI_FORMAT format) const;
		[[nodiscard("Pure function")]]
		UINT GetSampleQualityCount(DXGI_FORMAT format, UINT sampleCount) const;

		[[nodiscard("Pure function")]]
		Platform::Windows::ComPtr<ID3D12CommandQueue> CreateCommandQueue(const D3D12_COMMAND_QUEUE_DESC& queueDesc, const GUID& creatorId);

		[[nodiscard("Pure function")]]
		Platform::Windows::ComPtr<ID3D12Resource2> CreateResource(const D3D12_HEAP_PROPERTIES& heapProperties, D3D12_HEAP_FLAGS heapFlags, 
			const D3D12_RESOURCE_DESC1& resourceDesc, D3D12_BARRIER_LAYOUT initialLayout = D3D12_BARRIER_LAYOUT_UNDEFINED,
			const D3D12_CLEAR_VALUE& clearValue = D3D12_CLEAR_VALUE{.Format = DXGI_FORMAT_UNKNOWN}, 
			std::span<const DXGI_FORMAT> castableFormats = std::span<const DXGI_FORMAT>());

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
		PONY_LOG(renderDevice->Logger(), Log::LogType::Info, "Releasing d3d12 device...");
		device.Reset();
		PONY_LOG(renderDevice->Logger(), Log::LogType::Info, "Releasing d3d12 device done.");

#ifndef NDEBUG
		PONY_LOG(renderDevice->Logger(), Log::LogType::Info, "Releasing debug interface...");
		debug.Reset();
		PONY_LOG(renderDevice->Logger(), Log::LogType::Info, "Releasing debug interface done.");
#endif
	}

	D3D12_FEATURE_DATA_FORMAT_SUPPORT D3D12Device::GetFormatSupport(const DXGI_FORMAT format) const
	{
		auto formatSupport = D3D12_FEATURE_DATA_FORMAT_SUPPORT{.Format = format};
		if (const HRESULT result = device->CheckFeatureSupport(D3D12_FEATURE_FORMAT_SUPPORT, &formatSupport, sizeof(formatSupport)); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to check texture format support: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		return formatSupport;
	}

	UINT D3D12Device::GetSampleQualityCount(const DXGI_FORMAT format, const UINT sampleCount) const
	{
		auto levels = D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS{.Format = format, .SampleCount = sampleCount, .Flags = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE};
		if (const HRESULT result = device->CheckFeatureSupport(D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS, &levels, sizeof(levels)); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to check sampling support: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		return levels.NumQualityLevels;
	}

	Platform::Windows::ComPtr<ID3D12CommandQueue> D3D12Device::CreateCommandQueue(const D3D12_COMMAND_QUEUE_DESC& queueDesc, const GUID& creatorId)
	{
		Platform::Windows::ComPtr<ID3D12CommandQueue> commandQueue;
		if (const HRESULT result = this->device->CreateCommandQueue1(&queueDesc, creatorId, IID_PPV_ARGS(commandQueue.GetAddress())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to acquire d3d12 command queue: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		return commandQueue;
	}

	Platform::Windows::ComPtr<ID3D12Resource2> D3D12Device::CreateResource(const D3D12_HEAP_PROPERTIES& heapProperties, const D3D12_HEAP_FLAGS heapFlags, 
		const D3D12_RESOURCE_DESC1& resourceDesc, const D3D12_BARRIER_LAYOUT initialLayout, const D3D12_CLEAR_VALUE& clearValue,
		const std::span<const DXGI_FORMAT> castableFormats)
	{
		Platform::Windows::ComPtr<ID3D12Resource2> resource;
		if (const HRESULT result = device->CreateCommittedResource3(&heapProperties, heapFlags, &resourceDesc, initialLayout, 
			clearValue.Format != DXGI_FORMAT_UNKNOWN ? &clearValue : nullptr, nullptr, 
			static_cast<UINT32>(castableFormats.size()), castableFormats.data(), IID_PPV_ARGS(resource.GetAddress())); FAILED(result))
		{
			throw std::runtime_error(std::format("Failed to create resource: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		return resource;
	}

	void D3D12Device::SetName(const std::string_view name)
	{
		Windows::SetName(*device, name);
	}
}
