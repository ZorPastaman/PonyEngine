/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

#include "PonyEngine/Log/Log.h"

#include "PonyEngine/RenderDevice/Windows/D3D12Framework.h"
#include "PonyEngine/RenderDevice/Windows/DXGIFramework.h"

export module PonyEngine.RenderDevice.D3D12.Impl.Windows:D3D12Engine;

import std;

import PonyEngine.Log;
import PonyEngine.Memory;
import PonyEngine.Meta;
import PonyEngine.RenderDevice.Ext;
import PonyEngine.Surface.Windows;
import PonyEngine.Type;

import :DXGIFactory;
import :DXGISwapChain;
import :DXGISwapChainUtility;
import :D3D12Buffer;
import :D3D12BufferUtility;
import :D3D12CommandQueue;
import :D3D12ComputeCommandList;
import :D3D12CopyCommandList;
import :D3D12DescriptorHeapUtility;
import :D3D12Device;
import :D3D12Fence;
import :D3D12FormatUtility;
import :D3D12GraphicsCommandList;
import :D3D12HeapUtility;
import :D3D12ShaderDataContainer;
import :D3D12SwapChain;
import :D3D12Texture;
import :D3D12TextureFormatMap;
import :D3D12TextureUtility;
import :D3D12Waiter;

export namespace PonyEngine::RenderDevice::Windows
{
	class D3D12Engine final
	{
	public:
		static constexpr std::string_view ApiName = D3D12Device::ApiName;
		static constexpr auto ApiVersion = D3D12Device::ApiVersion;

		static constexpr std::uint32_t CBVAlignment = D3D12_CONSTANT_BUFFER_DATA_PLACEMENT_ALIGNMENT;

		[[nodiscard("Pure constructor")]]
		explicit D3D12Engine(IRenderDeviceContext& renderDevice);
		D3D12Engine(const D3D12Engine&) = delete;
		D3D12Engine(D3D12Engine&&) = delete;

		~D3D12Engine() noexcept = default;

		[[nodiscard("Pure function")]]
		static HeapTypeMask BufferHeapTypeSupport() noexcept;
		[[nodiscard("Pure function")]]
		std::shared_ptr<IBuffer> CreateBuffer(HeapType heapType, const BufferParams& params);

		[[nodiscard("Pure function")]]
		struct TextureFormatSupport TextureFormatSupport(TextureFormatId textureFormatId) const;
		[[nodiscard("Pure function")]]
		TextureSupportResponse TextureSupport(const TextureSupportRequest& request) const;
		[[nodiscard("Pure function")]]
		static HeapTypeMask TextureHeapTypeSupport() noexcept;
		[[nodiscard("Pure function")]]
		std::shared_ptr<ITexture> CreateTexture(HeapType heapType, const TextureParams& params);

		[[nodiscard("Pure function")]]
		std::uint32_t GetCopyableFootprintCount(const TextureParams& params, const SubTextureRange& range) const;
		[[nodiscard("Pure function")]]
		std::uint32_t GetCopyableFootprintCount(const ITexture& texture, const SubTextureRange& range) const;
		CopyableFootprintSize GetCopyableFootprints(const TextureParams& params, std::uint64_t offset, const SubTextureRange& range,
			std::span<CopyableFootprint> footprints) const;
		CopyableFootprintSize GetCopyableFootprints(const ITexture& texture, std::uint64_t offset, const SubTextureRange& range,
			std::span<CopyableFootprint> footprints) const;

		[[nodiscard("Pure function")]]
		std::shared_ptr<IShaderDataContainer> CreateShaderDataContainer(const ShaderDataContainerParams& params);
		void CreateView(const IBuffer& buffer, IShaderDataContainer& container, std::uint32_t index, const CBVParams& params);
		void CreateView(const IBuffer& buffer, IShaderDataContainer& container, std::uint32_t index, const BufferSRVParams& params);
		void CreateView(const ITexture& texture, IShaderDataContainer& container, std::uint32_t index, const Texture1DSRVParams& params);
		void CreateView(const ITexture& texture, IShaderDataContainer& container, std::uint32_t index, const Texture1DArraySRVParams& params);
		void CreateView(const ITexture& texture, IShaderDataContainer& container, std::uint32_t index, const Texture2DSRVParams& params);
		void CreateView(const ITexture& texture, IShaderDataContainer& container, std::uint32_t index, const Texture2DArraySRVParams& params);
		void CreateView(const ITexture& texture, IShaderDataContainer& container, std::uint32_t index, const Texture2DMSSRVParams& params);
		void CreateView(const ITexture& texture, IShaderDataContainer& container, std::uint32_t index, const Texture2DMSArraySRVParams& params);
		void CreateView(const ITexture& texture, IShaderDataContainer& container, std::uint32_t index, const Texture3DSRVParams& params);
		void CreateView(const ITexture& texture, IShaderDataContainer& container, std::uint32_t index, const TextureCubeSRVParams& params);
		void CreateView(const ITexture& texture, IShaderDataContainer& container, std::uint32_t index, const TextureCubeArraySRVParams& params);
		void EraseView(IShaderDataContainer& container, std::uint32_t index);

		[[nodiscard("Pure function")]]
		std::shared_ptr<IGraphicsCommandList> CreateGraphicsCommandList();
		[[nodiscard("Pure function")]]
		std::shared_ptr<IComputeCommandList> CreateComputeCommandList();
		[[nodiscard("Pure function")]]
		std::shared_ptr<ICopyCommandList> CreateCopyCommandList();
		void Execute(std::span<const IGraphicsCommandList* const> commandLists, const QueueSync& sync);
		void Execute(std::span<const IComputeCommandList* const> commandLists, const QueueSync& sync);
		void Execute(std::span<const ICopyCommandList* const> commandLists, const QueueSync& sync);

		[[nodiscard("Pure function")]]
		std::shared_ptr<IFence> CreateFence();
		[[nodiscard("Pure function")]]
		std::shared_ptr<IWaiter> CreateWaiter();

		[[nodiscard("Pure function")]]
		struct SwapChainSupport SwapChainSupport() const;
		[[nodiscard("Pure function")]]
		bool IsSwapChainAlive() const;
		[[nodiscard("Pure function")]]
		void CreateSwapChain(const SwapChainParams& params);
		void DestroySwapChain();
		[[nodiscard("Pure function")]]
		std::uint8_t SwapChainBufferCount() const;
		[[nodiscard("Pure function")]]
		std::uint8_t CurrentSwapChainBufferIndex() const;
		[[nodiscard("Pure function")]]
		std::shared_ptr<ITexture> SwapChainBuffer(std::uint8_t bufferIndex) const;
		void PresentNextSwapChainBuffer();

		D3D12Engine& operator =(const D3D12Engine&) = delete;
		D3D12Engine& operator =(D3D12Engine&&) = delete;

	private:
		struct CopyableFootprintInfo final
		{
			std::uint32_t mipCount;
			std::uint32_t arrayCount;
		};

		[[nodiscard("Pure function")]]
		TextureSupportResponse MakeResponse(DXGI_FORMAT format, const TextureSupportRequest& request, const D3D12_FEATURE_DATA_FORMAT_SUPPORT& formatSupport) const;
		[[nodiscard("Pure function")]]
		SampleCountMask GetSampleCountMask(DXGI_FORMAT format, const TextureSupportRequest& request, const D3D12_FEATURE_DATA_FORMAT_SUPPORT& formatSupport) const;

		[[nodiscard("Pure function")]]
		static CopyableFootprintInfo GetCopyableFootprintCount(const TextureParams& params, const SubTextureRange& range, DXGI_FORMAT format);
		[[nodiscard("Pure function")]]
		static CopyableFootprintInfo GetCopyableFootprintCount(const D3D12_RESOURCE_DESC1& resourceDesc, const SubTextureRange& range);
		[[nodiscard("Pure function")]]
		static CopyableFootprintInfo GetCopyableFootprintCount(std::uint32_t resourceMipCount, std::uint32_t resourceArrayCount, const SubTextureRange& range);
		CopyableFootprintSize GetCopyableFootprints(const D3D12_RESOURCE_DESC1& resourceDesc, const CopyableFootprintInfo& footprintCountInfo, UINT64 offset, 
			UINT16 mostDetailedMipIndex, UINT16 firstArrayIndex, Aspect aspect, std::span<CopyableFootprint> footprints) const;

