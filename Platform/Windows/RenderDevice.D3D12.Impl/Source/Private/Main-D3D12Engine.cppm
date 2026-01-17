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

import :DXGIFactory;
import :DXGISwapChain;
import :DXGITextureFormatMap;
import :D3D12Buffer;
import :D3D12CommandQueue;
import :D3D12ComputeCommandList;
import :D3D12CopyCommandList;
import :D3D12Device;
import :D3D12Fence;
import :D3D12GraphicsCommandList;
import :D3D12SwapChain;
import :D3D12Texture;
import :D3D12Utility;
import :D3D12Waiter;
import :EngineUtility;

export namespace PonyEngine::RenderDevice::Windows
{
	class D3D12Engine final
	{
	public:
		static constexpr std::string_view ApiName = D3D12Device::ApiName;
		static constexpr auto ApiVersion = D3D12Device::ApiVersion;

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
		TextureFormatFeature TextureFormatFeatures(TextureFormatId textureFormatId) const;
		[[nodiscard("Pure function")]]
		TextureSupportResponse TextureSupport(const TextureSupportRequest& request) const;
		[[nodiscard("Pure function")]]
		static HeapTypeMask TextureHeapTypeSupport() noexcept;
		[[nodiscard("Pure function")]]
		std::shared_ptr<ITexture> CreateTexture(HeapType heapType, const TextureParams& params);

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
		const std::shared_ptr<ITexture>& SwapChainBuffer(std::uint8_t bufferIndex) const;
		void PresentNextSwapChainBuffer();

		D3D12Engine& operator =(const D3D12Engine&) = delete;
		D3D12Engine& operator =(D3D12Engine&&) = delete;

	private:
		[[nodiscard("Pure function")]]
		TextureSupportResponse MakeResponse(DXGI_FORMAT format, const TextureSupportRequest& request, const D3D12_FEATURE_DATA_FORMAT_SUPPORT& formatSupport) const;
		[[nodiscard("Pure function")]]
		SampleCountMask GetSampleCountMask(DXGI_FORMAT format, const TextureSupportRequest& request, const D3D12_FEATURE_DATA_FORMAT_SUPPORT& formatSupport) const;

		template<typename T> [[nodiscard("Pure function")]]
		std::shared_ptr<T> CreateCommandList(D3D12_COMMAND_LIST_TYPE type);
		template<typename CommandList, typename CommandListInterface>
		void Execute(std::span<const CommandListInterface* const> commandLists, const QueueSync& sync, D3D12CommandQueue& commandQueue);
		template<typename CommandList, typename CommandListInterface>
		static void GetCommandLists(std::span<const CommandListInterface* const> commandLists, std::span<ID3D12CommandList*> lists) noexcept;
		static void GetFences(std::span<const FenceValue> input, std::span<std::pair<ID3D12Fence*, UINT64>> output) noexcept;

		[[nodiscard("Pure function")]]
		static D3D12_COMMAND_QUEUE_DESC GetCommandQueueDesc(D3D12_COMMAND_LIST_TYPE type) noexcept;

		static void ValidateSize(const BufferParams& params);
		static void ValidateDimension(const TextureParams& params);
		static void ValidateColorTexture(const TextureParams& params);
		static void ValidateDepthTexture(const TextureParams& params);
		static void ValidateSwapChainParams(const SwapChainParams& params);

		template<typename CommandList, typename CommandListInterface>
		void ValidateCommandLists(std::span<const CommandListInterface* const> commandLists);
		void ValidateFences(std::span<const FenceValue> fences);

		// {132D4628-84F4-40F4-B72F-8A7B08C3C566}
		static constexpr GUID CreatorId = { 0x132d4628, 0x84f4, 0x40f4, { 0xb7, 0x2f, 0x8a, 0x7b, 0x8, 0xc3, 0xc5, 0x66 } };

		IRenderDeviceContext* renderDevice;

		Memory::Arena arena;

		DXGITextureFormatMap textureFormatMap;

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

	TextureFormatFeature D3D12Engine::TextureFormatFeatures(const TextureFormatId textureFormatId) const
	{
		if (const std::size_t index = textureFormatMap.IndexOf(textureFormatId); index < textureFormatMap.Size())
		{
			const DXGI_FORMAT format = textureFormatMap.DXGIFormat(index);
			const D3D12_FEATURE_DATA_FORMAT_SUPPORT formatSupport = device.GetFormatSupport(format);

			return ToTextureFormatFeature(formatSupport);
		}

		return TextureFormatFeature::None;
	}

