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
#include "PonyEngine/RenderDevice/Windows/D3D12Framework.h"

export module PonyEngine.RenderDevice.D3D12.Impl.Windows:D3D12Device;

import std;

import PonyEngine.Log;
import PonyEngine.Meta;
import PonyEngine.Platform.Windows;
import PonyEngine.RenderDevice.Ext;

import :D3D12ObjectUtility;

export namespace PonyEngine::RenderDevice::Windows
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
		UINT8 GetPlaneCount(DXGI_FORMAT format) const;
		[[nodiscard("Pure function")]]
		UINT GetSampleQualityCount(DXGI_FORMAT format, UINT sampleCount) const;

		UINT64 GetCopyableFootprints(const D3D12_RESOURCE_DESC1& resourceDesc, UINT subresourceOffset, UINT subresourceCount,
			UINT64 baseOffset, D3D12_PLACED_SUBRESOURCE_FOOTPRINT* footprints, UINT* rowCounts, UINT64* rowSizes) const;

		[[nodiscard("Pure function")]]
		UINT GetDescriptorHandleIncrement(D3D12_DESCRIPTOR_HEAP_TYPE descriptorHeapType) const noexcept;

		[[nodiscard("Pure function")]]
		Platform::Windows::ComPtr<ID3D12CommandQueue> CreateCommandQueue(const D3D12_COMMAND_QUEUE_DESC& queueDesc, const GUID& creatorId);

		[[nodiscard("Pure function")]]
		Platform::Windows::ComPtr<ID3D12Resource2> CreateResource(const D3D12_HEAP_PROPERTIES& heapProperties, D3D12_HEAP_FLAGS heapFlags, 
			const D3D12_RESOURCE_DESC1& resourceDesc, D3D12_BARRIER_LAYOUT initialLayout = D3D12_BARRIER_LAYOUT_UNDEFINED,
			const D3D12_CLEAR_VALUE& clearValue = D3D12_CLEAR_VALUE{.Format = DXGI_FORMAT_UNKNOWN}, 
			std::span<const DXGI_FORMAT> castableFormats = std::span<const DXGI_FORMAT>());

		[[nodiscard("Pure function")]]
		Platform::Windows::ComPtr<ID3D12DescriptorHeap> CreateDescriptorHeap(const D3D12_DESCRIPTOR_HEAP_DESC& descriptorHeapDesc);
		void CreateCBV(const D3D12_CONSTANT_BUFFER_VIEW_DESC& cbvDesc, D3D12_CPU_DESCRIPTOR_HANDLE handle) noexcept;
		void CreateSRV(ID3D12Resource2& resource, const D3D12_SHADER_RESOURCE_VIEW_DESC& srvDesc, D3D12_CPU_DESCRIPTOR_HANDLE handle) noexcept;

		[[nodiscard("Pure function")]]
		Platform::Windows::ComPtr<ID3D12CommandAllocator> CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE commandListType);
		[[nodiscard("Pure function")]]
		Platform::Windows::ComPtr<ID3D12GraphicsCommandList10> CreateCommandList(D3D12_COMMAND_LIST_TYPE commandListType);

		[[nodiscard("Pure function")]]
		Platform::Windows::ComPtr<ID3D12Fence1> CreateFence();

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