		[[nodiscard("Pure function")]]
		DXGI_FORMAT GetFormat(TextureFormatId format) const;
		[[nodiscard("Pure function")]]
		static DXGI_FORMAT GetViewFormat(DXGI_FORMAT format, Aspect aspect);
		[[nodiscard("Pure function")]]
		DXGI_FORMAT GetViewFormat(TextureFormatId format, Aspect aspect) const;

		[[nodiscard("Pure function")]]
		static D3D12Buffer& ToNativeBuffer(IBuffer& buffer);
		[[nodiscard("Pure function")]]
		static const D3D12Buffer& ToNativeBuffer(const IBuffer& buffer);
		[[nodiscard("Pure function")]]
		static D3D12Texture& ToNativeTexture(ITexture& texture);
		[[nodiscard("Pure function")]]
		static const D3D12Texture& ToNativeTexture(const ITexture& texture);

		[[nodiscard("Pure function")]]
		static D3D12ShaderDataContainer& ToNativeContainer(IShaderDataContainer& container);
		[[nodiscard("Pure function")]]
		static const D3D12ShaderDataContainer& ToNativeContainer(const IShaderDataContainer& container);

		template<typename T> [[nodiscard("Pure function")]]
		std::shared_ptr<T> CreateCommandList(D3D12_COMMAND_LIST_TYPE type);
		template<typename CommandList, typename CommandListInterface>
		void Execute(std::span<const CommandListInterface* const> commandLists, const QueueSync& sync, D3D12CommandQueue& commandQueue);
		template<typename CommandList, typename CommandListInterface>
		static void GetCommandLists(std::span<const CommandListInterface* const> commandLists, std::span<ID3D12CommandList*> lists) noexcept;
		static void GetFences(std::span<const FenceValue> input, std::span<std::pair<ID3D12Fence*, UINT64>> output) noexcept;

		[[nodiscard("Pure function")]]
		static D3D12_COMMAND_QUEUE_DESC GetCommandQueueDesc(D3D12_COMMAND_LIST_TYPE type) noexcept;

		[[nodiscard("Pure function")]]
		D3D12SwapChain& GetSwapChain() const;

		static void ValidateSize(const BufferParams& params);
		static void ValidateDimension(const TextureParams& params);
		static void ValidateColorTexture(const TextureParams& params);
		static void ValidateDepthTexture(const TextureParams& params);
		static void ValidateAspect(Aspect aspect, DXGI_FORMAT format);
		static void ValidateCBVParams(const D3D12Buffer& buffer, const CBVParams& params);
		static void ValidateSRVParams(const D3D12Buffer& buffer, const BufferSRVParams& params);
		static void ValidateSRVParams(const D3D12Texture& texture, const TextureSRVParams& params);
		static void ValidateSRVParams(const D3D12Texture& texture, const Texture1DSRVParams& params);
		static void ValidateSRVParams(const D3D12Texture& texture, const Texture1DArraySRVParams& params);
		static void ValidateSRVParams(const D3D12Texture& texture, const Texture2DSRVParams& params);
		static void ValidateSRVParams(const D3D12Texture& texture, const Texture2DArraySRVParams& params);
		static void ValidateSRVParams(const D3D12Texture& texture, const Texture2DMSSRVParams& params);
		static void ValidateSRVParams(const D3D12Texture& texture, const Texture2DMSArraySRVParams& params);
		static void ValidateSRVParams(const D3D12Texture& texture, const Texture3DSRVParams& params);
		static void ValidateSRVParams(const D3D12Texture& texture, const TextureCubeSRVParams& params);
		static void ValidateSRVParams(const D3D12Texture& texture, const TextureCubeArraySRVParams& params);
		static void ValidateDimension(const D3D12Texture& texture, TextureDimension dimension);
		static void ValidateMipRange(const D3D12Texture& texture, const MipRange& range);
		static void ValidateArrayRange(const D3D12Texture& texture, const ArrayRange& range);
		static void ValidateSampleCount(const D3D12Texture& texture, bool shouldBeMS);
		static void ValidateSwapChainParams(const SwapChainParams& params);

		template<typename Container>
		static void ValidateContainer(const Container& container, std::uint32_t index);
		template<typename CommandList, typename CommandListInterface>
		static void ValidateCommandLists(std::span<const CommandListInterface* const> commandLists);
		static void ValidateFences(std::span<const FenceValue> fences);

		// {132D4628-84F4-40F4-B72F-8A7B08C3C566}
		static constexpr GUID CreatorId = { 0x132d4628, 0x84f4, 0x40f4, { 0xb7, 0x2f, 0x8a, 0x7b, 0x8, 0xc3, 0xc5, 0x66 } };

		IRenderDeviceContext* renderDevice;

		mutable Memory::Arena arena;

		D3D12TextureFormatMap textureFormatMap;

		DXGIFactory factory;
		D3D12Device device;

		D3D12CommandQueue graphicsCommandQueue;
		D3D12CommandQueue computeCommandQueue;
		D3D12CommandQueue copyCommandQueue;

		std::unique_ptr<D3D12SwapChain> swapChain;
	};
}

namespace PonyEngine::RenderDevice::Windows
{
	D3D12Engine::D3D12Engine(IRenderDeviceContext& renderDevice) :
		renderDevice{&renderDevice},
		arena(0uz, 256uz),
		textureFormatMap(*this->renderDevice),
		factory(*this->renderDevice),
		device(*this->renderDevice),
		graphicsCommandQueue(this->device.CreateCommandQueue(GetCommandQueueDesc(D3D12_COMMAND_LIST_TYPE_DIRECT), CreatorId)),
		computeCommandQueue(this->device.CreateCommandQueue(GetCommandQueueDesc(D3D12_COMMAND_LIST_TYPE_COMPUTE), CreatorId)),
		copyCommandQueue(this->device.CreateCommandQueue(GetCommandQueueDesc(D3D12_COMMAND_LIST_TYPE_COPY), CreatorId))
	{
	}

	HeapTypeMask D3D12Engine::BufferHeapTypeSupport() noexcept
	{
		return HeapTypeMask::Default | HeapTypeMask::Upload | HeapTypeMask::Download;
	}

	std::shared_ptr<IBuffer> D3D12Engine::CreateBuffer(const HeapType heapType, const BufferParams& params)
	{
		ValidateSize(params);

		const D3D12_HEAP_PROPERTIES heapProperties = ToHeapProperties(heapType);
		const D3D12_HEAP_FLAGS heapFlags = ToHeapFlags(params.usage);
		const D3D12_RESOURCE_DESC1 resourceDesc = ToResourceDesc(params);
		Platform::Windows::ComPtr<ID3D12Resource2> resource = device.CreateResource(heapProperties, heapFlags, resourceDesc);

		return std::make_shared<D3D12Buffer>(std::move(resource), static_cast<std::uint64_t>(resourceDesc.Width), params.usage);
	}

	struct TextureFormatSupport D3D12Engine::TextureFormatSupport(const TextureFormatId textureFormatId) const
	{
		if (const std::size_t index = textureFormatMap.IndexOf(textureFormatId); index < textureFormatMap.Size())
		{
			const DXGI_FORMAT format = textureFormatMap.DXGIFormat(index);

			auto support = RenderDevice::TextureFormatSupport{.supported = true};
			support.features = ToTextureFormatFeature(device.GetFormatSupport(format));
			support.aspects = GetAspects(format);

			return support;
		}

		return RenderDevice::TextureFormatSupport{};
	}

	TextureSupportResponse D3D12Engine::TextureSupport(const TextureSupportRequest& request) const
	{
		if (const std::size_t index = textureFormatMap.IndexOf(request.format); index < textureFormatMap.Size())
		{
			const DXGI_FORMAT format = textureFormatMap.DXGIFormat(index);
			const D3D12_FEATURE_DATA_FORMAT_SUPPORT formatSupport = device.GetFormatSupport(format);

			if (IsDepthStencilFormat(format))
			{
				if (!CheckDepthSupport(request, formatSupport))
				{
					return TextureSupportResponse{};
				}
			}
			else
			{
				if (!CheckColorSupport(request, formatSupport))
				{
					return TextureSupportResponse{};
				}
			}

			return MakeResponse(format, request, formatSupport);
		}

		return TextureSupportResponse{};
	}

	HeapTypeMask D3D12Engine::TextureHeapTypeSupport() noexcept
	{
		return HeapTypeMask::Default;
	}