	TextureSupportResponse D3D12Engine::TextureSupport(const TextureSupportRequest& request) const
	{
		if (!IsValidUsage(request.usage))
		{
			return TextureSupportResponse{};
		}

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
		if (!IsValidUsage(params.usage))
		{
			throw std::invalid_argument("Invalid usage");
		}

		const std::size_t formatIndex = textureFormatMap.IndexOf(params.format);
		if (formatIndex >= textureFormatMap.Size()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid texture format");
		}
		DXGI_FORMAT format = textureFormatMap.DXGIFormat(formatIndex);

		arena.Free();
		const bool srgb = Any(TextureFlag::SRGB, params.flags);
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
				const std::size_t castableFormatIndex = textureFormatMap.IndexOf(params.castableFormats[i]);
				if (castableFormatIndex >= textureFormatMap.Size()) [[unlikely]]
				{
					throw std::invalid_argument("Invalid castable texture format");
				}
				formats[i] = textureFormatMap.DXGIFormat(castableFormatIndex);
			}

			if (srgb)
			{
				const DXGI_FORMAT srgbFormat = GetSrgbFormat(format);
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

		return std::make_shared<D3D12Texture>(std::move(resource), params.format, params.castableFormats, 
			static_cast<std::uint32_t>(resourceDesc.Width), static_cast<std::uint32_t>(resourceDesc.Height), static_cast<std::uint16_t>(resourceDesc.DepthOrArraySize),
			static_cast<std::uint16_t>(resourceDesc.MipLevels), params.dimension, params.sampleCount, params.usage, srgb);
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

		const std::size_t formatIndex = textureFormatMap.IndexOf(params.format);
		if (formatIndex >= textureFormatMap.Size()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid texture format");
		}
		const DXGI_FORMAT format = textureFormatMap.DXGIFormat(formatIndex);

		const bool srgb = Any(SwapChainFlag::SRGB, params.flags);
		if (srgb && GetSrgbFormat(format) == DXGI_FORMAT_UNKNOWN) [[unlikely]]
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
			Platform::Windows::ComPtr<ID3D12Resource2> resource;
			dxgiSwapChain.GetBuffer(i, resource);
			buffers[i] = std::make_shared<D3D12Texture>(std::move(resource), params.format, std::span<const TextureFormatId>(),
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
		if (!swapChain) [[unlikely]]
		{
			throw std::logic_error("Swap chain is not created");
		}

		return swapChain->BufferCount();
	}

	std::uint8_t D3D12Engine::CurrentSwapChainBufferIndex() const
	{
		if (!swapChain) [[unlikely]]
		{
			throw std::logic_error("Swap chain is not created");
		}

		return static_cast<std::uint8_t>(swapChain->GetCurrentBufferIndex());
	}

	const std::shared_ptr<ITexture>& D3D12Engine::SwapChainBuffer(const std::uint8_t bufferIndex) const
	{
		if (!swapChain) [[unlikely]]
		{
			throw std::logic_error("Swap chain is not created");
		}
		if (bufferIndex >= swapChain->BufferCount()) [[unlikely]]
		{
			throw std::out_of_range("Buffer index is out of range");
		}

		return swapChain->GetBuffer(bufferIndex);
	}

	void D3D12Engine::PresentNextSwapChainBuffer()
	{
		if (!swapChain) [[unlikely]]
		{
			throw std::logic_error("Swap chain is not created");
		}

		swapChain->Present();
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
		case TextureDimension::TextureCube:
			response.maxSize = Math::Vector3<std::uint32_t>(D3D12_REQ_TEXTURECUBE_DIMENSION, D3D12_REQ_TEXTURECUBE_DIMENSION, 1u);
			response.maxMipCount = D3D12_REQ_MIP_LEVELS;
			response.maxArraySize = D3D12_REQ_TEXTURE2D_ARRAY_AXIS_DIMENSION / 6;
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
		if ((request.dimension != TextureDimension::Texture2D && request.dimension != TextureDimension::TextureCube) ||
			Any(TextureUsage::UnorderedAccess, request.usage) || 
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
		GetCommandLists<CommandList, CommandListInterface>(commandLists, arena.Span(lists));
		GetFences(sync.before, arena.Span(beforeFences));
		GetFences(sync.after, arena.Span(afterFences));

		commandQueue.Execute(arena.Span(lists), arena.Span(beforeFences), arena.Span(afterFences));
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
		if (ToNumber(params.sampleCount) > D3D12_MAX_MULTISAMPLE_SAMPLE_COUNT) [[unlikely]]
		{
			throw std::invalid_argument("Invalid sample count");
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
			break;
		case TextureDimension::TextureCube:
			if (params.size.X() > D3D12_REQ_TEXTURE2D_U_OR_V_DIMENSION || params.size.Y() > D3D12_REQ_TEXTURE2D_U_OR_V_DIMENSION || params.size.Z() != 1u) [[unlikely]]
			{
				throw std::invalid_argument("Invalid size");
			}
			if (params.arraySize > D3D12_REQ_TEXTURE2D_ARRAY_AXIS_DIMENSION / 6) [[unlikely]]
			{
				throw std::invalid_argument("Invalid array size");
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
