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
import :D3D12BundleCommandList;
import :D3D12CommandQueue;
import :D3D12ComputeCommandList;
import :D3D12CopyCommandList;
import :D3D12DepthStencilContainer;
import :D3D12DescriptorHeapUtility;
import :D3D12Device;
import :D3D12Fence;
import :D3D12FormatUtility;
import :D3D12GraphicsCommandList;
import :D3D12HeapUtility;
import :D3D12RenderTargetContainer;
import :D3D12RootSignature;
import :D3D12RootSignatureUtility;
import :D3D12SamplerContainer;
import :D3D12SamplerUtility;
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
		static constexpr std::string_view ShaderIRName = D3D12Device::ShaderIRName;

		static constexpr auto BufferHeapTypeSupport = HeapTypeMask::Default | HeapTypeMask::Upload | HeapTypeMask::Download;
		static constexpr auto TextureHeapTypeSupport = HeapTypeMask::Default;

		static constexpr std::uint32_t CBVAlignment = std::uint32_t{D3D12_CONSTANT_BUFFER_DATA_PLACEMENT_ALIGNMENT};

		static constexpr float MaxAnisotropy = float{D3D12_DEFAULT_MAX_ANISOTROPY};

		[[nodiscard("Pure constructor")]]
		explicit D3D12Engine(IRenderDeviceContext& renderDevice);
		D3D12Engine(const D3D12Engine&) = delete;
		D3D12Engine(D3D12Engine&&) = delete;

		~D3D12Engine() noexcept = default;

		[[nodiscard("Pure function")]]
		std::shared_ptr<IBuffer> CreateBuffer(HeapType heapType, const BufferParams& params);

		[[nodiscard("Pure function")]]
		struct TextureFormatSupport TextureFormatSupport(TextureFormatId textureFormatId) const;
		[[nodiscard("Pure function")]]
		TextureSupportResponse TextureSupport(const TextureSupportRequest& request) const;
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
		void CreateView(const IBuffer* buffer, IShaderDataContainer& container, std::uint32_t index, const CBVParams& params);
		void CreateView(const IBuffer* buffer, IShaderDataContainer& container, std::uint32_t index, const BufferSRVParams& params);
		void CreateView(const ITexture* texture, IShaderDataContainer& container, std::uint32_t index, const TextureSRVParams& params);
		void CreateView(const IBuffer* buffer, IShaderDataContainer& container, std::uint32_t index, const BufferUAVParams& params);
		void CreateView(const ITexture* texture, IShaderDataContainer& container, std::uint32_t index, const TextureUAVParams& params);
		void CopyViews(std::span<const ShaderDataCopyRange> ranges);

		[[nodiscard("Pure function")]]
		std::shared_ptr<IRenderTargetContainer> CreateRenderTargetContainer(const RenderTargetContainerParams& params);
		void CreateView(const ITexture* texture, IRenderTargetContainer& container, std::uint32_t index, const RTVParams& params);
		void CopyViews(std::span<const RenderTargetCopyRange> ranges);

		[[nodiscard("Wierd call")]]
		std::shared_ptr<IDepthStencilContainer> CreateDepthStencilContainer(const DepthStencilContainerParams& params);
		void CreateView(const ITexture* texture, IDepthStencilContainer& container, std::uint32_t index, const DSVParams& params);
		void CopyViews(std::span<const DepthStencilCopyRange> ranges);

		[[nodiscard("Wierd call")]]
		std::shared_ptr<ISamplerContainer> CreateSamplerContainer(const SamplerContainerParams& params);
		void CreateSampler(ISamplerContainer& container, std::uint32_t index, const SamplerParams& params);
		void CopySamplers(std::span<const SamplerCopyRange> ranges);

		[[nodiscard("Pure function")]]
		Meta::Version ShaderIRVersion() const;

		[[nodiscard("Pure function")]]
		std::shared_ptr<IPipelineLayout> CreatePipelineLayout(const PipelineLayoutParams& params);

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
		std::shared_ptr<ISecondaryGraphicsCommandList> CreateSecondaryGraphicsCommandList();

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
		static DXGI_FORMAT GetViewFormat(DXGI_FORMAT format, Aspect aspect) noexcept;
		[[nodiscard("Pure function")]]
		DXGI_FORMAT GetViewFormat(TextureFormatId format, Aspect aspect) const;
		[[nodiscard("Pure function")]]
		static std::uint32_t GetMaxArraySize(TextureDimension dimension) noexcept;
		[[nodiscard("Pure function")]]
		static std::uint32_t GetMaxArraySize(TextureViewDimension dimension) noexcept;
		[[nodiscard("Pure function")]]
		static std::uint32_t GetMaxArraySize(DSVDimension dimension) noexcept;

		[[nodiscard("Pure function")]]
		static D3D12Buffer& ToNativeBuffer(IBuffer& buffer);
		[[nodiscard("Pure function")]]
		static const D3D12Buffer& ToNativeBuffer(const IBuffer& buffer);
		[[nodiscard("Pure function")]]
		static D3D12Buffer* ToNativeBuffer(IBuffer* buffer);
		[[nodiscard("Pure function")]]
		static const D3D12Buffer* ToNativeBuffer(const IBuffer* buffer);
		[[nodiscard("Pure function")]]
		static D3D12Texture& ToNativeTexture(ITexture& texture);
		[[nodiscard("Pure function")]]
		static const D3D12Texture& ToNativeTexture(const ITexture& texture);
		[[nodiscard("Pure function")]]
		static D3D12Texture* ToNativeTexture(ITexture* texture);
		[[nodiscard("Pure function")]]
		static const D3D12Texture* ToNativeTexture(const ITexture* texture);

		[[nodiscard("Pure function")]]
		static D3D12ShaderDataContainer& ToNativeContainer(IShaderDataContainer& container);
		[[nodiscard("Pure function")]]
		static const D3D12ShaderDataContainer& ToNativeContainer(const IShaderDataContainer& container);
		[[nodiscard("Pure function")]]
		static D3D12RenderTargetContainer& ToNativeContainer(IRenderTargetContainer& container);
		[[nodiscard("Pure function")]]
		static const D3D12RenderTargetContainer& ToNativeContainer(const IRenderTargetContainer& container);
		[[nodiscard("Pure function")]]
		static D3D12DepthStencilContainer& ToNativeContainer(IDepthStencilContainer& container);
		[[nodiscard("Pure function")]]
		static const D3D12DepthStencilContainer& ToNativeContainer(const IDepthStencilContainer& container);
		[[nodiscard("Pure function")]]
		static D3D12SamplerContainer& ToNativeContainer(ISamplerContainer& container);
		[[nodiscard("Pure function")]]
		static const D3D12SamplerContainer& ToNativeContainer(const ISamplerContainer& container);

		template<typename Container, typename Range>
		void CopyViews(std::span<const Range> ranges, D3D12_DESCRIPTOR_HEAP_TYPE type);

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
		static void ValidateSRVParams(const TextureSRVParams& params, DXGI_FORMAT format, std::uint32_t maxMipCount, std::uint32_t maxArraySize);
		static void ValidateUAVParams(const D3D12Buffer& buffer, const BufferUAVParams& params);
		static void ValidateUAVParams(const D3D12Texture& texture, const TextureUAVParams& params);
		static void ValidateUAVParams(const TextureUAVParams& params, DXGI_FORMAT format, std::uint32_t maxMipCount, std::uint32_t maxArraySize);
		static void ValidateRTVParams(const D3D12Texture& texture, const RTVParams& params);
		static void ValidateRTVParams(const RTVParams& params, DXGI_FORMAT format, std::uint32_t maxMipCount, std::uint32_t maxArraySize);
		static void ValidateDSVParams(const D3D12Texture& texture, const DSVParams& params);
		static void ValidateDSVParams(const DSVParams& params, DXGI_FORMAT format, std::uint32_t maxMipCount, std::uint32_t maxArraySize);
		static void ValidateSize(const D3D12Buffer& buffer, std::uint64_t firstElementIndex, std::uint32_t elementCount, std::uint32_t stride);
		static void ValidateViewFormat(const D3D12Texture& texture, TextureFormatId viewFormat);
		static void ValidateDimension(const D3D12Texture& texture, TextureViewDimension dimension);
		static void ValidateDimension(const D3D12Texture& texture, TextureDimension dimension);
		static void ValidateDimension(const D3D12Texture& texture, DSVDimension dimension);
		static void ValidateLayout(const D3D12Texture& texture, const TextureSRVLayout& layout, TextureViewDimension dimension);
		static void ValidateLayout(const TextureSRVLayout& layout, TextureViewDimension dimension, std::uint32_t maxMipCount, std::uint32_t maxArraySize);
		static void ValidateLayout(const D3D12Texture& texture, const TextureUAVLayout& layout);
		static void ValidateLayout(const TextureUAVLayout& layout, std::uint32_t maxMipCount, std::uint32_t maxArraySize);
		static void ValidateLayout(const D3D12Texture& texture, const RTVLayout& layout);
		static void ValidateLayout(const RTVLayout& layout, std::uint32_t maxMipCount, std::uint32_t maxArraySize);
		static void ValidateLayout(const D3D12Texture& texture, const DSVLayout& layout);
		static void ValidateLayout(const DSVLayout& layout, std::uint32_t maxMipCount, std::uint32_t maxArraySize);
		static void ValidateMipRange(const D3D12Texture& texture, const MipRange& range);
		static void ValidateMipRange(const MipRange& range, std::uint32_t maxMipCount);
		static void ValidateArrayRange(const D3D12Texture& texture, const ArrayRange& range);
		static void ValidateArrayRange(const ArrayRange& range, std::uint32_t maxArraySize);
		static void ValidateSampleCount(const D3D12Texture& texture, bool shouldBeMS);
		static void ValidateSwapChainParams(const SwapChainParams& params);

		static void ValidateContainer(const D3D12ShaderDataContainer& container, std::uint32_t index);
		static void ValidateCopyRange(std::span<const ShaderDataCopyRange> ranges);
		static void ValidateContainer(const D3D12RenderTargetContainer& container, std::uint32_t index);
		static void ValidateCopyRange(std::span<const RenderTargetCopyRange> ranges);
		static void ValidateContainer(const D3D12DepthStencilContainer& container, std::uint32_t index);
		static void ValidateCopyRange(std::span<const DepthStencilCopyRange> ranges);
		static void ValidateContainer(const D3D12SamplerContainer& container, std::uint32_t index);
		static void ValidateCopyRange(std::span<const SamplerCopyRange> ranges);

		static void ValidatePipelineLayoutParams(const PipelineLayoutParams& params);

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