namespace PonyEngine::RenderDevice::Windows
{
	D3D12Device::D3D12Device(IRenderDeviceContext& renderDevice) :
		renderDevice{&renderDevice}
	{
#ifndef NDEBUG
		PONY_LOG(this->renderDevice->Logger(), Log::LogType::Info, "Acquiring D3D12 debug interface...");
		if (const HRESULT result = D3D12GetDebugInterface(IID_PPV_ARGS(debug.GetAddress())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to acquire debug interface: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->renderDevice->Logger(), Log::LogType::Info, "Acquiring D3D12 debug interface done.");

		PONY_LOG(this->renderDevice->Logger(), Log::LogType::Debug, "Enabling D3D12 debug layer.");
		debug->EnableDebugLayer();
#endif

		PONY_LOG(this->renderDevice->Logger(), Log::LogType::Info, "Acquiring D3D12 device...");
		if (const HRESULT result = D3D12CreateDevice(nullptr, FeatureLevel, IID_PPV_ARGS(device.GetAddress())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to acquire D3D12 device: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->renderDevice->Logger(), Log::LogType::Info, "Acquiring D3D12 device done.");
	}

	D3D12Device::~D3D12Device() noexcept
	{
		PONY_LOG(renderDevice->Logger(), Log::LogType::Info, "Releasing D3D12 device...");
		device.Reset();
		PONY_LOG(renderDevice->Logger(), Log::LogType::Info, "Releasing D3D12 device done.");

#ifndef NDEBUG
		PONY_LOG(renderDevice->Logger(), Log::LogType::Info, "Releasing D3D12 debug interface...");
		debug.Reset();
		PONY_LOG(renderDevice->Logger(), Log::LogType::Info, "Releasing D3D12 debug interface done.");
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

	UINT8 D3D12Device::GetPlaneCount(const DXGI_FORMAT format) const
	{
		auto formatInfo = D3D12_FEATURE_DATA_FORMAT_INFO{.Format = format};
		if (const HRESULT result = device->CheckFeatureSupport(D3D12_FEATURE_FORMAT_INFO, &formatInfo, sizeof(formatInfo)); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to check texture format info: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		return formatInfo.PlaneCount;
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

	UINT64 D3D12Device::GetCopyableFootprints(const D3D12_RESOURCE_DESC1& resourceDesc, const UINT subresourceOffset, const UINT subresourceCount, const UINT64 baseOffset, 
		D3D12_PLACED_SUBRESOURCE_FOOTPRINT* const footprints, UINT* const rowCounts, UINT64* const rowSizes) const
	{
		UINT64 totalSize;
		device->GetCopyableFootprints1(&resourceDesc, subresourceOffset, subresourceCount, baseOffset, footprints, rowCounts, rowSizes, &totalSize);
		if (totalSize == std::numeric_limits<UINT64>::max()) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to get copyable footprints: invalid resource description"));
		}

		return totalSize;
	}

	UINT D3D12Device::GetDescriptorHandleIncrement(const D3D12_DESCRIPTOR_HEAP_TYPE descriptorHeapType) const noexcept
	{
		return device->GetDescriptorHandleIncrementSize(descriptorHeapType);
	}

	Platform::Windows::ComPtr<ID3D12CommandQueue> D3D12Device::CreateCommandQueue(const D3D12_COMMAND_QUEUE_DESC& queueDesc, const GUID& creatorId)
	{
		Platform::Windows::ComPtr<ID3D12CommandQueue> commandQueue;
		if (const HRESULT result = this->device->CreateCommandQueue1(&queueDesc, creatorId, IID_PPV_ARGS(commandQueue.GetAddress())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to acquire D3D12 command queue: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		return commandQueue;
	}

	Platform::Windows::ComPtr<ID3D12Resource2> D3D12Device::CreateResource(const D3D12_HEAP_PROPERTIES& heapProperties, const D3D12_HEAP_FLAGS heapFlags, 
		const D3D12_RESOURCE_DESC1& resourceDesc, const D3D12_BARRIER_LAYOUT initialLayout, const D3D12_CLEAR_VALUE& clearValue,
		const std::span<const DXGI_FORMAT> castableFormats)
	{
		if (castableFormats.size() > std::numeric_limits<UINT32>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Castable format count is too great");
		}

		Platform::Windows::ComPtr<ID3D12Resource2> resource;
		if (const HRESULT result = device->CreateCommittedResource3(&heapProperties, heapFlags, &resourceDesc, initialLayout, 
			clearValue.Format != DXGI_FORMAT_UNKNOWN ? &clearValue : nullptr, nullptr, 
			static_cast<UINT32>(castableFormats.size()), castableFormats.data(), IID_PPV_ARGS(resource.GetAddress())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to create D3D12 resource: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		return resource;
	}

	Platform::Windows::ComPtr<ID3D12DescriptorHeap> D3D12Device::CreateDescriptorHeap(const D3D12_DESCRIPTOR_HEAP_DESC& descriptorHeapDesc)
	{
		Platform::Windows::ComPtr<ID3D12DescriptorHeap> descriptorHeap;
		if (const HRESULT result = device->CreateDescriptorHeap(&descriptorHeapDesc, IID_PPV_ARGS(descriptorHeap.GetAddress())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to create D3D12 descriptor heap: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		return descriptorHeap;
	}

	void D3D12Device::CreateCBV(const D3D12_CONSTANT_BUFFER_VIEW_DESC& cbvDesc, const D3D12_CPU_DESCRIPTOR_HANDLE handle) noexcept
	{
		device->CreateConstantBufferView(&cbvDesc, handle);
	}

	void D3D12Device::CreateSRV(ID3D12Resource2& resource, const D3D12_SHADER_RESOURCE_VIEW_DESC& srvDesc, const D3D12_CPU_DESCRIPTOR_HANDLE handle) noexcept
	{
		device->CreateShaderResourceView(&resource, &srvDesc, handle);
	}

	Platform::Windows::ComPtr<ID3D12CommandAllocator> D3D12Device::CreateCommandAllocator(const D3D12_COMMAND_LIST_TYPE commandListType)
	{
		Platform::Windows::ComPtr<ID3D12CommandAllocator> allocator;
		if (const HRESULT result = device->CreateCommandAllocator(commandListType, IID_PPV_ARGS(allocator.GetAddress())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to create D3D12 command allocator: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		return allocator;
	}

	Platform::Windows::ComPtr<ID3D12GraphicsCommandList10> D3D12Device::CreateCommandList(const D3D12_COMMAND_LIST_TYPE commandListType)
	{
		Platform::Windows::ComPtr<ID3D12GraphicsCommandList10> commandList;
		if (const HRESULT result = device->CreateCommandList1(0u, commandListType, D3D12_COMMAND_LIST_FLAG_NONE, IID_PPV_ARGS(commandList.GetAddress())); 
			FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to create D3D12 graphics command list: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		return commandList;
	}

	Platform::Windows::ComPtr<ID3D12Fence1> D3D12Device::CreateFence()
	{
		Platform::Windows::ComPtr<ID3D12Fence1> fence;
		if (const HRESULT result = device->CreateFence(0ull, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(fence.GetAddress())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to create D3D12 fence: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		return fence;
	}

	void D3D12Device::SetName(const std::string_view name)
	{
		SetObjectName(*device, name);
	}
}