	std::shared_ptr<ITexture> D3D12Engine::CreateTexture(const HeapType heapType, const TextureParams& params)
	{
		ValidateDimension(params);
		DXGI_FORMAT format = GetFormat(params.format);
		const bool srgb = Any(TextureFlag::SRGB, params.flags);

		arena.Free();
		auto castableFormats = Memory::Arena::Slice<DXGI_FORMAT>{};
		if (IsDepthStencilFormat(format))
		{
			ValidateDepthTexture(params);

			if (Any(TextureUsage::ShaderResource, params.usage))
			{
				if (GetStencilViewFormat(format) == DXGI_FORMAT_UNKNOWN)
				{
					castableFormats = arena.Allocate<DXGI_FORMAT>(1uz);
					const std::span<DXGI_FORMAT> formats = arena.Span(castableFormats);
					formats[0] = GetDepthViewFormat(format);
				}
				else
				{
					format = GetTypelessFormat(format);
				}
			}
		}
		else
		{
			ValidateColorTexture(params);

			castableFormats = arena.Allocate<DXGI_FORMAT>(params.castableFormats.size() + srgb);
			const std::span<DXGI_FORMAT> formats = arena.Span(castableFormats);
			for (std::size_t i = 0uz; i < params.castableFormats.size(); ++i)
			{
				formats[i] = GetFormat(params.castableFormats[i]);
			}

			if (srgb)
			{
				const DXGI_FORMAT srgbFormat = GetSRGBFormat(format);
				if (srgbFormat == DXGI_FORMAT_UNKNOWN) [[unlikely]]
				{
					throw std::invalid_argument("Invalid srgb flag");
				}
				formats[formats.size() - 1] = srgbFormat;
			}
		}

		const D3D12_HEAP_PROPERTIES heapProperties = ToHeapProperties(heapType);
		const D3D12_HEAP_FLAGS heapFlags = ToHeapFlags(params.usage);
		const D3D12_RESOURCE_DESC1 resourceDesc = ToResourceDesc(params, format);
		const D3D12_BARRIER_LAYOUT initialLayout = ToLayout(params.initialLayout);
		const D3D12_CLEAR_VALUE clearValue = ToClearValue(params.clearValue, format);
		Platform::Windows::ComPtr<ID3D12Resource2> resource = device.CreateResource(heapProperties, heapFlags,
			resourceDesc, initialLayout, clearValue, arena.Span(castableFormats));

		return std::make_shared<D3D12Texture>(std::move(resource), params.format, format, params.castableFormats, 
			static_cast<std::uint32_t>(resourceDesc.Width), static_cast<std::uint32_t>(resourceDesc.Height), static_cast<std::uint16_t>(resourceDesc.DepthOrArraySize),
			static_cast<std::uint16_t>(resourceDesc.MipLevels), params.dimension, params.sampleCount, params.usage, srgb);
	}

	std::uint32_t D3D12Engine::GetCopyableFootprintCount(const TextureParams& params, const SubTextureRange& range) const
	{
		const auto [mipCount, arrayCount] = GetCopyableFootprintCount(params, range, GetFormat(params.format));
		return mipCount * arrayCount;
	}

	std::uint32_t D3D12Engine::GetCopyableFootprintCount(const ITexture& texture, const SubTextureRange& range) const
	{
		const D3D12_RESOURCE_DESC1 resourceDesc = ToNativeTexture(texture).Resource().GetDesc1();
		const auto [mipCount, arrayCount] = GetCopyableFootprintCount(resourceDesc, range);
		return mipCount * arrayCount;
	}

	CopyableFootprintSize D3D12Engine::GetCopyableFootprints(const TextureParams& params, const std::uint64_t offset, const SubTextureRange& range,
		const std::span<CopyableFootprint> footprints) const
	{
		const DXGI_FORMAT format = GetFormat(params.format);
		const CopyableFootprintInfo footprintCount = GetCopyableFootprintCount(params, range, format);
		const D3D12_RESOURCE_DESC1 resourceDesc = ToResourceDesc(params, format);
		return GetCopyableFootprints(resourceDesc, footprintCount, static_cast<UINT64>(offset), 
			static_cast<UINT16>(range.mipRange.mostDetailedMipIndex), static_cast<UINT16>(range.arrayRange.firstArrayIndex), range.aspect, footprints);
	}

	CopyableFootprintSize D3D12Engine::GetCopyableFootprints(const ITexture& texture, const std::uint64_t offset, const SubTextureRange& range,
		const std::span<CopyableFootprint> footprints) const
	{
		const D3D12_RESOURCE_DESC1 resourceDesc = ToNativeTexture(texture).Resource().GetDesc1();
		const CopyableFootprintInfo footprintCount = GetCopyableFootprintCount(resourceDesc, range);
		return GetCopyableFootprints(resourceDesc, footprintCount, static_cast<UINT64>(offset), 
			static_cast<UINT16>(range.mipRange.mostDetailedMipIndex), static_cast<UINT16>(range.arrayRange.firstArrayIndex), range.aspect, footprints);
	}

	std::shared_ptr<IShaderDataContainer> D3D12Engine::CreateShaderDataContainer(const ShaderDataContainerParams& params)
	{
		const D3D12_DESCRIPTOR_HEAP_DESC descriptorHeapDesc = ToDescriptorHeapDesc(params);		
		return std::make_shared<D3D12ShaderDataContainer>(device.CreateDescriptorHeap(descriptorHeapDesc), device.GetDescriptorHandleIncrement(descriptorHeapDesc.Type),
			params.size, params.shaderVisible);
	}

	void D3D12Engine::CreateView(const IBuffer& buffer, IShaderDataContainer& container, const std::uint32_t index, const CBVParams& params)
	{
		const D3D12Buffer& nativeBuffer = ToNativeBuffer(buffer);
		ValidateCBVParams(nativeBuffer, params);

		D3D12ShaderDataContainer& nativeContainer = ToNativeContainer(container);
		ValidateContainer(nativeContainer, index);

		const D3D12_GPU_VIRTUAL_ADDRESS address = nativeBuffer.Resource().GetGPUVirtualAddress();
		const D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = ToCBVDesc(address, params);
		device.CreateCBV(cbvDesc, nativeContainer.CpuHandle(static_cast<UINT>(index)));

		nativeContainer.Set(index, BufferCBVMeta{.resource = &nativeBuffer, .params = params});
	}

	void D3D12Engine::CreateView(const IBuffer& buffer, IShaderDataContainer& container, const std::uint32_t index, const BufferSRVParams& params)
	{
		const D3D12Buffer& nativeBuffer = ToNativeBuffer(buffer);
		ValidateSRVParams(nativeBuffer, params);

		D3D12ShaderDataContainer& nativeContainer = ToNativeContainer(container);
		ValidateContainer(nativeContainer, index);

		const D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = ToSRVDesc(params);
		device.CreateSRV(nativeBuffer.Resource(), srvDesc, nativeContainer.CpuHandle(static_cast<UINT>(index)));

		nativeContainer.Set(index, BufferSRVMeta{.resource = &nativeBuffer, .params = params});
	}

	void D3D12Engine::CreateView(const ITexture& texture, IShaderDataContainer& container, const std::uint32_t index, const Texture1DSRVParams& params)
	{
		const D3D12Texture& nativeTexture = ToNativeTexture(texture);
		ValidateSRVParams(nativeTexture, params);

		D3D12ShaderDataContainer& nativeContainer = ToNativeContainer(container);
		ValidateContainer(nativeContainer, index);

		const DXGI_FORMAT viewFormat = GetViewFormat(params.format, params.aspect);
		const D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = ToSRVDesc(params, viewFormat, nativeTexture.MipCount());
		device.CreateSRV(nativeTexture.Resource(), srvDesc, nativeContainer.CpuHandle(static_cast<UINT>(index)));

		nativeContainer.Set(index, Texture1DSRVMeta{.resource = &nativeTexture, .params = params});
	}

	void D3D12Engine::CreateView(const ITexture& texture, IShaderDataContainer& container, const std::uint32_t index, const Texture1DArraySRVParams& params)
	{
		const D3D12Texture& nativeTexture = ToNativeTexture(texture);
		ValidateSRVParams(nativeTexture, params);

		D3D12ShaderDataContainer& nativeContainer = ToNativeContainer(container);
		ValidateContainer(nativeContainer, index);

		const DXGI_FORMAT viewFormat = GetViewFormat(params.format, params.aspect);
		const D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = ToSRVDesc(params, viewFormat, nativeTexture.MipCount(), nativeTexture.ArraySize());
		device.CreateSRV(nativeTexture.Resource(), srvDesc, nativeContainer.CpuHandle(static_cast<UINT>(index)));

		nativeContainer.Set(index, Texture1DArraySRVMeta{.resource = &nativeTexture, .params = params});
	}

