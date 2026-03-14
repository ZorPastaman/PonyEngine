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
import :BufferUtility;
import :CommandListUtility;
import :ComputePipelineState;
import :DepthStencilContainer;
import :DescriptorHeapUtility;
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
	/// @brief Command list wrapper.
	class CommandList final
	{
	public:
		/// @brief Creates a command list wrapper.
		/// @param allocator Command allocator.
		/// @param commandList Command list.
		[[nodiscard("Pure constructor")]]
		CommandList(ID3D12CommandAllocator& allocator, ID3D12GraphicsCommandList10& commandList);
		/// @brief Creates a command list wrapper.
		/// @param allocator Command allocator.
		/// @param commandList Command list.
		[[nodiscard("Pure constructor")]]
		CommandList(Platform::Windows::ComPtr<ID3D12CommandAllocator>&& allocator, Platform::Windows::ComPtr<ID3D12GraphicsCommandList10>&& commandList);
		CommandList(const CommandList&) = delete;
		CommandList(CommandList&&) = delete;

		~CommandList() noexcept = default;

		/// @brief Gets the command list.
		/// @return Command list.
		[[nodiscard("Pure function")]]
		ID3D12GraphicsCommandList10& GetCommandList() const noexcept;

		/// @brief Resets the command allocator and command list.
		void Reset();
		/// @brief Closes the command list.
		void Close();
		/// @brief Checks if the command list is open.
		/// @return @a True if it's open; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsOpen() const noexcept;

		/// @brief Adds barriers to the command list.
		/// @param bufferBarriers Buffer barriers.
		/// @param textureBarriers Texture barriers.
		void Barrier(std::span<const BufferBarrier> bufferBarriers, std::span<const TextureBarrier> textureBarriers);

		/// @brief Sets the raster regions.
		/// @param regions Raster regions.
		void SetRasterRegions(std::span<const RasterRegion> regions);
		/// @brief Sets the depth bias.
		/// @param bias Depth bias.
		void SetDepthBias(const DepthBias& bias);
		/// @brief Sets the depth range.
		/// @param range Depth range.
		void SetDepthBounds(const DepthRange& range);
		/// @brief Sets the stencil reference.
		/// @param reference Stencil reference.
		void SetStencilReference(const StencilReference& reference);
		/// @brief Sets the blend factor.
		/// @param factor Blend factor.
		void SetBlendFactor(const Math::ColorRGBA<float>& factor);

		/// @brief Sets the render targets and depth stencil.
		/// @param renderTargetBindings Render targets.
		/// @param depthStencilBinding Depth stencil.
		void SetTargets(std::span<const RenderTargetBinding> renderTargetBindings, const DepthStencilBinding* depthStencilBinding);
		/// @brief Sets the render targets and depth stencil
		/// @param renderTargetBinding Render targets.
		/// @param renderTargetCount Render target count.
		/// @param depthStencilBinding Depth stencil.
		void SetTargets(const RenderTargetBinding* renderTargetBinding, std::uint8_t renderTargetCount, const DepthStencilBinding* depthStencilBinding);
		/// @brief Sets the shader data and sampler containers.
		/// @param shaderDataContainer Shader data container.
		/// @param samplerContainer Sampler container.
		/// @note The call is not validated.
		void SetContainers(const ShaderDataContainer* shaderDataContainer, const SamplerContainer* samplerContainer);
		/// @brief Sets the graphics root signature.
		/// @param rootSig Root signature.
		/// @note The call is not validated.
		void SetGraphicsRootSignature(ID3D12RootSignature* rootSig);
		/// @brief Sets the compute root signature.
		/// @param rootSig Root signature.
		/// @note The call is not validated.
		void SetComputeRootSignature(ID3D12RootSignature* rootSig);
		/// @brief Sets the pipeline state object.
		/// @param pso Pipeline state object.
		/// @note The call is not validated.
		void SetPipelineState(ID3D12PipelineState& pso);
		/// @brief Binds the graphics descriptor table.
		/// @param tableIndex Bound graphics root signature table index.
		/// @param handle Descriptor handle to bind.
		/// @note The call is not validated.
		void SetGraphicsDescriptorTable(std::uint32_t tableIndex, D3D12_GPU_DESCRIPTOR_HANDLE handle);
		/// @brief Binds the compute descriptor table.
		/// @param tableIndex Bound compute root signature table index.
		/// @param handle Descriptor handle to bind.
		/// @note The call is not validated.
		void SetComputeDescriptorTable(std::uint32_t tableIndex, D3D12_GPU_DESCRIPTOR_HANDLE handle);

		/// @brief Dispatches a graphics command.
		/// @param threadGroupCounts X, Y and Z thread group counts.
		/// @note The call is not validated.
		void DispatchGraphics(const Math::Vector3<std::uint32_t>& threadGroupCounts);
		/// @brief Dispatches a compute command.
		/// @param threadGroupCounts X, Y and Z thread group counts.
		/// @note The call is not validated.
		void DispatchCompute(const Math::Vector3<std::uint32_t>& threadGroupCounts);

		/// @brief Clears the render target view.
		/// @param container RTV container.
		/// @param viewIndex RTV index.
		/// @param color Clear color.
		/// @param rects Clear rectangles.
		void ClearRTV(const IRenderTargetContainer& container, std::uint32_t viewIndex, const Math::ColorRGBA<float>& color, std::span<const Math::CornerRect<std::uint32_t>> rects);
		/// @brief Clears the depth stencil view.
		/// @param container DSV container.
		/// @param viewIndex DSV index.
		/// @param depth Clear depth. Nullopt means no depth clearing.
		/// @param stencil Clear stencil. Nullopt means no stencil clearing.
		/// @param rects Clear rectangles.
		void ClearDSV(const IDepthStencilContainer& container, std::uint32_t viewIndex, std::optional<float> depth, std::optional<std::uint8_t> stencil,
			std::span<const Math::CornerRect<std::uint32_t>> rects);
		/// @brief Clears the unordered access view.
		/// @param buffer Target buffer.
		/// @param gpuContainer GPU shader data container. Must be bound.
		/// @param gpuViewIndex GPU shader data container index.
		/// @param cpuContainer CPU shader data container.
		/// @param cpuViewIndex CPU shader data container index.
		/// @param values Clear values.
		void ClearUAV(const IBuffer& buffer, const ShaderDataContainer& gpuContainer, std::uint32_t gpuViewIndex, const IShaderDataContainer& cpuContainer, std::uint32_t cpuViewIndex,
			const Math::Vector4<std::uint32_t>& values);
		/// @brief Clears the unordered access view.
		/// @param texture Target texture.
		/// @param gpuContainer GPU shader data container. Must be bound.
		/// @param gpuViewIndex GPU shader data container index.
		/// @param cpuContainer CPU shader data container.
		/// @param cpuViewIndex CPU shader data container index.
		/// @param values Clear values.
		/// @param rects Clear rectangles.
		void ClearUAV(const ITexture& texture, const ShaderDataContainer& gpuContainer, std::uint32_t gpuViewIndex, const IShaderDataContainer& cpuContainer, std::uint32_t cpuViewIndex,
			const Math::Vector4<std::uint32_t>& values, std::span<const Math::CornerRect<std::uint32_t>> rects);
		/// @brief Clears the unordered access view.
		/// @param buffer Target buffer.
		/// @param gpuContainer GPU shader data container. Must be bound.
		/// @param gpuViewIndex GPU shader data container index.
		/// @param cpuContainer CPU shader data container.
		/// @param cpuViewIndex CPU shader data container index.
		/// @param values Clear values.
		void ClearUAV(const IBuffer& buffer, const ShaderDataContainer& gpuContainer, std::uint32_t gpuViewIndex, const IShaderDataContainer& cpuContainer, std::uint32_t cpuViewIndex,
			const Math::Vector4<float>& values);
		/// @brief Clears the unordered access view.
		/// @param texture Target texture.
		/// @param gpuContainer GPU shader data container. Must be bound.
		/// @param gpuViewIndex GPU shader data container index.
		/// @param cpuContainer CPU shader data container.
		/// @param cpuViewIndex CPU shader data container index.
		/// @param values Clear values.
		/// @param rects Clear rectangles.
		void ClearUAV(const ITexture& texture, const ShaderDataContainer& gpuContainer, std::uint32_t gpuViewIndex, const IShaderDataContainer& cpuContainer, std::uint32_t cpuViewIndex,
			const Math::Vector4<float>& values, std::span<const Math::CornerRect<std::uint32_t>> rects);

		/// @brief Copies from the buffer to the buffer.
		/// @param source Source buffer.
		/// @param destination Destination buffer.
		void Copy(const IBuffer& source, IBuffer& destination);
		/// @brief Copes from the buffer range to the buffer range.
		/// @param source Source buffer.
		/// @param destination Destination buffer.
		/// @param ranges Copy ranges.
		void Copy(const IBuffer& source, IBuffer& destination, std::span<const CopyBufferRange> ranges);
		/// @brief Copies from the texture to the texture.
		/// @param source Source texture.
		/// @param destination Destination texture.
		void Copy(const ITexture& source, ITexture& destination);
		/// @brief Copies from the texture range to the texture range.
		/// @param source Source texture.
		/// @param destination Destination texture.
		/// @param subTextures Sub-textures to copy.
		void Copy(const ITexture& source, ITexture& destination, std::span<const CopySubTextureIndex> subTextures);
		/// @brief Copies from the texture range to the texture range with the box limits.
		/// @param source Source texture.
		/// @param destination Destination texture.
		/// @param subTextures Sub-textures to copy.
		/// @param boxes Copy boxes.
		void Copy(const ITexture& source, ITexture& destination, std::span<const CopySubTextureIndex> subTextures, std::span<const CopySubTextureBox> boxes);
		/// @brief Copies from the buffer to the texture.
		/// @param source Source buffer.
		/// @param destination Destination texture.
		/// @param footprints Copyable footprints.
		void Copy(const IBuffer& source, ITexture& destination, std::span<const CopyableFootprint> footprints);
		/// @brief Copies from the buffer range to the texture range.
		/// @param source Source buffer.
		/// @param destination Destination texture.
		/// @param footprints Copyable footprints.
		/// @param boxes Copy boxes.
		void Copy(const IBuffer& source, ITexture& destination, std::span<const CopyableFootprint> footprints, std::span<const CopySubTextureBox> boxes);
		/// @brief Copies from the texture to the buffer.
		/// @param source Source texture.
		/// @param destination Destination buffer.
		/// @param footprints Copyable footprints.
		void Copy(const ITexture& source, IBuffer& destination, std::span<const CopyableFootprint> footprints);
		/// @brief Copies from the texture range to the buffer range.
		/// @param source Source texture.
		/// @param destination Destination buffer.
		/// @param footprints Copyable footprints.
		/// @param boxes Copy boxes.
		void Copy(const ITexture& source, IBuffer& destination, std::span<const CopyableFootprint> footprints, std::span<const CopySubTextureBox> boxes);

		/// @brief Resolves the texture to the texture.
		/// @param source Source texture.
		/// @param destination Destination texture.
		/// @param mode Resolve mode.
		void Resolve(const ITexture& source, ITexture& destination, ResolveMode mode);
		/// @brief Resolves the texture range to the texture range.
		/// @param source Source texture.
		/// @param destination Destination texture.
		/// @param subTextures Sub-textures to resolve.
		/// @param mode Resolve mode.
		void Resolve(const ITexture& source, ITexture& destination, std::span<const CopySubTextureIndex> subTextures, ResolveMode mode);
		/// @brief Resolves the texture range to the texture range with the box limits.
		/// @param source Source texture.
		/// @param destination Destination texture.
		/// @param subTextures Sub-textures to resolve.
		/// @param boxes Resolve boxes.
		/// @param mode Resolve mode.
		void Resolve(const ITexture& source, ITexture& destination, std::span<const CopySubTextureIndex> subTextures, std::span<const CopySubTextureBox> boxes, ResolveMode mode);

		/// @brief Executes the bundle.
		/// @param bundle Bundle to execute.
		void ExecuteBundle(ID3D12GraphicsCommandList10& bundle);

		/// @brief Validates if the command list is in a correct state for new commands.
		void ValidateState() const;

		/// @brief Gets the name.
		/// @return Name.
		[[nodiscard("Pure function")]]
		std::string_view Name() const noexcept;
		/// @brief Sets the name.
		/// @param name Name to set.
		void Name(std::string_view name);

		CommandList& operator =(const CommandList&) = delete;
		CommandList& operator =(CommandList&&) = delete;

	private:
		/// @brief Casts the engine buffer barrier to native buffer barriers.
		/// @param bufferBarriers Engine buffer barriers.
		/// @param nativeBufferBarriers Native buffer barriers.
		static void ToNativeBarriers(std::span<const BufferBarrier> bufferBarriers, std::span<D3D12_BUFFER_BARRIER> nativeBufferBarriers);
		/// @brief Casts the engine texture barriers to native texture barriers.
		/// @param textureBarriers Engine texture barriers.
		/// @param nativeTextureBarriers Native texture barriers.
		static void ToNativeBarriers(std::span<const TextureBarrier> textureBarriers, std::span<D3D12_TEXTURE_BARRIER> nativeTextureBarriers);

		/// @brief Makes a copy location.
		/// @param buffer Target buffer.
		/// @param footprint Copyable footprint.
		/// @param format Texture format.
		/// @return Copy location.
		[[nodiscard("Pure function")]]
		static D3D12_TEXTURE_COPY_LOCATION MakeCopyLocation(const Buffer& buffer, const CopyableFootprint& footprint, DXGI_FORMAT format) noexcept;
		/// @brief Makes a copy location.
		/// @param texture Target texture.
		/// @param mipIndex Mip index.
		/// @param arrayIndex Array element index.
		/// @param aspect Aspect.
		/// @return Copy location.
		[[nodiscard("Pure function")]]
		static D3D12_TEXTURE_COPY_LOCATION MakeCopyLocation(const Texture& texture, UINT16 mipIndex, UINT16 arrayIndex, Aspect aspect) noexcept;
		/// @brief Makes a copy location.
		/// @param texture Target texture.
		/// @param footprint Footprint.
		/// @return Copy location.
		[[nodiscard("Pure function")]]
		static D3D12_TEXTURE_COPY_LOCATION MakeCopyLocation(const Texture& texture, const CopyableFootprint& footprint) noexcept;
		/// @brief Casts the engine raster region to a native viewport.
		/// @param region Engine raster region.
		/// @return Native viewport.
		[[nodiscard("Pure function")]]
		static D3D12_VIEWPORT ToViewport(const RasterRegion& region) noexcept;
		/// @brief Casts the engine corner rectangle to a native rectangle.
		/// @param rect Engine corner rectangle.
		/// @return Native rectangle.
		[[nodiscard("Pure function")]]
		static D3D12_RECT ToRect(const Math::CornerRect<std::uint32_t>& rect) noexcept;
		/// @brief Casts the engine rectangle parameters to a native rectangle.
		/// @param offset Engine rectangle offset.
		/// @param size Engine rectangle size.
		/// @return Native rectangle.
		[[nodiscard("Pure function")]]
		static D3D12_RECT ToRect(const Math::Vector2<std::uint32_t>& offset, const Math::Vector2<std::uint32_t>& size) noexcept;
		/// @brief Casts the engine rectangle parameters to a native rectangle.
		/// @param offset Engine rectangle offset.
		/// @param size Engine rectangle size.
		/// @return Native rectangle.
		[[nodiscard("Pure function")]]
		static D3D12_RECT ToRect(const Math::Vector3<std::uint32_t>& offset, const Math::Vector3<std::uint32_t>& size) noexcept;
		/// @brief Casts the engine box parameters to a native box.
		/// @param offset Engine box offset.
		/// @param size Engine box size.
		/// @return Native box.
		[[nodiscard("Pure function")]]
		static D3D12_BOX ToBox(const Math::Vector3<std::uint32_t>& offset, const Math::Vector3<std::uint32_t>& size) noexcept;

		/// @brief Casts the engine render target binding to a native descriptor handle.
		/// @param binding Engine render target binding.
		/// @return Native descriptor handle.
		[[nodiscard("Pure function")]]
		static D3D12_CPU_DESCRIPTOR_HANDLE ToRenderTargetHandle(const RenderTargetBinding& binding);
		/// @brief Casts the engine render target binding to a native descriptor handle.
		/// @param binding Engine render target binding.
		/// @param renderTargetCount Render target count.
		/// @return Native descriptor handle.
		[[nodiscard("Pure function")]]
		static D3D12_CPU_DESCRIPTOR_HANDLE ToRenderTargetHandle(const RenderTargetBinding* binding, std::uint8_t renderTargetCount);
		/// @brief Casts the engine depth stencil binding to a native descriptor handle.
		/// @param binding Engine depth stencil binding.
		/// @return Native descriptor handle.
		[[nodiscard("Pure function")]]
		static std::optional<D3D12_CPU_DESCRIPTOR_HANDLE> ToDepthStencilHandle(const DepthStencilBinding* binding);

		/// @brief Clears the unordered access view.
		/// @tparam UAVMeta Unordered access view meta type.
		/// @tparam Resource Resource type.
		/// @tparam Value Clear value type.
		/// @param resource Resource.
		/// @param gpuContainer GPU shader data container.
		/// @param gpuViewIndex GPU container view index.
		/// @param cpuContainer CPU shader data container.
		/// @param cpuViewIndex CPU container view index.
		/// @param clearValue Clear value.
		/// @param rects Clear rectangles.
		template<typename UAVMeta, typename Resource, typename Value>
		void ClearUAV(const Resource& resource, const ShaderDataContainer& gpuContainer, std::uint32_t gpuViewIndex, 
			const ShaderDataContainer& cpuContainer, std::uint32_t cpuViewIndex, std::span<const Value, 4> clearValue, std::span<const D3D12_RECT> rects);

		/// @brief Validates the buffers for copying.
		/// @param source Source buffer.
		/// @param destination Destination buffer.
		static void ValidateCopy(const Buffer& source, const Buffer& destination);
		/// @brief Validates the textures for copying.
		/// @param source Source texture.
		/// @param destination Destination texture.
		static void ValidateCopy(const Texture& source, const Texture& destination);
		/// @brief Validates the sub-textures for copying.
		/// @param source Source texture.
		/// @param destination Destination texture.
		/// @param subTextures Sub-textures to copy.
		static void ValidateSubTextures(const Texture& source, const Texture& destination, std::span<const CopySubTextureIndex> subTextures);
		/// @brief Validates the boxes for copying.
		/// @param source Source texture.
		/// @param destination Destination texture.
		/// @param subTextures Sub-textures to copy.
		/// @param boxes Copy boxes.
		static void ValidateBoxes(const Texture& source, const Texture& destination, std::span<const CopySubTextureIndex> subTextures, std::span<const CopySubTextureBox> boxes);
		/// @brief Validates the buffer and texture for copying.
		/// @param buffer Source buffer.
		/// @param texture Destination texture.
		/// @param footprints Copyable footprints.
		static void ValidateFootprints(const Buffer& buffer, const Texture& texture, std::span<const CopyableFootprint> footprints);
		/// @brief Validates the boxes for copying.
		/// @param texture Source texture.
		/// @param footprints Copyable footprints.
		/// @param boxes Copy boxes.
		static void ValidateBoxesForSource(const Texture& texture, std::span<const CopyableFootprint> footprints, std::span<const CopySubTextureBox> boxes);
		/// @brief Validates the boxes for copying.
		/// @param texture Destination texture.
		/// @param footprints Copyable footprints.
		/// @param boxes Copy boxes.
		static void ValidateBoxesForDestination(const Texture& texture, std::span<const CopyableFootprint> footprints, std::span<const CopySubTextureBox> boxes);

		/// @brief Validates the textures for resolving.
		/// @param source Source texture.
		/// @param destination Destination texture.
		static void ValidateResolve(const Texture& source, const Texture& destination);

		Platform::Windows::ComPtr<ID3D12CommandAllocator> allocator; ///< Command allocator.
		Platform::Windows::ComPtr<ID3D12GraphicsCommandList10> commandList; ///< Command list.

		Memory::Arena arena; ///< Arena memory.

		bool isOpen; ///< Is the command list open?

		std::string name; ///< Name.
	};
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	CommandList::CommandList(ID3D12CommandAllocator& allocator, ID3D12GraphicsCommandList10& commandList) :
		allocator(&allocator),
		commandList(&commandList),
		arena(0uz, 1024uz),
		isOpen{true}
	{
		Reset();
	}

	CommandList::CommandList(Platform::Windows::ComPtr<ID3D12CommandAllocator>&& allocator,
		Platform::Windows::ComPtr<ID3D12GraphicsCommandList10>&& commandList) :
		allocator(std::move(allocator)),
		commandList(std::move(commandList)),
		arena(0uz, 1024uz),
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

