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

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:Device;

import std;

import PonyEngine.Log;
import PonyEngine.Meta;
import PonyEngine.Platform.Windows;
import PonyEngine.RenderDevice.Ext;

import :ObjectUtility;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	class Device final
	{
	public:
		static constexpr std::string_view ApiName = RenderAPI::Direct3D;
		static constexpr auto ApiVersion = Meta::Version(12, 2);
		static constexpr D3D_FEATURE_LEVEL FeatureLevel = D3D_FEATURE_LEVEL_12_2;

		[[nodiscard("Pure constructor")]]
		explicit Device(IRenderDeviceContext& renderDevice);
		Device(const Device&) = delete;
		Device(Device&&) = delete;

		~Device() noexcept;

		[[nodiscard("Pure function")]]
		D3D_SHADER_MODEL GetShaderModel() const;
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
		void CreateCBV(const D3D12_CONSTANT_BUFFER_VIEW_DESC* cbvDesc, D3D12_CPU_DESCRIPTOR_HANDLE handle) noexcept;
		void CreateSRV(ID3D12Resource2* resource, const D3D12_SHADER_RESOURCE_VIEW_DESC& srvDesc, D3D12_CPU_DESCRIPTOR_HANDLE handle) noexcept;
		void CreateUAV(ID3D12Resource2* resource, const D3D12_UNORDERED_ACCESS_VIEW_DESC& uavDesc, D3D12_CPU_DESCRIPTOR_HANDLE handle) noexcept;
		void CreateRTV(ID3D12Resource2* resource, const D3D12_RENDER_TARGET_VIEW_DESC& rtvDesc, D3D12_CPU_DESCRIPTOR_HANDLE handle) noexcept;
		void CreateDSV(ID3D12Resource2* resource, const D3D12_DEPTH_STENCIL_VIEW_DESC& dsvDesc, D3D12_CPU_DESCRIPTOR_HANDLE handle) noexcept;
		void CreateSampler(const D3D12_SAMPLER_DESC2& samplerDesc, D3D12_CPU_DESCRIPTOR_HANDLE handle) noexcept;
		void CopyDescriptors(UINT rangeCount, const UINT* rangeSizes, 
			const D3D12_CPU_DESCRIPTOR_HANDLE* sourceHandles, const D3D12_CPU_DESCRIPTOR_HANDLE* destinationHandles,
			D3D12_DESCRIPTOR_HEAP_TYPE descriptorHeapType) noexcept;

		[[nodiscard("Pure function")]]
		Platform::Windows::ComPtr<ID3D12RootSignature> CreateRootSignature(const D3D12_ROOT_SIGNATURE_DESC1& rootSigDesc);
		[[nodiscard("Pure function")]]
		Platform::Windows::ComPtr<ID3D12PipelineState> CreatePipelineState(const D3D12_PIPELINE_STATE_STREAM_DESC& pipelineStateStream);

		[[nodiscard("Pure function")]]
		Platform::Windows::ComPtr<ID3D12CommandAllocator> CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE commandListType);
		[[nodiscard("Pure function")]]
		Platform::Windows::ComPtr<ID3D12GraphicsCommandList10> CreateCommandList(D3D12_COMMAND_LIST_TYPE commandListType);

		[[nodiscard("Pure function")]]
		Platform::Windows::ComPtr<ID3D12Fence1> CreateFence();

		void SetName(std::string_view name);

		Device& operator =(const Device&) = delete;
		Device& operator =(Device&&) = delete;

	private:
		IRenderDeviceContext* renderDevice;

#ifndef NDEBUG
		Platform::Windows::ComPtr<ID3D12Debug6> debug; ///< Debug interface.