	void D3D12Engine::CreateView(const ITexture& texture, IShaderDataContainer& container, const std::uint32_t index, const Texture2DSRVParams& params)
	{
		const D3D12Texture& nativeTexture = ToNativeTexture(texture);
		ValidateSRVParams(nativeTexture, params);

		D3D12ShaderDataContainer& nativeContainer = ToNativeContainer(container);
		ValidateContainer(nativeContainer, index);

		const DXGI_FORMAT viewFormat = GetViewFormat(params.format, params.aspect);
		const D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = ToSRVDesc(params, viewFormat, nativeTexture.MipCount());
		device.CreateSRV(nativeTexture.Resource(), srvDesc, nativeContainer.CpuHandle(static_cast<UINT>(index)));

		nativeContainer.Set(index, Texture2DSRVMeta{.resource = &nativeTexture, .params = params});
	}

	void D3D12Engine::CreateView(const ITexture& texture, IShaderDataContainer& container, const std::uint32_t index, const Texture2DArraySRVParams& params)
	{
		const D3D12Texture& nativeTexture = ToNativeTexture(texture);
		ValidateSRVParams(nativeTexture, params);

		D3D12ShaderDataContainer& nativeContainer = ToNativeContainer(container);
		ValidateContainer(nativeContainer, index);

		const DXGI_FORMAT viewFormat = GetViewFormat(params.format, params.aspect);
		const D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = ToSRVDesc(params, viewFormat, nativeTexture.MipCount(), nativeTexture.ArraySize());
		device.CreateSRV(nativeTexture.Resource(), srvDesc, nativeContainer.CpuHandle(static_cast<UINT>(index)));

		nativeContainer.Set(index, Texture2DArraySRVMeta{.resource = &nativeTexture, .params = params});
	}

	void D3D12Engine::CreateView(const ITexture& texture, IShaderDataContainer& container, const std::uint32_t index, const Texture2DMSSRVParams& params)
	{
		const D3D12Texture& nativeTexture = ToNativeTexture(texture);
		ValidateSRVParams(nativeTexture, params);

		D3D12ShaderDataContainer& nativeContainer = ToNativeContainer(container);
		ValidateContainer(nativeContainer, index);

		const DXGI_FORMAT viewFormat = GetViewFormat(params.format, params.aspect);
		const D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = ToSRVDesc(params, viewFormat);
		device.CreateSRV(nativeTexture.Resource(), srvDesc, nativeContainer.CpuHandle(static_cast<UINT>(index)));

		nativeContainer.Set(index, Texture2DMSSRVMeta{.resource = &nativeTexture, .params = params});
	}

	void D3D12Engine::CreateView(const ITexture& texture, IShaderDataContainer& container, const std::uint32_t index, const Texture2DMSArraySRVParams& params)
	{
		const D3D12Texture& nativeTexture = ToNativeTexture(texture);
		ValidateSRVParams(nativeTexture, params);

		D3D12ShaderDataContainer& nativeContainer = ToNativeContainer(container);
		ValidateContainer(nativeContainer, index);

		const DXGI_FORMAT viewFormat = GetViewFormat(params.format, params.aspect);
		const D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = ToSRVDesc(params, viewFormat, texture.ArraySize());
		device.CreateSRV(nativeTexture.Resource(), srvDesc, nativeContainer.CpuHandle(static_cast<UINT>(index)));

		nativeContainer.Set(index, Texture2DMSArraySRVMeta{.resource = &nativeTexture, .params = params});
	}

	void D3D12Engine::CreateView(const ITexture& texture, IShaderDataContainer& container, const std::uint32_t index, const Texture3DSRVParams& params)
	{
		const D3D12Texture& nativeTexture = ToNativeTexture(texture);
		ValidateSRVParams(nativeTexture, params);

		D3D12ShaderDataContainer& nativeContainer = ToNativeContainer(container);
		ValidateContainer(nativeContainer, index);

		const DXGI_FORMAT viewFormat = GetViewFormat(params.format, params.aspect);
		const D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = ToSRVDesc(params, viewFormat, nativeTexture.MipCount());
		device.CreateSRV(nativeTexture.Resource(), srvDesc, nativeContainer.CpuHandle(static_cast<UINT>(index)));

		nativeContainer.Set(index, Texture3DSRVMeta{.resource = &nativeTexture, .params = params});
	}

	void D3D12Engine::CreateView(const ITexture& texture, IShaderDataContainer& container, const std::uint32_t index, const TextureCubeSRVParams& params)
	{
		const D3D12Texture& nativeTexture = ToNativeTexture(texture);
		ValidateSRVParams(nativeTexture, params);

		D3D12ShaderDataContainer& nativeContainer = ToNativeContainer(container);
		ValidateContainer(nativeContainer, index);

		const DXGI_FORMAT viewFormat = GetViewFormat(params.format, params.aspect);
		const D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = ToSRVDesc(params, viewFormat, nativeTexture.MipCount());
		device.CreateSRV(nativeTexture.Resource(), srvDesc, nativeContainer.CpuHandle(static_cast<UINT>(index)));

		nativeContainer.Set(index, TextureCubeSRVMeta{.resource = &nativeTexture, .params = params});
	}

	void D3D12Engine::CreateView(const ITexture& texture, IShaderDataContainer& container, const std::uint32_t index, const TextureCubeArraySRVParams& params)
	{
		const D3D12Texture& nativeTexture = ToNativeTexture(texture);
		ValidateSRVParams(nativeTexture, params);

		D3D12ShaderDataContainer& nativeContainer = ToNativeContainer(container);
		ValidateContainer(nativeContainer, index);

		const DXGI_FORMAT viewFormat = GetViewFormat(params.format, params.aspect);
		const D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = ToSRVDesc(params, viewFormat, nativeTexture.MipCount(), nativeTexture.ArraySize());
		device.CreateSRV(nativeTexture.Resource(), srvDesc, nativeContainer.CpuHandle(static_cast<UINT>(index)));

		nativeContainer.Set(index, TextureCubeArraySRVMeta{.resource = &nativeTexture, .params = params});
	}

	void D3D12Engine::EraseView(IShaderDataContainer& container, const std::uint32_t index)
	{
		D3D12ShaderDataContainer& nativeContainer = ToNativeContainer(container);
		ValidateContainer(nativeContainer, index);
		nativeContainer.Set(index, EmptyShaderDataMeta{});
	}

	std::shared_ptr<IGraphicsCommandList> D3D12Engine::CreateGraphicsCommandList()
	{
		return CreateCommandList<D3D12GraphicsCommandList>(D3D12_COMMAND_LIST_TYPE_DIRECT);
	}

	std::shared_ptr<IComputeCommandList> D3D12Engine::CreateComputeCommandList()
	{
		return CreateCommandList<D3D12ComputeCommandList>(D3D12_COMMAND_LIST_TYPE_COMPUTE);
	}

	std::shared_ptr<ICopyCommandList> D3D12Engine::CreateCopyCommandList()
	{
		return CreateCommandList<D3D12CopyCommandList>(D3D12_COMMAND_LIST_TYPE_COPY);
	}

	void D3D12Engine::Execute(const std::span<const IGraphicsCommandList* const> commandLists, const QueueSync& sync)
	{
		Execute<D3D12GraphicsCommandList>(commandLists, sync, graphicsCommandQueue);
	}

	void D3D12Engine::Execute(const std::span<const IComputeCommandList* const> commandLists, const QueueSync& sync)
	{
		Execute<D3D12ComputeCommandList>(commandLists, sync, computeCommandQueue);
	}

	void D3D12Engine::Execute(const std::span<const ICopyCommandList* const> commandLists, const QueueSync& sync)
	{
		Execute<D3D12CopyCommandList>(commandLists, sync, copyCommandQueue);
	}

	std::shared_ptr<IFence> D3D12Engine::CreateFence()
	{
		return std::make_shared<D3D12Fence>(device.CreateFence());
	}

	std::shared_ptr<IWaiter> D3D12Engine::CreateWaiter()
	{
		return std::make_shared<D3D12Waiter>(*renderDevice);
	}