#ifndef NDEBUG
			if (srgb) [[unlikely]]
			{
				throw std::invalid_argument("Invalid srgb flag");
			}
#endif
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
#ifndef NDEBUG
				if (srgbFormat == DXGI_FORMAT_UNKNOWN) [[unlikely]]
				{
					throw std::invalid_argument("Invalid srgb flag");
				}
#endif
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

	void D3D12Engine::CreateView(const IBuffer* const buffer, IShaderDataContainer& container, const std::uint32_t index, const CBVParams& params)
	{
		const D3D12Buffer* const nativeBuffer = ToNativeBuffer(buffer);
		if (nativeBuffer)
		{
			ValidateCBVParams(*nativeBuffer, params);
		}

		D3D12ShaderDataContainer& nativeContainer = ToNativeContainer(container);
		ValidateContainer(nativeContainer, index);
		const D3D12_CPU_DESCRIPTOR_HANDLE handle = nativeContainer.CpuHandle(static_cast<UINT>(index));

		if (nativeBuffer)
		{
			const D3D12_GPU_VIRTUAL_ADDRESS address = nativeBuffer->Resource().GetGPUVirtualAddress();
			const D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = ToCBVDesc(address, params);
			device.CreateCBV(&cbvDesc, handle);
		}
		else
		{
			device.CreateCBV(nullptr, handle);
		}

		nativeContainer.Set(index, CBVMeta{.resource = nativeBuffer, .params = params});
	}

	void D3D12Engine::CreateView(const IBuffer* const buffer, IShaderDataContainer& container, const std::uint32_t index, const BufferSRVParams& params)
	{
		const D3D12Buffer* const nativeBuffer = ToNativeBuffer(buffer);
		if (nativeBuffer)
		{
			ValidateSRVParams(*nativeBuffer, params);
		}

		D3D12ShaderDataContainer& nativeContainer = ToNativeContainer(container);
		ValidateContainer(nativeContainer, index);
		const D3D12_CPU_DESCRIPTOR_HANDLE handle = nativeContainer.CpuHandle(static_cast<UINT>(index));

		const D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = ToSRVDesc(params);
		device.CreateSRV(nativeBuffer ? &nativeBuffer->Resource() : nullptr, srvDesc, handle);

		nativeContainer.Set(index, BufferSRVMeta{.resource = nativeBuffer, .params = params});
	}

	void D3D12Engine::CreateView(const ITexture* const texture, IShaderDataContainer& container, const std::uint32_t index, const TextureSRVParams& params)
	{
		const D3D12Texture* const nativeTexture = ToNativeTexture(texture);
		const DXGI_FORMAT format = GetFormat(params.format);
		const std::uint32_t mipCount = nativeTexture ? nativeTexture->MipCount() : std::uint32_t{D3D12_REQ_MIP_LEVELS};
		const std::uint32_t arraySize = nativeTexture ? nativeTexture->ArraySize() : GetMaxArraySize(params.dimension);
		if (nativeTexture)
		{
			ValidateSRVParams(*nativeTexture, params);
		}
		else
		{
			ValidateSRVParams(params, format, mipCount, arraySize);
		}

		D3D12ShaderDataContainer& nativeContainer = ToNativeContainer(container);
		ValidateContainer(nativeContainer, index);
		const D3D12_CPU_DESCRIPTOR_HANDLE handle = nativeContainer.CpuHandle(static_cast<UINT>(index));

		const DXGI_FORMAT viewFormat = GetViewFormat(format, params.aspect);
		const D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = ToSRVDesc(params, viewFormat, mipCount, arraySize);
		device.CreateSRV(nativeTexture ? &nativeTexture->Resource() : nullptr, srvDesc, handle);

		nativeContainer.Set(index, TextureSRVMeta{.resource = nativeTexture, .params = params});
	}

	void D3D12Engine::CreateView(const IBuffer* const buffer, IShaderDataContainer& container, const std::uint32_t index, const BufferUAVParams& params)
	{
		const D3D12Buffer* const nativeBuffer = ToNativeBuffer(buffer);
		if (nativeBuffer)
		{
			ValidateUAVParams(*nativeBuffer, params);
		}

		D3D12ShaderDataContainer& nativeContainer = ToNativeContainer(container);
		ValidateContainer(nativeContainer, index);
		const D3D12_CPU_DESCRIPTOR_HANDLE handle = nativeContainer.CpuHandle(static_cast<UINT>(index));

		const D3D12_UNORDERED_ACCESS_VIEW_DESC uavDesc = ToUAVDesc(params);
		device.CreateUAV(nativeBuffer ? &nativeBuffer->Resource() : nullptr, uavDesc, handle);

		nativeContainer.Set(index, BufferUAVMeta{.resource = nativeBuffer, .params = params});
	}

	void D3D12Engine::CreateView(const ITexture* const texture, IShaderDataContainer& container, const std::uint32_t index, const TextureUAVParams& params)
	{
		const D3D12Texture* const nativeTexture = ToNativeTexture(texture);
		const DXGI_FORMAT format = GetFormat(params.format);
		const std::uint32_t arraySize = nativeTexture ? nativeTexture->ArraySize() : GetMaxArraySize(params.dimension);
		if (nativeTexture)
		{
			ValidateUAVParams(*nativeTexture, params);
		}
		else
		{
			ValidateUAVParams(params, format, std::uint32_t{D3D12_REQ_MIP_LEVELS}, arraySize);
		}

		D3D12ShaderDataContainer& nativeContainer = ToNativeContainer(container);
		ValidateContainer(nativeContainer, index);
		const D3D12_CPU_DESCRIPTOR_HANDLE handle = nativeContainer.CpuHandle(static_cast<UINT>(index));

		const DXGI_FORMAT viewFormat = GetViewFormat(format, params.aspect);
		const D3D12_UNORDERED_ACCESS_VIEW_DESC uavDesc = ToUAVDesc(params, viewFormat, arraySize);
		device.CreateUAV(nativeTexture ? &nativeTexture->Resource() : nullptr, uavDesc, handle);

		nativeContainer.Set(index, TextureUAVMeta{.resource = nativeTexture, .params = params});
	}

	void D3D12Engine::CopyViews(const std::span<const ShaderDataCopyRange> ranges)
	{
		CopyViews<D3D12ShaderDataContainer>(ranges, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	}

	std::shared_ptr<IRenderTargetContainer> D3D12Engine::CreateRenderTargetContainer(const RenderTargetContainerParams& params)
	{
		const D3D12_DESCRIPTOR_HEAP_DESC descriptorHeapDesc = ToDescriptorHeapDesc(params);
		return std::make_shared<D3D12RenderTargetContainer>(device.CreateDescriptorHeap(descriptorHeapDesc), device.GetDescriptorHandleIncrement(descriptorHeapDesc.Type), params.size);
	}

	void D3D12Engine::CreateView(const ITexture* texture, IRenderTargetContainer& container, const std::uint32_t index, const RTVParams& params)
	{
		const D3D12Texture* const nativeTexture = ToNativeTexture(texture);
		const DXGI_FORMAT format = GetFormat(params.format);
		const std::uint32_t arraySize = nativeTexture ? nativeTexture->ArraySize() : GetMaxArraySize(params.dimension);
		if (nativeTexture)
		{
			ValidateRTVParams(*nativeTexture, params);
		}
		else
		{
			ValidateRTVParams(params, format, std::uint32_t{D3D12_REQ_MIP_LEVELS}, arraySize);
		}

		D3D12RenderTargetContainer& nativeContainer = ToNativeContainer(container);
		ValidateContainer(nativeContainer, index);
		const D3D12_CPU_DESCRIPTOR_HANDLE handle = nativeContainer.CpuHandle(static_cast<UINT>(index));

		const D3D12_RENDER_TARGET_VIEW_DESC rtvDesc = ToRTVDesc(params, format, arraySize);
		device.CreateRTV(nativeTexture ? &nativeTexture->Resource() : nullptr, rtvDesc, handle);

		nativeContainer.Set(index, RenderTargetTextureMeta{.texture = nativeTexture, .params = params});
	}

	void D3D12Engine::CopyViews(const std::span<const RenderTargetCopyRange> ranges)
	{
		CopyViews<D3D12RenderTargetContainer>(ranges, D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	}

	std::shared_ptr<IDepthStencilContainer> D3D12Engine::CreateDepthStencilContainer(const DepthStencilContainerParams& params)
	{
		const D3D12_DESCRIPTOR_HEAP_DESC descriptorHeapDesc = ToDescriptorHeapDesc(params);
		return std::make_shared<D3D12DepthStencilContainer>(device.CreateDescriptorHeap(descriptorHeapDesc), device.GetDescriptorHandleIncrement(descriptorHeapDesc.Type), params.size);
	}

	void D3D12Engine::CreateView(const ITexture* const texture, IDepthStencilContainer& container, const std::uint32_t index, const DSVParams& params)
	{
		const D3D12Texture* const nativeTexture = ToNativeTexture(texture);
		const DXGI_FORMAT format = GetFormat(params.format);
		const std::uint32_t arraySize = nativeTexture ? nativeTexture->ArraySize() : GetMaxArraySize(params.dimension);
		if (nativeTexture)
		{
			ValidateDSVParams(*nativeTexture, params);
		}
		else
		{
			ValidateDSVParams(params, format, std::uint32_t{D3D12_REQ_MIP_LEVELS}, arraySize);
		}

		D3D12DepthStencilContainer& nativeContainer = ToNativeContainer(container);
		ValidateContainer(nativeContainer, index);
		const D3D12_CPU_DESCRIPTOR_HANDLE handle = nativeContainer.CpuHandle(static_cast<UINT>(index));

		const D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = ToDSVDesc(params, format, arraySize);
		device.CreateDSV(nativeTexture ? &nativeTexture->Resource() : nullptr, dsvDesc, handle);

		nativeContainer.Set(index, DepthStencilTextureMeta{.texture = nativeTexture, .params = params});
	}

	void D3D12Engine::CopyViews(const std::span<const DepthStencilCopyRange> ranges)
	{
		CopyViews<D3D12DepthStencilContainer>(ranges, D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
	}

	std::shared_ptr<ISamplerContainer> D3D12Engine::CreateSamplerContainer(const SamplerContainerParams& params)
	{
		const D3D12_DESCRIPTOR_HEAP_DESC descriptorHeapDesc = ToDescriptorHeapDesc(params);
		return std::make_shared<D3D12SamplerContainer>(device.CreateDescriptorHeap(descriptorHeapDesc), device.GetDescriptorHandleIncrement(descriptorHeapDesc.Type), 
			params.size, params.shaderVisible);
	}

	void D3D12Engine::CreateSampler(ISamplerContainer& container, const std::uint32_t index, const SamplerParams& params)
	{
		D3D12SamplerContainer& nativeContainer = ToNativeContainer(container);
		ValidateContainer(nativeContainer, index);
		const D3D12_CPU_DESCRIPTOR_HANDLE handle = nativeContainer.CpuHandle(static_cast<UINT>(index));

		const D3D12_SAMPLER_DESC2 samplerDesc = ToSamplerDesc(params);
		device.CreateSampler(samplerDesc, handle);

		nativeContainer.Set(index, params);
	}

	void D3D12Engine::CopySamplers(const std::span<const SamplerCopyRange> ranges)
	{
		CopyViews<D3D12SamplerContainer>(ranges, D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER);
	}

	Meta::Version D3D12Engine::ShaderIRVersion() const
	{
		const auto shaderModel = std::to_underlying(device.GetShaderModel());
		return Meta::Version(shaderModel / 0xF, shaderModel & 0xF);
	}

	std::shared_ptr<IPipelineLayout> D3D12Engine::CreatePipelineLayout(const PipelineLayoutParams& params)
	{
		ValidatePipelineLayoutParams(params);

		arena.Free();
		const RootSignatureDescCounts rootSigDescCounts = GetRootSignatureCounts(params.descriptorSets);
		const Memory::Arena::Slice<D3D12_ROOT_PARAMETER1> parameters = arena.Allocate<D3D12_ROOT_PARAMETER1>(static_cast<std::size_t>(rootSigDescCounts.tableCount));
		const Memory::Arena::Slice<D3D12_DESCRIPTOR_RANGE1> ranges = arena.Allocate<D3D12_DESCRIPTOR_RANGE1>(static_cast<std::size_t>(rootSigDescCounts.rangeCount));
		const Memory::Arena::Slice<D3D12_STATIC_SAMPLER_DESC1> staticSamplers = arena.Allocate<D3D12_STATIC_SAMPLER_DESC1>(static_cast<std::size_t>(rootSigDescCounts.staticSamplerCount));
		const std::span<D3D12_ROOT_PARAMETER1> parametersSpan = arena.Span(parameters);
		const std::span<D3D12_DESCRIPTOR_RANGE1> rangesSpan = arena.Span(ranges);
		const std::span<D3D12_STATIC_SAMPLER_DESC1> staticSamplersSpan = arena.Span(staticSamplers);

		const D3D12_ROOT_SIGNATURE_DESC2 rootSigDesc = ToRootSignatureDesc(params, parametersSpan, rangesSpan, staticSamplersSpan);
		return std::make_shared<D3D12RootSignature>(device.CreateRootSignature(rootSigDesc), params);
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

	std::shared_ptr<ISecondaryGraphicsCommandList> D3D12Engine::CreateSecondaryGraphicsCommandList()
	{
		return CreateCommandList<D3D12BundleCommandList>(D3D12_COMMAND_LIST_TYPE_BUNDLE);
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

		return RenderDevice::SwapChainSupport
		{
			.maxSize = Math::Vector2<std::uint32_t>(std::uint32_t{D3D12_REQ_TEXTURE2D_U_OR_V_DIMENSION}, std::uint32_t{D3D12_REQ_TEXTURE2D_U_OR_V_DIMENSION}),
			.minBufferCount = 2u,
			.maxBufferCount = std::uint8_t{DXGI_MAX_SWAP_CHAIN_BUFFERS},
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
#ifndef NDEBUG
		if (swapChain) [[unlikely]]
		{
			throw std::logic_error("Swap chain is alive");
		}
#endif

		ValidateSwapChainParams(params);

		const DXGI_FORMAT format = GetFormat(params.format);
		const bool srgb = Any(SwapChainFlag::SRGB, params.flags);
#ifndef NDEBUG
		if (srgb && !IsSRGBCompatibleFormat(format)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid srgb flag");
		}
#endif

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
		return static_cast<std::uint8_t>(GetSwapChain().BufferCount());
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

		switch (request.dimension)
		{
		case TextureDimension::Texture1D:
			response.maxSize = Math::Vector3<std::uint32_t>(std::uint32_t{D3D12_REQ_TEXTURE1D_U_DIMENSION}, 1u, 1u);
			response.maxMipCount = std::uint32_t{D3D12_REQ_MIP_LEVELS};
			response.maxArraySize = std::uint32_t{D3D12_REQ_TEXTURE1D_ARRAY_AXIS_DIMENSION};
			response.sampleCounts = GetSampleCountMask(format, request, formatSupport);
			break;
		case TextureDimension::Texture2D:
			response.maxSize = Math::Vector3<std::uint32_t>(std::uint32_t{D3D12_REQ_TEXTURE2D_U_OR_V_DIMENSION}, std::uint32_t{D3D12_REQ_TEXTURE2D_U_OR_V_DIMENSION}, 1u);
			response.maxMipCount = std::uint32_t{D3D12_REQ_MIP_LEVELS};
			response.maxArraySize = std::uint32_t{D3D12_REQ_TEXTURE2D_ARRAY_AXIS_DIMENSION};
			response.sampleCounts = GetSampleCountMask(format, request, formatSupport);
			break;
		case TextureDimension::Texture3D:
			response.maxSize = Math::Vector3<std::uint32_t>(std::uint32_t{D3D12_REQ_TEXTURE3D_U_V_OR_W_DIMENSION}, std::uint32_t{D3D12_REQ_TEXTURE3D_U_V_OR_W_DIMENSION}, std::uint32_t{D3D12_REQ_TEXTURE3D_U_V_OR_W_DIMENSION});
			response.maxMipCount = std::uint32_t{D3D12_REQ_MIP_LEVELS};
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
#ifndef NDEBUG
		if (range.mipRange.mostDetailedMipIndex + range.mipRange.mipCount.value_or(1u) > resourceMipCount) [[unlikely]]
		{
			throw std::invalid_argument("Invalid mip range");
		}
		if (range.arrayRange.firstArrayIndex + range.arrayRange.arrayCount.value_or(1u) > resourceArrayCount) [[unlikely]]
		{
			throw std::invalid_argument("Invalid array range");
		}
#endif

		const std::uint32_t mipCount = range.mipRange.mipCount.value_or(resourceMipCount - range.mipRange.mostDetailedMipIndex);
		const std::uint32_t arrayCount = range.arrayRange.arrayCount.value_or(resourceArrayCount - range.arrayRange.firstArrayIndex);
#ifndef NDEBUG
		if (arrayCount > 1u && (range.mipRange.mostDetailedMipIndex != 0u || mipCount != resourceMipCount))
		{
			throw std::invalid_argument("Invalid mip range: mip gaps aren't allowed");
		}
#endif

		return CopyableFootprintInfo{.mipCount = mipCount, .arrayCount = arrayCount};
	}

	CopyableFootprintSize D3D12Engine::GetCopyableFootprints(const D3D12_RESOURCE_DESC1& resourceDesc, const CopyableFootprintInfo& footprintCountInfo, const UINT64 offset, 
		const UINT16 mostDetailedMipIndex, const UINT16 firstArrayIndex, const Aspect aspect, const std::span<CopyableFootprint> footprints) const
	{
		const std::uint32_t footprintCount = footprintCountInfo.mipCount * footprintCountInfo.arrayCount;
#ifndef NDEBUG
		if (footprints.size() != 0uz && footprints.size() != footprintCount) [[unlikely]]
		{
			throw std::invalid_argument("Invalid footprints count");
		}
#endif

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
#ifndef NDEBUG
		if (formatIndex >= textureFormatMap.Size()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid texture format");
		}
#endif

		return textureFormatMap.DXGIFormat(formatIndex);
	}

	DXGI_FORMAT D3D12Engine::GetViewFormat(const DXGI_FORMAT format, const Aspect aspect) noexcept
	{
		switch (aspect)
		{
		case Aspect::Color:
			return format;
		case Aspect::Depth:
			return GetDepthViewFormat(format);
		case Aspect::Stencil:
			return GetStencilViewFormat(format);
		default: [[unlikely]]
			assert(false && "Invalid aspect.");
			return DXGI_FORMAT_UNKNOWN;
		}
	}

	DXGI_FORMAT D3D12Engine::GetViewFormat(const TextureFormatId format, const Aspect aspect) const
	{
		return GetViewFormat(GetFormat(format), aspect);
	}

	std::uint32_t D3D12Engine::GetMaxArraySize(const TextureDimension dimension) noexcept
	{
		switch (dimension)
		{
		case TextureDimension::Texture1D:
			return std::uint32_t{D3D12_REQ_TEXTURE1D_ARRAY_AXIS_DIMENSION};
		case TextureDimension::Texture2D:
			return std::uint32_t{D3D12_REQ_TEXTURE2D_ARRAY_AXIS_DIMENSION};
		case TextureDimension::Texture3D:
			return 1u;
		default: [[unlikely]]
			assert(false && "Invalid dimension.");
			return 1u;
		}
	}

	std::uint32_t D3D12Engine::GetMaxArraySize(const TextureViewDimension dimension) noexcept
	{
		switch (dimension)
		{
		case TextureViewDimension::Texture1D:
			return std::uint32_t{D3D12_REQ_TEXTURE1D_ARRAY_AXIS_DIMENSION};
		case TextureViewDimension::Texture2D:
		case TextureViewDimension::TextureCube:
			return std::uint32_t{D3D12_REQ_TEXTURE2D_ARRAY_AXIS_DIMENSION};
		case TextureViewDimension::Texture3D:
			return 1u;
		default: [[unlikely]]
			assert(false && "Invalid dimension.");
			return 1u;
		}
	}

	std::uint32_t D3D12Engine::GetMaxArraySize(const DSVDimension dimension) noexcept
	{
		switch (dimension)
		{
		case DSVDimension::Texture1D:
			return std::uint32_t{D3D12_REQ_TEXTURE1D_ARRAY_AXIS_DIMENSION};
		case DSVDimension::Texture2D:
			return std::uint32_t{D3D12_REQ_TEXTURE2D_ARRAY_AXIS_DIMENSION};
		default: [[unlikely]]
			assert(false && "Invalid dimension.");
			return 1u;
		}
	}

	D3D12Buffer& D3D12Engine::ToNativeBuffer(IBuffer& buffer)
	{
#ifndef NDEBUG
		if (typeid(buffer) != typeid(D3D12Buffer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid buffer");
		}
#endif

		return static_cast<D3D12Buffer&>(buffer);
	}

	const D3D12Buffer& D3D12Engine::ToNativeBuffer(const IBuffer& buffer)
	{
#ifndef NDEBUG
		if (typeid(buffer) != typeid(D3D12Buffer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid buffer");
		}
#endif

		return static_cast<const D3D12Buffer&>(buffer);
	}

	D3D12Buffer* D3D12Engine::ToNativeBuffer(IBuffer* const buffer)
	{
#ifndef NDEBUG
		if (buffer != nullptr && typeid(*buffer) != typeid(D3D12Buffer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid buffer");
		}
#endif

		return static_cast<D3D12Buffer*>(buffer);
	}

	const D3D12Buffer* D3D12Engine::ToNativeBuffer(const IBuffer* const buffer)
	{
#ifndef NDEBUG
		if (buffer != nullptr && typeid(*buffer) != typeid(D3D12Buffer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid buffer");
		}
#endif

		return static_cast<const D3D12Buffer*>(buffer);
	}

	D3D12Texture& D3D12Engine::ToNativeTexture(ITexture& texture)
	{
#ifndef NDEBUG
		if (typeid(texture) != typeid(D3D12Texture)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid texture");
		}
#endif

		return static_cast<D3D12Texture&>(texture);
	}

	const D3D12Texture& D3D12Engine::ToNativeTexture(const ITexture& texture)
	{
#ifndef NDEBUG
		if (typeid(texture) != typeid(D3D12Texture)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid texture");
		}
#endif

		return static_cast<const D3D12Texture&>(texture);
	}

	D3D12Texture* D3D12Engine::ToNativeTexture(ITexture* const texture)
	{
#ifndef NDEBUG
		if (texture != nullptr && typeid(texture) != typeid(D3D12Texture)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid texture");
		}
#endif

		return static_cast<D3D12Texture*>(texture);
	}

	const D3D12Texture* D3D12Engine::ToNativeTexture(const ITexture* const texture)
	{
#ifndef NDEBUG
		if (texture != nullptr && typeid(texture) != typeid(D3D12Texture)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid texture");
		}
#endif

		return static_cast<const D3D12Texture*>(texture);
	}

	D3D12ShaderDataContainer& D3D12Engine::ToNativeContainer(IShaderDataContainer& container)
	{
#ifndef NDEBUG
		if (typeid(container) != typeid(D3D12ShaderDataContainer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid container");
		}
#endif

		return static_cast<D3D12ShaderDataContainer&>(container);
	}

	const D3D12ShaderDataContainer& D3D12Engine::ToNativeContainer(const IShaderDataContainer& container)
	{
#ifndef NDEBUG
		if (typeid(container) != typeid(D3D12ShaderDataContainer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid container");
		}
#endif

		return static_cast<const D3D12ShaderDataContainer&>(container);
	}

	D3D12RenderTargetContainer& D3D12Engine::ToNativeContainer(IRenderTargetContainer& container)
	{
#ifndef NDEBUG
		if (typeid(container) != typeid(D3D12RenderTargetContainer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid container");
		}
#endif

		return static_cast<D3D12RenderTargetContainer&>(container);
	}

	const D3D12RenderTargetContainer& D3D12Engine::ToNativeContainer(const IRenderTargetContainer& container)
	{
#ifndef NDEBUG
		if (typeid(container) != typeid(D3D12RenderTargetContainer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid container");
		}
#endif

		return static_cast<const D3D12RenderTargetContainer&>(container);
	}

	D3D12DepthStencilContainer& D3D12Engine::ToNativeContainer(IDepthStencilContainer& container)
	{
#ifndef NDEBUG
		if (typeid(container) != typeid(D3D12DepthStencilContainer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid container");
		}
#endif

		return static_cast<D3D12DepthStencilContainer&>(container);
	}

	const D3D12DepthStencilContainer& D3D12Engine::ToNativeContainer(const IDepthStencilContainer& container)
	{
#ifndef NDEBUG
		if (typeid(container) != typeid(D3D12DepthStencilContainer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid container");
		}
#endif

		return static_cast<const D3D12DepthStencilContainer&>(container);
	}

	D3D12SamplerContainer& D3D12Engine::ToNativeContainer(ISamplerContainer& container)
	{
#ifndef NDEBUG
		if (typeid(container) != typeid(D3D12SamplerContainer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid container");
		}
#endif

		return static_cast<D3D12SamplerContainer&>(container);
	}

	const D3D12SamplerContainer& D3D12Engine::ToNativeContainer(const ISamplerContainer& container)
	{
#ifndef NDEBUG
		if (typeid(container) != typeid(D3D12SamplerContainer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid container");
		}
#endif

		return static_cast<const D3D12SamplerContainer&>(container);
	}

	template<typename Container, typename Range>
	void D3D12Engine::CopyViews(const std::span<const Range> ranges, const D3D12_DESCRIPTOR_HEAP_TYPE type)
	{
		ValidateCopyRange(ranges);

		arena.Free();
		const Memory::Arena::Slice<D3D12_CPU_DESCRIPTOR_HANDLE> sources = arena.Allocate<D3D12_CPU_DESCRIPTOR_HANDLE>(ranges.size());
		const Memory::Arena::Slice<D3D12_CPU_DESCRIPTOR_HANDLE> destinations = arena.Allocate<D3D12_CPU_DESCRIPTOR_HANDLE>(ranges.size());
		const Memory::Arena::Slice<UINT> rangeSizes = arena.Allocate<UINT>(ranges.size());
		const std::span<D3D12_CPU_DESCRIPTOR_HANDLE> sourcesSpan = arena.Span(sources);
		const std::span<D3D12_CPU_DESCRIPTOR_HANDLE> destinationsSpan = arena.Span(destinations);
		const std::span<UINT> rangesSizesSpan = arena.Span(rangeSizes);

		for (std::size_t i = 0uz; i < ranges.size(); ++i)
		{
			const Range& range = ranges[i];
			sourcesSpan[i] = static_cast<const Container*>(range.source)->CpuHandle(range.sourceOffset);
			destinationsSpan[i] = static_cast<const Container*>(range.destination)->CpuHandle(range.destinationOffset);
			rangesSizesSpan[i] = static_cast<UINT>(range.count);
		}

		device.CopyDescriptors(static_cast<UINT>(ranges.size()), rangesSizesSpan.data(),
			sourcesSpan.data(), destinationsSpan.data(), type);

		for (std::size_t i = 0uz; i < ranges.size(); ++i)
		{
			const Range& range = ranges[i];
			const auto source = static_cast<const Container*>(range.source);
			const auto destination = static_cast<Container*>(range.destination);
			std::ranges::copy(&source->Meta(range.sourceOffset), &source->Meta(range.sourceOffset) + range.count, &destination->Meta(range.destinationOffset));
		}
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
#ifndef NDEBUG
		if (!swapChain) [[unlikely]]
		{
			throw std::logic_error("Swap chain is not created");
		}
#endif

		return *swapChain;
	}

	void D3D12Engine::ValidateSize(const BufferParams& params)
	{
#ifndef NDEBUG
		if (params.size == 0uz) [[unlikely]]
		{
			throw std::invalid_argument("Invalid size");
		}
#endif
	}

	void D3D12Engine::ValidateDimension(const TextureParams& params)
	{
#ifndef NDEBUG
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
#endif
	}

	void D3D12Engine::ValidateColorTexture(const TextureParams& params)
	{
#ifndef NDEBUG
		if (Any(TextureUsage::DepthStencil, params.usage)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid usage");
		}
#endif
	}

	void D3D12Engine::ValidateDepthTexture(const TextureParams& params)
	{
#ifndef NDEBUG
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
#endif
	}

	void D3D12Engine::ValidateAspect(const Aspect aspect, const DXGI_FORMAT format)
	{
#ifndef NDEBUG
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
			assert(false && "Invalid aspect.");
			break;
		}
#endif
	}

	void D3D12Engine::ValidateCBVParams(const D3D12Buffer& buffer, const CBVParams& params)
	{
#ifndef NDEBUG
		if (params.offset % CBVAlignment) [[unlikely]]
		{
			throw std::invalid_argument("Invalid offset");
		}
		if (params.size == 0ull || params.size % CBVAlignment) [[unlikely]]
		{
			throw std::invalid_argument("Invalid size");
		}
		if (params.offset + params.size > buffer.Size() || std::numeric_limits<std::uint64_t>::max() - params.size < params.offset) [[unlikely]]
		{
			throw std::invalid_argument("Invalid cbv params");
		}

		if (None(BufferUsage::ShaderResource, buffer.Usage())) [[unlikely]]
		{
			throw std::invalid_argument("Invalid buffer usage");
		}
#endif
	}

	void D3D12Engine::ValidateSRVParams(const D3D12Buffer& buffer, const BufferSRVParams& params)
	{
		ValidateSize(buffer, params.firstElementIndex, params.elementCount, params.stride);

#ifndef NDEBUG
		if (None(BufferUsage::ShaderResource, buffer.Usage())) [[unlikely]]
		{
			throw std::invalid_argument("Invalid buffer usage");
		}
#endif
	}

	void D3D12Engine::ValidateSRVParams(const D3D12Texture& texture, const TextureSRVParams& params)
	{
		ValidateViewFormat(texture, params.format);
		ValidateDimension(texture, params.dimension);
		ValidateAspect(params.aspect, texture.NativeFormat());
		ValidateLayout(texture, params.layout, params.dimension);

#ifndef NDEBUG
		if (None(TextureUsage::ShaderResource, texture.Usage())) [[unlikely]]
		{
			throw std::invalid_argument("Invalid texture usage");
		}
#endif
	}

	void D3D12Engine::ValidateSRVParams(const TextureSRVParams& params, const DXGI_FORMAT format, const std::uint32_t maxMipCount, const std::uint32_t maxArraySize)
	{
		ValidateAspect(params.aspect, format);
		ValidateLayout(params.layout, params.dimension, maxMipCount, maxArraySize);
	}

	void D3D12Engine::ValidateUAVParams(const D3D12Buffer& buffer, const BufferUAVParams& params)
	{
		ValidateSize(buffer, params.firstElementIndex, params.elementCount, params.stride);

#ifndef NDEBUG
		if (None(BufferUsage::UnorderedAccess, buffer.Usage())) [[unlikely]]
		{
			throw std::invalid_argument("Invalid buffer usage");
		}
#endif
	}

	void D3D12Engine::ValidateUAVParams(const D3D12Texture& texture, const TextureUAVParams& params)
	{
		ValidateViewFormat(texture, params.format);
		ValidateDimension(texture, params.dimension);
		ValidateAspect(params.aspect, texture.NativeFormat());
		ValidateLayout(texture, params.layout);

#ifndef NDEBUG
		if (None(TextureUsage::UnorderedAccess, texture.Usage())) [[unlikely]]
		{
			throw std::invalid_argument("Invalid texture usage");
		}
#endif
	}

	void D3D12Engine::ValidateUAVParams(const TextureUAVParams& params, const DXGI_FORMAT format, const std::uint32_t maxMipCount, const std::uint32_t maxArraySize)
	{
		ValidateAspect(params.aspect, format);
		ValidateLayout(params.layout, maxMipCount, maxArraySize);
	}

	void D3D12Engine::ValidateRTVParams(const D3D12Texture& texture, const RTVParams& params)
	{
		ValidateViewFormat(texture, params.format);
		ValidateDimension(texture, params.dimension);
		ValidateAspect(Aspect::Color, texture.NativeFormat());
		ValidateLayout(texture, params.layout);

#ifndef NDEBUG
		if (None(TextureUsage::RenderTarget, texture.Usage())) [[unlikely]]
		{
			throw std::invalid_argument("Invalid texture usage");
		}
#endif
	}

	void D3D12Engine::ValidateRTVParams(const RTVParams& params, const DXGI_FORMAT format, const std::uint32_t maxMipCount, const std::uint32_t maxArraySize)
	{
		ValidateAspect(Aspect::Color, format);
		ValidateLayout(params.layout, maxMipCount, maxArraySize);
	}

	void D3D12Engine::ValidateDSVParams(const D3D12Texture& texture, const DSVParams& params)
	{
		ValidateViewFormat(texture, params.format);
		ValidateDimension(texture, params.dimension);
		ValidateAspect(Aspect::Depth, texture.NativeFormat());
		ValidateLayout(texture, params.layout);

#ifndef NDEBUG
		if (None(TextureUsage::DepthStencil, texture.Usage())) [[unlikely]]
		{
			throw std::invalid_argument("Invalid texture usage");
		}
#endif
	}

	void D3D12Engine::ValidateDSVParams(const DSVParams& params, const DXGI_FORMAT format, const std::uint32_t maxMipCount, const std::uint32_t maxArraySize)
	{
		ValidateAspect(Aspect::Depth, format);
		ValidateLayout(params.layout, maxMipCount, maxArraySize);
	}

	void D3D12Engine::ValidateSize(const D3D12Buffer& buffer, const std::uint64_t firstElementIndex, const std::uint32_t elementCount, const std::uint32_t stride)
	{
#ifndef NDEBUG
		if (stride == 0u) [[unlikely]]
		{
			throw std::invalid_argument("Invalid stride");
		}
		if ((firstElementIndex + elementCount) * stride > buffer.Size()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid size");
		}
#endif
	}

	void D3D12Engine::ValidateViewFormat(const D3D12Texture& texture, const TextureFormatId viewFormat)
	{
#ifndef NDEBUG
		if (texture.Format() != viewFormat && std::ranges::find(texture.CastableFormats(), viewFormat) == texture.CastableFormats().cend()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid format");
		}
#endif
	}

	void D3D12Engine::ValidateDimension(const D3D12Texture& texture, const TextureViewDimension dimension)
	{
#ifndef NDEBUG
		switch (dimension)
		{
		case TextureViewDimension::Texture1D:
			if (texture.Dimension() != TextureDimension::Texture1D) [[unlikely]]
			{
				throw std::invalid_argument("Invalid dimension");
			}
			break;
		case TextureViewDimension::Texture2D:
		case TextureViewDimension::TextureCube:
			if (texture.Dimension() != TextureDimension::Texture2D) [[unlikely]]
			{
				throw std::invalid_argument("Invalid dimension");
			}
			break;
		case TextureViewDimension::Texture3D:
			if (texture.Dimension() != TextureDimension::Texture3D) [[unlikely]]
			{
				throw std::invalid_argument("Invalid dimension");
			}
			break;
		default: [[unlikely]]
			assert(false && "Invalid dimension");
			break;
		}
#endif
	}

	void D3D12Engine::ValidateDimension(const D3D12Texture& texture, const TextureDimension dimension)
	{
#ifndef NDEBUG
		if (texture.Dimension() != dimension) [[unlikely]]
		{
			throw std::invalid_argument("Invalid dimension");
		}
#endif
	}

	void D3D12Engine::ValidateDimension(const D3D12Texture& texture, const DSVDimension dimension)
	{
#ifndef NDEBUG
		switch (dimension)
		{
		case DSVDimension::Texture1D:
			if (texture.Dimension() != TextureDimension::Texture1D) [[unlikely]]
			{
				throw std::invalid_argument("Invalid dimension");
			}
			break;
		case DSVDimension::Texture2D:
			if (texture.Dimension() != TextureDimension::Texture2D) [[unlikely]]
			{
				throw std::invalid_argument("Invalid dimension");
			}
			break;
		default: [[unlikely]]
			assert(false && "Invalid dimension");
			break;
		}
#endif
	}

	void D3D12Engine::ValidateLayout(const D3D12Texture& texture, const TextureSRVLayout& layout, const TextureViewDimension dimension)
	{
		std::visit(Type::Overload
		{
			[&](const TextureSingleSRVLayout& l)
			{
				ValidateSampleCount(texture, false);
				ValidateMipRange(texture, l.mipRange);
				if (dimension == TextureViewDimension::TextureCube) [[unlikely]]
				{
					ValidateArrayRange(texture, ArrayRange{.firstArrayIndex = 0u, .arrayCount = 6u});
				}
			},
			[&](const TextureArraySRVLayout& l)
			{
				ValidateSampleCount(texture, false);
				ValidateMipRange(texture, l.mipRange);
				if (dimension == TextureViewDimension::TextureCube)
				{
					if (l.arrayRange.arrayCount)
					{
						if (*l.arrayRange.arrayCount % 6) [[unlikely]]
						{
							throw std::invalid_argument("Invalid array range");
						}
					}
					else
					{
						if ((texture.ArraySize() - l.arrayRange.firstArrayIndex) % 6) [[unlikely]]
						{
							throw std::invalid_argument("Invalid array range");
						}
					}
				}
				ValidateArrayRange(texture, l.arrayRange);
			},
			[&](const TextureMSSRVLayout&)
			{
				ValidateSampleCount(texture, true);
				if (dimension != TextureViewDimension::Texture2D) [[unlikely]]
				{
					throw std::invalid_argument("Invalid dimension");
				}
			},
			[&](const TextureMSArraySRVLayout& l)
			{
				ValidateSampleCount(texture, true);
				ValidateArrayRange(texture, l.arrayRange);
				if (dimension != TextureViewDimension::Texture2D) [[unlikely]]
				{
					throw std::invalid_argument("Invalid dimension");
				}
			}
		}, layout);
	}

	void D3D12Engine::ValidateLayout(const TextureSRVLayout& layout, const TextureViewDimension dimension,
		const std::uint32_t maxMipCount, const std::uint32_t maxArraySize)
	{
		std::visit(Type::Overload
		{
			[&](const TextureSingleSRVLayout& l)
			{
				ValidateMipRange(l.mipRange, maxMipCount);
				if (dimension == TextureViewDimension::TextureCube) [[unlikely]]
				{
					ValidateArrayRange(ArrayRange{.firstArrayIndex = 0u, .arrayCount = 6u}, maxArraySize);
				}
			},
			[&](const TextureArraySRVLayout& l)
			{
				ValidateMipRange(l.mipRange, maxMipCount);
				if (dimension == TextureViewDimension::TextureCube)
				{
					if (l.arrayRange.arrayCount)
					{
						if (*l.arrayRange.arrayCount % 6) [[unlikely]]
						{
							throw std::invalid_argument("Invalid array range");
						}
					}
					else
					{
						if ((maxArraySize - l.arrayRange.firstArrayIndex) % 6) [[unlikely]]
						{
							throw std::invalid_argument("Invalid array range");
						}
					}
				}
				ValidateArrayRange(l.arrayRange, maxArraySize);
			},
			[&](const TextureMSSRVLayout&)
			{
				if (dimension != TextureViewDimension::Texture2D) [[unlikely]]
				{
					throw std::invalid_argument("Invalid dimension");
				}
			},
			[&](const TextureMSArraySRVLayout& l)
			{
				ValidateArrayRange(l.arrayRange, maxArraySize);
				if (dimension != TextureViewDimension::Texture2D) [[unlikely]]
				{
					throw std::invalid_argument("Invalid dimension");
				}
			}
		}, layout);
	}

	void D3D12Engine::ValidateLayout(const D3D12Texture& texture, const TextureUAVLayout& layout)
	{
		std::visit(Type::Overload
		{
			[&](const TextureSingleUAVLayout& l)
			{
				ValidateSampleCount(texture, false);
				ValidateMipRange(texture, MipRange{.mostDetailedMipIndex = l.mipIndex, .mipCount = 1u});
			},
			[&](const TextureArrayUAVLayout& l)
			{
				ValidateSampleCount(texture, false);
				ValidateMipRange(texture, MipRange{.mostDetailedMipIndex = l.mipIndex, .mipCount = 1u});
				ValidateArrayRange(texture, l.arrayRange);
			}
		}, layout);
	}

	void D3D12Engine::ValidateLayout(const TextureUAVLayout& layout, const std::uint32_t maxMipCount, const std::uint32_t maxArraySize)
	{
		std::visit(Type::Overload
		{
			[&](const TextureSingleUAVLayout& l)
			{
				ValidateMipRange(MipRange{.mostDetailedMipIndex = l.mipIndex, .mipCount = 1u}, maxMipCount);
			},
			[&](const TextureArrayUAVLayout& l)
			{
				ValidateMipRange(MipRange{.mostDetailedMipIndex = l.mipIndex, .mipCount = 1u}, maxMipCount);
				ValidateArrayRange(l.arrayRange, maxArraySize);
			}
		}, layout);
	}

	void D3D12Engine::ValidateLayout(const D3D12Texture& texture, const RTVLayout& layout)
	{
		std::visit(Type::Overload
		{
			[&](const SingleRTVLayout& l)
			{
				ValidateSampleCount(texture, false);
				ValidateMipRange(texture, MipRange{.mostDetailedMipIndex = l.mipIndex, .mipCount = 1u});
			},
			[&](const ArrayRTVLayout& l)
			{
				ValidateSampleCount(texture, false);
				ValidateMipRange(texture, MipRange{ .mostDetailedMipIndex = l.mipIndex, .mipCount = 1u});
				ValidateArrayRange(texture, l.arrayRange);
			},
			[&](const MSRTVLayout&)
			{
				ValidateSampleCount(texture, true);
			},
			[&](const MSArrayRTVLayout& l)
			{
				ValidateSampleCount(texture, true);
				ValidateArrayRange(texture, l.arrayRange);
			}
		}, layout);
	}

	void D3D12Engine::ValidateLayout(const RTVLayout& layout, const std::uint32_t maxMipCount, const std::uint32_t maxArraySize)
	{
		std::visit(Type::Overload
		{
			[&](const SingleRTVLayout& l)
			{
				ValidateMipRange(MipRange{.mostDetailedMipIndex = l.mipIndex, .mipCount = 1u}, maxMipCount);
			},
			[&](const ArrayRTVLayout& l)
			{
				ValidateMipRange(MipRange{.mostDetailedMipIndex = l.mipIndex, .mipCount = 1u}, maxMipCount);
				ValidateArrayRange(l.arrayRange, maxArraySize);
			},
			[&](const MSRTVLayout&)
			{
			},
			[&](const MSArrayRTVLayout& l)
			{
				ValidateArrayRange(l.arrayRange, maxArraySize);
			}
		}, layout);
	}

	void D3D12Engine::ValidateLayout(const D3D12Texture& texture, const DSVLayout& layout)
	{
		std::visit(Type::Overload
		{
			[&](const SingleDSVLayout& l)
			{
				ValidateSampleCount(texture, false);
				ValidateMipRange(texture, MipRange{.mostDetailedMipIndex = l.mipIndex, .mipCount = 1u});
			},
			[&](const ArrayDSVLayout& l)
			{
				ValidateSampleCount(texture, false);
				ValidateMipRange(texture, MipRange{.mostDetailedMipIndex = l.mipIndex, .mipCount = 1u});
				ValidateArrayRange(texture, l.arrayRange);
			},
			[&](const MSDSVLayout&)
			{
				ValidateSampleCount(texture, true);
			},
			[&](const MSArrayDSVLayout& l)
			{
				ValidateSampleCount(texture, true);
				ValidateArrayRange(texture, l.arrayRange);
			}
		}, layout);
	}

	void D3D12Engine::ValidateLayout(const DSVLayout& layout, const std::uint32_t maxMipCount, const std::uint32_t maxArraySize)
	{
		std::visit(Type::Overload
		{
			[&](const SingleDSVLayout& l)
			{
				ValidateMipRange(MipRange{.mostDetailedMipIndex = l.mipIndex, .mipCount = 1u}, maxMipCount);
			},
			[&](const ArrayDSVLayout& l)
			{
				ValidateMipRange(MipRange{.mostDetailedMipIndex = l.mipIndex, .mipCount = 1u}, maxMipCount);
				ValidateArrayRange(l.arrayRange, maxArraySize);
			},
			[&](const MSDSVLayout&)
			{
			},
			[&](const MSArrayDSVLayout& l)
			{
				ValidateArrayRange(l.arrayRange, maxArraySize);
			}
		}, layout);
	}

	void D3D12Engine::ValidateMipRange(const D3D12Texture& texture, const MipRange& range)
	{
		ValidateMipRange(range, texture.MipCount());
	}

	void D3D12Engine::ValidateMipRange(const MipRange& range, const std::uint32_t maxMipCount)
	{
#ifndef NDEBUG
		if (range.mostDetailedMipIndex + range.mipCount.value_or(1u) > maxMipCount) [[unlikely]]
		{
			throw std::invalid_argument("Invalid mip range");
		}
#endif
	}

	void D3D12Engine::ValidateArrayRange(const D3D12Texture& texture, const ArrayRange& range)
	{
		ValidateArrayRange(range, texture.ArraySize());
	}

	void D3D12Engine::ValidateArrayRange(const ArrayRange& range, const std::uint32_t maxArraySize)
	{
#ifndef NDEBUG
		if (range.firstArrayIndex + range.arrayCount.value_or(1u) > maxArraySize) [[unlikely]]
		{
			throw std::invalid_argument("Invalid array range");
		}
#endif
	}

	void D3D12Engine::ValidateSampleCount(const D3D12Texture& texture, const bool shouldBeMS)
	{
#ifndef NDEBUG
		if (ToNumber(texture.SampleCount()) > 1u != shouldBeMS) [[unlikely]]
		{
			throw std::invalid_argument("Invalid sample count");
		}
#endif
	}

	void D3D12Engine::ValidateSwapChainParams(const SwapChainParams& params)
	{
#ifndef NDEBUG
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
#endif
	}

	void D3D12Engine::ValidateContainer(const D3D12ShaderDataContainer& container, const std::uint32_t index)
	{
#ifndef NDEBUG
		if (index >= container.Size()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid container index");
		}
		if (container.IsShaderVisible()) [[unlikely]]
		{
			throw std::invalid_argument("Container is shader visible");
		}
#endif
	}

	void D3D12Engine::ValidateCopyRange(const std::span<const ShaderDataCopyRange> ranges)
	{
#ifndef NDEBUG
		if (ranges.size() > std::numeric_limits<UINT>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Range count is too great");
		}
		for (const ShaderDataCopyRange& range : ranges)
		{
			if (!range.source || typeid(*range.source) != typeid(D3D12ShaderDataContainer)) [[unlikely]]
			{
				throw std::invalid_argument("Invalid source");
			}
			const D3D12ShaderDataContainer* const source = static_cast<const D3D12ShaderDataContainer*>(range.source);
			if (source->Size() < range.sourceOffset + range.count) [[unlikely]]
			{
				throw std::invalid_argument("Invalid source range");
			}
			if (source->IsShaderVisible()) [[unlikely]]
			{
				throw std::invalid_argument("Source is shader visible");
			}

			if (!range.destination || typeid(*range.destination) != typeid(D3D12ShaderDataContainer)) [[unlikely]]
			{
				throw std::invalid_argument("Invalid destination");
			}
			if (static_cast<const D3D12ShaderDataContainer*>(range.destination)->Size() < range.destinationOffset + range.count) [[unlikely]]
			{
				throw std::invalid_argument("Invalid destination range");
			}
		}
#endif
	}

	void D3D12Engine::ValidateContainer(const D3D12RenderTargetContainer& container, const std::uint32_t index)
	{
#ifndef NDEBUG
		if (index >= container.Size()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid container index");
		}
#endif
	}

	void D3D12Engine::ValidateCopyRange(std::span<const RenderTargetCopyRange> ranges)
	{
#ifndef NDEBUG
		if (ranges.size() > std::numeric_limits<UINT>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Range count is too great");
		}
		for (const RenderTargetCopyRange& range : ranges)
		{
			if (!range.source || typeid(*range.source) != typeid(D3D12ShaderDataContainer)) [[unlikely]]
			{
				throw std::invalid_argument("Invalid source");
			}
			const D3D12RenderTargetContainer* const source = static_cast<const D3D12RenderTargetContainer*>(range.source);
			if (source->Size() < range.sourceOffset + range.count) [[unlikely]]
			{
				throw std::invalid_argument("Invalid source range");
			}

			if (!range.destination || typeid(*range.destination) != typeid(D3D12RenderTargetContainer)) [[unlikely]]
			{
				throw std::invalid_argument("Invalid destination");
			}
			if (static_cast<const D3D12RenderTargetContainer*>(range.destination)->Size() < range.destinationOffset + range.count) [[unlikely]]
			{
				throw std::invalid_argument("Invalid destination range");
			}
		}
#endif
	}

	void D3D12Engine::ValidateContainer(const D3D12DepthStencilContainer& container, const std::uint32_t index)
	{
#ifndef NDEBUG
		if (index >= container.Size()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid container index");
		}
#endif
	}

	void D3D12Engine::ValidateCopyRange(const std::span<const DepthStencilCopyRange> ranges)
	{
#ifndef NDEBUG
		if (ranges.size() > std::numeric_limits<UINT>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Range count is too great");
		}
		for (const DepthStencilCopyRange& range : ranges)
		{
			if (!range.source || typeid(*range.source) != typeid(D3D12ShaderDataContainer)) [[unlikely]]
			{
				throw std::invalid_argument("Invalid source");
			}
			const D3D12DepthStencilContainer* const source = static_cast<const D3D12DepthStencilContainer*>(range.source);
			if (source->Size() < range.sourceOffset + range.count) [[unlikely]]
			{
				throw std::invalid_argument("Invalid source range");
			}

			if (!range.destination || typeid(*range.destination) != typeid(D3D12DepthStencilContainer)) [[unlikely]]
			{
				throw std::invalid_argument("Invalid destination");
			}
			if (static_cast<const D3D12DepthStencilContainer*>(range.destination)->Size() < range.destinationOffset + range.count) [[unlikely]]
			{
				throw std::invalid_argument("Invalid destination range");
			}
		}
#endif
	}

	void D3D12Engine::ValidateContainer(const D3D12SamplerContainer& container, const std::uint32_t index)
	{
#ifndef NDEBUG
		if (index >= container.Size()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid container index");
		}
		if (container.IsShaderVisible()) [[unlikely]]
		{
			throw std::invalid_argument("Container is shader visible");
		}
#endif
	}

	void D3D12Engine::ValidateCopyRange(const std::span<const SamplerCopyRange> ranges)
	{
#ifndef NDEBUG
		if (ranges.size() > std::numeric_limits<UINT>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Range count is too great");
		}
		for (const SamplerCopyRange& range : ranges)
		{
			if (!range.source || typeid(*range.source) != typeid(D3D12SamplerContainer)) [[unlikely]]
			{
				throw std::invalid_argument("Invalid source");
			}
			const D3D12SamplerContainer* const source = static_cast<const D3D12SamplerContainer*>(range.source);
			if (source->Size() < range.sourceOffset + range.count) [[unlikely]]
			{
				throw std::invalid_argument("Invalid source range");
			}
			if (source->IsShaderVisible()) [[unlikely]]
			{
				throw std::invalid_argument("Source is shader visible");
			}

			if (!range.destination || typeid(*range.destination) != typeid(D3D12SamplerContainer)) [[unlikely]]
			{
				throw std::invalid_argument("Invalid destination");
			}
			if (static_cast<const D3D12SamplerContainer*>(range.destination)->Size() < range.destinationOffset + range.count) [[unlikely]]
			{
				throw std::invalid_argument("Invalid destination range");
			}
		}
#endif
	}

	void D3D12Engine::ValidatePipelineLayoutParams(const PipelineLayoutParams& params)
	{
#ifndef NDEBUG
		if (params.descriptorSets.size() > std::numeric_limits<UINT>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Descriptor set count is too great");
		}

		for (const DescriptorSet& set : params.descriptorSets)
		{
			if (set.ranges.size() > std::numeric_limits<UINT>::max()) [[unlikely]]
			{
				throw std::invalid_argument("Descriptor set range count is too great");
			}
			if (set.staticSamplers.size() > std::numeric_limits<UINT>::max()) [[unlikely]]
			{
				throw std::invalid_argument("Descriptor set static sampler count is too great");
			}
		}
#endif
	}

	template<typename CommandList, typename CommandListInterface>
	void D3D12Engine::ValidateCommandLists(const std::span<const CommandListInterface* const> commandLists)
	{
#ifndef NDEBUG
		for (const CommandListInterface* const commandList : commandLists)
		{
			if (!commandList || typeid(*commandList) != typeid(CommandList)) [[unlikely]]
			{
				throw std::invalid_argument("Invalid command list");
			}
		}
#endif
	}

	void D3D12Engine::ValidateFences(const std::span<const FenceValue> fences)
	{
#ifndef NDEBUG
		for (const FenceValue& fenceValue : fences)
		{
			if (!fenceValue.fence || typeid(*fenceValue.fence) != typeid(D3D12Fence))
			{
				throw std::invalid_argument("Invalid fence");
			}
		}
#endif
	}
}
