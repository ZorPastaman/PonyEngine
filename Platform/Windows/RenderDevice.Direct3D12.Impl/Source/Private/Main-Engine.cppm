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

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:Engine;

import std;

import PonyEngine.Log;
import PonyEngine.Memory;
import PonyEngine.Meta;
import PonyEngine.RenderDevice.Ext;
import PonyEngine.Surface.Windows;
import PonyEngine.Type;

import :AtomicSupport;
import :Buffer;
import :BufferUtility;
import :BundleCommandList;
import :CommandQueue;
import :ComputeCommandList;
import :ComputePipelineState;
import :CopyCommandList;
import :DepthStencilContainer;
import :DescriptorHeapUtility;
import :Device;
import :Factory;
import :Fence;
import :FormatUtility;
import :GraphicsCommandList;
import :GraphicsPipelineState;
import :HeapUtility;
import :PipelineStateSubobject;
import :PipelineStateUtility;
import :RenderTargetContainer;
import :RootSignature;
import :RootSignatureUtility;
import :SamplerContainer;
import :SamplerUtility;
import :ShaderDataContainer;
import :SwapChain;
import :SwapChainUtility;
import :SwapChainWrapper;
import :Texture;
import :TextureFormatMap;
import :TextureUtility;
import :Waiter;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	class Engine final
	{
	public:
		static constexpr std::string_view ApiName = Device::ApiName;
		static constexpr auto ApiVersion = Device::ApiVersion;

		static constexpr std::string_view ShaderIRName = ShaderIR::DXIL;
		static constexpr std::uint8_t SimultaneousTargetCount = std::uint8_t{D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT};

		static constexpr auto BufferHeapTypeSupport = HeapTypeMask::Default | HeapTypeMask::Upload | HeapTypeMask::Download;
		static constexpr auto TextureHeapTypeSupport = HeapTypeMask::Default;

		static constexpr std::uint32_t CBVAlignment = std::uint32_t{D3D12_CONSTANT_BUFFER_DATA_PLACEMENT_ALIGNMENT};

		static constexpr float MaxAnisotropy = float{D3D12_DEFAULT_MAX_ANISOTROPY};

		[[nodiscard("Pure constructor")]]
		explicit Engine(IRenderDeviceContext& renderDevice);
		Engine(const Engine&) = delete;
		Engine(Engine&&) = delete;

		~Engine() noexcept = default;

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
		ShaderScalarTypeMask ScalarTypeSupport() const;
		[[nodiscard("Pure function")]]
		static ShaderScalarTypeMask ToAtomicScalarTypeSupport(const AtomicSupport& support) noexcept;
		[[nodiscard("Pure function")]]
		static ShaderScalarTypeMask ToGroupSharedAtomicScalarTypeSupport(const AtomicSupport& support) noexcept;
		[[nodiscard("Pure function")]]
		struct ShaderSupport ShaderSupport() const;

		[[nodiscard("Pure function")]]
		LineRasterizationModeMask LineRasterizationSupport() const;
		[[nodiscard("Pure function")]]
		struct RasterizerSupport RasterizerSupport() const;

		[[nodiscard("Pure function")]]
		std::shared_ptr<IPipelineLayout> CreatePipelineLayout(const PipelineLayoutParams& params);
		[[nodiscard("Pure function")]]
		std::shared_ptr<IGraphicsPipelineState> CreateGraphicsPipelineState(const std::shared_ptr<const IPipelineLayout>& layout,
			const GraphicsPipelineStateParams& params);
		[[nodiscard("Pure function")]]
		std::shared_ptr<IComputePipelineState> CreateComputePipelineState(const std::shared_ptr<const IPipelineLayout>& layout, const ComputePipelineStateParams& params);

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

		Engine& operator =(const Engine&) = delete;
		Engine& operator =(Engine&&) = delete;

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
		static Buffer& ToNativeBuffer(IBuffer& buffer);
		[[nodiscard("Pure function")]]
		static const Buffer& ToNativeBuffer(const IBuffer& buffer);
		[[nodiscard("Pure function")]]
		static Buffer* ToNativeBuffer(IBuffer* buffer);
		[[nodiscard("Pure function")]]
		static const Buffer* ToNativeBuffer(const IBuffer* buffer);
		[[nodiscard("Pure function")]]
		static Texture& ToNativeTexture(ITexture& texture);
		[[nodiscard("Pure function")]]
		static const Texture& ToNativeTexture(const ITexture& texture);
		[[nodiscard("Pure function")]]
		static Texture* ToNativeTexture(ITexture* texture);
		[[nodiscard("Pure function")]]
		static const Texture* ToNativeTexture(const ITexture* texture);

		[[nodiscard("Pure function")]]
		static ShaderDataContainer& ToNativeContainer(IShaderDataContainer& container);
		[[nodiscard("Pure function")]]
		static const ShaderDataContainer& ToNativeContainer(const IShaderDataContainer& container);
		[[nodiscard("Pure function")]]
		static RenderTargetContainer& ToNativeContainer(IRenderTargetContainer& container);
		[[nodiscard("Pure function")]]
		static const RenderTargetContainer& ToNativeContainer(const IRenderTargetContainer& container);
		[[nodiscard("Pure function")]]
		static DepthStencilContainer& ToNativeContainer(IDepthStencilContainer& container);
		[[nodiscard("Pure function")]]
		static const DepthStencilContainer& ToNativeContainer(const IDepthStencilContainer& container);
		[[nodiscard("Pure function")]]
		static SamplerContainer& ToNativeContainer(ISamplerContainer& container);
		[[nodiscard("Pure function")]]
		static const SamplerContainer& ToNativeContainer(const ISamplerContainer& container);

		[[nodiscard("Pure function")]]
		static D3D12_SHADER_BYTECODE ToByteCode(std::span<const std::byte> byteCode) noexcept;

		template<typename Container, typename Range>
		void CopyViews(std::span<const Range> ranges, D3D12_DESCRIPTOR_HEAP_TYPE type);

		template<typename T> [[nodiscard("Pure function")]]
		std::shared_ptr<T> CreateCommandList(D3D12_COMMAND_LIST_TYPE type);
		template<typename CommandList, typename CommandListInterface>
		void Execute(std::span<const CommandListInterface* const> commandLists, const QueueSync& sync, CommandQueue& commandQueue);
		template<typename CommandList, typename CommandListInterface>
		static void GetCommandLists(std::span<const CommandListInterface* const> commandLists, std::span<ID3D12CommandList*> lists) noexcept;
		static void GetFences(std::span<const FenceValue> input, std::span<std::pair<ID3D12Fence*, UINT64>> output) noexcept;

		[[nodiscard("Pure function")]]
		static D3D12_COMMAND_QUEUE_DESC GetCommandQueueDesc(D3D12_COMMAND_LIST_TYPE type) noexcept;

		[[nodiscard("Pure function")]]
		SwapChainWrapper& GetSwapChain() const;

		[[nodiscard("Pure function")]]
		static Memory::Arena& Arena();

		static void ValidateSize(const BufferParams& params);
		static void ValidateDimension(const TextureParams& params);
		static void ValidateColorTexture(const TextureParams& params);
		static void ValidateDepthTexture(const TextureParams& params);
		static void ValidateAspect(Aspect aspect, DXGI_FORMAT format);
		static void ValidateCBVParams(const Buffer& buffer, const CBVParams& params);
		static void ValidateSRVParams(const Buffer& buffer, const BufferSRVParams& params);
		static void ValidateSRVParams(const Texture& texture, const TextureSRVParams& params);
		static void ValidateSRVParams(const TextureSRVParams& params, DXGI_FORMAT format, std::uint32_t maxMipCount, std::uint32_t maxArraySize);
		static void ValidateUAVParams(const Buffer& buffer, const BufferUAVParams& params);
		static void ValidateUAVParams(const Texture& texture, const TextureUAVParams& params);
		static void ValidateUAVParams(const TextureUAVParams& params, DXGI_FORMAT format, std::uint32_t maxMipCount, std::uint32_t maxArraySize);
		static void ValidateRTVParams(const Texture& texture, const RTVParams& params);
		static void ValidateRTVParams(const RTVParams& params, DXGI_FORMAT format, std::uint32_t maxMipCount, std::uint32_t maxArraySize);
		static void ValidateDSVParams(const Texture& texture, const DSVParams& params);
		static void ValidateDSVParams(const DSVParams& params, DXGI_FORMAT format, std::uint32_t maxMipCount, std::uint32_t maxArraySize);
		static void ValidateSize(const Buffer& buffer, std::uint64_t firstElementIndex, std::uint32_t elementCount, std::uint32_t stride);
		static void ValidateViewFormat(const Texture& texture, TextureFormatId viewFormat);
		static void ValidateDimension(const Texture& texture, TextureViewDimension dimension);
		static void ValidateDimension(const Texture& texture, TextureDimension dimension);
		static void ValidateDimension(const Texture& texture, DSVDimension dimension);
		static void ValidateLayout(const Texture& texture, const TextureSRVLayout& layout, TextureViewDimension dimension);
		static void ValidateLayout(const TextureSRVLayout& layout, TextureViewDimension dimension, std::uint32_t maxMipCount, std::uint32_t maxArraySize);
		static void ValidateLayout(const Texture& texture, const TextureUAVLayout& layout);
		static void ValidateLayout(const TextureUAVLayout& layout, std::uint32_t maxMipCount, std::uint32_t maxArraySize);
		static void ValidateLayout(const Texture& texture, const RTVLayout& layout);
		static void ValidateLayout(const RTVLayout& layout, std::uint32_t maxMipCount, std::uint32_t maxArraySize);
		static void ValidateLayout(const Texture& texture, const DSVLayout& layout);
		static void ValidateLayout(const DSVLayout& layout, std::uint32_t maxMipCount, std::uint32_t maxArraySize);
		static void ValidateMipRange(const Texture& texture, const MipRange& range);
		static void ValidateMipRange(const MipRange& range, std::uint32_t maxMipCount);
		static void ValidateArrayRange(const Texture& texture, const ArrayRange& range);
		static void ValidateArrayRange(const ArrayRange& range, std::uint32_t maxArraySize);
		static void ValidateSampleCount(const Texture& texture, bool shouldBeMS);
		static void ValidateSwapChainParams(const SwapChainParams& params);

		static void ValidateContainer(const ShaderDataContainer& container, std::uint32_t index);
		static void ValidateCopyRange(std::span<const ShaderDataCopyRange> ranges);
		static void ValidateContainer(const RenderTargetContainer& container, std::uint32_t index);
		static void ValidateCopyRange(std::span<const RenderTargetCopyRange> ranges);
		static void ValidateContainer(const DepthStencilContainer& container, std::uint32_t index);
		static void ValidateCopyRange(std::span<const DepthStencilCopyRange> ranges);
		static void ValidateContainer(const SamplerContainer& container, std::uint32_t index);
		static void ValidateCopyRange(std::span<const SamplerCopyRange> ranges);

		static void ValidatePipelineLayoutParams(const PipelineLayoutParams& params);
		static void ValidatePipelineLayoutSizes(const PipelineLayoutParams& params);
		static void ValidatePipelineLayoutOverlaps(std::span<const DescriptorSet> descriptorSets);

		static void ValidatePipelineLayout(const IPipelineLayout* layout);
		void ValidatePipelineStateParams(const GraphicsPipelineStateParams& params) const;
		static void ValidatePipelineStateParams(const ComputePipelineStateParams& params);

		template<typename CommandList, typename CommandListInterface>
		static void ValidateCommandLists(std::span<const CommandListInterface* const> commandLists);
		static void ValidateFences(std::span<const FenceValue> fences);

		// {132D4628-84F4-40F4-B72F-8A7B08C3C566}
		static constexpr GUID CreatorId = { 0x132d4628, 0x84f4, 0x40f4, { 0xb7, 0x2f, 0x8a, 0x7b, 0x8, 0xc3, 0xc5, 0x66 } };

		IRenderDeviceContext* renderDevice;

		TextureFormatMap textureFormatMap;

		Factory factory;
		Device device;

		CommandQueue graphicsCommandQueue;
		CommandQueue computeCommandQueue;
		CommandQueue copyCommandQueue;

		std::unique_ptr<SwapChainWrapper> swapChain;
	};
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	Engine::Engine(IRenderDeviceContext& renderDevice) :
		renderDevice{&renderDevice},
		textureFormatMap(*this->renderDevice),
		factory(*this->renderDevice),
		device(*this->renderDevice, *factory.GetMostPerformantAdapter()),
		graphicsCommandQueue(this->device.CreateCommandQueue(GetCommandQueueDesc(D3D12_COMMAND_LIST_TYPE_DIRECT), CreatorId)),
		computeCommandQueue(this->device.CreateCommandQueue(GetCommandQueueDesc(D3D12_COMMAND_LIST_TYPE_COMPUTE), CreatorId)),
		copyCommandQueue(this->device.CreateCommandQueue(GetCommandQueueDesc(D3D12_COMMAND_LIST_TYPE_COPY), CreatorId))
	{
	}

	std::shared_ptr<IBuffer> Engine::CreateBuffer(const HeapType heapType, const BufferParams& params)
	{
		ValidateSize(params);

		const D3D12_HEAP_PROPERTIES heapProperties = ToHeapProperties(heapType);
		const D3D12_HEAP_FLAGS heapFlags = ToHeapFlags(params.usage);
		const D3D12_RESOURCE_DESC1 resourceDesc = ToResourceDesc(params);
		Platform::Windows::ComPtr<ID3D12Resource2> resource = device.CreateResource(heapProperties, heapFlags, resourceDesc);

		return std::make_shared<Buffer>(std::move(resource), static_cast<std::uint64_t>(resourceDesc.Width), params.usage);
	}

	struct TextureFormatSupport Engine::TextureFormatSupport(const TextureFormatId textureFormatId) const
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

	TextureSupportResponse Engine::TextureSupport(const TextureSupportRequest& request) const
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

	std::shared_ptr<ITexture> Engine::CreateTexture(const HeapType heapType, const TextureParams& params)
	{
		ValidateDimension(params);
		DXGI_FORMAT format = GetFormat(params.format);
		const bool srgb = Any(TextureFlag::SRGB, params.flags);

		Memory::Arena& arena = Arena();
		arena.Free();
		auto castableFormats = Memory::Arena::Slice<DXGI_FORMAT>{};
		if (IsDepthStencilFormat(format))
		{
			ValidateDepthTexture(params);

			if (Any(TextureUsage::ShaderResource, params.usage))
			{
				if (HasStencil(format))
				{
					format = GetTypelessFormat(format);
				}
				else
				{
					castableFormats = arena.Allocate<DXGI_FORMAT>(1uz);
					const std::span<DXGI_FORMAT> formats = arena.Span(castableFormats);
					formats[0] = GetDepthViewFormat(format);
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

		return std::make_shared<Texture>(std::move(resource), params.format, format, params.castableFormats, 
			static_cast<std::uint32_t>(resourceDesc.Width), static_cast<std::uint32_t>(resourceDesc.Height), static_cast<std::uint16_t>(resourceDesc.DepthOrArraySize),
			static_cast<std::uint16_t>(resourceDesc.MipLevels), params.dimension, params.sampleCount, params.usage, srgb);
	}

	std::uint32_t Engine::GetCopyableFootprintCount(const TextureParams& params, const SubTextureRange& range) const
	{
		const auto [mipCount, arrayCount] = GetCopyableFootprintCount(params, range, GetFormat(params.format));
		return mipCount * arrayCount;
	}

	std::uint32_t Engine::GetCopyableFootprintCount(const ITexture& texture, const SubTextureRange& range) const
	{
		const D3D12_RESOURCE_DESC1 resourceDesc = ToNativeTexture(texture).Resource().GetDesc1();
		const auto [mipCount, arrayCount] = GetCopyableFootprintCount(resourceDesc, range);
		return mipCount * arrayCount;
	}

	CopyableFootprintSize Engine::GetCopyableFootprints(const TextureParams& params, const std::uint64_t offset, const SubTextureRange& range,
		const std::span<CopyableFootprint> footprints) const
	{
		const DXGI_FORMAT format = GetFormat(params.format);
		const CopyableFootprintInfo footprintCount = GetCopyableFootprintCount(params, range, format);
		const D3D12_RESOURCE_DESC1 resourceDesc = ToResourceDesc(params, format);
		return GetCopyableFootprints(resourceDesc, footprintCount, static_cast<UINT64>(offset), 
			static_cast<UINT16>(range.mipRange.mostDetailedMipIndex), static_cast<UINT16>(range.arrayRange.firstArrayIndex), range.aspect, footprints);
	}

	CopyableFootprintSize Engine::GetCopyableFootprints(const ITexture& texture, const std::uint64_t offset, const SubTextureRange& range,
		const std::span<CopyableFootprint> footprints) const
	{
		const D3D12_RESOURCE_DESC1 resourceDesc = ToNativeTexture(texture).Resource().GetDesc1();
		const CopyableFootprintInfo footprintCount = GetCopyableFootprintCount(resourceDesc, range);
		return GetCopyableFootprints(resourceDesc, footprintCount, static_cast<UINT64>(offset), 
			static_cast<UINT16>(range.mipRange.mostDetailedMipIndex), static_cast<UINT16>(range.arrayRange.firstArrayIndex), range.aspect, footprints);
	}

	std::shared_ptr<IShaderDataContainer> Engine::CreateShaderDataContainer(const ShaderDataContainerParams& params)
	{
		const D3D12_DESCRIPTOR_HEAP_DESC descriptorHeapDesc = ToDescriptorHeapDesc(params);
		return std::make_shared<ShaderDataContainer>(device.CreateDescriptorHeap(descriptorHeapDesc), device.GetDescriptorHandleIncrement(descriptorHeapDesc.Type),
			params.size, params.shaderVisible);
	}

	void Engine::CreateView(const IBuffer* const buffer, IShaderDataContainer& container, const std::uint32_t index, const CBVParams& params)
	{
		const Buffer* const nativeBuffer = ToNativeBuffer(buffer);
		if (nativeBuffer)
		{
			ValidateCBVParams(*nativeBuffer, params);
		}

		ShaderDataContainer& nativeContainer = ToNativeContainer(container);
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

	void Engine::CreateView(const IBuffer* const buffer, IShaderDataContainer& container, const std::uint32_t index, const BufferSRVParams& params)
	{
		const Buffer* const nativeBuffer = ToNativeBuffer(buffer);
		if (nativeBuffer)
		{
			ValidateSRVParams(*nativeBuffer, params);
		}

		ShaderDataContainer& nativeContainer = ToNativeContainer(container);
		ValidateContainer(nativeContainer, index);
		const D3D12_CPU_DESCRIPTOR_HANDLE handle = nativeContainer.CpuHandle(static_cast<UINT>(index));

		const D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = ToSRVDesc(params);
		device.CreateSRV(nativeBuffer ? &nativeBuffer->Resource() : nullptr, srvDesc, handle);

		nativeContainer.Set(index, BufferSRVMeta{.resource = nativeBuffer, .params = params});
	}

	void Engine::CreateView(const ITexture* const texture, IShaderDataContainer& container, const std::uint32_t index, const TextureSRVParams& params)
	{
		const Texture* const nativeTexture = ToNativeTexture(texture);
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

		ShaderDataContainer& nativeContainer = ToNativeContainer(container);
		ValidateContainer(nativeContainer, index);
		const D3D12_CPU_DESCRIPTOR_HANDLE handle = nativeContainer.CpuHandle(static_cast<UINT>(index));

		const DXGI_FORMAT viewFormat = GetViewFormat(format, params.aspect);
		const D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = ToSRVDesc(params, viewFormat, mipCount, arraySize);
		device.CreateSRV(nativeTexture ? &nativeTexture->Resource() : nullptr, srvDesc, handle);

		nativeContainer.Set(index, TextureSRVMeta{.resource = nativeTexture, .params = params});
	}

	void Engine::CreateView(const IBuffer* const buffer, IShaderDataContainer& container, const std::uint32_t index, const BufferUAVParams& params)
	{
		const Buffer* const nativeBuffer = ToNativeBuffer(buffer);
		if (nativeBuffer)
		{
			ValidateUAVParams(*nativeBuffer, params);
		}

		ShaderDataContainer& nativeContainer = ToNativeContainer(container);
		ValidateContainer(nativeContainer, index);
		const D3D12_CPU_DESCRIPTOR_HANDLE handle = nativeContainer.CpuHandle(static_cast<UINT>(index));

		const D3D12_UNORDERED_ACCESS_VIEW_DESC uavDesc = ToUAVDesc(params);
		device.CreateUAV(nativeBuffer ? &nativeBuffer->Resource() : nullptr, uavDesc, handle);

		nativeContainer.Set(index, BufferUAVMeta{.resource = nativeBuffer, .params = params});
	}

	void Engine::CreateView(const ITexture* const texture, IShaderDataContainer& container, const std::uint32_t index, const TextureUAVParams& params)
	{
		const Texture* const nativeTexture = ToNativeTexture(texture);
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

		ShaderDataContainer& nativeContainer = ToNativeContainer(container);
		ValidateContainer(nativeContainer, index);
		const D3D12_CPU_DESCRIPTOR_HANDLE handle = nativeContainer.CpuHandle(static_cast<UINT>(index));

		const DXGI_FORMAT viewFormat = GetViewFormat(format, params.aspect);
		const D3D12_UNORDERED_ACCESS_VIEW_DESC uavDesc = ToUAVDesc(params, viewFormat, arraySize);
		device.CreateUAV(nativeTexture ? &nativeTexture->Resource() : nullptr, uavDesc, handle);

		nativeContainer.Set(index, TextureUAVMeta{.resource = nativeTexture, .params = params});
	}

	void Engine::CopyViews(const std::span<const ShaderDataCopyRange> ranges)
	{
		CopyViews<ShaderDataContainer>(ranges, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	}

	std::shared_ptr<IRenderTargetContainer> Engine::CreateRenderTargetContainer(const RenderTargetContainerParams& params)
	{
		const D3D12_DESCRIPTOR_HEAP_DESC descriptorHeapDesc = ToDescriptorHeapDesc(params);
		return std::make_shared<RenderTargetContainer>(device.CreateDescriptorHeap(descriptorHeapDesc), device.GetDescriptorHandleIncrement(descriptorHeapDesc.Type), params.size);
	}

	void Engine::CreateView(const ITexture* texture, IRenderTargetContainer& container, const std::uint32_t index, const RTVParams& params)
	{
		const Texture* const nativeTexture = ToNativeTexture(texture);
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

		RenderTargetContainer& nativeContainer = ToNativeContainer(container);
		ValidateContainer(nativeContainer, index);
		const D3D12_CPU_DESCRIPTOR_HANDLE handle = nativeContainer.CpuHandle(static_cast<UINT>(index));

		const D3D12_RENDER_TARGET_VIEW_DESC rtvDesc = ToRTVDesc(params, format, arraySize);
		device.CreateRTV(nativeTexture ? &nativeTexture->Resource() : nullptr, rtvDesc, handle);

		nativeContainer.Set(index, RenderTargetTextureMeta{.texture = nativeTexture, .params = params});
	}

	void Engine::CopyViews(const std::span<const RenderTargetCopyRange> ranges)
	{
		CopyViews<RenderTargetContainer>(ranges, D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	}

	std::shared_ptr<IDepthStencilContainer> Engine::CreateDepthStencilContainer(const DepthStencilContainerParams& params)
	{
		const D3D12_DESCRIPTOR_HEAP_DESC descriptorHeapDesc = ToDescriptorHeapDesc(params);
		return std::make_shared<DepthStencilContainer>(device.CreateDescriptorHeap(descriptorHeapDesc), device.GetDescriptorHandleIncrement(descriptorHeapDesc.Type), params.size);
	}

	void Engine::CreateView(const ITexture* const texture, IDepthStencilContainer& container, const std::uint32_t index, const DSVParams& params)
	{
		const Texture* const nativeTexture = ToNativeTexture(texture);
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

		DepthStencilContainer& nativeContainer = ToNativeContainer(container);
		ValidateContainer(nativeContainer, index);
		const D3D12_CPU_DESCRIPTOR_HANDLE handle = nativeContainer.CpuHandle(static_cast<UINT>(index));

		const D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = ToDSVDesc(params, format, arraySize);
		device.CreateDSV(nativeTexture ? &nativeTexture->Resource() : nullptr, dsvDesc, handle);

		nativeContainer.Set(index, DepthStencilTextureMeta{.texture = nativeTexture, .params = params});
	}

	void Engine::CopyViews(const std::span<const DepthStencilCopyRange> ranges)
	{
		CopyViews<DepthStencilContainer>(ranges, D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
	}

	std::shared_ptr<ISamplerContainer> Engine::CreateSamplerContainer(const SamplerContainerParams& params)
	{
		const D3D12_DESCRIPTOR_HEAP_DESC descriptorHeapDesc = ToDescriptorHeapDesc(params);
		return std::make_shared<SamplerContainer>(device.CreateDescriptorHeap(descriptorHeapDesc), device.GetDescriptorHandleIncrement(descriptorHeapDesc.Type), 
			params.size, params.shaderVisible);
	}

	void Engine::CreateSampler(ISamplerContainer& container, const std::uint32_t index, const SamplerParams& params)
	{
		SamplerContainer& nativeContainer = ToNativeContainer(container);
		ValidateContainer(nativeContainer, index);
		const D3D12_CPU_DESCRIPTOR_HANDLE handle = nativeContainer.CpuHandle(static_cast<UINT>(index));

		const D3D12_SAMPLER_DESC2 samplerDesc = ToSamplerDesc(params);
		device.CreateSampler(samplerDesc, handle);

		nativeContainer.Set(index, params);
	}

	void Engine::CopySamplers(const std::span<const SamplerCopyRange> ranges)
	{
		CopyViews<SamplerContainer>(ranges, D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER);
	}

	Meta::Version Engine::ShaderIRVersion() const
	{
		const auto shaderModel = std::to_underlying(device.GetShaderModel());
		return Meta::Version(shaderModel / 0xF, shaderModel & 0xF);
	}

	ShaderScalarTypeMask Engine::ScalarTypeSupport() const
	{
		auto answer = ShaderScalarTypeMask::Int32 | ShaderScalarTypeMask::Float32;
		if (device.IsIntFloat16Supported())
		{
			answer |= ShaderScalarTypeMask::Int16 | ShaderScalarTypeMask::Float16;
		}
		if constexpr (Device::Int64BitSupport)
		{
			answer |= ShaderScalarTypeMask::Int64;
		}
		if (device.IsFloat64Supported())
		{
			answer |= ShaderScalarTypeMask::Float64;
		}

		return answer;
	}

	ShaderScalarTypeMask Engine::ToAtomicScalarTypeSupport(const AtomicSupport& support) noexcept
	{
		auto answer = ShaderScalarTypeMask::Int32 | ShaderScalarTypeMask::Float32;
		if (support.atomicInt64 && support.atomicInt64OnDescriptorHeap) // The engine doesn't support direct views.
		{
			answer |= ShaderScalarTypeMask::Int64;
		}

		return answer;
	}

	ShaderScalarTypeMask Engine::ToGroupSharedAtomicScalarTypeSupport(const AtomicSupport& support) noexcept
	{
		auto answer = ShaderScalarTypeMask::Int32 | ShaderScalarTypeMask::Float32;
		if (support.groupSharedAtomicInt64)
		{
			answer |= ShaderScalarTypeMask::Int64;
		}

		return answer;
	}

	LineRasterizationModeMask Engine::LineRasterizationSupport() const
	{
		auto answer = LineRasterizationModeMask::Aliased | LineRasterizationModeMask::AlphaAntialiased | LineRasterizationModeMask::QuadrilateralWide;
		if (device.IsQuadrilateralNarrowLineSupported())
		{
			answer |= LineRasterizationModeMask::QuadrilateralNarrow;
		}

		return answer;
	}

	struct ShaderSupport Engine::ShaderSupport() const
	{
		const AtomicSupport atomicSupport = device.AtomicSupport();

		return RenderDevice::ShaderSupport
		{
			.shaderIRName = ShaderIRName,
			.version = ShaderIRVersion(),
			.scalarTypes = ScalarTypeSupport(),
			.atomicTypes = ToAtomicScalarTypeSupport(atomicSupport),
			.groupSharedAtomicTypes = ToGroupSharedAtomicScalarTypeSupport(atomicSupport),
			.simultaneousTargetCount = SimultaneousTargetCount
		};
	}

	struct RasterizerSupport Engine::RasterizerSupport() const
	{
		return RenderDevice::RasterizerSupport
		{
			.lineRasterizationModes = LineRasterizationSupport(),
			.conservativeRasterization = Device::ConservativeRasterizationSupport
		};
	}

	std::shared_ptr<IPipelineLayout> Engine::CreatePipelineLayout(const PipelineLayoutParams& params)
	{
		ValidatePipelineLayoutParams(params);

		Memory::Arena& arena = Arena();
		arena.Free();
		const RootSignatureDescCounts rootSigDescCounts = GetRootSignatureCounts(params.descriptorSets);
		const Memory::Arena::Slice<D3D12_ROOT_PARAMETER1> parameters = arena.Allocate<D3D12_ROOT_PARAMETER1>(static_cast<std::size_t>(rootSigDescCounts.tableCount));
		const Memory::Arena::Slice<D3D12_DESCRIPTOR_RANGE1> ranges = arena.Allocate<D3D12_DESCRIPTOR_RANGE1>(static_cast<std::size_t>(rootSigDescCounts.rangeCount));
		const Memory::Arena::Slice<D3D12_STATIC_SAMPLER_DESC> staticSamplers = arena.Allocate<D3D12_STATIC_SAMPLER_DESC>(static_cast<std::size_t>(rootSigDescCounts.staticSamplerCount));
		const std::span<D3D12_ROOT_PARAMETER1> parametersSpan = arena.Span(parameters);
		const std::span<D3D12_DESCRIPTOR_RANGE1> rangesSpan = arena.Span(ranges);
		const std::span<D3D12_STATIC_SAMPLER_DESC> staticSamplersSpan = arena.Span(staticSamplers);

		const D3D12_ROOT_SIGNATURE_DESC1 rootSigDesc = ToRootSignatureDesc(params, parametersSpan, rangesSpan, staticSamplersSpan);
		return std::make_shared<RootSignature>(device.CreateRootSignature(rootSigDesc), params);
	}

	std::shared_ptr<IGraphicsPipelineState> Engine::CreateGraphicsPipelineState(const std::shared_ptr<const IPipelineLayout>& layout, 
		const GraphicsPipelineStateParams& params)
	{
		ValidatePipelineLayout(layout.get());
		ValidatePipelineStateParams(params);

		Memory::Arena& arena = Arena();
		arena.Free();

		if (layout)
		{
			const Memory::Arena::Slice<PipelineStateSubobjectRootSignature> rootSignature = arena.Allocate<PipelineStateSubobjectRootSignature>(1u);
			arena.Span(rootSignature)[0] = &static_cast<const RootSignature&>(*layout).GetRootSignature();
		}

		if (!params.amplificationShader.empty())
		{
			const Memory::Arena::Slice<PipelineStateSubobjectAmplificationShader> amplificationShader = arena.Allocate<PipelineStateSubobjectAmplificationShader>(1u);
			arena.Span(amplificationShader)[0] = ToByteCode(params.amplificationShader);
		}
		const Memory::Arena::Slice<PipelineStateSubobjectMeshShader> meshShader = arena.Allocate<PipelineStateSubobjectMeshShader>(1u);
		arena.Span(meshShader)[0] = ToByteCode(params.meshShader);
		if (!params.pixelShader.empty())
		{
			const Memory::Arena::Slice<PipelineStateSubobjectPixelShader> pixelShader = arena.Allocate<PipelineStateSubobjectPixelShader>(1u);
			arena.Span(pixelShader)[0] = ToByteCode(params.pixelShader);
		}

		const Memory::Arena::Slice<PipelineStateSubobjectRasterizer> rasterizer = arena.Allocate<PipelineStateSubobjectRasterizer>(1u);
		arena.Span(rasterizer)[0] = ToRasterizerDesc(params.rasterizer);

		if (!params.attachmentParams.renderTargetFormats.empty())
		{
			const Memory::Arena::Slice<PipelineStateSubobjectBlend> blend = arena.Allocate<PipelineStateSubobjectBlend>(1u);
			arena.Span(blend)[0] = ToBlendDesc(params);
			const Memory::Arena::Slice<PipelineStateSubobjectRenderTargetFormats> rtFormats = arena.Allocate<PipelineStateSubobjectRenderTargetFormats>(1u);
			arena.Span(rtFormats)[0] = D3D12_RT_FORMAT_ARRAY{.NumRenderTargets = static_cast<UINT>(params.attachmentParams.renderTargetFormats.size())};
			D3D12_RT_FORMAT_ARRAY& rtArray = arena.Span(rtFormats)[0].Data();
			for (std::size_t i = 0uz; i < std::min(std::size(rtArray.RTFormats), params.attachmentParams.renderTargetFormats.size()); ++i)
			{
				rtArray.RTFormats[i] = GetFormat(params.attachmentParams.renderTargetFormats[i]);
			}
		}

		if (params.attachmentParams.depthStencilFormat)
		{
			const Memory::Arena::Slice<PipelineStateSubobjectDepthStencil> depthStencil = arena.Allocate<PipelineStateSubobjectDepthStencil>(1u);
			arena.Span(depthStencil)[0] = ToDepthStencilDesc(params.depthStencil);
			const Memory::Arena::Slice<PipelineStateSubobjectDepthStencilFormat> dsFormat = arena.Allocate<PipelineStateSubobjectDepthStencilFormat>(1u);
			arena.Span(dsFormat)[0] = GetFormat(*params.attachmentParams.depthStencilFormat);
		}

		const Memory::Arena::Slice<PipelineStateSubobjectSampleDesc> sampleDesc = arena.Allocate<PipelineStateSubobjectSampleDesc>(1u);
		arena.Span(sampleDesc)[0] = DXGI_SAMPLE_DESC{.Count = static_cast<UINT>(ToNumber(params.sample.sampleCount)), .Quality = 0u};
		const Memory::Arena::Slice<PipelineStateSubobjectSampleMask> sampleMask = arena.Allocate<PipelineStateSubobjectSampleMask>(1u);
		arena.Span(sampleMask)[0] = static_cast<UINT>(params.sample.sampleMask);

		const Memory::Arena::Slice<PipelineStateSubobjectFlags> flags = arena.Allocate<PipelineStateSubobjectFlags>(1u);
		arena.Span(flags)[0] = D3D12_PIPELINE_STATE_FLAG_DYNAMIC_DEPTH_BIAS;

		const auto pipelineStateStream = D3D12_PIPELINE_STATE_STREAM_DESC
		{
			.SizeInBytes = static_cast<SIZE_T>(arena.Size()),
			.pPipelineStateSubobjectStream = arena.Data()
		};
		return std::make_shared<GraphicsPipelineState>(device.CreatePipelineState(pipelineStateStream), layout, params);
	}

	std::shared_ptr<IComputePipelineState> Engine::CreateComputePipelineState(const std::shared_ptr<const IPipelineLayout>& layout, const ComputePipelineStateParams& params)
	{
		ValidatePipelineLayout(layout.get());
		ValidatePipelineStateParams(params);

		Memory::Arena& arena = Arena();
		arena.Free();

		if (layout)
		{
			const Memory::Arena::Slice<PipelineStateSubobjectRootSignature> rootSignature = arena.Allocate<PipelineStateSubobjectRootSignature>(1u);
			arena.Span(rootSignature)[0] = &static_cast<const RootSignature&>(*layout).GetRootSignature();
		}

		const Memory::Arena::Slice<PipelineStateSubobjectComputeShader> computeShader = arena.Allocate<PipelineStateSubobjectComputeShader>(1u);
		arena.Span(computeShader)[0] = ToByteCode(params.computeShader);

		const auto pipelineStateStream = D3D12_PIPELINE_STATE_STREAM_DESC
		{
			.SizeInBytes = static_cast<SIZE_T>(arena.Size()),
			.pPipelineStateSubobjectStream = arena.Data()
		};
		return std::make_shared<ComputePipelineState>(device.CreatePipelineState(pipelineStateStream), layout);
	}

	std::shared_ptr<IGraphicsCommandList> Engine::CreateGraphicsCommandList()
	{
		return CreateCommandList<GraphicsCommandList>(D3D12_COMMAND_LIST_TYPE_DIRECT);
	}

	std::shared_ptr<IComputeCommandList> Engine::CreateComputeCommandList()
	{
		return CreateCommandList<ComputeCommandList>(D3D12_COMMAND_LIST_TYPE_COMPUTE);
	}

	std::shared_ptr<ICopyCommandList> Engine::CreateCopyCommandList()
	{
		return CreateCommandList<CopyCommandList>(D3D12_COMMAND_LIST_TYPE_COPY);
	}

	void Engine::Execute(const std::span<const IGraphicsCommandList* const> commandLists, const QueueSync& sync)
	{
		Execute<GraphicsCommandList>(commandLists, sync, graphicsCommandQueue);
	}

	void Engine::Execute(const std::span<const IComputeCommandList* const> commandLists, const QueueSync& sync)
	{
		Execute<ComputeCommandList>(commandLists, sync, computeCommandQueue);
	}

	void Engine::Execute(const std::span<const ICopyCommandList* const> commandLists, const QueueSync& sync)
	{
		Execute<CopyCommandList>(commandLists, sync, copyCommandQueue);
	}

	std::shared_ptr<ISecondaryGraphicsCommandList> Engine::CreateSecondaryGraphicsCommandList()
	{
		return CreateCommandList<BundleCommandList>(D3D12_COMMAND_LIST_TYPE_BUNDLE);
	}

	std::shared_ptr<IFence> Engine::CreateFence()
	{
		return std::make_shared<Fence>(device.CreateFence());
	}

	std::shared_ptr<IWaiter> Engine::CreateWaiter()
	{
		return std::make_shared<Waiter>();
	}

	struct SwapChainSupport Engine::SwapChainSupport() const
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

	bool Engine::IsSwapChainAlive() const
	{
		return static_cast<bool>(swapChain);
	}

	void Engine::CreateSwapChain(const SwapChainParams& params)
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

		auto dxgiSwapChain = SwapChain(factory.CreateSwapChain(graphicsCommandQueue.GetCommandQueue(), windowHandle, swapChainDesc));
		factory.MakeWindowAssociation(windowHandle);
		dxgiSwapChain.SetFullscreenState(false);

		auto buffers = std::vector<std::shared_ptr<Texture>>(params.bufferCount);
		for (UINT i = 0u; i < params.bufferCount; ++i)
		{
			Platform::Windows::ComPtr<ID3D12Resource2> resource = dxgiSwapChain.GetBuffer<ID3D12Resource2>(i);
			buffers[i] = std::make_shared<Texture>(std::move(resource), params.format, format, std::span<const TextureFormatId>(),
				static_cast<std::uint32_t>(swapChainDesc.Width), static_cast<std::uint32_t>(swapChainDesc.Height), 1u, 1u,
				TextureDimension::Texture2D, SampleCount::X1, params.usage, srgb);
		}

		swapChain = std::make_unique<SwapChainWrapper>(std::move(dxgiSwapChain), std::move(buffers), ToSyncInterval(params.syncMode), ToPresentFlags(params.syncMode));
	}

	void Engine::DestroySwapChain()
	{
		swapChain.reset();
	}

	std::uint8_t Engine::SwapChainBufferCount() const
	{
		return static_cast<std::uint8_t>(GetSwapChain().BufferCount());
	}

	std::uint8_t Engine::CurrentSwapChainBufferIndex() const
	{
		return static_cast<std::uint8_t>(GetSwapChain().GetCurrentBufferIndex());
	}

	std::shared_ptr<ITexture> Engine::SwapChainBuffer(const std::uint8_t bufferIndex) const
	{
		return GetSwapChain().GetBuffer(bufferIndex);
	}

	void Engine::PresentNextSwapChainBuffer()
	{
		GetSwapChain().Present();
	}

	TextureSupportResponse Engine::MakeResponse(const DXGI_FORMAT format, const TextureSupportRequest& request,
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

	SampleCountMask Engine::GetSampleCountMask(const DXGI_FORMAT format, const TextureSupportRequest& request, 
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

	Engine::CopyableFootprintInfo Engine::GetCopyableFootprintCount(const TextureParams& params, const SubTextureRange& range, const DXGI_FORMAT format)
	{
		ValidateDimension(params);
		ValidateAspect(range.aspect, format);

		return GetCopyableFootprintCount(params.mipCount, params.arraySize, range);
	}

	Engine::CopyableFootprintInfo Engine::GetCopyableFootprintCount(const D3D12_RESOURCE_DESC1& resourceDesc, const SubTextureRange& range)
	{
		ValidateAspect(range.aspect, resourceDesc.Format);

		const UINT16 arraySize = GetArraySize(resourceDesc);
		return GetCopyableFootprintCount(static_cast<std::uint32_t>(resourceDesc.MipLevels), static_cast<std::uint32_t>(arraySize), range);
	}

	Engine::CopyableFootprintInfo Engine::GetCopyableFootprintCount(const std::uint32_t resourceMipCount, const std::uint32_t resourceArrayCount, const SubTextureRange& range)
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

	CopyableFootprintSize Engine::GetCopyableFootprints(const D3D12_RESOURCE_DESC1& resourceDesc, const CopyableFootprintInfo& footprintCountInfo, const UINT64 offset, 
		const UINT16 mostDetailedMipIndex, const UINT16 firstArrayIndex, const Aspect aspect, const std::span<CopyableFootprint> footprints) const
	{
		const std::uint32_t footprintCount = footprintCountInfo.mipCount * footprintCountInfo.arrayCount;
#ifndef NDEBUG
		if (footprints.size() != 0uz && footprints.size() != footprintCount) [[unlikely]]
		{
			throw std::invalid_argument("Invalid footprints count");
		}
#endif

		Memory::Arena& arena = Arena();
		arena.Free();
		const Memory::Arena::Slice<D3D12_PLACED_SUBRESOURCE_FOOTPRINT> subresourceFootprints = arena.Allocate<D3D12_PLACED_SUBRESOURCE_FOOTPRINT>(footprintCount);
		const Memory::Arena::Slice<UINT> rowCounts = arena.Allocate<UINT>(footprintCount);
		const Memory::Arena::Slice<UINT64> rowSizes = arena.Allocate<UINT64>(footprintCount);
		const std::span<D3D12_PLACED_SUBRESOURCE_FOOTPRINT> subresourceFootprintsSpan = arena.Span(subresourceFootprints);
		const std::span<UINT> rowCountsSpan = arena.Span(rowCounts);
		const std::span<UINT64> rowSizesSpan = arena.Span(rowSizes);

		const UINT8 planeIndex = ToPlaneIndex(aspect);
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

	DXGI_FORMAT Engine::GetFormat(const TextureFormatId format) const
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

	DXGI_FORMAT Engine::GetViewFormat(const DXGI_FORMAT format, const Aspect aspect) noexcept
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

	DXGI_FORMAT Engine::GetViewFormat(const TextureFormatId format, const Aspect aspect) const
	{
		return GetViewFormat(GetFormat(format), aspect);
	}

	std::uint32_t Engine::GetMaxArraySize(const TextureDimension dimension) noexcept
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

	std::uint32_t Engine::GetMaxArraySize(const TextureViewDimension dimension) noexcept
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

	std::uint32_t Engine::GetMaxArraySize(const DSVDimension dimension) noexcept
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

	Buffer& Engine::ToNativeBuffer(IBuffer& buffer)
	{
#ifndef NDEBUG
		if (typeid(buffer) != typeid(Buffer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid buffer");
		}
#endif

		return static_cast<Buffer&>(buffer);
	}

	const Buffer& Engine::ToNativeBuffer(const IBuffer& buffer)
	{
#ifndef NDEBUG
		if (typeid(buffer) != typeid(Buffer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid buffer");
		}
#endif

		return static_cast<const Buffer&>(buffer);
	}

	Buffer* Engine::ToNativeBuffer(IBuffer* const buffer)
	{
#ifndef NDEBUG
		if (buffer != nullptr && typeid(*buffer) != typeid(Buffer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid buffer");
		}
#endif

		return static_cast<Buffer*>(buffer);
	}

	const Buffer* Engine::ToNativeBuffer(const IBuffer* const buffer)
	{
#ifndef NDEBUG
		if (buffer != nullptr && typeid(*buffer) != typeid(Buffer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid buffer");
		}
#endif

		return static_cast<const Buffer*>(buffer);
	}

	Texture& Engine::ToNativeTexture(ITexture& texture)
	{
#ifndef NDEBUG
		if (typeid(texture) != typeid(Texture)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid texture");
		}
#endif

		return static_cast<Texture&>(texture);
	}

	const Texture& Engine::ToNativeTexture(const ITexture& texture)
	{
#ifndef NDEBUG
		if (typeid(texture) != typeid(Texture)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid texture");
		}
#endif

		return static_cast<const Texture&>(texture);
	}

	Texture* Engine::ToNativeTexture(ITexture* const texture)
	{
#ifndef NDEBUG
		if (texture != nullptr && typeid(texture) != typeid(Texture)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid texture");
		}
#endif

		return static_cast<Texture*>(texture);
	}

	const Texture* Engine::ToNativeTexture(const ITexture* const texture)
	{
#ifndef NDEBUG
		if (texture != nullptr && typeid(texture) != typeid(Texture)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid texture");
		}
#endif

		return static_cast<const Texture*>(texture);
	}

	ShaderDataContainer& Engine::ToNativeContainer(IShaderDataContainer& container)
	{
#ifndef NDEBUG
		if (typeid(container) != typeid(ShaderDataContainer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid container");
		}
#endif

		return static_cast<ShaderDataContainer&>(container);
	}

	const ShaderDataContainer& Engine::ToNativeContainer(const IShaderDataContainer& container)
	{
#ifndef NDEBUG
		if (typeid(container) != typeid(ShaderDataContainer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid container");
		}
#endif

		return static_cast<const ShaderDataContainer&>(container);
	}

	RenderTargetContainer& Engine::ToNativeContainer(IRenderTargetContainer& container)
	{
#ifndef NDEBUG
		if (typeid(container) != typeid(RenderTargetContainer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid container");
		}
#endif

		return static_cast<RenderTargetContainer&>(container);
	}

	const RenderTargetContainer& Engine::ToNativeContainer(const IRenderTargetContainer& container)
	{
#ifndef NDEBUG
		if (typeid(container) != typeid(RenderTargetContainer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid container");
		}
#endif

		return static_cast<const RenderTargetContainer&>(container);
	}

	DepthStencilContainer& Engine::ToNativeContainer(IDepthStencilContainer& container)
	{
#ifndef NDEBUG
		if (typeid(container) != typeid(DepthStencilContainer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid container");
		}
#endif

		return static_cast<DepthStencilContainer&>(container);
	}

	const DepthStencilContainer& Engine::ToNativeContainer(const IDepthStencilContainer& container)
	{
#ifndef NDEBUG
		if (typeid(container) != typeid(DepthStencilContainer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid container");
		}
#endif

		return static_cast<const DepthStencilContainer&>(container);
	}

	SamplerContainer& Engine::ToNativeContainer(ISamplerContainer& container)
	{
#ifndef NDEBUG
		if (typeid(container) != typeid(SamplerContainer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid container");
		}
#endif

		return static_cast<SamplerContainer&>(container);
	}

	const SamplerContainer& Engine::ToNativeContainer(const ISamplerContainer& container)
	{
#ifndef NDEBUG
		if (typeid(container) != typeid(SamplerContainer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid container");
		}
#endif

		return static_cast<const SamplerContainer&>(container);
	}

	D3D12_SHADER_BYTECODE Engine::ToByteCode(const std::span<const std::byte> byteCode) noexcept
	{
		return D3D12_SHADER_BYTECODE{.pShaderBytecode = byteCode.data(), .BytecodeLength = static_cast<SIZE_T>(byteCode.size())};
	}

	template<typename Container, typename Range>
	void Engine::CopyViews(const std::span<const Range> ranges, const D3D12_DESCRIPTOR_HEAP_TYPE type)
	{
		ValidateCopyRange(ranges);

		Memory::Arena& arena = Arena();
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
	std::shared_ptr<T> Engine::CreateCommandList(const D3D12_COMMAND_LIST_TYPE type)
	{
		return std::make_shared<T>(device.CreateCommandAllocator(type), device.CreateCommandList(type));
	}

	template<typename CommandList, typename CommandListInterface>
	void Engine::Execute(const std::span<const CommandListInterface* const> commandLists, const QueueSync& sync, CommandQueue& commandQueue)
	{
		ValidateCommandLists<CommandList, CommandListInterface>(commandLists);
		ValidateFences(sync.before);
		ValidateFences(sync.after);

		Memory::Arena& arena = Arena();
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
	void Engine::GetCommandLists(const std::span<const CommandListInterface* const> commandLists, const std::span<ID3D12CommandList*> lists) noexcept
	{
		assert(commandLists.size() == lists.size() && "Input and output sizes are not the same.");
		for (std::size_t i = 0uz; i < commandLists.size(); ++i)
		{
			lists[i] = &static_cast<const CommandList*>(commandLists[i])->CommandList();
		}
	}

	void Engine::GetFences(const std::span<const FenceValue> input, const std::span<std::pair<ID3D12Fence*, UINT64>> output) noexcept
	{
		assert(input.size() == output.size() && "Input and output sizes are not the same.");
		for (std::size_t i = 0uz; i < input.size(); ++i)
		{
			output[i] = std::pair(&static_cast<const Fence*>(input[i].fence)->GetFence(), static_cast<UINT64>(input[i].value));
		}
	}

	D3D12_COMMAND_QUEUE_DESC Engine::GetCommandQueueDesc(const D3D12_COMMAND_LIST_TYPE type) noexcept
	{
		return D3D12_COMMAND_QUEUE_DESC
		{
			.Type = type,
			.Priority = D3D12_COMMAND_QUEUE_PRIORITY_HIGH,
			.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE,
			.NodeMask = 0u
		};
	}

	SwapChainWrapper& Engine::GetSwapChain() const
	{
#ifndef NDEBUG
		if (!swapChain) [[unlikely]]
		{
			throw std::logic_error("Swap chain is not created");
		}
#endif

		return *swapChain;
	}

	Memory::Arena& Engine::Arena()
	{
		thread_local auto arena = Memory::Arena(0uz, 1024uz);
		return arena;
	}

	void Engine::ValidateSize(const BufferParams& params)
	{
#ifndef NDEBUG
		if (params.size == 0uz) [[unlikely]]
		{
			throw std::invalid_argument("Invalid size");
		}
#endif
	}

	void Engine::ValidateDimension(const TextureParams& params)
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

	void Engine::ValidateColorTexture(const TextureParams& params)
	{
#ifndef NDEBUG
		if (Any(TextureUsage::DepthStencil, params.usage)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid usage");
		}
#endif
	}

	void Engine::ValidateDepthTexture(const TextureParams& params)
	{
#ifndef NDEBUG
		if (!params.castableFormats.empty()) [[unlikely]]
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

	void Engine::ValidateAspect(const Aspect aspect, const DXGI_FORMAT format)
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
			if (!HasStencil(format)) [[unlikely]]
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

	void Engine::ValidateCBVParams(const Buffer& buffer, const CBVParams& params)
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

	void Engine::ValidateSRVParams(const Buffer& buffer, const BufferSRVParams& params)
	{
		ValidateSize(buffer, params.firstElementIndex, params.elementCount, params.stride);

#ifndef NDEBUG
		if (None(BufferUsage::ShaderResource, buffer.Usage())) [[unlikely]]
		{
			throw std::invalid_argument("Invalid buffer usage");
		}
#endif
	}

	void Engine::ValidateSRVParams(const Texture& texture, const TextureSRVParams& params)
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

	void Engine::ValidateSRVParams(const TextureSRVParams& params, const DXGI_FORMAT format, const std::uint32_t maxMipCount, const std::uint32_t maxArraySize)
	{
		ValidateAspect(params.aspect, format);
		ValidateLayout(params.layout, params.dimension, maxMipCount, maxArraySize);
	}

	void Engine::ValidateUAVParams(const Buffer& buffer, const BufferUAVParams& params)
	{
		ValidateSize(buffer, params.firstElementIndex, params.elementCount, params.stride);

#ifndef NDEBUG
		if (None(BufferUsage::UnorderedAccess, buffer.Usage())) [[unlikely]]
		{
			throw std::invalid_argument("Invalid buffer usage");
		}
#endif
	}

	void Engine::ValidateUAVParams(const Texture& texture, const TextureUAVParams& params)
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

	void Engine::ValidateUAVParams(const TextureUAVParams& params, const DXGI_FORMAT format, const std::uint32_t maxMipCount, const std::uint32_t maxArraySize)
	{
		ValidateAspect(params.aspect, format);
		ValidateLayout(params.layout, maxMipCount, maxArraySize);
	}

	void Engine::ValidateRTVParams(const Texture& texture, const RTVParams& params)
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

	void Engine::ValidateRTVParams(const RTVParams& params, const DXGI_FORMAT format, const std::uint32_t maxMipCount, const std::uint32_t maxArraySize)
	{
		ValidateAspect(Aspect::Color, format);
		ValidateLayout(params.layout, maxMipCount, maxArraySize);
	}

	void Engine::ValidateDSVParams(const Texture& texture, const DSVParams& params)
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

	void Engine::ValidateDSVParams(const DSVParams& params, const DXGI_FORMAT format, const std::uint32_t maxMipCount, const std::uint32_t maxArraySize)
	{
		ValidateAspect(Aspect::Depth, format);
		ValidateLayout(params.layout, maxMipCount, maxArraySize);
	}

	void Engine::ValidateSize(const Buffer& buffer, const std::uint64_t firstElementIndex, const std::uint32_t elementCount, const std::uint32_t stride)
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

	void Engine::ValidateViewFormat(const Texture& texture, const TextureFormatId viewFormat)
	{
#ifndef NDEBUG
		if (texture.Format() != viewFormat && std::ranges::find(texture.CastableFormats(), viewFormat) == texture.CastableFormats().cend()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid format");
		}
#endif
	}

	void Engine::ValidateDimension(const Texture& texture, const TextureViewDimension dimension)
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

	void Engine::ValidateDimension(const Texture& texture, const TextureDimension dimension)
	{
#ifndef NDEBUG
		if (texture.Dimension() != dimension) [[unlikely]]
		{
			throw std::invalid_argument("Invalid dimension");
		}
#endif
	}

	void Engine::ValidateDimension(const Texture& texture, const DSVDimension dimension)
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

	void Engine::ValidateLayout(const Texture& texture, const TextureSRVLayout& layout, const TextureViewDimension dimension)
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

	void Engine::ValidateLayout(const TextureSRVLayout& layout, const TextureViewDimension dimension,
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

	void Engine::ValidateLayout(const Texture& texture, const TextureUAVLayout& layout)
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

	void Engine::ValidateLayout(const TextureUAVLayout& layout, const std::uint32_t maxMipCount, const std::uint32_t maxArraySize)
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

	void Engine::ValidateLayout(const Texture& texture, const RTVLayout& layout)
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

	void Engine::ValidateLayout(const RTVLayout& layout, const std::uint32_t maxMipCount, const std::uint32_t maxArraySize)
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

	void Engine::ValidateLayout(const Texture& texture, const DSVLayout& layout)
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

	void Engine::ValidateLayout(const DSVLayout& layout, const std::uint32_t maxMipCount, const std::uint32_t maxArraySize)
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

	void Engine::ValidateMipRange(const Texture& texture, const MipRange& range)
	{
		ValidateMipRange(range, texture.MipCount());
	}

	void Engine::ValidateMipRange(const MipRange& range, const std::uint32_t maxMipCount)
	{
#ifndef NDEBUG
		if (range.mostDetailedMipIndex + range.mipCount.value_or(1u) > maxMipCount) [[unlikely]]
		{
			throw std::invalid_argument("Invalid mip range");
		}
#endif
	}

	void Engine::ValidateArrayRange(const Texture& texture, const ArrayRange& range)
	{
		ValidateArrayRange(range, texture.ArraySize());
	}

	void Engine::ValidateArrayRange(const ArrayRange& range, const std::uint32_t maxArraySize)
	{
#ifndef NDEBUG
		if (range.firstArrayIndex + range.arrayCount.value_or(1u) > maxArraySize) [[unlikely]]
		{
			throw std::invalid_argument("Invalid array range");
		}
#endif
	}

	void Engine::ValidateSampleCount(const Texture& texture, const bool shouldBeMS)
	{
#ifndef NDEBUG
		if (ToNumber(texture.SampleCount()) > 1u != shouldBeMS) [[unlikely]]
		{
			throw std::invalid_argument("Invalid sample count");
		}
#endif
	}

	void Engine::ValidateSwapChainParams(const SwapChainParams& params)
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

	void Engine::ValidateContainer(const ShaderDataContainer& container, const std::uint32_t index)
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

	void Engine::ValidateCopyRange(const std::span<const ShaderDataCopyRange> ranges)
	{
#ifndef NDEBUG
		if (ranges.size() > std::numeric_limits<UINT>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Range count is too great");
		}
		for (const ShaderDataCopyRange& range : ranges)
		{
			if (!range.source || typeid(*range.source) != typeid(ShaderDataContainer)) [[unlikely]]
			{
				throw std::invalid_argument("Invalid source");
			}
			const ShaderDataContainer* const source = static_cast<const ShaderDataContainer*>(range.source);
			if (source->Size() < range.sourceOffset + range.count) [[unlikely]]
			{
				throw std::invalid_argument("Invalid source range");
			}
			if (source->IsShaderVisible()) [[unlikely]]
			{
				throw std::invalid_argument("Source is shader visible");
			}

			if (!range.destination || typeid(*range.destination) != typeid(ShaderDataContainer)) [[unlikely]]
			{
				throw std::invalid_argument("Invalid destination");
			}
			if (static_cast<const ShaderDataContainer*>(range.destination)->Size() < range.destinationOffset + range.count) [[unlikely]]
			{
				throw std::invalid_argument("Invalid destination range");
			}
		}
#endif
	}

	void Engine::ValidateContainer(const RenderTargetContainer& container, const std::uint32_t index)
	{
#ifndef NDEBUG
		if (index >= container.Size()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid container index");
		}
#endif
	}

	void Engine::ValidateCopyRange(std::span<const RenderTargetCopyRange> ranges)
	{
#ifndef NDEBUG
		if (ranges.size() > std::numeric_limits<UINT>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Range count is too great");
		}
		for (const RenderTargetCopyRange& range : ranges)
		{
			if (!range.source || typeid(*range.source) != typeid(ShaderDataContainer)) [[unlikely]]
			{
				throw std::invalid_argument("Invalid source");
			}
			const RenderTargetContainer* const source = static_cast<const RenderTargetContainer*>(range.source);
			if (source->Size() < range.sourceOffset + range.count) [[unlikely]]
			{
				throw std::invalid_argument("Invalid source range");
			}

			if (!range.destination || typeid(*range.destination) != typeid(RenderTargetContainer)) [[unlikely]]
			{
				throw std::invalid_argument("Invalid destination");
			}
			if (static_cast<const RenderTargetContainer*>(range.destination)->Size() < range.destinationOffset + range.count) [[unlikely]]
			{
				throw std::invalid_argument("Invalid destination range");
			}
		}
#endif
	}

	void Engine::ValidateContainer(const DepthStencilContainer& container, const std::uint32_t index)
	{
#ifndef NDEBUG
		if (index >= container.Size()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid container index");
		}
#endif
	}

	void Engine::ValidateCopyRange(const std::span<const DepthStencilCopyRange> ranges)
	{
#ifndef NDEBUG
		if (ranges.size() > std::numeric_limits<UINT>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Range count is too great");
		}
		for (const DepthStencilCopyRange& range : ranges)
		{
			if (!range.source || typeid(*range.source) != typeid(ShaderDataContainer)) [[unlikely]]
			{
				throw std::invalid_argument("Invalid source");
			}
			const DepthStencilContainer* const source = static_cast<const DepthStencilContainer*>(range.source);
			if (source->Size() < range.sourceOffset + range.count) [[unlikely]]
			{
				throw std::invalid_argument("Invalid source range");
			}

			if (!range.destination || typeid(*range.destination) != typeid(DepthStencilContainer)) [[unlikely]]
			{
				throw std::invalid_argument("Invalid destination");
			}
			if (static_cast<const DepthStencilContainer*>(range.destination)->Size() < range.destinationOffset + range.count) [[unlikely]]
			{
				throw std::invalid_argument("Invalid destination range");
			}
		}
#endif
	}

	void Engine::ValidateContainer(const SamplerContainer& container, const std::uint32_t index)
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

	void Engine::ValidateCopyRange(const std::span<const SamplerCopyRange> ranges)
	{
#ifndef NDEBUG
		if (ranges.size() > std::numeric_limits<UINT>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Range count is too great");
		}
		for (const SamplerCopyRange& range : ranges)
		{
			if (!range.source || typeid(*range.source) != typeid(SamplerContainer)) [[unlikely]]
			{
				throw std::invalid_argument("Invalid source");
			}
			const SamplerContainer* const source = static_cast<const SamplerContainer*>(range.source);
			if (source->Size() < range.sourceOffset + range.count) [[unlikely]]
			{
				throw std::invalid_argument("Invalid source range");
			}
			if (source->IsShaderVisible()) [[unlikely]]
			{
				throw std::invalid_argument("Source is shader visible");
			}

			if (!range.destination || typeid(*range.destination) != typeid(SamplerContainer)) [[unlikely]]
			{
				throw std::invalid_argument("Invalid destination");
			}
			if (static_cast<const SamplerContainer*>(range.destination)->Size() < range.destinationOffset + range.count) [[unlikely]]
			{
				throw std::invalid_argument("Invalid destination range");
			}
		}
#endif
	}

	void Engine::ValidatePipelineLayoutParams(const PipelineLayoutParams& params)
	{
		ValidatePipelineLayoutSizes(params);
		ValidatePipelineLayoutOverlaps(params.descriptorSets);
	}

	void Engine::ValidatePipelineLayoutSizes(const PipelineLayoutParams& params)
	{
#ifndef NDEBUG
		if (params.descriptorSets.size() > std::numeric_limits<UINT>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Descriptor set count is too great");
		}

		for (const DescriptorSet& set : params.descriptorSets)
		{
			if (GetRangeCount(set.ranges) > std::numeric_limits<UINT>::max()) [[unlikely]]
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

	void Engine::ValidatePipelineLayoutOverlaps(const std::span<const DescriptorSet> descriptorSets)
	{
#ifndef NDEBUG
		static constexpr auto checkRange = []<typename T>(const std::span<const T> r, const DescriptorSet& set)
		{
			for (std::size_t i = 0uz; i < r.size(); ++i)
			{
				const T& base = r[i];
				std::uint32_t baseBegin = base.baseShaderRegister;
				std::uint32_t baseEnd = base.baseShaderRegister + base.count;
				for (std::size_t j = i + 1uz; j < r.size(); ++j)
				{
					const T& compared = r[j];
					std::uint32_t comparedBegin = compared.baseShaderRegister;
					std::uint32_t comparedEnd = compared.baseShaderRegister + compared.count;
					if (!(comparedBegin >= baseEnd || comparedEnd <= baseBegin)) [[unlikely]]
					{
						throw std::invalid_argument("Overlapping ranges");
					}
				}
				for (const StaticSamplerParams& compared : set.staticSamplers)
				{
					if (compared.shaderRegister >= baseBegin && compared.shaderRegister < baseEnd) [[unlikely]]
					{
						throw std::invalid_argument("Overlapping ranges");
					}
				}
			}
		};

		for (std::size_t setIndex = 0uz; setIndex < descriptorSets.size(); ++setIndex)
		{
			const DescriptorSet& set = descriptorSets[setIndex];
			for (std::size_t i = 0uz; i < setIndex; ++i)
			{
				if (set.setIndex == descriptorSets[i].setIndex) [[unlikely]]
				{
					throw std::invalid_argument("Overlapping set indices");
				}
			}

			std::visit(Type::Overload
			{
				[&](const std::span<const ShaderDataDescriptorRange> r)
				{
					checkRange(r, set);
				},
				[&](const std::span<const SamplerDescriptorRange> r)
				{
					checkRange(r, set);
				}
			}, set.ranges);

			for (std::size_t i = 0uz; i < set.staticSamplers.size(); ++i)
			{
				for (std::size_t j = i + 1uz; j < set.staticSamplers.size(); ++j)
				{
					if (set.staticSamplers[i].shaderRegister == set.staticSamplers[j].shaderRegister) [[unlikely]]
					{
						throw std::invalid_argument("Overlapping ranges");
					}
				}
			}
		}
#endif
	}

	void Engine::ValidatePipelineLayout(const IPipelineLayout* const layout)
	{
#ifndef NDEBUG
		if (layout && typeid(*layout) != typeid(RootSignature)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid pipeline layout");
		}
#endif
	}

	void Engine::ValidatePipelineStateParams(const GraphicsPipelineStateParams& params) const
	{
#ifndef NDEBUG
		if (params.meshShader.empty()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid mesh shader");
		}

		const std::size_t blendCount = std::visit(Type::Overload
		{
			[](const BlendGroupParams& p)
			{
				return p.renderTargetBlend.size();
			},
			[](const LogicBlendGroupParams& p)
			{
				return p.renderTargetBlend.size();
			}
		}, params.blend.blendGroup);
		if (blendCount != params.attachmentParams.renderTargetFormats.size()) [[unlikely]]
		{
			throw std::invalid_argument("Blend render target count and attachment render target count don't match");
		}
		if (blendCount > SimultaneousTargetCount) [[unlikely]]
		{
			throw std::invalid_argument("Invalid render target count");
		}
		if ((params.depthStencil.depth || params.depthStencil.stencil) != params.attachmentParams.depthStencilFormat.has_value()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid depth stencil format");
		}

		for (const TextureFormatId format : params.attachmentParams.renderTargetFormats)
		{
			if (None(AspectMask::Color, GetAspects(GetFormat(format)))) [[unlikely]]
			{
				throw std::invalid_argument("Invalid render target format");
			}
		}

		if (params.attachmentParams.depthStencilFormat)
		{
			const DXGI_FORMAT depthStencilFormat = GetFormat(*params.attachmentParams.depthStencilFormat);
			if (!IsDepthStencilFormat(depthStencilFormat)) [[unlikely]]
			{
				throw std::invalid_argument("Invalid depth stencil format");
			}
			if (params.depthStencil.stencil && HasStencil(depthStencilFormat)) [[unlikely]]
			{
				throw std::invalid_argument("Invalid depth stencil format");
			}
		}
#endif
	}

	void Engine::ValidatePipelineStateParams(const ComputePipelineStateParams& params)
	{
#ifndef NDEBUG
		if (params.computeShader.empty()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid mesh shader");
		}
#endif
	}

	template<typename CommandList, typename CommandListInterface>
	void Engine::ValidateCommandLists(const std::span<const CommandListInterface* const> commandLists)
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

	void Engine::ValidateFences(const std::span<const FenceValue> fences)
	{
#ifndef NDEBUG
		for (const FenceValue& fenceValue : fences)
		{
			if (!fenceValue.fence || typeid(*fenceValue.fence) != typeid(Fence))
			{
				throw std::invalid_argument("Invalid fence");
			}
		}
#endif
	}
}