	struct SwapChainSupport D3D12Engine::SwapChainSupport() const
	{
		const BOOL isTearingSupported = factory.GetTearingSupport();

		static_assert(D3D12_REQ_TEXTURE2D_U_OR_V_DIMENSION <= std::numeric_limits<std::uint32_t>::max(), "D3D12_REQ_TEXTURE2D_U_OR_V_DIMENSION is too great for uint32.");
		static_assert(DXGI_MAX_SWAP_CHAIN_BUFFERS <= std::numeric_limits<std::uint8_t>::max(), "DXGI_MAX_SWAP_CHAIN_BUFFERS is too great for uint8.");

		return RenderDevice::SwapChainSupport
		{
			.maxSize = Math::Vector2<std::uint32_t>(D3D12_REQ_TEXTURE2D_U_OR_V_DIMENSION, D3D12_REQ_TEXTURE2D_U_OR_V_DIMENSION),
			.minBufferCount = 2u,
			.maxBufferCount = DXGI_MAX_SWAP_CHAIN_BUFFERS,
			.alphaModes = SwapChainAlphaModeMask::Ignore | SwapChainAlphaModeMask::Straight | SwapChainAlphaModeMask::Premultiplied,
			.scalingModes = SwapChainScalingMask::NoScaling | SwapChainScalingMask::Stretch | SwapChainScalingMask::StretchAspectRatio,
			.swapEffects = SwapChainEffectMask::FlipDiscard | SwapChainEffectMask::FlipSequential,
			.syncModes = SwapChainSyncMask::FastSync | SwapChainSyncMask::FullSync | (isTearingSupported ? SwapChainSyncMask::NoSync : SwapChainSyncMask::None),
			.usage = TextureUsage::ShaderResource | TextureUsage::RenderTarget | TextureUsage::UnorderedAccess
		};
	}

	bool D3D12Engine::IsSwapChainAlive() const
	{
		return static_cast<bool>(swapChain);
	}

	void D3D12Engine::CreateSwapChain(const SwapChainParams& params)
	{
		if (swapChain) [[unlikely]]
		{
			throw std::logic_error("Swap chain is alive");
		}

		ValidateSwapChainParams(params);

		const DXGI_FORMAT format = GetFormat(params.format);
		const bool srgb = Any(SwapChainFlag::SRGB, params.flags);
		if (srgb && !IsSRGBCompatibleFormat(format)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid srgb flag");
		}

		const HWND windowHandle = renderDevice->Application().GetService<Surface::Windows::ISurfaceService>().Handle();
		const DXGI_SWAP_CHAIN_DESC1 swapChainDesc = ToSwapChainDesc(params, format);

		auto dxgiSwapChain = DXGISwapChain(factory.CreateSwapChain(graphicsCommandQueue.CommandQueue(), windowHandle, swapChainDesc));
		factory.MakeWindowAssociation(windowHandle);
		dxgiSwapChain.SetFullscreenState(FALSE);

		auto buffers = std::vector<std::shared_ptr<D3D12Texture>>(params.bufferCount);
		for (UINT i = 0u; i < params.bufferCount; ++i)
		{
			Platform::Windows::ComPtr<ID3D12Resource2> resource = dxgiSwapChain.GetBuffer<ID3D12Resource2>(i);
			buffers[i] = std::make_shared<D3D12Texture>(std::move(resource), params.format, format, std::span<const TextureFormatId>(),
				static_cast<std::uint32_t>(swapChainDesc.Width), static_cast<std::uint32_t>(swapChainDesc.Height), 1u, 1u,
				TextureDimension::Texture2D, SampleCount::X1, params.usage, srgb);
		}

		swapChain = std::make_unique<D3D12SwapChain>(std::move(dxgiSwapChain), std::move(buffers), ToSyncInterval(params.syncMode), ToPresentFlags(params.syncMode));
	}

	void D3D12Engine::DestroySwapChain()
	{
		swapChain.reset();
	}

	std::uint8_t D3D12Engine::SwapChainBufferCount() const
	{
		return GetSwapChain().BufferCount();
	}

	std::uint8_t D3D12Engine::CurrentSwapChainBufferIndex() const
	{
		return static_cast<std::uint8_t>(GetSwapChain().GetCurrentBufferIndex());
	}

	std::shared_ptr<ITexture> D3D12Engine::SwapChainBuffer(const std::uint8_t bufferIndex) const
	{
		return GetSwapChain().GetBuffer(bufferIndex);
	}

	void D3D12Engine::PresentNextSwapChainBuffer()
	{
		GetSwapChain().Present();
	}

	TextureSupportResponse D3D12Engine::MakeResponse(const DXGI_FORMAT format, const TextureSupportRequest& request,
		const D3D12_FEATURE_DATA_FORMAT_SUPPORT& formatSupport) const
	{
		auto response = TextureSupportResponse{.supported = true};

		static_assert(D3D12_REQ_TEXTURE1D_U_DIMENSION <= std::numeric_limits<std::uint32_t>::max(), "D3D12_REQ_TEXTURE1D_U_DIMENSION is too great for uint32.");
		static_assert(D3D12_REQ_TEXTURE2D_U_OR_V_DIMENSION <= std::numeric_limits<std::uint32_t>::max(), "D3D12_REQ_TEXTURE2D_U_OR_V_DIMENSION is too great for uint32.");
		static_assert(D3D12_REQ_TEXTURE3D_U_V_OR_W_DIMENSION <= std::numeric_limits<std::uint32_t>::max(), "D3D12_REQ_TEXTURE3D_U_V_OR_W_DIMENSION is too great for uint32.");
		static_assert(D3D12_REQ_MIP_LEVELS <= std::numeric_limits<std::uint32_t>::max(), "D3D12_REQ_MIP_LEVELS is too great for uint32.");
		static_assert(D3D12_REQ_TEXTURE1D_ARRAY_AXIS_DIMENSION <= std::numeric_limits<std::uint32_t>::max(), "D3D12_REQ_TEXTURE1D_ARRAY_AXIS_DIMENSION is too great for uint32.");
		static_assert(D3D12_REQ_TEXTURE2D_ARRAY_AXIS_DIMENSION <= std::numeric_limits<std::uint32_t>::max(), "D3D12_REQ_TEXTURE2D_ARRAY_AXIS_DIMENSION is too great for uint32.");

		switch (request.dimension)
		{
		case TextureDimension::Texture1D:
			response.maxSize = Math::Vector3<std::uint32_t>(D3D12_REQ_TEXTURE1D_U_DIMENSION, 1u, 1u);
			response.maxMipCount = D3D12_REQ_MIP_LEVELS;
			response.maxArraySize = D3D12_REQ_TEXTURE1D_ARRAY_AXIS_DIMENSION;
			response.sampleCounts = GetSampleCountMask(format, request, formatSupport);
			break;
		case TextureDimension::Texture2D:
			response.maxSize = Math::Vector3<std::uint32_t>(D3D12_REQ_TEXTURE2D_U_OR_V_DIMENSION, D3D12_REQ_TEXTURE2D_U_OR_V_DIMENSION, 1u);
			response.maxMipCount = D3D12_REQ_MIP_LEVELS;
			response.maxArraySize = D3D12_REQ_TEXTURE2D_ARRAY_AXIS_DIMENSION;
			response.sampleCounts = GetSampleCountMask(format, request, formatSupport);
			break;
		case TextureDimension::Texture3D:
			response.maxSize = Math::Vector3<std::uint32_t>(D3D12_REQ_TEXTURE3D_U_V_OR_W_DIMENSION, D3D12_REQ_TEXTURE3D_U_V_OR_W_DIMENSION, D3D12_REQ_TEXTURE3D_U_V_OR_W_DIMENSION);
			response.maxMipCount = D3D12_REQ_MIP_LEVELS;
			response.maxArraySize = 1u;
			response.sampleCounts = GetSampleCountMask(format, request, formatSupport);
			break;
		default:
			break;
		}

		return response;
	}