#ifndef NDEBUG
		if (regions.size() > D3D12_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE) [[unlikely]]
		{
			throw std::invalid_argument("Region count is too great");
		}
#endif

		std::array<D3D12_VIEWPORT, D3D12_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE> viewports;
		std::array<D3D12_RECT, D3D12_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE> scissors;
		const std::size_t regionCount = std::min(viewports.size(), regions.size());
		for (std::size_t i = 0uz; i < regionCount; ++i)
		{
			const RasterRegion& region = regions[i];
			viewports[i] = ToViewport(region);
			scissors[i] = ToRect(region.scissors);
		}

		commandList->RSSetViewports(static_cast<UINT>(regionCount), regionCount > 0u ? viewports.data() : nullptr);
		commandList->RSSetScissorRects(static_cast<UINT>(regionCount), regionCount > 0u ? scissors.data() : nullptr);
	}

	void CommandList::SetDepthBias(const DepthBias& bias)
	{
		ValidateState();
		commandList->RSSetDepthBias(bias.depthBias, bias.depthBiasClamp, bias.slopeScaledDepthBias);
	}

	void CommandList::SetDepthBounds(const DepthRange& range)
	{
		ValidateState();
		commandList->OMSetDepthBounds(range.min, range.max);
	}

	void CommandList::SetStencilReference(const StencilReference& reference)
	{
		ValidateState();
		commandList->OMSetFrontAndBackStencilRef(reference.front, reference.back);
	}

	void CommandList::SetBlendFactor(const Math::ColorRGBA<float>& factor)
	{
		ValidateState();
		const FLOAT blendFactor[4] = { factor.R(), factor.G(), factor.B(), factor.A() };
		commandList->OMSetBlendFactor(blendFactor);
	}

	void CommandList::SetTargets(const std::span<const RenderTargetBinding> renderTargetBindings, const DepthStencilBinding* const depthStencilBinding)
	{
		ValidateState();

#ifndef NDEBUG
		if (renderTargetBindings.size() > D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT) [[unlikely]]
		{
			throw std::invalid_argument("Render target binding count is too great");
		}
#endif

		std::array<D3D12_CPU_DESCRIPTOR_HANDLE, D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT> renderTargets;
		const std::size_t renderTargetCount = std::min(renderTargetBindings.size(), renderTargets.size());
		for (std::size_t i = 0uz; i < renderTargetCount; ++i)
		{
			renderTargets[i] = ToRenderTargetHandle(renderTargetBindings[i]);
		}

		const std::optional<D3D12_CPU_DESCRIPTOR_HANDLE> depthStencil = ToDepthStencilHandle(depthStencilBinding);

		commandList->OMSetRenderTargets(static_cast<UINT>(renderTargetCount), renderTargetCount > 0uz ? renderTargets.data() : nullptr, false, depthStencil ? &*depthStencil : nullptr);
	}

	void CommandList::SetTargets(const RenderTargetBinding* const renderTargetBinding, const std::uint8_t renderTargetCount, const DepthStencilBinding* const depthStencilBinding)
	{
		ValidateState();

		const D3D12_CPU_DESCRIPTOR_HANDLE renderTarget = ToRenderTargetHandle(renderTargetBinding, renderTargetCount);
		const std::optional<D3D12_CPU_DESCRIPTOR_HANDLE> depthStencil = ToDepthStencilHandle(depthStencilBinding);

		commandList->OMSetRenderTargets(renderTargetCount, renderTargetCount > 0uz ? &renderTarget : nullptr, true, depthStencil ? &*depthStencil : nullptr);
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

		if (heapCount > 0u) [[likely]]
		{
			commandList->SetDescriptorHeaps(heapCount, heaps.data());
		}
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

	void CommandList::DispatchGraphics(const Math::Vector3<std::uint32_t>& threadGroupCounts)
	{
		commandList->DispatchMesh(threadGroupCounts.X(), threadGroupCounts.Y(), threadGroupCounts.Z());
	}

	void CommandList::DispatchCompute(const Math::Vector3<std::uint32_t>& threadGroupCounts)
	{
		commandList->Dispatch(threadGroupCounts.X(), threadGroupCounts.Y(), threadGroupCounts.Z());
	}

	void CommandList::ClearRTV(const IRenderTargetContainer& container, const std::uint32_t viewIndex, const Math::ColorRGBA<float>& color, 
		const std::span<const Math::CornerRect<std::uint32_t>> rects)
	{
		ValidateState();

		const RenderTargetContainer& nativeContainer = ToNativeContainer(container);

#ifndef NDEBUG
		if (viewIndex >= nativeContainer.Size() || !std::holds_alternative<TextureRTVMeta>(nativeContainer.Meta(viewIndex))) [[unlikely]]
		{
			throw std::invalid_argument("Invalid view index");
		}

		if (rects.size() > std::numeric_limits<UINT>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Rect count is too great");
		}
#endif

		arena.Free();
		const Memory::Arena::Slice<D3D12_RECT> clearRects = arena.Allocate<D3D12_RECT>(rects.size());
		const std::span<D3D12_RECT> clearRectsSpan = arena.Span(clearRects);
		for (std::size_t i = 0uz; i < rects.size(); ++i)
		{
			clearRectsSpan[i] = ToRect(rects[i]);
		}

		const FLOAT clearColor[4] = { color.R(), color.G(), color.B(), color.A() };
		commandList->ClearRenderTargetView(nativeContainer.CpuHandle(viewIndex), clearColor, 
			static_cast<UINT>(clearRectsSpan.size()), clearRectsSpan.empty() ? nullptr : clearRectsSpan.data());
	}

	void CommandList::ClearDSV(const IDepthStencilContainer& container, const std::uint32_t viewIndex, const std::optional<float> depth, const std::optional<std::uint8_t> stencil,
		const std::span<const Math::CornerRect<std::uint32_t>> rects)
	{
		ValidateState();

		const DepthStencilContainer& nativeContainer = ToNativeContainer(container);

#ifndef NDEBUG
		if (viewIndex >= nativeContainer.Size() || !std::holds_alternative<TextureDSVMeta>(nativeContainer.Meta(viewIndex))) [[unlikely]]
		{
			throw std::invalid_argument("Invalid view index");
		}

		if (rects.size() > std::numeric_limits<UINT>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Rect count is too great");
		}
#endif

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
		commandList->ClearDepthStencilView(nativeContainer.CpuHandle(viewIndex), clearFlags, depth.value_or(0.f), stencil.value_or(0u),
			static_cast<UINT>(clearRectsSpan.size()), clearRectsSpan.empty() ? nullptr : clearRectsSpan.data());
	}

	void CommandList::ClearUAV(const IBuffer& buffer, const ShaderDataContainer& gpuContainer, const std::uint32_t gpuViewIndex, 
		const IShaderDataContainer& cpuContainer, const std::uint32_t cpuViewIndex, const Math::Vector4<std::uint32_t>& values)
	{
		ValidateState();

		const UINT clearValue[4] = { values.X(), values.Y(), values.Z(), values.W() };
		ClearUAV<BufferUAVMeta>(ToNativeBuffer(buffer), gpuContainer, gpuViewIndex, ToNativeContainer(cpuContainer), cpuViewIndex, std::span(clearValue), std::span<const D3D12_RECT>());
	}

	void CommandList::ClearUAV(const ITexture& texture, const ShaderDataContainer& gpuContainer, const std::uint32_t gpuViewIndex, 
		const IShaderDataContainer& cpuContainer, const std::uint32_t cpuViewIndex,
		const Math::Vector4<std::uint32_t>& values, const std::span<const Math::CornerRect<std::uint32_t>> rects)
	{
		ValidateState();

		arena.Free();
		const Memory::Arena::Slice<D3D12_RECT> clearRects = arena.Allocate<D3D12_RECT>(rects.size());
		const std::span<D3D12_RECT> clearRectsSpan = arena.Span(clearRects);
		for (std::size_t i = 0uz; i < rects.size(); ++i)
		{
			clearRectsSpan[i] = ToRect(rects[i]);
		}

		const UINT clearValue[4] = { values.X(), values.Y(), values.Z(), values.W() };
		ClearUAV<TextureUAVMeta>(ToNativeTexture(texture), gpuContainer, gpuViewIndex, ToNativeContainer(cpuContainer), cpuViewIndex, std::span(clearValue), clearRectsSpan);
	}

	void CommandList::ClearUAV(const IBuffer& buffer, const ShaderDataContainer& gpuContainer, const std::uint32_t gpuViewIndex, 
		const IShaderDataContainer& cpuContainer, const std::uint32_t cpuViewIndex, const Math::Vector4<float>& values)
	{
		ValidateState();

		const FLOAT clearValue[4] = { values.X(), values.Y(), values.Z(), values.W() };
		ClearUAV<BufferUAVMeta>(ToNativeBuffer(buffer), gpuContainer, gpuViewIndex, ToNativeContainer(cpuContainer), cpuViewIndex, std::span(clearValue), std::span<const D3D12_RECT>());
	}

	void CommandList::ClearUAV(const ITexture& texture, const ShaderDataContainer& gpuContainer, const std::uint32_t gpuViewIndex, 
		const IShaderDataContainer& cpuContainer, const std::uint32_t cpuViewIndex,
		const Math::Vector4<float>& values, const std::span<const Math::CornerRect<std::uint32_t>> rects)
	{
		ValidateState();

		arena.Free();
		const Memory::Arena::Slice<D3D12_RECT> clearRects = arena.Allocate<D3D12_RECT>(rects.size());
		const std::span<D3D12_RECT> clearRectsSpan = arena.Span(clearRects);
		for (std::size_t i = 0uz; i < rects.size(); ++i)
		{
			clearRectsSpan[i] = ToRect(rects[i]);
		}

		const FLOAT clearValue[4] = { values.X(), values.Y(), values.Z(), values.W() };
		ClearUAV<TextureUAVMeta>(ToNativeTexture(texture), gpuContainer, gpuViewIndex, ToNativeContainer(cpuContainer), cpuViewIndex, std::span(clearValue), clearRectsSpan);
	}

	void CommandList::Copy(const IBuffer& source, IBuffer& destination)
	{
		ValidateState();

		const Buffer& nativeSource = ToNativeBuffer(source);
		const Buffer& nativeDestination = ToNativeBuffer(destination);

		ValidateCopy(nativeSource, nativeDestination);
#ifndef NDEBUG
		if (nativeSource.Size() != nativeDestination.Size()) [[unlikely]]
		{
			throw std::invalid_argument("Buffer sizes don't match");
		}
#endif

		commandList->CopyResource(&nativeDestination.Resource(), &nativeSource.Resource());
	}

	void CommandList::Copy(const IBuffer& source, IBuffer& destination, const std::span<const CopyBufferRange> ranges)
	{
		ValidateState();

		const Buffer& nativeSource = ToNativeBuffer(source);
		const Buffer& nativeDestination = ToNativeBuffer(destination);

		ValidateCopy(nativeSource, nativeDestination);
#ifndef NDEBUG
		for (const CopyBufferRange& range : ranges)
		{
			if (std::numeric_limits<std::uint64_t>::max() - range.sourceOffset < range.size || std::numeric_limits<std::uint64_t>::max() - range.destinationOffset < range.size) [[unlikely]]
			{
				throw std::invalid_argument("Invalid range");
			}

			if (nativeSource.Size() < range.sourceOffset + range.size) [[unlikely]]
			{
				throw std::invalid_argument("Source buffer is too small");
			}
			if (nativeDestination.Size() < range.destinationOffset + range.size) [[unlikely]]
			{
				throw std::invalid_argument("Destination buffer is too small");
			}
		}
#endif

		for (const CopyBufferRange& range : ranges)
		{
			commandList->CopyBufferRegion(&nativeDestination.Resource(), range.destinationOffset, &nativeSource.Resource(), range.sourceOffset, range.size);
		}
	}

	void CommandList::Copy(const ITexture& source, ITexture& destination)
	{
		ValidateState();

		const Texture& nativeSource = ToNativeTexture(source);
		const Texture& nativeDestination = ToNativeTexture(destination);

		ValidateCopy(nativeSource, nativeDestination);

#ifndef NDEBUG
		if (nativeSource.MipCount() != nativeDestination.MipCount()) [[unlikely]]
		{
			throw std::invalid_argument("Texture mip counts don't match");
		}
		if (nativeSource.ArraySize() != nativeDestination.ArraySize()) [[unlikely]]
		{
			throw std::invalid_argument("Texture mip counts don't match");
		}

		if (GetAspects(nativeSource.NativeFormat()) != GetAspects(nativeDestination.NativeFormat())) [[unlikely]]
		{
			throw std::invalid_argument("Texture aspects don't match");
		}
#endif

		commandList->CopyResource(&nativeDestination.Resource(), &nativeSource.Resource());
	}

	void CommandList::Copy(const ITexture& source, ITexture& destination, const std::span<const CopySubTextureIndex> subTextures)
	{
		ValidateState();

		const Texture& nativeSource = ToNativeTexture(source);
		const Texture& nativeDestination = ToNativeTexture(destination);

		ValidateCopy(nativeSource, nativeDestination);
		ValidateSubTextures(nativeSource, nativeDestination, subTextures);

		for (const CopySubTextureIndex& subTexture : subTextures)
		{
			const D3D12_TEXTURE_COPY_LOCATION sourceLocation = MakeCopyLocation(nativeSource, subTexture.sourceMipIndex, subTexture.sourceArrayIndex, subTexture.aspect);
			const D3D12_TEXTURE_COPY_LOCATION destinationLocation = MakeCopyLocation(nativeDestination, subTexture.destinationMipIndex, subTexture.destinationArrayIndex, subTexture.aspect);
			commandList->CopyTextureRegion(&destinationLocation, 0u, 0u, 0u, &sourceLocation, nullptr);
		}
	}

	void CommandList::Copy(const ITexture& source, ITexture& destination, const std::span<const CopySubTextureIndex> subTextures, const std::span<const CopySubTextureBox> boxes)
	{
		ValidateState();

		const Texture& nativeSource = ToNativeTexture(source);
		const Texture& nativeDestination = ToNativeTexture(destination);

		ValidateCopy(nativeSource, nativeDestination);
		ValidateSubTextures(nativeSource, nativeDestination, subTextures);
		ValidateBoxes(nativeSource, nativeDestination, subTextures, boxes);

		for (std::size_t i = 0uz; i < subTextures.size(); ++i)
		{
			const CopySubTextureIndex& subTexture = subTextures[i];
			const CopySubTextureBox& box = boxes[i];
			const D3D12_TEXTURE_COPY_LOCATION sourceLocation = MakeCopyLocation(nativeSource, subTexture.sourceMipIndex, subTexture.sourceArrayIndex, subTexture.aspect);
			const D3D12_TEXTURE_COPY_LOCATION destinationLocation = MakeCopyLocation(nativeDestination, subTexture.destinationMipIndex, subTexture.destinationArrayIndex, subTexture.aspect);
			const Math::Vector3<std::uint32_t>& destinationOffset = box.destinationOffset;
			const D3D12_BOX sourceBox = ToBox(box.sourceOffset, box.sourceSize);
			commandList->CopyTextureRegion(&destinationLocation, destinationOffset.X(), destinationOffset.Y(), destinationOffset.Z(), &sourceLocation, &sourceBox);
		}
	}

	void CommandList::Copy(const IBuffer& source, ITexture& destination, const std::span<const CopyableFootprint> footprints)
	{
		ValidateState();

		const Buffer& nativeSource = ToNativeBuffer(source);
		const Texture& nativeDestination = ToNativeTexture(destination);

		ValidateFootprints(nativeSource, nativeDestination, footprints);

		for (const CopyableFootprint& footprint : footprints)
		{
			const D3D12_TEXTURE_COPY_LOCATION sourceLocation = MakeCopyLocation(nativeSource, footprint, nativeDestination.NativeFormat());
			const D3D12_TEXTURE_COPY_LOCATION destinationLocation = MakeCopyLocation(nativeDestination, footprint);
			commandList->CopyTextureRegion(&destinationLocation, 0u, 0u, 0u, &sourceLocation, nullptr);
		}
	}

	void CommandList::Copy(const IBuffer& source, ITexture& destination, const std::span<const CopyableFootprint> footprints, const std::span<const CopySubTextureBox> boxes)
	{
		ValidateState();

		const Buffer& nativeSource = ToNativeBuffer(source);
		const Texture& nativeDestination = ToNativeTexture(destination);

		ValidateFootprints(nativeSource, nativeDestination, footprints);
		ValidateBoxesForDestination(nativeDestination, footprints, boxes);

		for (std::size_t i = 0uz; i < footprints.size(); ++i)
		{
			const CopyableFootprint& footprint = footprints[i];
			const CopySubTextureBox& box = boxes[i];
			const D3D12_TEXTURE_COPY_LOCATION sourceLocation = MakeCopyLocation(nativeSource, footprint, nativeDestination.NativeFormat());
			const D3D12_TEXTURE_COPY_LOCATION destinationLocation = MakeCopyLocation(nativeDestination, footprint);
			const Math::Vector3<std::uint32_t>& destinationOffset = box.destinationOffset;
			const D3D12_BOX sourceBox = ToBox(box.sourceOffset, box.sourceSize);
			commandList->CopyTextureRegion(&destinationLocation, destinationOffset.X(), destinationOffset.Y(), destinationOffset.Z(), &sourceLocation, &sourceBox);
		}
	}

	void CommandList::Copy(const ITexture& source, IBuffer& destination, const std::span<const CopyableFootprint> footprints)
	{
		ValidateState();

		const Texture& nativeSource = ToNativeTexture(source);
		const Buffer& nativeDestination = ToNativeBuffer(destination);

		ValidateFootprints(nativeDestination, nativeSource, footprints);

		for (const CopyableFootprint& footprint : footprints)
		{
			const D3D12_TEXTURE_COPY_LOCATION sourceLocation = MakeCopyLocation(nativeSource, footprint);
			const D3D12_TEXTURE_COPY_LOCATION destinationLocation = MakeCopyLocation(nativeDestination, footprint, nativeSource.NativeFormat());
			commandList->CopyTextureRegion(&destinationLocation, 0u, 0u, 0u, &sourceLocation, nullptr);
		}
	}

	void CommandList::Copy(const ITexture& source, IBuffer& destination, const std::span<const CopyableFootprint> footprints, const std::span<const CopySubTextureBox> boxes)
	{
		ValidateState();

		const Texture& nativeSource = ToNativeTexture(source);
		const Buffer& nativeDestination = ToNativeBuffer(destination);

		ValidateFootprints(nativeDestination, nativeSource, footprints);
		ValidateBoxesForSource(nativeSource, footprints, boxes);

		for (std::size_t i = 0uz; i < footprints.size(); ++i)
		{
			const CopyableFootprint& footprint = footprints[i];
			const CopySubTextureBox& box = boxes[i];
			const D3D12_TEXTURE_COPY_LOCATION sourceLocation = MakeCopyLocation(nativeSource, footprint);
			const D3D12_TEXTURE_COPY_LOCATION destinationLocation = MakeCopyLocation(nativeDestination, footprint, nativeSource.NativeFormat());
			const Math::Vector3<std::uint32_t>& destinationOffset = box.destinationOffset;
			const D3D12_BOX sourceBox = ToBox(box.sourceOffset, box.sourceSize);
			commandList->CopyTextureRegion(&destinationLocation, destinationOffset.X(), destinationOffset.Y(), destinationOffset.Z(), &sourceLocation, &sourceBox);
		}
	}

	void CommandList::Resolve(const ITexture& source, ITexture& destination, const ResolveMode mode)
	{
		ValidateState();

		const Texture& sourceTexture = ToNativeTexture(source);
		const Texture& destinationTexture = ToNativeTexture(destination);
		const D3D12_RESOLVE_MODE resolveMode = ToResolveMode(mode);

		ValidateResolve(sourceTexture, destinationTexture);
#ifndef NDEBUG
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

		const UINT subresourceCount = static_cast<UINT>(sourceTexture.MipCount()) * sourceTexture.ArraySize() * ToPlaneCount(GetAspects(sourceTexture.NativeFormat()));
		for (UINT i = 0u; i < subresourceCount; ++i)
		{
			commandList->ResolveSubresourceRegion(&destinationTexture.Resource(), i, 0u, 0u, &sourceTexture.Resource(), i, nullptr, sourceTexture.NativeFormat(), resolveMode);
		}
	}

	void CommandList::Resolve(const ITexture& source, ITexture& destination, const std::span<const CopySubTextureIndex> subTextures, const ResolveMode mode)
	{
		ValidateState();

		const Texture& sourceTexture = ToNativeTexture(source);
		const Texture& destinationTexture = ToNativeTexture(destination);
		const D3D12_RESOLVE_MODE resolveMode = ToResolveMode(mode);

		ValidateResolve(sourceTexture, destinationTexture);
		ValidateSubTextures(sourceTexture, destinationTexture, subTextures);

		for (const CopySubTextureIndex& subTexture : subTextures)
		{
			const UINT sourceSubresource = CalculateSubresource(subTexture.sourceMipIndex, subTexture.sourceArrayIndex, ToPlaneIndex(subTexture.aspect), 
				sourceTexture.MipCount(), sourceTexture.ArraySize());
			const UINT destinationSubresource = CalculateSubresource(subTexture.destinationMipIndex, subTexture.destinationArrayIndex, ToPlaneIndex(subTexture.aspect), 
				destinationTexture.MipCount(), destinationTexture.ArraySize());
			commandList->ResolveSubresourceRegion(&destinationTexture.Resource(), destinationSubresource, 0u, 0u, &sourceTexture.Resource(), sourceSubresource,
				nullptr, sourceTexture.NativeFormat(), resolveMode);
		}
	}

	void CommandList::Resolve(const ITexture& source, ITexture& destination, const std::span<const CopySubTextureIndex> subTextures, const std::span<const CopySubTextureBox> boxes, 
		const ResolveMode mode)
	{
		ValidateState();

		const Texture& sourceTexture = ToNativeTexture(source);
		const Texture& destinationTexture = ToNativeTexture(destination);
		const D3D12_RESOLVE_MODE resolveMode = ToResolveMode(mode);

		ValidateResolve(sourceTexture, destinationTexture);
		ValidateSubTextures(sourceTexture, destinationTexture, subTextures);
		ValidateBoxes(sourceTexture, destinationTexture, subTextures, boxes);

		for (std::size_t i = 0uz; i < subTextures.size(); ++i)
		{
			const CopySubTextureIndex& subTexture = subTextures[i];
			const CopySubTextureBox& box = boxes[i];
			const UINT sourceSubresource = CalculateSubresource(subTexture.sourceMipIndex, subTexture.sourceArrayIndex, ToPlaneIndex(subTexture.aspect),
				sourceTexture.MipCount(), sourceTexture.ArraySize());
			const UINT destinationSubresource = CalculateSubresource(subTexture.destinationMipIndex, subTexture.destinationArrayIndex, ToPlaneIndex(subTexture.aspect),
				destinationTexture.MipCount(), destinationTexture.ArraySize());
			const Math::Vector3<std::uint32_t>& destinationOffset = box.destinationOffset;
			D3D12_RECT sourceRect = ToRect(box.sourceOffset, box.sourceSize);
			commandList->ResolveSubresourceRegion(&destinationTexture.Resource(), destinationSubresource, destinationOffset.X(), destinationOffset.Y(),
				&sourceTexture.Resource(), sourceSubresource, &sourceRect, sourceTexture.NativeFormat(), resolveMode);
		}
	}

	void CommandList::ExecuteBundle(ID3D12GraphicsCommandList10& bundle)
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

	void CommandList::ToNativeBarriers(const std::span<const BufferBarrier> bufferBarriers, const std::span<D3D12_BUFFER_BARRIER> nativeBufferBarriers)
	{
		assert(bufferBarriers.size() == nativeBufferBarriers.size() && "Invalid buffer barrier count.");

#ifndef NDEBUG
		if (bufferBarriers.size() > std::numeric_limits<UINT32>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Too many buffer barriers");
		}

		for (std::size_t i = 1uz; i < bufferBarriers.size(); ++i)
		{
			for (std::size_t j = 0uz; j < i; ++j)
			{
				if (bufferBarriers[i].buffer == bufferBarriers[j].buffer) [[unlikely]]
				{
					throw std::invalid_argument("Same buffer is found twice");
				}
			}
		}
#endif

		for (std::size_t i = 0uz; i < bufferBarriers.size(); ++i)
		{
			const BufferBarrier& barrier = bufferBarriers[i];
			nativeBufferBarriers[i] = D3D12_BUFFER_BARRIER
			{
				.SyncBefore = ToSync(barrier.beforeStages),
				.SyncAfter = ToSync(barrier.afterStages),
				.AccessBefore = ToAccess(barrier.beforeAccesses),
				.AccessAfter = ToAccess(barrier.afterAccesses),
				.pResource = &ToNativeBufferNotNullptr(barrier.buffer)->Resource(),
				.Offset = 0ull,
				.Size = std::numeric_limits<UINT64>::max()
			};
		}
	}

	void CommandList::ToNativeBarriers(const std::span<const TextureBarrier> textureBarriers, const std::span<D3D12_TEXTURE_BARRIER> nativeTextureBarriers)
	{
		assert(textureBarriers.size() == nativeTextureBarriers.size() && "Invalid texture barrier count.");

#ifndef NDEBUG
		if (textureBarriers.size() > std::numeric_limits<UINT32>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Too many texture barriers");
		}

		for (std::size_t i = 1uz; i < textureBarriers.size(); ++i)
		{
			for (std::size_t j = 0uz; j < i; ++j)
			{
				if (textureBarriers[i].texture == textureBarriers[j].texture) [[unlikely]]
				{
					throw std::invalid_argument("Same texture is found twice");
				}
			}
		}
#endif

		for (std::size_t i = 0uz; i < textureBarriers.size(); ++i)
		{
			const TextureBarrier& barrier = textureBarriers[i];
			const Texture* const texture = ToNativeTextureNotNullptr(barrier.texture);

#ifndef NDEBUG
			if (barrier.range)
			{
				const SubTextureRange& range = *barrier.range;
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
#endif

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
					? CalculateSubresourceRange(barrier.range->mipRange, barrier.range->arrayRange, barrier.range->aspects, texture->MipCount(), texture->ArraySize())
					: static_cast<D3D12_BARRIER_SUBRESOURCE_RANGE>(D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES),
				.Flags = barrier.discard ? D3D12_TEXTURE_BARRIER_FLAG_DISCARD : D3D12_TEXTURE_BARRIER_FLAG_NONE
			};
		}
	}

	D3D12_TEXTURE_COPY_LOCATION CommandList::MakeCopyLocation(const Buffer& buffer, const CopyableFootprint& footprint, const DXGI_FORMAT format) noexcept
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
					.Depth = footprint.depth,
					.RowPitch = static_cast<UINT>(footprint.rowPitch)
				}
			}
		};
	}

	D3D12_TEXTURE_COPY_LOCATION CommandList::MakeCopyLocation(const Texture& texture, const UINT16 mipIndex, const UINT16 arrayIndex, const Aspect aspect) noexcept
	{
		return D3D12_TEXTURE_COPY_LOCATION
		{
			.pResource = &texture.Resource(),
			.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX,
			.SubresourceIndex = CalculateSubresource(mipIndex, arrayIndex, ToPlaneIndex(aspect), texture.MipCount(), texture.ArraySize())
		};
	}

	D3D12_TEXTURE_COPY_LOCATION CommandList::MakeCopyLocation(const Texture& texture, const CopyableFootprint& footprint) noexcept
	{
		return D3D12_TEXTURE_COPY_LOCATION
		{
			.pResource = &texture.Resource(),
			.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX,
			.SubresourceIndex = CalculateSubresource(footprint.mipIndex, footprint.arrayIndex, ToPlaneIndex(footprint.aspect), texture.MipCount(), texture.ArraySize())
		};
	}

	D3D12_VIEWPORT CommandList::ToViewport(const RasterRegion& region) noexcept
	{
		return D3D12_VIEWPORT
		{
			.TopLeftX = region.viewport.Position().X(),
			.TopLeftY = region.viewport.Position().Y(),
			.Width = region.viewport.Size().X(),
			.Height = region.viewport.Size().Y(),
			.MinDepth = region.depthRange.min,
			.MaxDepth = region.depthRange.max
		};
	}

	D3D12_RECT CommandList::ToRect(const Math::CornerRect<std::uint32_t>& rect) noexcept
	{
		return ToRect(rect.Position(), rect.Size());
	}

	D3D12_RECT CommandList::ToRect(const Math::Vector2<std::uint32_t>& offset, const Math::Vector2<std::uint32_t>& size) noexcept
	{
		return D3D12_RECT
		{
			.left = static_cast<LONG>(offset.X()),
			.top = static_cast<LONG>(offset.Y()),
			.right = static_cast<LONG>(offset.X() + size.X()),
			.bottom = static_cast<LONG>(offset.Y() + size.Y()),
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

	D3D12_CPU_DESCRIPTOR_HANDLE CommandList::ToRenderTargetHandle(const RenderTargetBinding& binding)
	{
		const RenderTargetContainer* const container = ToNativeContainerNotNullptr(binding.container);

#ifndef NDEBUG
		if (binding.index >= container->Size()) [[unlikely]]
		{
			throw std::invalid_argument("Index is too great");
		}
		if (!std::holds_alternative<TextureRTVMeta>(container->Meta(binding.index))) [[unlikely]]
		{
			throw std::invalid_argument("Invalid render target view");
		}
#endif

		return container->CpuHandle(binding.index);
	}

	D3D12_CPU_DESCRIPTOR_HANDLE CommandList::ToRenderTargetHandle(const RenderTargetBinding* const binding, const std::uint8_t renderTargetCount)
	{
		if (renderTargetCount == 0u)
		{
			return D3D12_CPU_DESCRIPTOR_HANDLE{};
		}

#ifndef NDEBUG
		if (renderTargetCount > D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT) [[unlikely]]
		{
			throw std::invalid_argument("Render target binding count is too great");
		}
		if (!binding) [[unlikely]]
		{
			throw std::invalid_argument("Render target binding is nullptr");
		}
#endif

		const RenderTargetContainer* const container = ToNativeContainerNotNullptr(binding->container);

#ifndef NDEBUG
		if (std::numeric_limits<std::uint32_t>::max() - binding->index < renderTargetCount || binding->index + renderTargetCount > container->Size()) [[unlikely]]
		{
			throw std::invalid_argument("Index is too great");
		}

		for (std::uint8_t i = 0u; i < renderTargetCount; ++i)
		{
			if (!std::holds_alternative<TextureRTVMeta>(container->Meta(binding->index + i))) [[unlikely]]
			{
				throw std::invalid_argument("Invalid render target view");
			}
		}
#endif

		return container->CpuHandle(binding->index);
	}

	std::optional<D3D12_CPU_DESCRIPTOR_HANDLE> CommandList::ToDepthStencilHandle(const DepthStencilBinding* const binding)
	{
		if (!binding)
		{
			return std::nullopt;
		}

		const DepthStencilContainer* const container = ToNativeContainerNotNullptr(binding->container);

#ifndef NDEBUG
		if (binding->index >= container->Size()) [[unlikely]]
		{
			throw std::invalid_argument("Index is too great");
		}
		if (!std::holds_alternative<TextureDSVMeta>(container->Meta(binding->index))) [[unlikely]]
		{
			throw std::invalid_argument("Invalid depth stencil view");
		}
#endif

		return container->CpuHandle(binding->index);
	}

	template<typename UAVMeta, typename Resource, typename Value>
	void CommandList::ClearUAV(const Resource& resource, const ShaderDataContainer& gpuContainer, const std::uint32_t gpuViewIndex,
		const ShaderDataContainer& cpuContainer, const std::uint32_t cpuViewIndex, const std::span<const Value, 4> clearValue, const std::span<const D3D12_RECT> rects)
	{
		static_assert(std::is_same_v<Resource, Buffer> || std::is_same_v<Resource, Texture>, "Invalid resource type.");
		static_assert(std::is_same_v<Value, UINT> || std::is_same_v<Value, FLOAT>, "Invalid clear type.");

#ifndef NDEBUG
		if (gpuViewIndex >= gpuContainer.Size()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid gpu container index");
		}
		if (cpuViewIndex >= cpuContainer.Size()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid cpu container index");
		}

		if (!std::holds_alternative<UAVMeta>(gpuContainer.Meta(gpuViewIndex))) [[unlikely]]
		{
			throw std::invalid_argument("Invalid gpu view");
		}
		if (!std::holds_alternative<UAVMeta>(cpuContainer.Meta(cpuViewIndex))) [[unlikely]]
		{
			throw std::invalid_argument("Invalid cpu view");
		}

		if (std::get<UAVMeta>(gpuContainer.Meta(gpuViewIndex)).resource != &resource ||
			std::get<UAVMeta>(cpuContainer.Meta(cpuViewIndex)).resource != &resource) [[unlikely]]
		{
			throw std::invalid_argument("Resource mismatch");
		}

		if (rects.size() > std::numeric_limits<UINT>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Too many clear rectangles");
		}
#endif

		const D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle = gpuContainer.GpuHandle(gpuViewIndex);
		const D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle = cpuContainer.CpuHandle(cpuViewIndex);

		if constexpr (std::is_same_v<Value, UINT>)
		{
			commandList->ClearUnorderedAccessViewUint(gpuHandle, cpuHandle, &resource.Resource(), clearValue.data(), 
				static_cast<UINT>(rects.size()), rects.empty() ? nullptr : rects.data());
		}
		else
		{
			commandList->ClearUnorderedAccessViewFloat(gpuHandle, cpuHandle, &resource.Resource(), clearValue.data(),
				static_cast<UINT>(rects.size()), rects.empty() ? nullptr : rects.data());
		}
	}

	void CommandList::ValidateCopy(const Buffer& source, const Buffer& destination)
	{
#ifndef NDEBUG
		if (&source == &destination) [[unlikely]]
		{
			throw std::invalid_argument("Source and destination are the same");
		}
#endif
	}

	void CommandList::ValidateCopy(const Texture& source, const Texture& destination)
	{
#ifndef NDEBUG
		if (&source == &destination) [[unlikely]]
		{
			throw std::invalid_argument("Source and destination are the same");
		}

		if (source.Dimension() != destination.Dimension()) [[unlikely]]
		{
			throw std::invalid_argument("Texture dimensions don't match");
		}
		if (source.SampleCount() != destination.SampleCount()) [[unlikely]]
		{
			throw std::invalid_argument("Texture sample counts don't match");
		}
#endif
	}

	void CommandList::ValidateSubTextures(const Texture& source, const Texture& destination, const std::span<const CopySubTextureIndex> subTextures)
	{
#ifndef NDEBUG
		for (const CopySubTextureIndex& subTexture : subTextures)
		{
			if (subTexture.sourceMipIndex >= source.MipCount() || subTexture.destinationMipIndex >= destination.MipCount()) [[unlikely]]
			{
				throw std::invalid_argument("Invalid mip range");
			}
			if (subTexture.sourceArrayIndex >= source.ArraySize() || subTexture.destinationArrayIndex >= destination.ArraySize()) [[unlikely]]
			{
				throw std::invalid_argument("Invalid array range");
			}

			if (!IsInMask(subTexture.aspect, GetAspects(source.NativeFormat())) || !IsInMask(subTexture.aspect, GetAspects(destination.NativeFormat()))) [[unlikely]]
			{
				throw std::invalid_argument("Invalid aspect");
			}
		}
#endif
	}

	void CommandList::ValidateBoxes(const Texture& source, const Texture& destination, const std::span<const CopySubTextureIndex> subTextures, 
		const std::span<const CopySubTextureBox> boxes)
	{
#ifndef NDEBUG
		if (subTextures.size() != boxes.size())
		{
			throw std::invalid_argument("Invalid box count");
		}

		const Math::Vector3<std::uint32_t> sourceSize = source.Size();
		const Math::Vector3<std::uint32_t> destinationSize = destination.Size();

		for (std::size_t i = 0uz; i < subTextures.size(); ++i)
		{
			const Math::Vector3<std::uint32_t> sourceMipSize = MipSize(sourceSize, subTextures[i].sourceMipIndex);
			const Math::Vector3<std::uint32_t> destinationMipSize = MipSize(destinationSize, subTextures[i].destinationMipIndex);

			const Math::Vector3<std::uint32_t> sourceRequiredSize = boxes[i].sourceOffset + boxes[i].sourceSize;
			if (sourceRequiredSize.X() > sourceMipSize.X() || sourceRequiredSize.Y() > sourceMipSize.Y() || sourceRequiredSize.Z() > sourceMipSize.Z()) [[unlikely]]
			{
				throw std::invalid_argument("Source box is too great");
			}

			const Math::Vector3<std::uint32_t> destinationRequiredSize = boxes[i].destinationOffset;
			if (destinationRequiredSize.X() >= destinationMipSize.X() || destinationRequiredSize.Y() >= destinationMipSize.Y() || destinationRequiredSize.Z() >= destinationMipSize.Z()) [[unlikely]]
			{
				throw std::invalid_argument("Destination size is too little");
			}
		}
#endif
	}

	void CommandList::ValidateFootprints(const Buffer& buffer, const Texture& texture, const std::span<const CopyableFootprint> footprints)
	{
#ifndef NDEBUG
		for (const CopyableFootprint& footprint : footprints)
		{
			if (footprint.rowPitch > std::numeric_limits<UINT>::max() ||
				footprint.offset + footprint.rowPitch * footprint.rowCount > buffer.Size() ||
				footprint.mipIndex >= texture.MipCount() ||
				Math::Vector3<std::uint32_t>(footprint.width, footprint.height, footprint.depth) != MipSize(texture.Size(), footprint.mipIndex) ||
				footprint.arrayIndex >= texture.ArraySize() ||
				!IsInMask(footprint.aspect, GetAspects(texture.NativeFormat()))) [[unlikely]]
			{
				throw std::invalid_argument("Invalid footprint");
			}
		}
#endif
	}

	void CommandList::ValidateBoxesForSource(const Texture& texture, const std::span<const CopyableFootprint> footprints, const std::span<const CopySubTextureBox> boxes)
	{
#ifndef NDEBUG
		if (footprints.size() != boxes.size())
		{
			throw std::invalid_argument("Invalid box count");
		}

		const Math::Vector3<std::uint32_t> textureSize = texture.Size();

		for (std::size_t i = 0uz; i < footprints.size(); ++i)
		{
			const Math::Vector3<std::uint32_t> mipSize = MipSize(textureSize, footprints[i].mipIndex);
			const Math::Vector3<std::uint32_t> sourceRequiredSize = boxes[i].sourceOffset + boxes[i].sourceSize;
			if (sourceRequiredSize.X() > mipSize.X() || sourceRequiredSize.Y() > mipSize.Y() || sourceRequiredSize.Z() > mipSize.Z()) [[unlikely]]
			{
				throw std::invalid_argument("Source box is too great");
			}
		}
#endif
	}

	void CommandList::ValidateBoxesForDestination(const Texture& texture, const std::span<const CopyableFootprint> footprints, const std::span<const CopySubTextureBox> boxes)
	{
#ifndef NDEBUG
		if (footprints.size() != boxes.size())
		{
			throw std::invalid_argument("Invalid box count");
		}

		const Math::Vector3<std::uint32_t> textureSize = texture.Size();

		for (std::size_t i = 0uz; i < footprints.size(); ++i)
		{
			const Math::Vector3<std::uint32_t> mipSize = MipSize(textureSize, footprints[i].mipIndex);
			const Math::Vector3<std::uint32_t>& destinationRequiredSize = boxes[i].destinationOffset;
			if (destinationRequiredSize.X() >= mipSize.X() || destinationRequiredSize.Y() >= mipSize.Y() || destinationRequiredSize.Z() >= mipSize.Z()) [[unlikely]]
			{
				throw std::invalid_argument("Destination size is too little");
			}
		}
#endif
	}

	void CommandList::ValidateResolve(const Texture& source, const Texture& destination)
	{
#ifndef NDEBUG
		if (&source == &destination) [[unlikely]]
		{
			throw std::invalid_argument("Source and destination are the same");
		}

		if (source.Dimension() != destination.Dimension()) [[unlikely]]
		{
			throw std::invalid_argument("Texture dimensions don't match");
		}
		if (ToNumber(source.SampleCount()) <= 1u) [[unlikely]]
		{
			throw std::invalid_argument("Source texture is not multi-sampled");
		}
		if (ToNumber(destination.SampleCount()) > 1u) [[unlikely]]
		{
			throw std::invalid_argument("Destination texture is multi-sampled");
		}
		if (source.NativeFormat() != destination.NativeFormat()) [[unlikely]]
		{
			throw std::invalid_argument("Texture formats don't match");
		}
#endif
	}
}
