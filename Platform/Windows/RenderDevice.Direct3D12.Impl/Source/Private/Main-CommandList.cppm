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

#include "PonyEngine/RenderDevice/Windows/D3D12Framework.h"

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:CommandList;

import std;

import PonyEngine.Math;
import PonyEngine.Memory;
import PonyEngine.Platform.Windows;
import PonyEngine.RenderDevice;

import :Buffer;
import :CommandListUtility;
import :ComputePipelineState;
import :DepthStencilContainer;
import :FormatUtility;
import :GraphicsPipelineState;
import :ObjectUtility;
import :RenderTargetContainer;
import :SamplerContainer;
import :ShaderDataContainer;
import :Texture;
import :TextureUtility;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	class CommandList final
	{
	public:
		[[nodiscard("Pure constructor")]]
		CommandList(ID3D12CommandAllocator& allocator, ID3D12GraphicsCommandList10& commandList);
		[[nodiscard("Pure constructor")]]
		CommandList(Platform::Windows::ComPtr<ID3D12CommandAllocator>&& allocator, Platform::Windows::ComPtr<ID3D12GraphicsCommandList10>&& commandList);
		CommandList(const CommandList&) = delete;
		CommandList(CommandList&&) = delete;

		~CommandList() noexcept = default;

		[[nodiscard("Pure function")]]
		ID3D12GraphicsCommandList10& GetCommandList() const noexcept;

		void Reset();
		void Close();
		[[nodiscard("Pure function")]]
		bool IsOpen() const noexcept;

		void Barrier(std::span<const BufferBarrier> bufferBarriers, std::span<const TextureBarrier> textureBarriers);

		void SetRasterRegions(std::span<const RasterRegion> regions);
		void SetDepthBias(const DepthBias& bias) noexcept;
		void SetDepthBounds(const DepthRange& range) noexcept;
		void SetStencilReference(const StencilReference& reference) noexcept;
		void SetBlendFactor(const Math::ColorRGBA<float>& factor) noexcept;

		void SetTargets(std::span<const RenderTargetBinding> renderTargetBindings, const DepthStencilBinding* depthStencilBinding);
		void SetTargets(const RenderTargetBinding* renderTargetBinding, std::uint8_t renderTargetCount, const DepthStencilBinding* depthStencilBinding);
		void SetContainers(const ShaderDataContainer* shaderDataContainer, const SamplerContainer* samplerContainer);
		void SetGraphicsRootSignature(ID3D12RootSignature* rootSig);
		void SetComputeRootSignature(ID3D12RootSignature* rootSig);
		void SetPipelineState(ID3D12PipelineState& pso);
		void SetGraphicsDescriptorTable(std::uint32_t tableIndex, D3D12_GPU_DESCRIPTOR_HANDLE handle);
		void SetComputeDescriptorTable(std::uint32_t tableIndex, D3D12_GPU_DESCRIPTOR_HANDLE handle);

		void DispatchGraphics(const Math::Vector3<std::uint32_t>& threadGroupCounts) noexcept;
		void DispatchCompute(const Math::Vector3<std::uint32_t>& threadGroupCounts) noexcept;

		void ClearRTV(const IRenderTargetContainer& container, std::uint32_t viewIndex, const Math::ColorRGBA<float>& color, std::span<const Math::CornerRect<std::uint32_t>> rects);
		void ClearDSV(const IDepthStencilContainer& container, std::uint32_t viewIndex, std::optional<float> depth, std::optional<std::uint8_t> stencil,
			std::span<const Math::CornerRect<std::uint32_t>> rects);
		void ClearUAV(const IBuffer& buffer, const ShaderDataContainer& gpuContainer, std::uint32_t gpuViewIndex, const IShaderDataContainer& cpuContainer, std::uint32_t cpuViewIndex,
			const Math::Vector4<std::uint32_t>& values, std::span<const Math::CornerRect<std::uint32_t>> rects = std::span<const Math::CornerRect<std::uint32_t>>());
		void ClearUAV(const ITexture& texture, const ShaderDataContainer& gpuContainer, std::uint32_t gpuViewIndex, const IShaderDataContainer& cpuContainer, std::uint32_t cpuViewIndex,
			const Math::Vector4<std::uint32_t>& values, std::span<const Math::CornerRect<std::uint32_t>> rects = std::span<const Math::CornerRect<std::uint32_t>>());
		void ClearUAV(const IBuffer& buffer, const ShaderDataContainer& gpuContainer, std::uint32_t gpuViewIndex, const IShaderDataContainer& cpuContainer, std::uint32_t cpuViewIndex,
			const Math::Vector4<float>& values, std::span<const Math::CornerRect<std::uint32_t>> rects = std::span<const Math::CornerRect<std::uint32_t>>());
		void ClearUAV(const ITexture& texture, const ShaderDataContainer& gpuContainer, std::uint32_t gpuViewIndex, const IShaderDataContainer& cpuContainer, std::uint32_t cpuViewIndex,
			const Math::Vector4<float>& values, std::span<const Math::CornerRect<std::uint32_t>> rects = std::span<const Math::CornerRect<std::uint32_t>>());

		void Copy(const IBuffer& source, IBuffer& destination);
		void Copy(const IBuffer& source, IBuffer& destination, std::uint64_t sourceOffset, std::uint64_t destinationOffset, std::uint64_t size);
		void Copy(const ITexture& source, ITexture& destination);
		void Copy(const ITexture& source, ITexture& destination, const CopySubTextureRange& range);
		void Copy(const ITexture& source, ITexture& destination, const BoxCopySubTextureRange& range);
		void Copy(const IBuffer& source, ITexture& destination, std::span<const CopyableFootprint> footprints);
		void Copy(const IBuffer& source, ITexture& destination, std::span<const CopyableFootprint> footprints, const FootprintedCopySubTextureRange& range);
		void Copy(const IBuffer& source, ITexture& destination, std::span<const CopyableFootprint> footprints, const FootprintedBoxCopySubTextureRange& range);
		void Copy(const ITexture& source, IBuffer& destination, std::span<const CopyableFootprint> footprints);
		void Copy(const ITexture& source, IBuffer& destination, std::span<const CopyableFootprint> footprints, const FootprintedCopySubTextureRange& range);
		void Copy(const ITexture& source, IBuffer& destination, std::span<const CopyableFootprint> footprints, const FootprintedBoxCopySubTextureRange& range);

		void Resolve(const ITexture& source, ITexture& destination, ResolveMode mode);
		void Resolve(const ITexture& source, ITexture& destination, const CopySubTextureRange& range, ResolveMode mode = ResolveMode::Average);
		void Resolve(const ITexture& source, ITexture& destination, const BoxCopySubTextureRange& range, ResolveMode mode = ResolveMode::Average);

		void ExecuteBundle(ID3D12GraphicsCommandList10& bundle) noexcept;

		void ValidateState() const;
		void ValidateContainers(const IShaderDataContainer* shaderDataContainer, const ISamplerContainer* samplerContainer) const;
		void ValidatePipelineState(const IGraphicsPipelineState& pipelineState) const;
		void ValidatePipelineState(const IComputePipelineState& pipelineState) const;

		[[nodiscard("Pure function")]]
		std::string_view Name() const noexcept;
		void Name(std::string_view name);

		CommandList& operator =(const CommandList&) = delete;
		CommandList& operator =(CommandList&&) = delete;

	private:
		static void ToNativeBarriers(std::span<const BufferBarrier> bufferBarriers, std::span<D3D12_BUFFER_BARRIER> nativeBufferBarriers) noexcept;
		static void ToNativeBarriers(std::span<const TextureBarrier> textureBarriers, std::span<D3D12_TEXTURE_BARRIER> nativeTextureBarriers) noexcept;

		static void ToViewports(std::span<const RasterRegion> regions, std::span<D3D12_VIEWPORT> viewports) noexcept;
		static void ToScissors(std::span<const RasterRegion> regions, std::span<D3D12_RECT> rects) noexcept;

		[[nodiscard("Pure function")]]
		static D3D12_TEXTURE_COPY_LOCATION ToCopyLocation(const Buffer& buffer, const CopyableFootprint& footprint, DXGI_FORMAT format) noexcept;
		[[nodiscard("Pure function")]]
		static D3D12_TEXTURE_COPY_LOCATION ToCopyLocation(const Texture& texture, UINT16 mipIndex, UINT16 arrayIndex, Aspect aspect) noexcept;
		[[nodiscard("Pure function")]]
		static D3D12_TEXTURE_COPY_LOCATION ToCopyLocation(const Texture& texture, UINT subresourceIndex) noexcept;
		[[nodiscard("Pure function")]]
		static D3D12_RECT ToRect(const Math::CornerRect<std::uint32_t>& rect) noexcept;
		[[nodiscard("Pure function")]]
		static D3D12_RECT ToRect(const Math::Vector3<std::uint32_t>& offset, const Math::Vector3<std::uint32_t>& size) noexcept;
		[[nodiscard("Pure function")]]
		static D3D12_BOX ToBox(const Math::Vector3<std::uint32_t>& offset, const Math::Vector3<std::uint32_t>& size) noexcept;

		static void ValidateBarriers(std::span<const BufferBarrier> bufferBarriers);
		static void ValidateBarriers(std::span<const TextureBarrier> textureBarriers);

		static void ValidateRasterRegion(std::span<const RasterRegion> regions);

		static void ValidateRenderTargets(std::span<const RenderTargetBinding> renderTargetBindings);
		static void ValidateRenderTargets(const RenderTargetBinding* renderTargetBinding, std::uint8_t renderTargetCount);
		static void ValidateDepthTarget(const DepthStencilBinding* binding);

		void ValidateRenderTarget(const IRenderTargetContainer& container, std::uint32_t viewIndex);
		void ValidateDepthStencil(const IDepthStencilContainer& container, std::uint32_t viewIndex);
		template<typename UAVMeta, typename NativeResource, typename Resource>
		void ValidateUnorderedAccess(const Resource& resource, const ShaderDataContainer& gpuContainer, std::uint32_t gpuViewIndex, 
			const IShaderDataContainer& cpuContainer, std::uint32_t cpuViewIndex);

		static void ValidateCopy(const IBuffer& source, const IBuffer& destination);
		static void ValidateCopy(const IBuffer& source, const IBuffer& destination, std::uint64_t sourceOffset, std::uint64_t destinationOffset, std::uint64_t size);
		static void ValidateCopyBase(const IBuffer& source, const IBuffer& destination);
		static void ValidateCopy(const ITexture& source, const ITexture& destination);
		static void ValidateCopy(const ITexture& source, const ITexture& destination, const CopySubTextureRange& range);
		static void ValidateCopy(const ITexture& source, const ITexture& destination, const BoxCopySubTextureRange& range);
		static void ValidateCopyBase(const ITexture& source, const ITexture& destination);
		static void ValidateCopy(const IBuffer& buffer, const ITexture& texture, std::span<const CopyableFootprint> footprints);
		static void ValidateCopy(const IBuffer& buffer, const ITexture& texture, std::span<const CopyableFootprint> footprints, const FootprintedCopySubTextureRange& range);
		static void ValidateCopy(const IBuffer& buffer, const ITexture& texture, std::span<const CopyableFootprint> footprints, const FootprintedBoxCopySubTextureRange& range, 
			bool textureSource);
		static void ValidateCopyBase(const IBuffer& buffer, const ITexture& texture, std::span<const CopyableFootprint> footprints);

		static void ValidateResolve(const ITexture& source, const ITexture& destination);
		static void ValidateResolve(const ITexture& source, const ITexture& destination, const CopySubTextureRange& range);
		static void ValidateResolve(const ITexture& source, const ITexture& destination, const BoxCopySubTextureRange& range);
		static void ValidateResolveBase(const ITexture& source, const ITexture& destination);

		Platform::Windows::ComPtr<ID3D12CommandAllocator> allocator;
		Platform::Windows::ComPtr<ID3D12GraphicsCommandList10> commandList;

		Memory::Arena arena;

		bool isOpen;

		std::string name;
	};
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	CommandList::CommandList(ID3D12CommandAllocator& allocator, ID3D12GraphicsCommandList10& commandList) :
		allocator(&allocator),
		commandList(&commandList),
		arena(0uz, 2048uz),
		isOpen{true}
	{
		Reset();
	}

	CommandList::CommandList(Platform::Windows::ComPtr<ID3D12CommandAllocator>&& allocator,
		Platform::Windows::ComPtr<ID3D12GraphicsCommandList10>&& commandList) :
		allocator(std::move(allocator)),
		commandList(std::move(commandList)),
		arena(0uz, 2048uz),
		isOpen{true}
	{
		assert(this->allocator && "The allocator is nullptr.");
		assert(this->commandList && "The command list is nullptr.");

		Reset();
	}

	ID3D12GraphicsCommandList10& CommandList::GetCommandList() const noexcept
	{
		return *commandList;
	}

	void CommandList::Reset()
	{
		if (const HRESULT result = allocator->Reset(); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to reset command allocator: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		if (const HRESULT result = commandList->Reset(allocator.Get(), nullptr); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to reset command list: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		isOpen = true;
	}

	void CommandList::Close()
	{
		if (const HRESULT result = commandList->Close(); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to close command list: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		isOpen = false;
	}

	bool CommandList::IsOpen() const noexcept
	{
		return isOpen;
	}

	void CommandList::Barrier(const std::span<const BufferBarrier> bufferBarriers, const std::span<const TextureBarrier> textureBarriers)
	{
		ValidateState();
		ValidateBarriers(bufferBarriers);
		ValidateBarriers(textureBarriers);

		arena.Free();
		const Memory::Arena::Slice<D3D12_BUFFER_BARRIER> nativeBufferBarriers = arena.Allocate<D3D12_BUFFER_BARRIER>(bufferBarriers.size());
		const Memory::Arena::Slice<D3D12_TEXTURE_BARRIER> nativeTextureBarriers = arena.Allocate<D3D12_TEXTURE_BARRIER>(textureBarriers.size());
		const std::span<D3D12_BUFFER_BARRIER> nativeBufferBarriersSpan = arena.Span(nativeBufferBarriers);
		const std::span<D3D12_TEXTURE_BARRIER> nativeTextureBarriersSpan = arena.Span(nativeTextureBarriers);
		ToNativeBarriers(bufferBarriers, nativeBufferBarriersSpan);
		ToNativeBarriers(textureBarriers, nativeTextureBarriersSpan);

		std::array<D3D12_BARRIER_GROUP, 2> barrierGroups;
		UINT32 groupCount = 0u;
		if (!nativeBufferBarriersSpan.empty())
		{
			barrierGroups[groupCount++] = D3D12_BARRIER_GROUP
			{
				.Type = D3D12_BARRIER_TYPE_BUFFER,
				.NumBarriers = static_cast<UINT32>(nativeBufferBarriersSpan.size()),
				.pBufferBarriers = nativeBufferBarriersSpan.data()
			};
		}
		if (!nativeTextureBarriersSpan.empty())
		{
			barrierGroups[groupCount++] = D3D12_BARRIER_GROUP
			{
				.Type = D3D12_BARRIER_TYPE_TEXTURE,
				.NumBarriers = static_cast<UINT32>(nativeTextureBarriersSpan.size()),
				.pTextureBarriers = nativeTextureBarriersSpan.data()
			};
		}

		if (groupCount > 0u) [[likely]]
		{
			commandList->Barrier(groupCount, barrierGroups.data());
		}
	}

	void CommandList::SetRasterRegions(const std::span<const RasterRegion> regions)
	{
		ValidateState();
		ValidateRasterRegion(regions);

		arena.Free();
		const Memory::Arena::Slice<D3D12_VIEWPORT> viewports = arena.Allocate<D3D12_VIEWPORT>(regions.size());
		const std::span<D3D12_VIEWPORT> viewportsSpan = arena.Span(viewports);
		ToViewports(regions, viewportsSpan);
		commandList->RSSetViewports(static_cast<UINT>(viewportsSpan.size()), viewportsSpan.data());

		arena.Free();
		const Memory::Arena::Slice<D3D12_RECT> scissors = arena.Allocate<D3D12_RECT>(regions.size());
		const std::span<D3D12_RECT> scissorsSpan = arena.Span(scissors);
		ToScissors(regions, scissorsSpan);
		commandList->RSSetScissorRects(static_cast<UINT>(scissorsSpan.size()), scissorsSpan.data());
	}

	void CommandList::SetDepthBias(const DepthBias& bias) noexcept
	{
		ValidateState();
		commandList->RSSetDepthBias(bias.depthBias, bias.depthBiasClamp, bias.slopeScaledDepthBias);
	}

	void CommandList::SetDepthBounds(const DepthRange& range) noexcept
	{
		ValidateState();
		commandList->OMSetDepthBounds(range.min, range.max);
	}

	void CommandList::SetStencilReference(const StencilReference& reference) noexcept
	{
		ValidateState();
		commandList->OMSetFrontAndBackStencilRef(reference.front, reference.back);
	}

	void CommandList::SetBlendFactor(const Math::ColorRGBA<float>& factor) noexcept
	{
		ValidateState();
		const FLOAT blendFactor[4] = { factor.R(), factor.G(), factor.B(), factor.A() };
		commandList->OMSetBlendFactor(blendFactor);
	}

	void CommandList::SetTargets(const std::span<const RenderTargetBinding> renderTargetBindings, const DepthStencilBinding* const depthStencilBinding)
	{
		ValidateState();
		ValidateRenderTargets(renderTargetBindings);
		ValidateDepthTarget(depthStencilBinding);

		std::array<D3D12_CPU_DESCRIPTOR_HANDLE, D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT> renderTargets;
		const std::size_t renderTargetCount = std::min(renderTargetBindings.size(), renderTargets.size());
		for (std::size_t i = 0uz; i < renderTargetCount; ++i)
		{
			renderTargets[i] = static_cast<const RenderTargetContainer*>(renderTargetBindings[i].container)->CpuHandle(renderTargetBindings[i].index);
		}
		const D3D12_CPU_DESCRIPTOR_HANDLE depthStencil = depthStencilBinding 
			? static_cast<const DepthStencilContainer*>(depthStencilBinding->container)->CpuHandle(depthStencilBinding->index)
			: D3D12_CPU_DESCRIPTOR_HANDLE{};

		commandList->OMSetRenderTargets(static_cast<UINT>(renderTargetCount), renderTargetCount > 0uz ? renderTargets.data() : nullptr, false,
			depthStencilBinding ? &depthStencil : nullptr);
	}

	void CommandList::SetTargets(const RenderTargetBinding* const renderTargetBinding, const std::uint8_t renderTargetCount, const DepthStencilBinding* const depthStencilBinding)
	{
		ValidateState();
		ValidateRenderTargets(renderTargetBinding, renderTargetCount);
		ValidateDepthTarget(depthStencilBinding);

		const D3D12_CPU_DESCRIPTOR_HANDLE renderTarget = renderTargetCount > 0u
			? static_cast<const RenderTargetContainer*>(renderTargetBinding->container)->CpuHandle(renderTargetBinding->index)
			: D3D12_CPU_DESCRIPTOR_HANDLE{};
		const D3D12_CPU_DESCRIPTOR_HANDLE depthStencil = depthStencilBinding
			? static_cast<const DepthStencilContainer*>(depthStencilBinding->container)->CpuHandle(depthStencilBinding->index)
			: D3D12_CPU_DESCRIPTOR_HANDLE{};

		commandList->OMSetRenderTargets(renderTargetCount, renderTargetCount > 0uz ? &renderTarget : nullptr, false, depthStencilBinding ? &depthStencil : nullptr);
	}

	void CommandList::SetContainers(const ShaderDataContainer* const shaderDataContainer, const SamplerContainer* const samplerContainer)
	{
		std::array<ID3D12DescriptorHeap*, 2> heaps;
		UINT heapCount = 0u;
		if (shaderDataContainer)
		{
			heaps[heapCount++] = &shaderDataContainer->DescriptorHeap();
		}
		if (samplerContainer)
		{
			heaps[heapCount++] = &samplerContainer->DescriptorHeap();
		}

		commandList->SetDescriptorHeaps(heapCount, heaps.data());
	}

	void CommandList::SetGraphicsRootSignature(ID3D12RootSignature* const rootSig)
	{
		commandList->SetGraphicsRootSignature(rootSig);
	}

	void CommandList::SetComputeRootSignature(ID3D12RootSignature* const rootSig)
	{
		commandList->SetComputeRootSignature(rootSig);
	}

	void CommandList::SetPipelineState(ID3D12PipelineState& pso)
	{
		commandList->SetPipelineState(&pso);
	}

	void CommandList::SetGraphicsDescriptorTable(const std::uint32_t tableIndex, const D3D12_GPU_DESCRIPTOR_HANDLE handle)
	{
		commandList->SetGraphicsRootDescriptorTable(tableIndex, handle);
	}

	void CommandList::SetComputeDescriptorTable(const std::uint32_t tableIndex, const D3D12_GPU_DESCRIPTOR_HANDLE handle)
	{
		commandList->SetComputeRootDescriptorTable(tableIndex, handle);
	}

	void CommandList::DispatchGraphics(const Math::Vector3<std::uint32_t>& threadGroupCounts) noexcept
	{
		commandList->DispatchMesh(threadGroupCounts.X(), threadGroupCounts.Y(), threadGroupCounts.Z());
	}

	void CommandList::DispatchCompute(const Math::Vector3<std::uint32_t>& threadGroupCounts) noexcept
	{
		commandList->Dispatch(threadGroupCounts.X(), threadGroupCounts.Y(), threadGroupCounts.Z());
	}

	void CommandList::ClearRTV(const IRenderTargetContainer& container, const std::uint32_t viewIndex, const Math::ColorRGBA<float>& color, 
		const std::span<const Math::CornerRect<std::uint32_t>> rects)
	{
		ValidateRenderTarget(container, viewIndex);

		arena.Free();
		const Memory::Arena::Slice<D3D12_RECT> clearRects = arena.Allocate<D3D12_RECT>(rects.size());
		const std::span<D3D12_RECT> clearRectsSpan = arena.Span(clearRects);
		for (std::size_t i = 0uz; i < rects.size(); ++i)
		{
			clearRectsSpan[i] = ToRect(rects[i]);
		}

		const FLOAT clearColor[4] = { color.R(), color.G(), color.B(), color.A() };
		commandList->ClearRenderTargetView(static_cast<const RenderTargetContainer&>(container).CpuHandle(viewIndex), clearColor,
			static_cast<UINT>(clearRectsSpan.size()), clearRectsSpan.empty() ? nullptr : clearRectsSpan.data());
	}

	void CommandList::ClearDSV(const IDepthStencilContainer& container, const std::uint32_t viewIndex, const std::optional<float> depth, const std::optional<std::uint8_t> stencil,
		const std::span<const Math::CornerRect<std::uint32_t>> rects)
	{
		ValidateDepthStencil(container, viewIndex);

		if (!depth && !stencil)
		{
			return;
		}

		arena.Free();
		const Memory::Arena::Slice<D3D12_RECT> clearRects = arena.Allocate<D3D12_RECT>(rects.size());
		const std::span<D3D12_RECT> clearRectsSpan = arena.Span(clearRects);
		for (std::size_t i = 0uz; i < rects.size(); ++i)
		{
			clearRectsSpan[i] = ToRect(rects[i]);
		}

		const auto clearFlags = static_cast<D3D12_CLEAR_FLAGS>((depth ? D3D12_CLEAR_FLAG_DEPTH : 0) | (stencil ? D3D12_CLEAR_FLAG_STENCIL : 0));
		commandList->ClearDepthStencilView(static_cast<const DepthStencilContainer&>(container).CpuHandle(viewIndex), clearFlags, depth.value_or(0.f), stencil.value_or(0u),
			static_cast<UINT>(clearRectsSpan.size()), clearRectsSpan.empty() ? nullptr : clearRectsSpan.data());
	}

	void CommandList::ClearUAV(const IBuffer& buffer, const ShaderDataContainer& gpuContainer, const std::uint32_t gpuViewIndex, 
		const IShaderDataContainer& cpuContainer, const std::uint32_t cpuViewIndex, 
		const Math::Vector4<std::uint32_t>& values, const std::span<const Math::CornerRect<std::uint32_t>> rects)
	{
		ValidateUnorderedAccess<BufferUAVMeta, Buffer>(buffer, gpuContainer, gpuViewIndex, cpuContainer, cpuViewIndex);

		arena.Free();
		const Memory::Arena::Slice<D3D12_RECT> clearRects = arena.Allocate<D3D12_RECT>(rects.size());
		const std::span<D3D12_RECT> clearRectsSpan = arena.Span(clearRects);
		for (std::size_t i = 0uz; i < rects.size(); ++i)
		{
			clearRectsSpan[i] = ToRect(rects[i]);
		}

		const UINT clearValue[4] = { values.X(), values.Y(), values.Z(), values.W() };
		commandList->ClearUnorderedAccessViewUint(gpuContainer.GpuHandle(gpuViewIndex), static_cast<const ShaderDataContainer&>(cpuContainer).CpuHandle(cpuViewIndex),
			&static_cast<const Buffer&>(buffer).Resource(), clearValue, static_cast<UINT>(clearRectsSpan.size()), clearRectsSpan.data());
	}

	void CommandList::ClearUAV(const ITexture& texture, const ShaderDataContainer& gpuContainer, const std::uint32_t gpuViewIndex, 
		const IShaderDataContainer& cpuContainer, const std::uint32_t cpuViewIndex,
		const Math::Vector4<std::uint32_t>& values, const std::span<const Math::CornerRect<std::uint32_t>> rects)
	{
		ValidateUnorderedAccess<TextureUAVMeta, Texture>(texture, gpuContainer, gpuViewIndex, cpuContainer, cpuViewIndex);

		arena.Free();
		const Memory::Arena::Slice<D3D12_RECT> clearRects = arena.Allocate<D3D12_RECT>(rects.size());
		const std::span<D3D12_RECT> clearRectsSpan = arena.Span(clearRects);
		for (std::size_t i = 0uz; i < rects.size(); ++i)
		{
			clearRectsSpan[i] = ToRect(rects[i]);
		}

		const UINT clearValue[4] = { values.X(), values.Y(), values.Z(), values.W() };
		commandList->ClearUnorderedAccessViewUint(gpuContainer.GpuHandle(gpuViewIndex), static_cast<const ShaderDataContainer&>(cpuContainer).CpuHandle(cpuViewIndex),
			&static_cast<const Texture&>(texture).Resource(), clearValue, static_cast<UINT>(clearRectsSpan.size()), clearRectsSpan.data());
	}

	void CommandList::ClearUAV(const IBuffer& buffer, const ShaderDataContainer& gpuContainer, const std::uint32_t gpuViewIndex, 
		const IShaderDataContainer& cpuContainer, const std::uint32_t cpuViewIndex,
		const Math::Vector4<float>& values, const std::span<const Math::CornerRect<std::uint32_t>> rects)
	{
		ValidateUnorderedAccess<BufferUAVMeta, Buffer>(buffer, gpuContainer, gpuViewIndex, cpuContainer, cpuViewIndex);

		arena.Free();
		const Memory::Arena::Slice<D3D12_RECT> clearRects = arena.Allocate<D3D12_RECT>(rects.size());
		const std::span<D3D12_RECT> clearRectsSpan = arena.Span(clearRects);
		for (std::size_t i = 0uz; i < rects.size(); ++i)
		{
			clearRectsSpan[i] = ToRect(rects[i]);
		}

		const FLOAT clearValue[4] = { values.X(), values.Y(), values.Z(), values.W() };
		commandList->ClearUnorderedAccessViewFloat(gpuContainer.GpuHandle(gpuViewIndex), static_cast<const ShaderDataContainer&>(cpuContainer).CpuHandle(cpuViewIndex),
			&static_cast<const Buffer&>(buffer).Resource(), clearValue, static_cast<UINT>(clearRectsSpan.size()), clearRectsSpan.data());
	}

	void CommandList::ClearUAV(const ITexture& texture, const ShaderDataContainer& gpuContainer, const std::uint32_t gpuViewIndex, 
		const IShaderDataContainer& cpuContainer, const std::uint32_t cpuViewIndex,
		const Math::Vector4<float>& values, const std::span<const Math::CornerRect<std::uint32_t>> rects)
	{
		ValidateUnorderedAccess<TextureUAVMeta, Texture>(texture, gpuContainer, gpuViewIndex, cpuContainer, cpuViewIndex);

		arena.Free();
		const Memory::Arena::Slice<D3D12_RECT> clearRects = arena.Allocate<D3D12_RECT>(rects.size());
		const std::span<D3D12_RECT> clearRectsSpan = arena.Span(clearRects);
		for (std::size_t i = 0uz; i < rects.size(); ++i)
		{
			clearRectsSpan[i] = ToRect(rects[i]);
		}

		const FLOAT clearValue[4] = { values.X(), values.Y(), values.Z(), values.W() };
		commandList->ClearUnorderedAccessViewFloat(gpuContainer.GpuHandle(gpuViewIndex), static_cast<const ShaderDataContainer&>(cpuContainer).CpuHandle(cpuViewIndex),
			&static_cast<const Texture&>(texture).Resource(), clearValue, static_cast<UINT>(clearRectsSpan.size()), clearRectsSpan.data());
	}

	void CommandList::Copy(const IBuffer& source, IBuffer& destination)
	{
		ValidateState();
		ValidateCopy(source, destination);

		commandList->CopyResource(&static_cast<Buffer&>(destination).Resource(), &static_cast<const Buffer&>(source).Resource());
	}

	void CommandList::Copy(const IBuffer& source, IBuffer& destination, const std::uint64_t sourceOffset, const std::uint64_t destinationOffset, const std::uint64_t size)
	{
		ValidateState();
		ValidateCopy(source, destination, sourceOffset, destinationOffset, size);

		commandList->CopyBufferRegion(&static_cast<Buffer&>(destination).Resource(), destinationOffset, &static_cast<const Buffer&>(source).Resource(), sourceOffset, size);
	}

	void CommandList::Copy(const ITexture& source, ITexture& destination)
	{
		ValidateState();
		ValidateCopy(source, destination);

		commandList->CopyResource(&static_cast<Texture&>(destination).Resource(), &static_cast<const Texture&>(source).Resource());
	}

	void CommandList::Copy(const ITexture& source, ITexture& destination, const CopySubTextureRange& range)
	{
		ValidateState();
		ValidateCopy(source, destination, range);

		const auto& sourceTexture = static_cast<const Texture&>(source);
		auto& destinationTexture = static_cast<Texture&>(destination);

		static constexpr std::size_t AspectCount = std::countr_one(std::to_underlying(AspectMask::All));
		auto aspects = std::array<Aspect, AspectCount>();
		const std::size_t aspectCount = ToValues(range.aspects, aspects);

		for (std::size_t aspectIndex = 0uz; aspectIndex < aspectCount; ++aspectIndex)
		{
			const Aspect aspect = aspects[aspectIndex];
			for (std::uint16_t arrayIndex = 0u; arrayIndex < range.arrayCount; ++arrayIndex)
			{
				for (std::uint8_t mipIndex = 0u; mipIndex < range.mipCount; ++mipIndex)
				{
					const D3D12_TEXTURE_COPY_LOCATION sourceLocation = ToCopyLocation(sourceTexture, static_cast<UINT16>(range.sourceMipIndex + mipIndex),
						static_cast<UINT16>(range.sourceArrayIndex + arrayIndex), aspect);
					const D3D12_TEXTURE_COPY_LOCATION destinationLocation = ToCopyLocation(destinationTexture, static_cast<UINT16>(range.destinationMipIndex + mipIndex),
						static_cast<UINT16>(range.destinationArrayIndex + arrayIndex), aspect);
					commandList->CopyTextureRegion(&destinationLocation, 0u, 0u, 0u, &sourceLocation, nullptr);
				}
			}
		}
	}

	void CommandList::Copy(const ITexture& source, ITexture& destination, const BoxCopySubTextureRange& range)
	{
		ValidateState();
		ValidateCopy(source, destination, range);

		const auto& sourceTexture = static_cast<const Texture&>(source);
		auto& destinationTexture = static_cast<Texture&>(destination);

		static constexpr std::size_t AspectCount = std::countr_one(std::to_underlying(AspectMask::All));
		auto aspects = std::array<Aspect, AspectCount>();
		const std::size_t aspectCount = ToValues(range.aspects, aspects);

		for (std::size_t aspectIndex = 0uz; aspectIndex < aspectCount; ++aspectIndex)
		{
			const Aspect aspect = aspects[aspectIndex];
			for (std::uint16_t arrayIndex = 0u; arrayIndex < range.arrayCount; ++arrayIndex)
			{
				for (std::uint8_t mipIndex = 0u; mipIndex < range.mipCount; ++mipIndex)
				{
					const D3D12_TEXTURE_COPY_LOCATION sourceLocation = ToCopyLocation(sourceTexture, static_cast<UINT16>(range.sourceMipIndex + mipIndex),
						static_cast<UINT16>(range.sourceArrayIndex + arrayIndex), aspect);
					const D3D12_TEXTURE_COPY_LOCATION destinationLocation = ToCopyLocation(destinationTexture, static_cast<UINT16>(range.destinationMipIndex + mipIndex),
						static_cast<UINT16>(range.destinationArrayIndex + arrayIndex), aspect);
					const Math::Vector3<std::uint32_t> destinationOffset = range.destinationOffsets[mipIndex];
					const D3D12_BOX sourceBox = ToBox(range.sourceOffsets[mipIndex], range.sourceSizes[mipIndex]);
					commandList->CopyTextureRegion(&destinationLocation, destinationOffset.X(), destinationOffset.Y(), destinationOffset.Z(), &sourceLocation, &sourceBox);
				}
			}
		}
	}

	void CommandList::Copy(const IBuffer& source, ITexture& destination, const std::span<const CopyableFootprint> footprints)
	{
		ValidateState();
		ValidateCopy(source, destination, footprints);

		const auto& sourceBuffer = static_cast<const Buffer&>(source);
		auto& destinationTexture = static_cast<Texture&>(destination);

		for (std::size_t i = 0uz; i < footprints.size(); ++i)
		{
			const D3D12_TEXTURE_COPY_LOCATION sourceLocation = ToCopyLocation(sourceBuffer, footprints[i], destinationTexture.NativeFormat());
			const D3D12_TEXTURE_COPY_LOCATION destinationLocation = ToCopyLocation(destinationTexture, static_cast<UINT>(i));
			commandList->CopyTextureRegion(&destinationLocation, 0u, 0u, 0u, &sourceLocation, nullptr);
		}
	}

	void CommandList::Copy(const IBuffer& source, ITexture& destination, const std::span<const CopyableFootprint> footprints, const FootprintedCopySubTextureRange& range)
	{
		ValidateState();
		ValidateCopy(source, destination, footprints, range);

		const auto& sourceBuffer = static_cast<const Buffer&>(source);
		auto& destinationTexture = static_cast<Texture&>(destination);

		for (UINT8 planeIndex = ToFirstPlaneIndex(range.aspects); planeIndex < ToPlaneCount(range.aspects); ++planeIndex)
		{
			for (std::uint16_t arrayIndex = 0u; arrayIndex < range.arrayCount; ++arrayIndex)
			{
				for (std::uint8_t mipIndex = 0u; mipIndex < range.mipCount; ++mipIndex)
				{
					const UINT subresource = CalculateSubresource(mipIndex, arrayIndex, planeIndex, destinationTexture.MipCount(), destinationTexture.ArraySize());
					const D3D12_TEXTURE_COPY_LOCATION sourceLocation = ToCopyLocation(sourceBuffer, footprints[subresource], destinationTexture.NativeFormat());
					const D3D12_TEXTURE_COPY_LOCATION destinationLocation = ToCopyLocation(destinationTexture, subresource);
					commandList->CopyTextureRegion(&destinationLocation, 0u, 0u, 0u, &sourceLocation, nullptr);
				}
			}
		}
	}

	void CommandList::Copy(const IBuffer& source, ITexture& destination, const std::span<const CopyableFootprint> footprints, const FootprintedBoxCopySubTextureRange& range)
	{
		ValidateState();
		ValidateCopy(source, destination, footprints, range, false);

		const auto& sourceBuffer = static_cast<const Buffer&>(source);
		auto& destinationTexture = static_cast<Texture&>(destination);

		for (UINT8 planeIndex = ToFirstPlaneIndex(range.aspects); planeIndex < ToPlaneCount(range.aspects); ++planeIndex)
		{
			for (std::uint16_t arrayIndex = 0u; arrayIndex < range.arrayCount; ++arrayIndex)
			{
				for (std::uint8_t mipIndex = 0u; mipIndex < range.mipCount; ++mipIndex)
				{
					const UINT subresource = CalculateSubresource(mipIndex, arrayIndex, planeIndex, destinationTexture.MipCount(), destinationTexture.ArraySize());
					const D3D12_TEXTURE_COPY_LOCATION sourceLocation = ToCopyLocation(sourceBuffer, footprints[subresource], destinationTexture.NativeFormat());
					const D3D12_TEXTURE_COPY_LOCATION destinationLocation = ToCopyLocation(destinationTexture, subresource);
					const Math::Vector3<std::uint32_t> destinationOffset = range.destinationOffsets[mipIndex];
					const D3D12_BOX sourceBox = ToBox(range.sourceOffsets[mipIndex], range.sourceSizes[mipIndex]);
					commandList->CopyTextureRegion(&destinationLocation, destinationOffset.X(), destinationOffset.Y(), destinationOffset.Z(), &sourceLocation, &sourceBox);
				}
			}
		}
	}

	void CommandList::Copy(const ITexture& source, IBuffer& destination, const std::span<const CopyableFootprint> footprints)
	{
		ValidateState();
		ValidateCopy(destination, source, footprints);

		const auto& sourceTexture = static_cast<const Texture&>(source);
		auto& destinationBuffer = static_cast<Buffer&>(destination);

		for (std::size_t i = 0uz; i < footprints.size(); ++i)
		{
			const auto sourceLocation = ToCopyLocation(sourceTexture, static_cast<UINT>(i));
			const auto destinationLocation = ToCopyLocation(destinationBuffer, footprints[i], sourceTexture.NativeFormat());
			commandList->CopyTextureRegion(&destinationLocation, 0u, 0u, 0u, &sourceLocation, nullptr);
		}
	}

	void CommandList::Copy(const ITexture& source, IBuffer& destination, const std::span<const CopyableFootprint> footprints, const FootprintedCopySubTextureRange& range)
	{
		ValidateState();
		ValidateCopy(destination, source, footprints, range);

		const auto& sourceTexture = static_cast<const Texture&>(source);
		auto& destinationBuffer = static_cast<Buffer&>(destination);

		for (UINT8 planeIndex = ToFirstPlaneIndex(range.aspects); planeIndex < ToPlaneCount(range.aspects); ++planeIndex)
		{
			for (std::uint16_t arrayIndex = 0u; arrayIndex < range.arrayCount; ++arrayIndex)
			{
				for (std::uint8_t mipIndex = 0u; mipIndex < range.mipCount; ++mipIndex)
				{
					const UINT subresource = CalculateSubresource(mipIndex, arrayIndex, planeIndex, sourceTexture.MipCount(), sourceTexture.ArraySize());
					const D3D12_TEXTURE_COPY_LOCATION sourceLocation = ToCopyLocation(sourceTexture, subresource);
					const D3D12_TEXTURE_COPY_LOCATION destinationLocation = ToCopyLocation(destinationBuffer, footprints[subresource], sourceTexture.NativeFormat());
					commandList->CopyTextureRegion(&destinationLocation, 0u, 0u, 0u, &sourceLocation, nullptr);
				}
			}
		}
	}

	void CommandList::Copy(const ITexture& source, IBuffer& destination, const std::span<const CopyableFootprint> footprints, const FootprintedBoxCopySubTextureRange& range)
	{
		ValidateState();
		ValidateCopy(destination, source, footprints, range, true);

		const auto& sourceTexture = static_cast<const Texture&>(source);
		auto& destinationBuffer = static_cast<Buffer&>(destination);

		for (UINT8 planeIndex = ToFirstPlaneIndex(range.aspects); planeIndex < ToPlaneCount(range.aspects); ++planeIndex)
		{
			for (std::uint16_t arrayIndex = 0u; arrayIndex < range.arrayCount; ++arrayIndex)
			{
				for (std::uint8_t mipIndex = 0u; mipIndex < range.mipCount; ++mipIndex)
				{
					const UINT subresource = CalculateSubresource(mipIndex, arrayIndex, planeIndex, sourceTexture.MipCount(), sourceTexture.ArraySize());
					const D3D12_TEXTURE_COPY_LOCATION sourceLocation = ToCopyLocation(sourceTexture, subresource);
					const D3D12_TEXTURE_COPY_LOCATION destinationLocation = ToCopyLocation(destinationBuffer, footprints[subresource], sourceTexture.NativeFormat());
					const Math::Vector3<std::uint32_t> destinationOffset = range.destinationOffsets[mipIndex];
					const D3D12_BOX sourceBox = ToBox(range.sourceOffsets[mipIndex], range.sourceSizes[mipIndex]);
					commandList->CopyTextureRegion(&destinationLocation, destinationOffset.X(), destinationOffset.Y(), destinationOffset.Z(), &sourceLocation, &sourceBox);
				}
			}
		}
	}

	void CommandList::Resolve(const ITexture& source, ITexture& destination, const ResolveMode mode)
	{
		ValidateState();
		ValidateResolve(source, destination);

		const auto& sourceTexture = static_cast<const Texture&>(source);
		auto& destinationTexture = static_cast<Texture&>(destination);
		const D3D12_RESOLVE_MODE resolveMode = ToResolveMode(mode);

		const AspectMask aspects = GetAspects(sourceTexture.NativeFormat());
		for (UINT8 planeIndex = ToFirstPlaneIndex(aspects); planeIndex < ToPlaneCount(aspects); ++planeIndex)
		{
			for (std::uint16_t arrayIndex = 0u; arrayIndex < sourceTexture.ArraySize(); ++arrayIndex)
			{
				for (std::uint8_t mipIndex = 0u; mipIndex < sourceTexture.MipCount(); ++mipIndex)
				{
					const UINT subresource = CalculateSubresource(mipIndex, arrayIndex, planeIndex, sourceTexture.MipCount(), sourceTexture.ArraySize());
					commandList->ResolveSubresourceRegion(&destinationTexture.Resource(), subresource, 0u, 0u, &sourceTexture.Resource(), subresource, 
						nullptr, sourceTexture.NativeFormat(), resolveMode);
				}
			}
		}
	}

	void CommandList::Resolve(const ITexture& source, ITexture& destination, const CopySubTextureRange& range, const ResolveMode mode)
	{
		ValidateState();
		ValidateResolve(source, destination, range);

		const auto& sourceTexture = static_cast<const Texture&>(source);
		auto& destinationTexture = static_cast<Texture&>(destination);
		const D3D12_RESOLVE_MODE resolveMode = ToResolveMode(mode);

		for (UINT8 planeIndex = ToFirstPlaneIndex(range.aspects); planeIndex < ToPlaneCount(range.aspects); ++planeIndex)
		{
			for (std::uint16_t arrayIndex = 0u; arrayIndex < range.arrayCount; ++arrayIndex)
			{
				for (std::uint8_t mipIndex = 0u; mipIndex < range.mipCount; ++mipIndex)
				{
					const UINT sourceSubresource = CalculateSubresource(static_cast<UINT16>(range.sourceMipIndex + mipIndex), static_cast<UINT16>(range.sourceArrayIndex + arrayIndex),
						planeIndex, sourceTexture.MipCount(), sourceTexture.ArraySize());
					const UINT destinationSubresource = CalculateSubresource(static_cast<UINT16>(range.destinationMipIndex + mipIndex), 
						static_cast<UINT16>(range.destinationArrayIndex + arrayIndex), planeIndex, sourceTexture.MipCount(), sourceTexture.ArraySize());
					commandList->ResolveSubresourceRegion(&destinationTexture.Resource(), destinationSubresource, 0u, 0u, &sourceTexture.Resource(), sourceSubresource,
						nullptr, sourceTexture.NativeFormat(), resolveMode);
				}
			}
		}
	}

	void CommandList::Resolve(const ITexture& source, ITexture& destination, const BoxCopySubTextureRange& range, const ResolveMode mode)
	{
		ValidateState();
		ValidateResolve(source, destination, range);

		const auto& sourceTexture = static_cast<const Texture&>(source);
		auto& destinationTexture = static_cast<Texture&>(destination);
		const D3D12_RESOLVE_MODE resolveMode = ToResolveMode(mode);

		for (UINT8 planeIndex = ToFirstPlaneIndex(range.aspects); planeIndex < ToPlaneCount(range.aspects); ++planeIndex)
		{
			for (std::uint16_t arrayIndex = 0u; arrayIndex < range.arrayCount; ++arrayIndex)
			{
				for (std::uint8_t mipIndex = 0u; mipIndex < range.mipCount; ++mipIndex)
				{
					const UINT sourceSubresource = CalculateSubresource(static_cast<UINT16>(range.sourceMipIndex + mipIndex), static_cast<UINT16>(range.sourceArrayIndex + arrayIndex),
						planeIndex, sourceTexture.MipCount(), sourceTexture.ArraySize());
					const UINT destinationSubresource = CalculateSubresource(static_cast<UINT16>(range.destinationMipIndex + mipIndex),
						static_cast<UINT16>(range.destinationArrayIndex + arrayIndex), planeIndex, sourceTexture.MipCount(), sourceTexture.ArraySize());
					const auto destinationOffset = Math::Vector2<std::uint32_t>(range.destinationOffsets[mipIndex].X(), range.destinationOffsets[mipIndex].Y());
					D3D12_RECT sourceRect = ToRect(range.sourceOffsets[mipIndex], range.sourceSizes[mipIndex]);
					commandList->ResolveSubresourceRegion(&destinationTexture.Resource(), destinationSubresource, destinationOffset.X(), destinationOffset.Y(), 
						&sourceTexture.Resource(), sourceSubresource, &sourceRect, sourceTexture.NativeFormat(), resolveMode);
				}
			}
		}
	}

	void CommandList::ExecuteBundle(ID3D12GraphicsCommandList10& bundle) noexcept
	{
		ValidateState();
		commandList->ExecuteBundle(&bundle);
	}

	void CommandList::ValidateState() const
	{
#ifndef NDEBUG
		if (!isOpen) [[unlikely]]
		{
			throw std::logic_error("Command list is closed");
		}
#endif
	}

	void CommandList::ValidateContainers(const IShaderDataContainer* const shaderDataContainer, const ISamplerContainer* const samplerContainer) const
	{
		ValidateState();

#ifndef NDEBUG
		if (shaderDataContainer)
		{
			if (typeid(*shaderDataContainer) != typeid(ShaderDataContainer)) [[unlikely]]
			{
				throw std::invalid_argument("Invalid shader data container");
			}

			if (!static_cast<const ShaderDataContainer*>(shaderDataContainer)->IsShaderVisible()) [[unlikely]]
			{
				throw std::invalid_argument("Shader data container is not shader visible");
			}
		}

		if (samplerContainer)
		{
			if (typeid(*samplerContainer) != typeid(SamplerContainer)) [[unlikely]]
			{
				throw std::invalid_argument("Invalid sampler container");
			}

			if (!static_cast<const SamplerContainer*>(samplerContainer)->IsShaderVisible()) [[unlikely]]
			{
				throw std::invalid_argument("Sampler container is not shader visible");
			}
		}
#endif
	}

	void CommandList::ValidatePipelineState(const IGraphicsPipelineState& pipelineState) const
	{
		ValidateState();

#ifndef NDEBUG
		if (typeid(pipelineState) != typeid(GraphicsPipelineState)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid pipeline state");
		}
#endif
	}

	void CommandList::ValidatePipelineState(const IComputePipelineState& pipelineState) const
	{
		ValidateState();

#ifndef NDEBUG
		if (typeid(pipelineState) != typeid(ComputePipelineState)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid pipeline state");
		}
#endif
	}

	std::string_view CommandList::Name() const noexcept
	{
		return name;
	}

	void CommandList::Name(const std::string_view name)
	{
		SetObjectName(*allocator, name);

		try
		{
			SetObjectName(*commandList, name);

			try
			{
				this->name = name;
			}
			catch (...)
			{
				SetObjectName(*commandList, this->name);
				throw;
			}
		}
		catch (...)
		{
			SetObjectName(*allocator, this->name);
			throw;
		}
	}

	void CommandList::ToNativeBarriers(const std::span<const BufferBarrier> bufferBarriers, const std::span<D3D12_BUFFER_BARRIER> nativeBufferBarriers) noexcept
	{
		for (std::size_t i = 0uz; i < bufferBarriers.size(); ++i)
		{
			const BufferBarrier& barrier = bufferBarriers[i];
			nativeBufferBarriers[i] = D3D12_BUFFER_BARRIER
			{
				.SyncBefore = ToSync(barrier.beforeStages),
				.SyncAfter = ToSync(barrier.afterStages),
				.AccessBefore = ToAccess(barrier.beforeAccesses),
				.AccessAfter = ToAccess(barrier.afterAccesses),
				.pResource = &static_cast<Buffer*>(barrier.buffer)->Resource(),
				.Offset = 0ull,
				.Size = std::numeric_limits<UINT64>::max()
			};
		}
	}

	void CommandList::ToNativeBarriers(const std::span<const TextureBarrier> textureBarriers, const std::span<D3D12_TEXTURE_BARRIER> nativeTextureBarriers) noexcept
	{
		for (std::size_t i = 0uz; i < textureBarriers.size(); ++i)
		{
			const TextureBarrier& barrier = textureBarriers[i];
			const auto texture = static_cast<Texture*>(barrier.texture);
			nativeTextureBarriers[i] = D3D12_TEXTURE_BARRIER
			{
				.SyncBefore = ToSync(barrier.beforeStages),
				.SyncAfter = ToSync(barrier.afterStages),
				.AccessBefore = ToAccess(barrier.beforeAccesses),
				.AccessAfter = ToAccess(barrier.afterAccesses),
				.LayoutBefore = ToLayout(barrier.beforeLayout),
				.LayoutAfter = ToLayout(barrier.afterLayout),
				.pResource = &texture->Resource(),
				.Subresources = barrier.range 
					? ToSubresourceRange(barrier.range->mipRange, barrier.range->arrayRange, barrier.range->aspects, texture->MipCount(), texture->ArraySize())
					: static_cast<D3D12_BARRIER_SUBRESOURCE_RANGE>(D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES),
				.Flags = barrier.discard ? D3D12_TEXTURE_BARRIER_FLAG_DISCARD : D3D12_TEXTURE_BARRIER_FLAG_NONE
			};
		}
	}

	void CommandList::ToViewports(const std::span<const RasterRegion> regions, const std::span<D3D12_VIEWPORT> viewports) noexcept
	{
		for (std::size_t i = 0uz; i < regions.size(); ++i)
		{
			const RasterRegion& region = regions[i];
			viewports[i] = D3D12_VIEWPORT
			{
				.TopLeftX = region.viewport.Position().X(),
				.TopLeftY = region.viewport.Position().Y(),
				.Width = region.viewport.Size().X(),
				.Height = region.viewport.Size().Y(),
				.MinDepth = region.depthRange.min,
				.MaxDepth = region.depthRange.max
			};
		}
	}

	void CommandList::ToScissors(const std::span<const RasterRegion> regions, const std::span<D3D12_RECT> rects) noexcept
	{
		for (std::size_t i = 0uz; i < regions.size(); ++i)
		{
			const RasterRegion& region = regions[i];
			rects[i] = D3D12_RECT
			{
				.left = static_cast<LONG>(region.scissor.Position().X()),
				.top = static_cast<LONG>(region.scissor.Position().Y()),
				.right = static_cast<LONG>(region.scissor.Position().X() + region.scissor.Size().X()),
				.bottom = static_cast<LONG>(region.scissor.Position().Y() + region.scissor.Size().Y())
			};
		}
	}

	D3D12_TEXTURE_COPY_LOCATION CommandList::ToCopyLocation(const Buffer& buffer, const CopyableFootprint& footprint, const DXGI_FORMAT format) noexcept
	{
		return D3D12_TEXTURE_COPY_LOCATION
		{
			.pResource = &buffer.Resource(),
			.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT,
			.PlacedFootprint = D3D12_PLACED_SUBRESOURCE_FOOTPRINT
			{
				.Offset = footprint.offset,
				.Footprint = D3D12_SUBRESOURCE_FOOTPRINT
				{
					.Format = format,
					.Width = footprint.width,
					.Height = footprint.height,
					.Depth = footprint.sliceCount,
					.RowPitch = footprint.rowPitch
				}
			}
		};
	}

	D3D12_TEXTURE_COPY_LOCATION CommandList::ToCopyLocation(const Texture& texture, const UINT16 mipIndex, const UINT16 arrayIndex, const Aspect aspect) noexcept
	{
		return D3D12_TEXTURE_COPY_LOCATION
		{
			.pResource = &texture.Resource(),
			.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX,
			.SubresourceIndex = CalculateSubresource(mipIndex, arrayIndex, ToPlaneIndex(aspect), texture.MipCount(), texture.ArraySize())
		};
	}

	D3D12_TEXTURE_COPY_LOCATION CommandList::ToCopyLocation(const Texture& texture, const UINT subresourceIndex) noexcept
	{
		return D3D12_TEXTURE_COPY_LOCATION
		{
			.pResource = &texture.Resource(),
			.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX,
			.SubresourceIndex = subresourceIndex
		};
	}

	D3D12_RECT CommandList::ToRect(const Math::CornerRect<std::uint32_t>& rect) noexcept
	{
		return D3D12_RECT
		{
			.left = static_cast<LONG>(rect.Position().X()),
			.top = static_cast<LONG>(rect.Position().Y()),
			.right = static_cast<LONG>(rect.Position().X() + rect.Size().X()),
			.bottom = static_cast<LONG>(rect.Position().Y() + rect.Size().Y()),
		};
	}

	D3D12_RECT CommandList::ToRect(const Math::Vector3<std::uint32_t>& offset, const Math::Vector3<std::uint32_t>& size) noexcept
	{
		return D3D12_RECT
		{
			.left = static_cast<LONG>(offset.X()),
			.top = static_cast<LONG>(offset.Y()),
			.right = static_cast<LONG>(offset.X() + size.X()),
			.bottom = static_cast<LONG>(offset.Y() + size.Y()),
		};
	}

	D3D12_BOX CommandList::ToBox(const Math::Vector3<std::uint32_t>& offset, const Math::Vector3<std::uint32_t>& size) noexcept
	{
		return D3D12_BOX
		{
			.left = offset.X(),
			.top = offset.Y(),
			.front = offset.Z(),
			.right = offset.X() + size.X(),
			.bottom = offset.Y() + size.Y(),
			.back = offset.Z() + size.Z()
		};
	}

	void CommandList::ValidateBarriers(const std::span<const BufferBarrier> bufferBarriers)
	{
#ifndef NDEBUG
		if (bufferBarriers.size() > std::numeric_limits<UINT32>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Too many buffer barriers");
		}

		for (const BufferBarrier& barrier : bufferBarriers)
		{
			if (!barrier.buffer || typeid(*barrier.buffer) != typeid(Buffer)) [[unlikely]]
			{
				throw std::invalid_argument("Invalid buffer");
			}
		}
#endif
	}

	void CommandList::ValidateBarriers(const std::span<const TextureBarrier> textureBarriers)
	{
#ifndef NDEBUG
		if (textureBarriers.size() > std::numeric_limits<UINT32>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Too many texture barriers");
		}

		for (const TextureBarrier& barrier : textureBarriers)
		{
			if (!barrier.texture || typeid(*barrier.texture) != typeid(Texture)) [[unlikely]]
			{
				throw std::invalid_argument("Invalid texture");
			}

			if (barrier.range)
			{
				const Texture* const texture = static_cast<Texture*>(barrier.texture);
				const MultiAspectSubTextureRange& range = *barrier.range;

				if (range.mipRange.mostDetailedMipIndex + range.mipRange.mipCount.value_or(1u) > texture->MipCount()) [[unlikely]]
				{
					throw std::invalid_argument("Invalid mip range");
				}
				if (range.arrayRange.firstArrayIndex + range.arrayRange.arrayCount.value_or(1u) > texture->ArraySize()) [[unlikely]]
				{
					throw std::invalid_argument("Invalid array range");
				}
			}

			if (barrier.discard && barrier.beforeLayout != ResourceLayout::Undefined) [[unlikely]]
			{
				throw std::invalid_argument("Invalid discard flag");
			}
		}
#endif
	}

	void CommandList::ValidateRasterRegion(const std::span<const RasterRegion> regions)
	{
#ifndef NDEBUG
		if (regions.size() > D3D12_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE) [[unlikely]]
		{
			throw std::invalid_argument("Region count is too great");
		}
#endif
	}

	void CommandList::ValidateRenderTargets(const std::span<const RenderTargetBinding> renderTargetBindings)
	{
#ifndef NDEBUG
		if (renderTargetBindings.size() > D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT) [[unlikely]]
		{
			throw std::invalid_argument("Render target binding count is too great");
		}

		for (const RenderTargetBinding& binding : renderTargetBindings)
		{
			if (!binding.container || typeid(*binding.container) != typeid(RenderTargetContainer)) [[unlikely]]
			{
				throw std::invalid_argument("Invalid render target container");
			}

			const auto container = static_cast<const RenderTargetContainer*>(binding.container);
			if (binding.index >= container->Size()) [[unlikely]]
			{
				throw std::invalid_argument("Index is too great");
			}
			if (std::holds_alternative<EmptyRenderTargetMeta>(container->Meta(binding.index))) [[unlikely]]
			{
				throw std::invalid_argument("Invalid render target view");
			}
		}
#endif
	}

	void CommandList::ValidateRenderTargets(const RenderTargetBinding* const renderTargetBinding, const std::uint8_t renderTargetCount)
	{
#ifndef NDEBUG
		if (renderTargetCount == 0u)
		{
			return;
		}

		if (renderTargetCount > D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT) [[unlikely]]
		{
			throw std::invalid_argument("Render target binding count is too great");
		}
		if (renderTargetCount > 0u && !renderTargetBinding) [[unlikely]]
		{
			throw std::invalid_argument("Render target binding is nullptr");
		}

		if (!renderTargetBinding->container || typeid(*renderTargetBinding->container) != typeid(RenderTargetContainer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid render target container");
		}

		const auto container = static_cast<const RenderTargetContainer*>(renderTargetBinding->container);
		if (renderTargetBinding->index >= container->Size()) [[unlikely]]
		{
			throw std::invalid_argument("Index is too great");
		}

		for (std::uint8_t i = 0u; i < renderTargetCount; ++i)
		{
			if (std::holds_alternative<EmptyRenderTargetMeta>(container->Meta(renderTargetBinding->index + i))) [[unlikely]]
			{
				throw std::invalid_argument("Invalid render target view");
			}
		}
#endif
	}

	void CommandList::ValidateDepthTarget(const DepthStencilBinding* const binding)
	{
#ifndef NDEBUG
		if (!binding)
		{
			return;
		}

		if (!binding->container || typeid(*binding->container) != typeid(DepthStencilBinding)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid depth stencil container");
		}

		const auto container = static_cast<const DepthStencilContainer*>(binding->container);
		if (binding->index >= container->Size()) [[unlikely]]
		{
			throw std::invalid_argument("Index is too great");
		}
		if (std::holds_alternative<EmptyDepthStencilMeta>(container->Meta(binding->index))) [[unlikely]]
		{
			throw std::invalid_argument("Invalid depth stencil view");
		}
#endif
	}

	void CommandList::ValidateRenderTarget(const IRenderTargetContainer& container, const std::uint32_t viewIndex)
	{
		ValidateState();

#ifndef NDEBUG
		if (typeid(container) != typeid(RenderTargetContainer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid container");
		}

		const auto& nativeContainer = static_cast<const RenderTargetContainer&>(container);
		if (viewIndex >= nativeContainer.Size() || std::holds_alternative<EmptyRenderTargetMeta>(nativeContainer.Meta(viewIndex))) [[unlikely]]
		{
			throw std::invalid_argument("Invalid view index");
		}
#endif
	}

	void CommandList::ValidateDepthStencil(const IDepthStencilContainer& container, std::uint32_t viewIndex)
	{
		ValidateState();

#ifndef NDEBUG
		if (typeid(container) != typeid(DepthStencilContainer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid container");
		}

		const auto& nativeContainer = static_cast<const DepthStencilContainer&>(container);
		if (viewIndex >= nativeContainer.Size() || std::holds_alternative<EmptyDepthStencilMeta>(nativeContainer.Meta(viewIndex))) [[unlikely]]
		{
			throw std::invalid_argument("Invalid view index");
		}
#endif
	}

	template<typename UAVMeta, typename NativeResource, typename Resource>
	void CommandList::ValidateUnorderedAccess(const Resource& resource, const ShaderDataContainer& gpuContainer, const std::uint32_t gpuViewIndex,
		const IShaderDataContainer& cpuContainer, const std::uint32_t cpuViewIndex)
	{
		ValidateState();

#ifndef NDEBUG
		if (typeid(resource) != typeid(NativeResource)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid resource");
		}
		if (typeid(cpuContainer) != typeid(ShaderDataContainer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid cpu container");
		}

		const auto& nativeCpuContainer = static_cast<const ShaderDataContainer&>(cpuContainer);
		if (nativeCpuContainer.IsShaderVisible()) [[unlikely]]
		{
			throw std::invalid_argument("Cpu container is shader visible");
		}

		if (gpuViewIndex >= gpuContainer.Size()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid gpu container index");
		}
		if (cpuViewIndex >= nativeCpuContainer.Size()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid cpu container index");
		}

		if (!std::holds_alternative<UAVMeta>(gpuContainer.Meta(gpuViewIndex))) [[unlikely]]
		{
			throw std::invalid_argument("Invalid gpu view");
		}
		if (!std::holds_alternative<UAVMeta>(nativeCpuContainer.Meta(cpuViewIndex))) [[unlikely]]
		{
			throw std::invalid_argument("Invalid cpu view");
		}

		if (std::get<UAVMeta>(gpuContainer.Meta(gpuViewIndex)).resource != &resource ||
			std::get<UAVMeta>(nativeCpuContainer.Meta(cpuViewIndex)).resource != &resource) [[unlikely]]
		{
			throw std::invalid_argument("Resource mismatch");
		}
#endif
	}

	void CommandList::ValidateCopy(const IBuffer& source, const IBuffer& destination)
	{
		ValidateCopyBase(source, destination);

#ifndef NDEBUG
		if (static_cast<const Buffer&>(source).Size() != static_cast<const Buffer&>(destination).Size()) [[unlikely]]
		{
			throw std::invalid_argument("Buffer sizes don't match");
		}
#endif
	}

	void CommandList::ValidateCopy(const IBuffer& source, const IBuffer& destination, const std::uint64_t sourceOffset, const std::uint64_t destinationOffset, 
		const std::uint64_t size)
	{
		ValidateCopyBase(source, destination);

#ifndef NDEBUG
		if (std::numeric_limits<std::uint64_t>::max() - sourceOffset < size || std::numeric_limits<std::uint64_t>::max() - destinationOffset < size) [[unlikely]]
		{
			throw std::invalid_argument("Invalid size");
		}

		if (static_cast<const Buffer&>(source).Size() < sourceOffset + size) [[unlikely]]
		{
			throw std::invalid_argument("Source buffer is too small");
		}
		if (static_cast<const Buffer&>(destination).Size() < destinationOffset + size) [[unlikely]]
		{
			throw std::invalid_argument("Destination buffer is too small");
		}
#endif
	}

	void CommandList::ValidateCopyBase(const IBuffer& source, const IBuffer& destination)
	{
#ifndef NDEBUG
		if (&source == &destination) [[unlikely]]
		{
			throw std::invalid_argument("Source and destination are the same");
		}

		if (typeid(source) != typeid(Buffer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid source buffer");
		}
		if (typeid(destination) != typeid(Buffer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid destination buffer");
		}
#endif
	}

	void CommandList::ValidateCopy(const ITexture& source, const ITexture& destination)
	{
		ValidateCopyBase(source, destination);

#ifndef NDEBUG
		const Texture& sourceTexture = static_cast<const Texture&>(source);
		const Texture& destinationTexture = static_cast<const Texture&>(destination);

		if (sourceTexture.MipCount() != destinationTexture.MipCount()) [[unlikely]]
		{
			throw std::invalid_argument("Texture mip counts don't match");
		}
		if (sourceTexture.ArraySize() != destinationTexture.ArraySize()) [[unlikely]]
		{
			throw std::invalid_argument("Texture mip counts don't match");
		}

		if (GetAspects(sourceTexture.NativeFormat()) != GetAspects(destinationTexture.NativeFormat())) [[unlikely]]
		{
			throw std::invalid_argument("Texture aspects don't match");
		}
#endif
	}

	void CommandList::ValidateCopy(const ITexture& source, const ITexture& destination, const CopySubTextureRange& range)
	{
		ValidateCopyBase(source, destination);

#ifndef NDEBUG
		const auto& sourceTexture = static_cast<const Texture&>(source);
		const auto& destinationTexture = static_cast<const Texture&>(destination);

		if (range.sourceMipIndex + range.mipCount > sourceTexture.MipCount() || range.destinationMipIndex + range.mipCount > destinationTexture.MipCount()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid mip range");
		}
		if (range.sourceArrayIndex + range.arrayCount > sourceTexture.ArraySize() || range.destinationArrayIndex + range.arrayCount > destinationTexture.ArraySize()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid array range");
		}
		
		if (!All(range.aspects, GetAspects(sourceTexture.NativeFormat())) || !All(range.aspects, GetAspects(destinationTexture.NativeFormat()))) [[unlikely]]
		{
			throw std::invalid_argument("Invalid aspect");
		}
#endif
	}

	void CommandList::ValidateCopy(const ITexture& source, const ITexture& destination, const BoxCopySubTextureRange& range)
	{
		ValidateCopyBase(source, destination);

#ifndef NDEBUG
		const auto& sourceTexture = static_cast<const Texture&>(source);
		const auto& destinationTexture = static_cast<const Texture&>(destination);

		if (range.sourceMipIndex + range.mipCount > sourceTexture.MipCount() || range.destinationMipIndex + range.mipCount > destinationTexture.MipCount()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid mip range");
		}
		if (range.sourceArrayIndex + range.arrayCount > sourceTexture.ArraySize() || range.destinationArrayIndex + range.arrayCount > destinationTexture.ArraySize()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid array range");
		}

		if (!All(range.aspects, GetAspects(sourceTexture.NativeFormat())) || !All(range.aspects, GetAspects(destinationTexture.NativeFormat()))) [[unlikely]]
		{
			throw std::invalid_argument("Invalid aspect");
		}

		if (range.sourceOffsets.size() != range.mipCount) [[unlikely]]
		{
			throw std::invalid_argument("Invalid source offsets");
		}
		if (range.destinationOffsets.size() != range.mipCount) [[unlikely]]
		{
			throw std::invalid_argument("Invalid destination offsets");
		}
		if (range.sourceSizes.size() != range.mipCount) [[unlikely]]
		{
			throw std::invalid_argument("Invalid source sizes");
		}

		const Math::Vector3<std::uint32_t> sourceSize = sourceTexture.Size();
		const Math::Vector3<std::uint32_t> destinationSize = destinationTexture.Size();
		for (std::uint8_t i = 0u; i < range.mipCount; ++i)
		{
			const Math::Vector3<std::uint32_t> sourceMipSize = MipSize(sourceSize, range.sourceMipIndex + i);
			const Math::Vector3<std::uint32_t> destinationMipSize = MipSize(destinationSize, range.destinationMipIndex + i);

			const Math::Vector3<std::uint32_t> sourceRequiredSize = range.sourceOffsets[i] + range.sourceSizes[i];
			if (sourceRequiredSize.X() > sourceMipSize.X() || sourceRequiredSize.Y() > sourceMipSize.Y() || sourceRequiredSize.Z() > sourceMipSize.Z()) [[unlikely]]
			{
				throw std::invalid_argument("Source box is too great");
			}

			const Math::Vector3<std::uint32_t> destinationRequiredSize = range.destinationOffsets[i];
			if (destinationRequiredSize.X() >= destinationMipSize.X() || destinationRequiredSize.Y() >= destinationMipSize.Y() || destinationRequiredSize.Z() >= destinationMipSize.Z()) [[unlikely]]
			{
				throw std::invalid_argument("Destination size is too little");
			}
		}
#endif
	}

	void CommandList::ValidateCopyBase(const ITexture& source, const ITexture& destination)
	{
#ifndef NDEBUG
		if (&source == &destination) [[unlikely]]
		{
			throw std::invalid_argument("Source and destination are the same");
		}

		if (typeid(source) != typeid(Texture)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid source texture");
		}
		if (typeid(destination) != typeid(Texture)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid destination texture");
		}

		const auto& sourceTexture = static_cast<const Texture&>(source);
		const auto& destinationTexture = static_cast<const Texture&>(destination);

		if (sourceTexture.Dimension() != destinationTexture.Dimension()) [[unlikely]]
		{
			throw std::invalid_argument("Texture dimensions don't match");
		}
		if (sourceTexture.SampleCount() != destinationTexture.SampleCount()) [[unlikely]]
		{
			throw std::invalid_argument("Texture sample counts don't match");
		}
#endif
	}

	void CommandList::ValidateCopy(const IBuffer& buffer, const ITexture& texture, const std::span<const CopyableFootprint> footprints)
	{
		ValidateCopyBase(buffer, texture, footprints);
	}

	void CommandList::ValidateCopy(const IBuffer& buffer, const ITexture& texture, const std::span<const CopyableFootprint> footprints, const FootprintedCopySubTextureRange& range)
	{
		ValidateCopyBase(buffer, texture, footprints);

#ifndef NDEBUG
		const auto& destinationTexture = static_cast<const Texture&>(texture);

		if ((range.mipIndex + range.mipCount) * (range.arrayIndex + range.arrayCount) * ToPlaneCount(range.aspects) > footprints.size()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid range");
		}
		if (range.mipIndex + range.mipCount > destinationTexture.MipCount()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid mip range");
		}
		if (range.arrayIndex + range.arrayCount > destinationTexture.ArraySize()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid array range");
		}
		if (!All(range.aspects, GetAspects(destinationTexture.NativeFormat()))) [[unlikely]]
		{
			throw std::invalid_argument("Invalid aspect range");
		}
#endif
	}

	void CommandList::ValidateCopy(const IBuffer& buffer, const ITexture& texture, const std::span<const CopyableFootprint> footprints, const FootprintedBoxCopySubTextureRange& range,
		const bool textureSource)
	{
		ValidateCopyBase(buffer, texture, footprints);

#ifndef NDEBUG
		const auto& nativeTexture = static_cast<const Texture&>(texture);

		if ((range.mipIndex + range.mipCount) * (range.arrayIndex + range.arrayCount) * ToPlaneCount(range.aspects) > footprints.size()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid range");
		}
		if (range.mipIndex + range.mipCount > nativeTexture.MipCount()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid mip range");
		}
		if (range.arrayIndex + range.arrayCount > nativeTexture.ArraySize()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid array range");
		}
		if (!All(range.aspects, GetAspects(nativeTexture.NativeFormat()))) [[unlikely]]
		{
			throw std::invalid_argument("Invalid aspect range");
		}

		if (range.sourceOffsets.size() != range.mipCount) [[unlikely]]
		{
			throw std::invalid_argument("Invalid source offsets");
		}
		if (range.destinationOffsets.size() != range.mipCount) [[unlikely]]
		{
			throw std::invalid_argument("Invalid destination offsets");
		}
		if (range.sourceSizes.size() != range.mipCount) [[unlikely]]
		{
			throw std::invalid_argument("Invalid source sizes");
		}

		const Math::Vector3<std::uint32_t> textureSize = nativeTexture.Size();
		if (textureSource)
		{
			for (std::uint8_t i = 0u; i < range.mipCount; ++i)
			{
				const Math::Vector3<std::uint32_t> mipSize = MipSize(textureSize, range.mipIndex + i);
				const Math::Vector3<std::uint32_t> requiredSize = range.sourceOffsets[i] + range.sourceSizes[i];

				if (requiredSize.X() > mipSize.X() || requiredSize.Y() > mipSize.Y() || requiredSize.Z() > mipSize.Z()) [[unlikely]]
				{
					throw std::invalid_argument("Source box is too great");
				}
			}
		}
		else
		{
			for (std::uint8_t i = 0u; i < range.mipCount; ++i)
			{
				const Math::Vector3<std::uint32_t> mipSize = MipSize(textureSize, range.mipIndex + i);
				const Math::Vector3<std::uint32_t> requiredSize = range.destinationOffsets[i];

				if (requiredSize.X() >= mipSize.X() || requiredSize.Y() >= mipSize.Y() || requiredSize.Z() >= mipSize.Z()) [[unlikely]]
				{
					throw std::invalid_argument("Destination size is too little");
				}
			}
		}
#endif
	}

	void CommandList::ValidateCopyBase(const IBuffer& buffer, const ITexture& texture, const std::span<const CopyableFootprint> footprints)
	{
#ifndef NDEBUG
		if (typeid(buffer) != typeid(Buffer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid buffer");
		}
		if (typeid(texture) != typeid(Texture)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid texture");
		}

		// Skip validating footprints - it's too complicated to validate them thoroughly.
#endif
	}

	void CommandList::ValidateResolve(const ITexture& source, const ITexture& destination)
	{
		ValidateResolveBase(source, destination);

#ifndef NDEBUG
		const auto& sourceTexture = static_cast<const Texture&>(source);
		const auto& destinationTexture = static_cast<const Texture&>(destination);

		if (sourceTexture.Size() != destinationTexture.Size()) [[unlikely]]
		{
			throw std::invalid_argument("Texture sizes don't match");
		}
		if (sourceTexture.MipCount() != destinationTexture.MipCount()) [[unlikely]]
		{
			throw std::invalid_argument("Texture mip counts don't match");
		}
		if (sourceTexture.ArraySize() != destinationTexture.ArraySize()) [[unlikely]]
		{
			throw std::invalid_argument("Texture array sizes don't match");
		}
#endif
	}

	void CommandList::ValidateResolve(const ITexture& source, const ITexture& destination, const CopySubTextureRange& range)
	{
		ValidateResolveBase(source, destination);

#ifndef NDEBUG
		const auto& sourceTexture = static_cast<const Texture&>(source);
		const auto& destinationTexture = static_cast<const Texture&>(destination);

		if (range.sourceMipIndex + range.mipCount > sourceTexture.MipCount() || range.destinationMipIndex + range.mipCount > destinationTexture.MipCount()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid mip range");
		}
		if (range.sourceArrayIndex + range.arrayCount > sourceTexture.ArraySize() || range.destinationArrayIndex + range.arrayCount > destinationTexture.ArraySize()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid array range");
		}

		if (!All(range.aspects, GetAspects(sourceTexture.NativeFormat())) || !All(range.aspects, GetAspects(destinationTexture.NativeFormat()))) [[unlikely]]
		{
			throw std::invalid_argument("Invalid aspect");
		}

		if (MipSize(sourceTexture.Size(), range.sourceMipIndex) != MipSize(destinationTexture.Size(), range.destinationMipIndex)) [[unlikely]]
		{
			throw std::invalid_argument("Texture mipped sizes don't match");
		}
#endif
	}

	void CommandList::ValidateResolve(const ITexture& source, const ITexture& destination, const BoxCopySubTextureRange& range)
	{
		ValidateResolveBase(source, destination);

#ifndef NDEBUG
		const auto& sourceTexture = static_cast<const Texture&>(source);
		const auto& destinationTexture = static_cast<const Texture&>(destination);

		if (range.sourceMipIndex + range.mipCount > sourceTexture.MipCount() || range.destinationMipIndex + range.mipCount > destinationTexture.MipCount()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid mip range");
		}
		if (range.sourceArrayIndex + range.arrayCount > sourceTexture.ArraySize() || range.destinationArrayIndex + range.arrayCount > destinationTexture.ArraySize()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid array range");
		}

		if (!All(range.aspects, GetAspects(sourceTexture.NativeFormat())) || !All(range.aspects, GetAspects(destinationTexture.NativeFormat()))) [[unlikely]]
		{
			throw std::invalid_argument("Invalid aspect");
		}

		const Math::Vector3<std::uint32_t> sourceSize = sourceTexture.Size();
		const Math::Vector3<std::uint32_t> destinationSize = destinationTexture.Size();
		for (std::uint8_t i = 0u; i < range.mipCount; ++i)
		{
			const Math::Vector3<std::uint32_t> sourceMipSize = MipSize(sourceSize, range.sourceMipIndex + i);
			const Math::Vector3<std::uint32_t> destinationMipSize = MipSize(destinationSize, range.destinationMipIndex + i);

			const Math::Vector3<std::uint32_t> sourceRequiredSize = range.sourceOffsets[i] + range.sourceSizes[i];
			if (sourceRequiredSize.X() > sourceMipSize.X() || sourceRequiredSize.Y() > sourceMipSize.Y() || sourceRequiredSize.Z() > sourceMipSize.Z()) [[unlikely]]
			{
				throw std::invalid_argument("Source box is too great");
			}

			const Math::Vector3<std::uint32_t> destinationRequiredSize = range.destinationOffsets[i];
			if (destinationRequiredSize.X() >= destinationMipSize.X() || destinationRequiredSize.Y() >= destinationMipSize.Y() || destinationRequiredSize.Z() >= destinationMipSize.Z()) [[unlikely]]
			{
				throw std::invalid_argument("Destination size is too little");
			}
		}
#endif
	}

	void CommandList::ValidateResolveBase(const ITexture& source, const ITexture& destination)
	{
#ifndef NDEBUG
		if (&source == &destination) [[unlikely]]
		{
			throw std::invalid_argument("Source and destination are the same");
		}

		if (typeid(source) != typeid(Texture)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid source texture");
		}
		if (typeid(destination) != typeid(Texture)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid destination texture");
		}

		const auto& sourceTexture = static_cast<const Texture&>(source);
		const auto& destinationTexture = static_cast<const Texture&>(destination);

		if (sourceTexture.Dimension() != destinationTexture.Dimension()) [[unlikely]]
		{
			throw std::invalid_argument("Texture dimensions don't match");
		}
		if (ToNumber(sourceTexture.SampleCount()) <= 1u) [[unlikely]]
		{
			throw std::invalid_argument("Source texture is not multi-sampled");
		}
		if (ToNumber(destinationTexture.SampleCount()) > 1u) [[unlikely]]
		{
			throw std::invalid_argument("Destination texture is multi-sampled");
		}
		if (sourceTexture.NativeFormat() != destinationTexture.NativeFormat()) [[unlikely]]
		{
			throw std::invalid_argument("Texture formats don't match");
		}
#endif
	}
}