	SampleCountMask D3D12Engine::GetSampleCountMask(const DXGI_FORMAT format, const TextureSupportRequest& request, 
		const D3D12_FEATURE_DATA_FORMAT_SUPPORT& formatSupport) const
	{
		if (request.dimension != TextureDimension::Texture2D || Any(TextureUsage::UnorderedAccess, request.usage) || 
			(formatSupport.Support1 & D3D12_FORMAT_SUPPORT1_MULTISAMPLE_RENDERTARGET) == D3D12_FORMAT_SUPPORT1_NONE)
		{
			return SampleCountMask::X1;
		}

		static_assert(D3D12_MAX_MULTISAMPLE_SAMPLE_COUNT <= std::numeric_limits<std::uint8_t>::max(), "D3D12_MAX_MULTISAMPLE_SAMPLE_COUNT is too great for uint8.");

		auto mask = SampleCountMask::None;
		for (UINT i = 1u; i <= std::min(ToNumber(SampleCount::Max), std::uint8_t{D3D12_MAX_MULTISAMPLE_SAMPLE_COUNT}); i <<= 1u)
		{
			if (device.GetSampleQualityCount(format, i) > 0u)
			{
				mask |= static_cast<SampleCountMask>(i);
			}
		}

		return mask;
	}

	D3D12Engine::CopyableFootprintInfo D3D12Engine::GetCopyableFootprintCount(const TextureParams& params, const SubTextureRange& range, const DXGI_FORMAT format)
	{
		ValidateDimension(params);
		ValidateAspect(range.aspect, format);

		return GetCopyableFootprintCount(params.mipCount, params.arraySize, range);
	}

	D3D12Engine::CopyableFootprintInfo D3D12Engine::GetCopyableFootprintCount(const D3D12_RESOURCE_DESC1& resourceDesc, const SubTextureRange& range)
	{
		ValidateAspect(range.aspect, resourceDesc.Format);

		const UINT16 arraySize = GetArraySize(resourceDesc);
		return GetCopyableFootprintCount(static_cast<std::uint32_t>(resourceDesc.MipLevels), static_cast<std::uint32_t>(arraySize), range);
	}

	D3D12Engine::CopyableFootprintInfo D3D12Engine::GetCopyableFootprintCount(const std::uint32_t resourceMipCount, const std::uint32_t resourceArrayCount, const SubTextureRange& range)
	{
		if (range.mipRange.mostDetailedMipIndex + range.mipRange.mipCount.value_or(1u) > resourceMipCount) [[unlikely]]
		{
			throw std::invalid_argument("Invalid mip range");
		}
		const std::uint32_t mipCount = range.mipRange.mipCount.value_or(resourceMipCount - range.mipRange.mostDetailedMipIndex);

		if (range.arrayRange.firstArrayIndex + range.arrayRange.arrayCount.value_or(1u) > resourceArrayCount) [[unlikely]]
		{
			throw std::invalid_argument("Invalid array range");
		}
		const std::uint32_t arrayCount = range.arrayRange.arrayCount.value_or(resourceArrayCount - range.arrayRange.firstArrayIndex);

		if (arrayCount > 1u && (range.mipRange.mostDetailedMipIndex != 0u || mipCount != resourceMipCount))
		{
			throw std::invalid_argument("Invalid mip range: mip gaps aren't allowed");
		}

		return CopyableFootprintInfo{.mipCount = mipCount, .arrayCount = arrayCount};
	}

	CopyableFootprintSize D3D12Engine::GetCopyableFootprints(const D3D12_RESOURCE_DESC1& resourceDesc, const CopyableFootprintInfo& footprintCountInfo, const UINT64 offset, 
		const UINT16 mostDetailedMipIndex, const UINT16 firstArrayIndex, const Aspect aspect, const std::span<CopyableFootprint> footprints) const
	{
		const std::uint32_t footprintCount = footprintCountInfo.mipCount * footprintCountInfo.arrayCount;
		if (footprints.size() != 0uz && footprints.size() != footprintCount) [[unlikely]]
		{
			throw std::invalid_argument("Invalid footprints count");
		}

		arena.Free();
		const Memory::Arena::Slice<D3D12_PLACED_SUBRESOURCE_FOOTPRINT> subresourceFootprints = arena.Allocate<D3D12_PLACED_SUBRESOURCE_FOOTPRINT>(footprintCount);
		const Memory::Arena::Slice<UINT> rowCounts = arena.Allocate<UINT>(footprintCount);
		const Memory::Arena::Slice<UINT64> rowSizes = arena.Allocate<UINT64>(footprintCount);
		const std::span<D3D12_PLACED_SUBRESOURCE_FOOTPRINT> subresourceFootprintsSpan = arena.Span(subresourceFootprints);
		const std::span<UINT> rowCountsSpan = arena.Span(rowCounts);
		const std::span<UINT64> rowSizesSpan = arena.Span(rowSizes);

		const UINT8 planeIndex = static_cast<UINT8>(ToPlaneIndex(aspect));
		const UINT16 arraySize = GetArraySize(resourceDesc);
		const UINT footprintOffset = CalculateSubresource(mostDetailedMipIndex, firstArrayIndex, 
			planeIndex, resourceDesc.MipLevels, arraySize);

		const UINT64 totalSize = device.GetCopyableFootprints(resourceDesc, footprintOffset, footprintCount, offset, 
			subresourceFootprintsSpan.data(), rowCountsSpan.data(), rowSizesSpan.data());

		for (std::size_t i = 0uz; i < footprints.size(); ++i)
		{
			footprints[i] = CopyableFootprint
			{
				.offset = static_cast<std::uint64_t>(subresourceFootprintsSpan[i].Offset),
				.rowSize = static_cast<std::uint64_t>(rowSizesSpan[i]),
				.rowPitch = static_cast<std::uint64_t>(subresourceFootprintsSpan[i].Footprint.RowPitch),
				.rowCount = static_cast<std::uint32_t>(rowCountsSpan[i]),
				.sliceCount = static_cast<std::uint32_t>(subresourceFootprintsSpan[i].Footprint.Depth)
			};
		}

		UINT64 totalRowSizes = 0ull;
		for (std::size_t i = 0uz; i < footprintCount; ++i)
		{
			totalRowSizes += subresourceFootprintsSpan[i].Footprint.Depth * rowCountsSpan[i] * rowSizesSpan[i];
		}

		return CopyableFootprintSize{.sourceTotalSize = static_cast<std::uint64_t>(totalRowSizes), .destinationTotalSize = static_cast<std::uint64_t>(totalSize)};
	}

	DXGI_FORMAT D3D12Engine::GetFormat(const TextureFormatId format) const
	{
		const std::size_t formatIndex = textureFormatMap.IndexOf(format);
		if (formatIndex >= textureFormatMap.Size()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid texture format");
		}

		return textureFormatMap.DXGIFormat(formatIndex);
	}

	DXGI_FORMAT D3D12Engine::GetViewFormat(const DXGI_FORMAT format, const Aspect aspect)
	{
		DXGI_FORMAT viewFormat = DXGI_FORMAT_UNKNOWN;

		switch (aspect)
		{
		case Aspect::Color:
			viewFormat = IsDepthStencilFormat(format) ? DXGI_FORMAT_UNKNOWN : format;
			break;
		case Aspect::Depth:
			viewFormat = GetDepthViewFormat(format);
			break;
		case Aspect::Stencil:
			viewFormat = GetStencilViewFormat(format);
			break;
		default: [[unlikely]]
			assert(false && "Invalid aspect.");
			viewFormat = DXGI_FORMAT_UNKNOWN;
			break;
		}

		if (viewFormat == DXGI_FORMAT_UNKNOWN) [[unlikely]]
		{
			throw std::invalid_argument("Invalid aspect");
		}

		return viewFormat;
	}

	DXGI_FORMAT D3D12Engine::GetViewFormat(const TextureFormatId format, const Aspect aspect) const
	{
		return GetViewFormat(GetFormat(format), aspect);
	}