#endif
		Platform::Windows::ComPtr<ID3D12Device14> device; ///< Render device.
	};
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	Device::Device(IRenderDeviceContext& renderDevice) :
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

		PONY_LOG(this->renderDevice->Logger(), Log::LogType::Info, "Checking D3D12 required support...");
		auto options12 = D3D12_FEATURE_DATA_D3D12_OPTIONS12{};
		if (const HRESULT result = device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS12, &options12, sizeof(options12)); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to get options12 feature support: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		if (!options12.EnhancedBarriersSupported) [[unlikely]]
		{
			throw std::runtime_error("D3D12 enhanced barriers aren't supported");
		}
		if (!options12.RelaxedFormatCastingSupported) [[unlikely]]
		{
			throw std::runtime_error("D3D12 relaxed format casting isn't supported");
		}
		auto options13 = D3D12_FEATURE_DATA_D3D12_OPTIONS13{};
		if (const HRESULT result = device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS13, &options13, sizeof(options13)); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to get options13 feature support: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		if (!options13.AlphaBlendFactorSupported) [[unlikely]]
		{
			throw std::runtime_error("D3D12 alpha blend factor isn't supported");
		}
		auto options14 = D3D12_FEATURE_DATA_D3D12_OPTIONS14{};
		if (const HRESULT result = device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS14, &options14, sizeof(options14)); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to get options14 feature support: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		if (!options14.IndependentFrontAndBackStencilRefMaskSupported) [[unlikely]]
		{
			throw std::runtime_error("D3D12 independent front and back stencil ref mask isn't supported");
		}
		auto options16 = D3D12_FEATURE_DATA_D3D12_OPTIONS16{};
		if (const HRESULT result = device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS16, &options16, sizeof(options16)); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to get options16 feature support: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		if (!options16.DynamicDepthBiasSupported) [[unlikely]]
		{
			throw std::runtime_error("D3D12 dynamic depth bias isn't supported");
		}
		auto options19 = D3D12_FEATURE_DATA_D3D12_OPTIONS19{};
		if (const HRESULT result = device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS19, &options19, sizeof(options19)); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to get options19 feature support: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		if (!options19.RasterizerDesc2Supported) [[unlikely]]
		{
			throw std::runtime_error("D3D12 rasterizer desc 2 isn't supported");
		}
		if (!options19.NarrowQuadrilateralLinesSupported) [[unlikely]]
		{
			throw std::runtime_error("D3D12 narrow quadrilateral lines aren't supported");
		}
		PONY_LOG(this->renderDevice->Logger(), Log::LogType::Info, "Checking D3D12 required support done.");
	}

	Device::~Device() noexcept
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

	D3D_SHADER_MODEL Device::GetShaderModel() const
	{
		auto shaderModel = D3D12_FEATURE_DATA_SHADER_MODEL{.HighestShaderModel = D3D_SHADER_MODEL_6_9};
		if (const HRESULT result = device->CheckFeatureSupport(D3D12_FEATURE_SHADER_MODEL, &shaderModel, sizeof(shaderModel)); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to check shader model support: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		return shaderModel.HighestShaderModel;
	}

	D3D12_FEATURE_DATA_FORMAT_SUPPORT Device::GetFormatSupport(const DXGI_FORMAT format) const
	{
		auto formatSupport = D3D12_FEATURE_DATA_FORMAT_SUPPORT{.Format = format};
		if (const HRESULT result = device->CheckFeatureSupport(D3D12_FEATURE_FORMAT_SUPPORT, &formatSupport, sizeof(formatSupport)); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to check texture format support: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		return formatSupport;
	}

	UINT8 Device::GetPlaneCount(const DXGI_FORMAT format) const
	{
		auto formatInfo = D3D12_FEATURE_DATA_FORMAT_INFO{.Format = format};
		if (const HRESULT result = device->CheckFeatureSupport(D3D12_FEATURE_FORMAT_INFO, &formatInfo, sizeof(formatInfo)); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to check texture format info: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		return formatInfo.PlaneCount;
	}

	UINT Device::GetSampleQualityCount(const DXGI_FORMAT format, const UINT sampleCount) const
	{
		auto levels = D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS{.Format = format, .SampleCount = sampleCount, .Flags = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE};
		if (const HRESULT result = device->CheckFeatureSupport(D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS, &levels, sizeof(levels)); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to check sampling support: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		return levels.NumQualityLevels;
	}

	UINT64 Device::GetCopyableFootprints(const D3D12_RESOURCE_DESC1& resourceDesc, const UINT subresourceOffset, const UINT subresourceCount, const UINT64 baseOffset, 
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

	UINT Device::GetDescriptorHandleIncrement(const D3D12_DESCRIPTOR_HEAP_TYPE descriptorHeapType) const noexcept
	{
		return device->GetDescriptorHandleIncrementSize(descriptorHeapType);
	}

	Platform::Windows::ComPtr<ID3D12CommandQueue> Device::CreateCommandQueue(const D3D12_COMMAND_QUEUE_DESC& queueDesc, const GUID& creatorId)
	{
		Platform::Windows::ComPtr<ID3D12CommandQueue> commandQueue;
		if (const HRESULT result = this->device->CreateCommandQueue1(&queueDesc, creatorId, IID_PPV_ARGS(commandQueue.GetAddress())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to acquire D3D12 command queue: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		return commandQueue;
	}

	Platform::Windows::ComPtr<ID3D12Resource2> Device::CreateResource(const D3D12_HEAP_PROPERTIES& heapProperties, const D3D12_HEAP_FLAGS heapFlags, 
		const D3D12_RESOURCE_DESC1& resourceDesc, const D3D12_BARRIER_LAYOUT initialLayout, const D3D12_CLEAR_VALUE& clearValue,
		const std::span<const DXGI_FORMAT> castableFormats)
	{
#ifndef NDEBUG
		if (castableFormats.size() > std::numeric_limits<UINT32>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Castable format count is too great");
		}
#endif

		Platform::Windows::ComPtr<ID3D12Resource2> resource;
		if (const HRESULT result = device->CreateCommittedResource3(&heapProperties, heapFlags, &resourceDesc, initialLayout, 
			clearValue.Format != DXGI_FORMAT_UNKNOWN ? &clearValue : nullptr, nullptr, 
			static_cast<UINT32>(castableFormats.size()), castableFormats.data(), IID_PPV_ARGS(resource.GetAddress())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to create D3D12 resource: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		return resource;
	}

	Platform::Windows::ComPtr<ID3D12DescriptorHeap> Device::CreateDescriptorHeap(const D3D12_DESCRIPTOR_HEAP_DESC& descriptorHeapDesc)
	{
		Platform::Windows::ComPtr<ID3D12DescriptorHeap> descriptorHeap;
		if (const HRESULT result = device->CreateDescriptorHeap(&descriptorHeapDesc, IID_PPV_ARGS(descriptorHeap.GetAddress())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to create D3D12 descriptor heap: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		return descriptorHeap;
	}

	void Device::CreateCBV(const D3D12_CONSTANT_BUFFER_VIEW_DESC* const cbvDesc, const D3D12_CPU_DESCRIPTOR_HANDLE handle) noexcept
	{
		device->CreateConstantBufferView(cbvDesc, handle);
	}

	void Device::CreateSRV(ID3D12Resource2* const resource, const D3D12_SHADER_RESOURCE_VIEW_DESC& srvDesc, const D3D12_CPU_DESCRIPTOR_HANDLE handle) noexcept
	{
		device->CreateShaderResourceView(resource, &srvDesc, handle);
	}

	void Device::CreateUAV(ID3D12Resource2* const resource, const D3D12_UNORDERED_ACCESS_VIEW_DESC& uavDesc, const D3D12_CPU_DESCRIPTOR_HANDLE handle) noexcept
	{
		device->CreateUnorderedAccessView(resource, nullptr, &uavDesc, handle);
	}

	void Device::CreateRTV(ID3D12Resource2* const resource, const D3D12_RENDER_TARGET_VIEW_DESC& rtvDesc, const D3D12_CPU_DESCRIPTOR_HANDLE handle) noexcept
	{
		device->CreateRenderTargetView(resource, &rtvDesc, handle);
	}

	void Device::CreateDSV(ID3D12Resource2* const resource, const D3D12_DEPTH_STENCIL_VIEW_DESC& dsvDesc, const D3D12_CPU_DESCRIPTOR_HANDLE handle) noexcept
	{
		device->CreateDepthStencilView(resource, &dsvDesc, handle);
	}

	void Device::CreateSampler(const D3D12_SAMPLER_DESC2& samplerDesc, const D3D12_CPU_DESCRIPTOR_HANDLE handle) noexcept
	{
		device->CreateSampler2(&samplerDesc, handle);
	}

	void Device::CopyDescriptors(const UINT rangeCount, const UINT* const rangeSizes,
		const D3D12_CPU_DESCRIPTOR_HANDLE* const sourceHandles,
		const D3D12_CPU_DESCRIPTOR_HANDLE* const destinationHandles,
		const D3D12_DESCRIPTOR_HEAP_TYPE descriptorHeapType) noexcept
	{
		device->CopyDescriptors(rangeCount, destinationHandles, rangeSizes, 
			rangeCount, sourceHandles, rangeSizes, descriptorHeapType);
	}

	Platform::Windows::ComPtr<ID3D12RootSignature> Device::CreateRootSignature(const D3D12_ROOT_SIGNATURE_DESC1& rootSigDesc)
	{
		const auto versionedDesc = D3D12_VERSIONED_ROOT_SIGNATURE_DESC
		{
			.Version = D3D_ROOT_SIGNATURE_VERSION_1_1,
			.Desc_1_1 = rootSigDesc,
		};

		Platform::Windows::ComPtr<ID3DBlob> successBlob;
		Platform::Windows::ComPtr<ID3DBlob> errorBlob;
		if (const HRESULT result = D3D12SerializeVersionedRootSignature(&versionedDesc, successBlob.GetAddress(), errorBlob.GetAddress()); FAILED(result)) [[unlikely]]
		{
			if (errorBlob && errorBlob->GetBufferSize() > 0)
			{
				throw std::runtime_error(std::format("Failed to serialize D3D12 root signature: Result = '0x{:X}', Message = '{}'", 
					static_cast<std::make_unsigned_t<HRESULT>>(result), static_cast<const char*>(errorBlob->GetBufferPointer())));
			}

			throw std::runtime_error(std::format("Failed to serialize D3D12 root signature: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		Platform::Windows::ComPtr<ID3D12RootSignature> rootSignature;
		if (const HRESULT result = device->CreateRootSignature(0u, successBlob->GetBufferPointer(), successBlob->GetBufferSize(), 
			IID_PPV_ARGS(rootSignature.GetAddress())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to create D3D12 root signature: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		return rootSignature;
	}

	Platform::Windows::ComPtr<ID3D12PipelineState> Device::CreatePipelineState(const D3D12_PIPELINE_STATE_STREAM_DESC& pipelineStateStream)
	{
		Platform::Windows::ComPtr<ID3D12PipelineState> pipelineState;
		if (const HRESULT result = device->CreatePipelineState(&pipelineStateStream, IID_PPV_ARGS(pipelineState.GetAddress())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to create D3D12 pipeline state: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		return pipelineState;
	}

	Platform::Windows::ComPtr<ID3D12CommandAllocator> Device::CreateCommandAllocator(const D3D12_COMMAND_LIST_TYPE commandListType)
	{
		Platform::Windows::ComPtr<ID3D12CommandAllocator> allocator;
		if (const HRESULT result = device->CreateCommandAllocator(commandListType, IID_PPV_ARGS(allocator.GetAddress())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to create D3D12 command allocator: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		return allocator;
	}

	Platform::Windows::ComPtr<ID3D12GraphicsCommandList10> Device::CreateCommandList(const D3D12_COMMAND_LIST_TYPE commandListType)
	{
		Platform::Windows::ComPtr<ID3D12GraphicsCommandList10> commandList;
		if (const HRESULT result = device->CreateCommandList1(0u, commandListType, D3D12_COMMAND_LIST_FLAG_NONE, IID_PPV_ARGS(commandList.GetAddress())); 
			FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to create D3D12 graphics command list: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		return commandList;
	}

	Platform::Windows::ComPtr<ID3D12Fence1> Device::CreateFence()
	{
		Platform::Windows::ComPtr<ID3D12Fence1> fence;
		if (const HRESULT result = device->CreateFence(0ull, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(fence.GetAddress())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to create D3D12 fence: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		return fence;
	}

	void Device::SetName(const std::string_view name)
	{
		SetObjectName(*device, name);
	}
}