	D3D12Buffer& D3D12Engine::ToNativeBuffer(IBuffer& buffer)
	{
		if (typeid(buffer) != typeid(D3D12Buffer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid buffer");
		}

		return static_cast<D3D12Buffer&>(buffer);
	}

	const D3D12Buffer& D3D12Engine::ToNativeBuffer(const IBuffer& buffer)
	{
		if (typeid(buffer) != typeid(D3D12Buffer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid buffer");
		}

		return static_cast<const D3D12Buffer&>(buffer);
	}

	D3D12Texture& D3D12Engine::ToNativeTexture(ITexture& texture)
	{
		if (typeid(texture) != typeid(D3D12Texture)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid texture");
		}

		return static_cast<D3D12Texture&>(texture);
	}

	const D3D12Texture& D3D12Engine::ToNativeTexture(const ITexture& texture)
	{
		if (typeid(texture) != typeid(D3D12Texture)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid texture");
		}

		return static_cast<const D3D12Texture&>(texture);
	}

	D3D12ShaderDataContainer& D3D12Engine::ToNativeContainer(IShaderDataContainer& container)
	{
		if (typeid(container) != typeid(D3D12ShaderDataContainer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid container");
		}

		return static_cast<D3D12ShaderDataContainer&>(container);
	}

	const D3D12ShaderDataContainer& D3D12Engine::ToNativeContainer(const IShaderDataContainer& container)
	{
		if (typeid(container) != typeid(D3D12ShaderDataContainer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid container");
		}

		return static_cast<const D3D12ShaderDataContainer&>(container);
	}

	template<typename T>
	std::shared_ptr<T> D3D12Engine::CreateCommandList(const D3D12_COMMAND_LIST_TYPE type)
	{
		return std::make_shared<T>(device.CreateCommandAllocator(type), device.CreateCommandList(type));
	}

	template<typename CommandList, typename CommandListInterface>
	void D3D12Engine::Execute(const std::span<const CommandListInterface* const> commandLists, const QueueSync& sync, D3D12CommandQueue& commandQueue)
	{
		ValidateCommandLists<CommandList, CommandListInterface>(commandLists);
		ValidateFences(sync.before);
		ValidateFences(sync.after);

		arena.Free();
		const Memory::Arena::Slice<ID3D12CommandList*> lists = arena.Allocate<ID3D12CommandList*>(commandLists.size());
		const Memory::Arena::Slice<std::pair<ID3D12Fence*, UINT64>> beforeFences = arena.Allocate<std::pair<ID3D12Fence*, UINT64>>(sync.before.size());
		const Memory::Arena::Slice<std::pair<ID3D12Fence*, UINT64>> afterFences = arena.Allocate<std::pair<ID3D12Fence*, UINT64>>(sync.after.size());
		const std::span<ID3D12CommandList*> listsSpan = arena.Span(lists);
		const std::span<std::pair<ID3D12Fence*, UINT64>> beforeFencesSpan = arena.Span(beforeFences);
		const std::span<std::pair<ID3D12Fence*, UINT64>> afterFencesSpan = arena.Span(afterFences);

		GetCommandLists<CommandList, CommandListInterface>(commandLists, listsSpan);
		GetFences(sync.before, beforeFencesSpan);
		GetFences(sync.after, afterFencesSpan);
		commandQueue.Execute(listsSpan, beforeFencesSpan, afterFencesSpan);
	}

	template<typename CommandList, typename CommandListInterface>
	void D3D12Engine::GetCommandLists(const std::span<const CommandListInterface* const> commandLists, const std::span<ID3D12CommandList*> lists) noexcept
	{
		assert(commandLists.size() == lists.size() && "Input and output sizes are not the same.");
		for (std::size_t i = 0uz; i < commandLists.size(); ++i)
		{
			lists[i] = &static_cast<const CommandList*>(commandLists[i])->CommandList();
		}
	}

	void D3D12Engine::GetFences(const std::span<const FenceValue> input, const std::span<std::pair<ID3D12Fence*, UINT64>> output) noexcept
	{
		assert(input.size() == output.size() && "Input and output sizes are not the same.");
		for (std::size_t i = 0uz; i < input.size(); ++i)
		{
			output[i] = std::pair(&static_cast<const D3D12Fence*>(input[i].fence)->Fence(), static_cast<UINT64>(input[i].value));
		}
	}

	D3D12_COMMAND_QUEUE_DESC D3D12Engine::GetCommandQueueDesc(const D3D12_COMMAND_LIST_TYPE type) noexcept
	{
		return D3D12_COMMAND_QUEUE_DESC
		{
			.Type = type,
			.Priority = D3D12_COMMAND_QUEUE_PRIORITY_HIGH,
			.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE,
			.NodeMask = 0u
		};
	}

	D3D12SwapChain& D3D12Engine::GetSwapChain() const
	{
		if (!swapChain) [[unlikely]]
		{
			throw std::logic_error("Swap chain is not created");
		}

		return *swapChain;
	}

	void D3D12Engine::ValidateSize(const BufferParams& params)
	{
		if (params.size == 0uz) [[unlikely]]
		{
			throw std::invalid_argument("Invalid size");
		}
	}

	void D3D12Engine::ValidateDimension(const TextureParams& params)
	{
		if (params.size.Min() == 0u) [[unlikely]]
		{
			throw std::invalid_argument("Invalid size");
		}
		if (params.mipCount == 0u || params.mipCount > D3D12_REQ_MIP_LEVELS) [[unlikely]]
		{
			throw std::invalid_argument("Invalid mip count");
		}
		if (params.arraySize == 0u) [[unlikely]]
		{
			throw std::invalid_argument("Invalid array size");
		}
		if (params.mipCount > 1u && ToNumber(params.sampleCount) > 1u) [[unlikely]]
		{
			throw std::invalid_argument("Invalid mip count or sample count");
		}

		switch (params.dimension)
		{
		case TextureDimension::Texture1D:
			if (params.size.X() > D3D12_REQ_TEXTURE1D_U_DIMENSION || params.size.Y() != 1u || params.size.Z() != 1u) [[unlikely]]
			{
				throw std::invalid_argument("Invalid size");
			}
			if (params.arraySize > D3D12_REQ_TEXTURE1D_ARRAY_AXIS_DIMENSION) [[unlikely]]
			{
				throw std::invalid_argument("Invalid array size");
			}
			if (ToNumber(params.sampleCount) != 1u) [[unlikely]]
			{
				throw std::invalid_argument("Invalid sample count");
			}
			break;
		case TextureDimension::Texture2D:
			if (params.size.X() > D3D12_REQ_TEXTURE2D_U_OR_V_DIMENSION || params.size.Y() > D3D12_REQ_TEXTURE2D_U_OR_V_DIMENSION || params.size.Z() != 1u) [[unlikely]]
			{
				throw std::invalid_argument("Invalid size");
			}
			if (params.arraySize > D3D12_REQ_TEXTURE2D_ARRAY_AXIS_DIMENSION) [[unlikely]]
			{
				throw std::invalid_argument("Invalid array size");
			}
			if (ToNumber(params.sampleCount) > D3D12_MAX_MULTISAMPLE_SAMPLE_COUNT) [[unlikely]]
			{
				throw std::invalid_argument("Invalid sample count");
			}
			break;
		case TextureDimension::Texture3D:
			if (params.size.X() > D3D12_REQ_TEXTURE3D_U_V_OR_W_DIMENSION || params.size.Y() > D3D12_REQ_TEXTURE3D_U_V_OR_W_DIMENSION || params.size.Z() > D3D12_REQ_TEXTURE3D_U_V_OR_W_DIMENSION) [[unlikely]]
			{
				throw std::invalid_argument("Invalid size");
			}
			if (params.arraySize != 1u) [[unlikely]]
			{
				throw std::invalid_argument("Invalid array size");
			}
			if (ToNumber(params.sampleCount) != 1u) [[unlikely]]
			{
				throw std::invalid_argument("Invalid sample count");
			}
			break;
		}
	}

	void D3D12Engine::ValidateColorTexture(const TextureParams& params)
	{
		if (Any(TextureUsage::DepthStencil, params.usage)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid usage");
		}
	}

	void D3D12Engine::ValidateDepthTexture(const TextureParams& params)
	{
		if (params.castableFormats.size() > 0uz) [[unlikely]]
		{
			throw std::invalid_argument("Invalid castable texture format");
		}
		if (Any(TextureFlag::SRGB, params.flags)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid srgb flag");
		}
		if (Any(TextureUsage::RenderTarget | TextureUsage::UnorderedAccess, params.usage)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid usage");
		}
	}

	void D3D12Engine::ValidateAspect(const Aspect aspect, const DXGI_FORMAT format)
	{
		switch (aspect)
		{
		case Aspect::Color:
			if (IsDepthStencilFormat(format)) [[unlikely]]
			{
				throw std::invalid_argument("Invalid aspect");
			}
			break;
		case Aspect::Depth:
			if (!IsDepthStencilFormat(format)) [[unlikely]]
			{
				throw std::invalid_argument("Invalid aspect");
			}
			break;
		case Aspect::Stencil:
			if (GetStencilViewFormat(format) == DXGI_FORMAT_UNKNOWN) [[unlikely]]
			{
				throw std::invalid_argument("Invalid aspect");
			}
			break;
		default: [[unlikely]]
			throw std::invalid_argument("Invalid aspect");
		}
	}

	void D3D12Engine::ValidateCBVParams(const D3D12Buffer& buffer, const CBVParams& params)
	{
		if (params.offset % CBVAlignment) [[unlikely]]
		{
			throw std::invalid_argument("Invalid offset");
		}
		if (params.size == 0ull || params.size % CBVAlignment) [[unlikely]]
		{
			throw std::invalid_argument("Invalid size");
		}
		if (params.offset + params.size > buffer.Size()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid cbv params");
		}

		if (None(BufferUsage::ShaderResource, buffer.Usage())) [[unlikely]]
		{
			throw std::invalid_argument("Invalid buffer usage");
		}
	}

	void D3D12Engine::ValidateSRVParams(const D3D12Buffer& buffer, const BufferSRVParams& params)
	{
		if (params.stride == 0u) [[unlikely]]
		{
			throw std::invalid_argument("Invalid stride");
		}
		if ((params.firstElementIndex + params.elementCount) * params.stride > buffer.Size()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid size");
		}

		if (None(BufferUsage::ShaderResource, buffer.Usage())) [[unlikely]]
		{
			throw std::invalid_argument("Invalid buffer usage");
		}
	}

	void D3D12Engine::ValidateSRVParams(const D3D12Texture& texture, const TextureSRVParams& params)
	{
		if (texture.Format() != params.format && std::ranges::find(texture.CastableFormats(), params.format) == texture.CastableFormats().cend()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid format");
		}

		if (None(TextureUsage::ShaderResource, texture.Usage())) [[unlikely]]
		{
			throw std::invalid_argument("Invalid texture usage");
		}

		ValidateAspect(params.aspect, texture.NativeFormat());
	}

	void D3D12Engine::ValidateSRVParams(const D3D12Texture& texture, const Texture1DSRVParams& params)
	{
		ValidateSRVParams(texture, static_cast<const TextureSRVParams&>(params));
		ValidateDimension(texture, TextureDimension::Texture1D);
		ValidateMipRange(texture, params.mipRange);
		ValidateSampleCount(texture, false);
	}

	void D3D12Engine::ValidateSRVParams(const D3D12Texture& texture, const Texture1DArraySRVParams& params)
	{
		ValidateSRVParams(texture, static_cast<const Texture1DSRVParams&>(params));
		ValidateArrayRange(texture, params.arrayRange);
	}

	void D3D12Engine::ValidateSRVParams(const D3D12Texture& texture, const Texture2DSRVParams& params)
	{
		ValidateSRVParams(texture, static_cast<const TextureSRVParams&>(params));
		ValidateDimension(texture, TextureDimension::Texture2D);
		ValidateMipRange(texture, params.mipRange);
		ValidateSampleCount(texture, false);
	}

	void D3D12Engine::ValidateSRVParams(const D3D12Texture& texture, const Texture2DArraySRVParams& params)
	{
		ValidateSRVParams(texture, static_cast<const Texture2DSRVParams&>(params));
		ValidateArrayRange(texture, params.arrayRange);
	}

	void D3D12Engine::ValidateSRVParams(const D3D12Texture& texture, const Texture2DMSSRVParams& params)
	{
		ValidateSRVParams(texture, static_cast<const TextureSRVParams&>(params));
		ValidateDimension(texture, TextureDimension::Texture2D);
		ValidateSampleCount(texture, true);
	}

	void D3D12Engine::ValidateSRVParams(const D3D12Texture& texture, const Texture2DMSArraySRVParams& params)
	{
		ValidateSRVParams(texture, static_cast<const Texture2DMSSRVParams&>(params));
		ValidateArrayRange(texture, params.arrayRange);
	}

	void D3D12Engine::ValidateSRVParams(const D3D12Texture& texture, const Texture3DSRVParams& params)
	{
		ValidateSRVParams(texture, static_cast<const TextureSRVParams&>(params));
		ValidateDimension(texture, TextureDimension::Texture3D);
		ValidateMipRange(texture, params.mipRange);
		ValidateSampleCount(texture, false);
	}

	void D3D12Engine::ValidateSRVParams(const D3D12Texture& texture, const TextureCubeSRVParams& params)
	{
		ValidateSRVParams(texture, static_cast<const TextureSRVParams&>(params));
		ValidateDimension(texture, TextureDimension::Texture2D);
		ValidateMipRange(texture, params.mipRange);
		ValidateArrayRange(texture, ArrayRange{.firstArrayIndex = 0u, .arrayCount = 6u});
		ValidateSampleCount(texture, false);
	}

	void D3D12Engine::ValidateSRVParams(const D3D12Texture& texture, const TextureCubeArraySRVParams& params)
	{
		ValidateSRVParams(texture, static_cast<const TextureCubeSRVParams&>(params));
		const auto arrayRange = ArrayRange{.firstArrayIndex = params.arrayRange.firstArrayIndex, .arrayCount = params.arrayRange.arrayCount.value_or(texture.ArraySize() - params.arrayRange.firstArrayIndex)};
		ValidateArrayRange(texture, arrayRange);
		if (arrayRange.arrayCount.value() % 6) [[unlikely]]
		{
			throw std::invalid_argument("Invalid array range");
		}
	}

	void D3D12Engine::ValidateDimension(const D3D12Texture& texture, const TextureDimension dimension)
	{
		if (texture.Dimension() != dimension) [[unlikely]]
		{
			throw std::invalid_argument("Invalid dimension");
		}
	}

	void D3D12Engine::ValidateMipRange(const D3D12Texture& texture, const MipRange& range)
	{
		if (range.mostDetailedMipIndex + range.mipCount.value_or(1u) > texture.MipCount()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid mip range");
		}
	}

	void D3D12Engine::ValidateArrayRange(const D3D12Texture& texture, const ArrayRange& range)
	{
		if (range.firstArrayIndex + range.arrayCount.value_or(1u) > texture.ArraySize()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid array range");
		}
	}

	void D3D12Engine::ValidateSampleCount(const D3D12Texture& texture, const bool shouldBeMS)
	{
		if (ToNumber(texture.SampleCount()) > 1u != shouldBeMS) [[unlikely]]
		{
			throw std::invalid_argument("Invalid sample count");
		}
	}

	void D3D12Engine::ValidateSwapChainParams(const SwapChainParams& params)
	{
		if (params.size)
		{
			if (params.size->X() > D3D12_REQ_TEXTURE2D_U_OR_V_DIMENSION || params.size->Y() > D3D12_REQ_TEXTURE2D_U_OR_V_DIMENSION) [[unlikely]]
			{
				throw std::invalid_argument("Invalid size");
			}
		}

		if (params.bufferCount < 2u || params.bufferCount > DXGI_MAX_SWAP_CHAIN_BUFFERS) [[unlikely]]
		{
			throw std::invalid_argument("Invalid buffer count");
		}

		if (params.alphaMode != SwapChainAlphaMode::Ignore && params.alphaMode != SwapChainAlphaMode::Straight && params.alphaMode != SwapChainAlphaMode::Premultiplied) [[unlikely]]
		{
			throw std::invalid_argument("Invalid alpha mode");
		}

		if (Any(TextureUsage::DepthStencil, params.usage)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid usage");
		}
	}

	template<typename Container>
	void D3D12Engine::ValidateContainer(const Container& container, const std::uint32_t index)
	{
		if (index >= container.Size()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid container index");
		}
		if (container.IsShaderVisible()) [[unlikely]]
		{
			throw std::invalid_argument("Container is shader visible: it's allowed to copy into it only");
		}
	}

	template<typename CommandList, typename CommandListInterface>
	void D3D12Engine::ValidateCommandLists(const std::span<const CommandListInterface* const> commandLists)
	{
		for (const CommandListInterface* const commandList : commandLists)
		{
			if (!commandList || typeid(*commandList) != typeid(CommandList)) [[unlikely]]
			{
				throw std::invalid_argument("Invalid command list");
			}
		}
	}

	void D3D12Engine::ValidateFences(const std::span<const FenceValue> fences)
	{
		for (const FenceValue& fenceValue : fences)
		{
			if (!fenceValue.fence || typeid(*fenceValue.fence) != typeid(D3D12Fence))
			{
				throw std::invalid_argument("Invalid fence");
			}
		}
	}
}
