/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/RenderDevice/Windows/D3D12Framework.h"

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:GraphicsCommandList;

import std;

import PonyEngine.Math;
import PonyEngine.Memory;
import PonyEngine.Platform.Windows;
import PonyEngine.RenderDevice;

import :BundleCommandList;
import :CommandList;
import :ContainerBinding;
import :GraphicsComputePipelineBinding;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	/// @brief Graphics command list wrapper.
	class GraphicsCommandList final : public IGraphicsCommandList
	{
	public:
		/// @brief Creates a graphics command list wrapper.
		/// @param allocator Graphics command list allocator.
		/// @param commandList Graphics command list.
		[[nodiscard("Pure constructor")]]
		GraphicsCommandList(ID3D12CommandAllocator& allocator, ID3D12GraphicsCommandList10& commandList);
		/// @brief Creates a graphics command list wrapper.
		/// @param allocator Graphics command list allocator.
		/// @param commandList Graphics command list.
		[[nodiscard("Pure constructor")]]
		GraphicsCommandList(Platform::Windows::ComPtr<ID3D12CommandAllocator>&& allocator, Platform::Windows::ComPtr<ID3D12GraphicsCommandList10>&& commandList);
		GraphicsCommandList(const GraphicsCommandList&) = delete;
		GraphicsCommandList(GraphicsCommandList&&) = delete;

		~GraphicsCommandList() noexcept = default;

		virtual void Reset() override;
		virtual void Close() override;
		[[nodiscard("Pure function")]]
		virtual bool IsOpen() const noexcept override;

		virtual void Barrier(std::span<const BufferBarrier> bufferBarriers, std::span<const TextureBarrier> textureBarriers) override;

		virtual void SetRasterRegions(std::span<const RasterRegion> regions) override;
		virtual void SetDepthBias(const DepthBias& bias) override;
		virtual void SetDepthBounds(const DepthRange& range) override;
		virtual void SetStencilReference(const StencilReference& reference) override;
		virtual void SetBlendFactor(const Math::ColorRGBA<float>& factor) override;

		virtual void BindTargets(std::span<const RenderTargetBinding> renderTargetBindings, const DepthStencilBinding* depthStencilBinding) override;
		virtual void BindTargets(const RenderTargetBinding* renderTargetBinding, std::uint8_t renderTargetCount, const DepthStencilBinding* depthStencilBinding) override;
		virtual void BindContainers(const IShaderDataContainer* shaderDataContainer, const ISamplerContainer* samplerContainer) override;
		virtual void BindPipelineState(const IGraphicsPipelineState& pipelineState) override;
		virtual void BindPipelineState(const IComputePipelineState& pipelineState) override;
		virtual void BindGraphics(std::span<const ShaderDataBinding> shaderDataBindings, std::span<const SamplerBinding> samplerBindings) override;
		virtual void BindCompute(std::span<const ShaderDataBinding> shaderDataBindings, std::span<const SamplerBinding> samplerBindings) override;

		virtual void DispatchGraphics(const Math::Vector3<std::uint32_t>& threadGroupCounts) override;
		virtual void DispatchCompute(const Math::Vector3<std::uint32_t>& threadGroupCounts) override;

		virtual void ClearRTV(const IRenderTargetContainer& container, std::uint32_t viewIndex, const Math::ColorRGBA<float>& color, 
			std::span<const Math::CornerRect<std::uint32_t>> rects) override;
		virtual void ClearDSV(const IDepthStencilContainer& container, std::uint32_t viewIndex, std::optional<float> depth, std::optional<std::uint8_t> stencil,
			std::span<const Math::CornerRect<std::uint32_t>> rects) override;
		virtual void ClearUAV(const IBuffer& buffer, std::uint32_t gpuViewIndex, const IShaderDataContainer& cpuContainer, std::uint32_t cpuViewIndex,
			const Math::Vector4<std::uint32_t>& values) override;
		virtual void ClearUAV(const ITexture& texture, std::uint32_t gpuViewIndex, const IShaderDataContainer& cpuContainer, std::uint32_t cpuViewIndex,
			const Math::Vector4<std::uint32_t>& values, std::span<const Math::CornerRect<std::uint32_t>> rects) override;
		virtual void ClearUAV(const IBuffer& buffer, std::uint32_t gpuViewIndex, const IShaderDataContainer& cpuContainer, std::uint32_t cpuViewIndex, 
			const Math::Vector4<float>& values) override;
		virtual void ClearUAV(const ITexture& texture, std::uint32_t gpuViewIndex, const IShaderDataContainer& cpuContainer, std::uint32_t cpuViewIndex, 
			const Math::Vector4<float>& values, std::span<const Math::CornerRect<std::uint32_t>> rects) override;

		virtual void Copy(const IBuffer& source, IBuffer& destination) override;
		virtual void Copy(const IBuffer& source, IBuffer& destination, std::span<const CopyBufferRange> ranges) override;
		virtual void Copy(const ITexture& source, ITexture& destination) override;
		virtual void Copy(const ITexture& source, ITexture& destination, std::span<const CopySubTextureIndex> subTextures) override;
		virtual void Copy(const ITexture& source, ITexture& destination, std::span<const CopySubTextureIndex> subTextures, std::span<const CopySubTextureBox> boxes) override;
		virtual void Copy(const IBuffer& source, ITexture& destination, std::span<const CopyableFootprint> footprints) override;
		virtual void Copy(const IBuffer& source, ITexture& destination, std::span<const CopyableFootprint> footprints, std::span<const CopySubTextureBox> boxes) override;
		virtual void Copy(const ITexture& source, IBuffer& destination, std::span<const CopyableFootprint> footprints) override;
		virtual void Copy(const ITexture& source, IBuffer& destination, std::span<const CopyableFootprint> footprints, std::span<const CopySubTextureBox> boxes) override;

		virtual void Resolve(const ITexture& source, ITexture& destination, ResolveMode mode) override;
		virtual void Resolve(const ITexture& source, ITexture& destination, std::span<const CopySubTextureIndex> subTextures, ResolveMode mode) override;
		virtual void Resolve(const ITexture& source, ITexture& destination, std::span<const CopySubTextureIndex> subTextures, std::span<const CopySubTextureBox> boxes, ResolveMode mode) override;

		virtual void Execute(const ISecondaryGraphicsCommandList& secondary) override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;
		virtual void Name(std::string_view name) override;

		/// @brief Gets the command list.
		/// @return Command list.
		[[nodiscard("Pure function")]]
		ID3D12GraphicsCommandList10& CommandList() const noexcept;

		GraphicsCommandList& operator =(const GraphicsCommandList&) = delete;
		GraphicsCommandList& operator =(GraphicsCommandList&&) = delete;

	private:
		class CommandList commandList; ///< Command list.
		GraphicsComputePipelineBinding pipelineBinding; ///< Pipeline binding.
		ContainerBinding containerBinding; ///< Container binding.
		Memory::Arena arena; ///< Arena.
	};
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	GraphicsCommandList::GraphicsCommandList(ID3D12CommandAllocator& allocator, ID3D12GraphicsCommandList10& commandList) :
		commandList(allocator, commandList),
		arena(0uz, 128uz)
	{
	}

	GraphicsCommandList::GraphicsCommandList(Platform::Windows::ComPtr<ID3D12CommandAllocator>&& allocator, 
		Platform::Windows::ComPtr<ID3D12GraphicsCommandList10>&& commandList) :
		commandList(std::move(allocator), std::move(commandList)),
		arena(0uz, 128uz)
	{
	}

	void GraphicsCommandList::Reset()
	{
		commandList.Reset(containerBinding, pipelineBinding);
	}

	void GraphicsCommandList::Close()
	{
		commandList.Close();
	}

	bool GraphicsCommandList::IsOpen() const noexcept
	{
		return commandList.IsOpen();
	}

	void GraphicsCommandList::Barrier(const std::span<const BufferBarrier> bufferBarriers, const std::span<const TextureBarrier> textureBarriers)
	{
		commandList.Barrier(bufferBarriers, textureBarriers, arena);
	}

	void GraphicsCommandList::SetRasterRegions(const std::span<const RasterRegion> regions)
	{
		commandList.SetRasterRegions(regions);
	}

	void GraphicsCommandList::SetDepthBias(const DepthBias& bias)
	{
		commandList.SetDepthBias(bias);
	}

	void GraphicsCommandList::SetDepthBounds(const DepthRange& range)
	{
		commandList.SetDepthBounds(range);
	}

	void GraphicsCommandList::SetStencilReference(const StencilReference& reference)
	{
		commandList.SetStencilReference(reference);
	}

	void GraphicsCommandList::SetBlendFactor(const Math::ColorRGBA<float>& factor)
	{
		commandList.SetBlendFactor(factor);
	}

	void GraphicsCommandList::BindTargets(const std::span<const RenderTargetBinding> renderTargetBindings, const DepthStencilBinding* const depthStencilBinding)
	{
		commandList.SetTargets(renderTargetBindings, depthStencilBinding);
	}

	void GraphicsCommandList::BindTargets(const RenderTargetBinding* const renderTargetBinding, const std::uint8_t renderTargetCount, 
		const DepthStencilBinding* const depthStencilBinding)
	{
		commandList.SetTargets(renderTargetBinding, renderTargetCount, depthStencilBinding);
	}

	void GraphicsCommandList::BindContainers(const IShaderDataContainer* const shaderDataContainer, const ISamplerContainer* const samplerContainer)
	{
		commandList.SetContainers(shaderDataContainer, samplerContainer, containerBinding);
	}

	void GraphicsCommandList::BindPipelineState(const IGraphicsPipelineState& pipelineState)
	{
		commandList.SetPipelineState(pipelineState, pipelineBinding);
	}

	void GraphicsCommandList::BindPipelineState(const IComputePipelineState& pipelineState)
	{
		commandList.SetPipelineState(pipelineState, pipelineBinding);
	}

	void GraphicsCommandList::BindGraphics(const std::span<const ShaderDataBinding> shaderDataBindings, const std::span<const SamplerBinding> samplerBindings)
	{
		commandList.SetGraphicsBindings(shaderDataBindings, samplerBindings, containerBinding, pipelineBinding);
	}

	void GraphicsCommandList::BindCompute(const std::span<const ShaderDataBinding> shaderDataBindings, const std::span<const SamplerBinding> samplerBindings)
	{
		commandList.SetComputeBindings(shaderDataBindings, samplerBindings, containerBinding, pipelineBinding);
	}

	void GraphicsCommandList::DispatchGraphics(const Math::Vector3<std::uint32_t>& threadGroupCounts)
	{
		commandList.DispatchGraphics(threadGroupCounts, pipelineBinding);
	}

	void GraphicsCommandList::DispatchCompute(const Math::Vector3<std::uint32_t>& threadGroupCounts)
	{
		commandList.DispatchCompute(threadGroupCounts, pipelineBinding);
	}

	void GraphicsCommandList::ClearRTV(const IRenderTargetContainer& container, const std::uint32_t viewIndex, const Math::ColorRGBA<float>& color,
		const std::span<const Math::CornerRect<std::uint32_t>> rects)
	{
		commandList.ClearRTV(container, viewIndex, color, rects, arena);
	}

	void GraphicsCommandList::ClearDSV(const IDepthStencilContainer& container, const std::uint32_t viewIndex, const std::optional<float> depth, const std::optional<std::uint8_t> stencil,
		const std::span<const Math::CornerRect<std::uint32_t>> rects)
	{
		commandList.ClearDSV(container, viewIndex, depth, stencil, rects, arena);
	}

	void GraphicsCommandList::ClearUAV(const IBuffer& buffer, const std::uint32_t gpuViewIndex, const IShaderDataContainer& cpuContainer, const std::uint32_t cpuViewIndex,
		const Math::Vector4<std::uint32_t>& values)
	{
		commandList.ClearUAV(buffer, gpuViewIndex, cpuContainer, cpuViewIndex, values, containerBinding);
	}

	void GraphicsCommandList::ClearUAV(const ITexture& texture, const std::uint32_t gpuViewIndex, const IShaderDataContainer& cpuContainer, const std::uint32_t cpuViewIndex,
		const Math::Vector4<std::uint32_t>& values, const std::span<const Math::CornerRect<std::uint32_t>> rects)
	{
		commandList.ClearUAV(texture, gpuViewIndex, cpuContainer, cpuViewIndex, values, rects, containerBinding, arena);
	}

	void GraphicsCommandList::ClearUAV(const IBuffer& buffer, const std::uint32_t gpuViewIndex, const IShaderDataContainer& cpuContainer, const std::uint32_t cpuViewIndex, 
		const Math::Vector4<float>& values)
	{
		commandList.ClearUAV(buffer, gpuViewIndex, cpuContainer, cpuViewIndex, values, containerBinding);
	}

	void GraphicsCommandList::ClearUAV(const ITexture& texture, const std::uint32_t gpuViewIndex, const IShaderDataContainer& cpuContainer, const std::uint32_t cpuViewIndex, 
		const Math::Vector4<float>& values, const std::span<const Math::CornerRect<std::uint32_t>> rects)
	{
		commandList.ClearUAV(texture, gpuViewIndex, cpuContainer, cpuViewIndex, values, rects, containerBinding, arena);
	}

	void GraphicsCommandList::Copy(const IBuffer& source, IBuffer& destination)
	{
		commandList.Copy(source, destination);
	}

	void GraphicsCommandList::Copy(const IBuffer& source, IBuffer& destination, const std::span<const CopyBufferRange> ranges)
	{
		commandList.Copy(source, destination, ranges);
	}

	void GraphicsCommandList::Copy(const ITexture& source, ITexture& destination)
	{
		commandList.Copy(source, destination);
	}

	void GraphicsCommandList::Copy(const ITexture& source, ITexture& destination, const std::span<const CopySubTextureIndex> subTextures)
	{
		commandList.Copy(source, destination, subTextures);
	}

	void GraphicsCommandList::Copy(const ITexture& source, ITexture& destination, const std::span<const CopySubTextureIndex> subTextures, const std::span<const CopySubTextureBox> boxes)
	{
		commandList.Copy(source, destination, subTextures, boxes);
	}

	void GraphicsCommandList::Copy(const IBuffer& source, ITexture& destination, const std::span<const CopyableFootprint> footprints)
	{
		commandList.Copy(source, destination, footprints);
	}

	void GraphicsCommandList::Copy(const IBuffer& source, ITexture& destination, const std::span<const CopyableFootprint> footprints, const std::span<const CopySubTextureBox> boxes)
	{
		commandList.Copy(source, destination, footprints, boxes);
	}

	void GraphicsCommandList::Copy(const ITexture& source, IBuffer& destination, const std::span<const CopyableFootprint> footprints)
	{
		commandList.Copy(source, destination, footprints);
	}

	void GraphicsCommandList::Copy(const ITexture& source, IBuffer& destination, const std::span<const CopyableFootprint> footprints, const std::span<const CopySubTextureBox> boxes)
	{
		commandList.Copy(source, destination, footprints, boxes);
	}

	void GraphicsCommandList::Resolve(const ITexture& source, ITexture& destination, const ResolveMode mode)
	{
		commandList.Resolve(source, destination, mode);
	}

	void GraphicsCommandList::Resolve(const ITexture& source, ITexture& destination, const std::span<const CopySubTextureIndex> subTextures, const ResolveMode mode)
	{
		commandList.Resolve(source, destination, subTextures, mode);
	}

	void GraphicsCommandList::Resolve(const ITexture& source, ITexture& destination, const std::span<const CopySubTextureIndex> subTextures, 
		const std::span<const CopySubTextureBox> boxes, const ResolveMode mode)
	{
		commandList.Resolve(source, destination, subTextures, boxes, mode);
	}

	void GraphicsCommandList::Execute(const ISecondaryGraphicsCommandList& secondary)
	{
#ifndef NDEBUG
		if (typeid(secondary) != typeid(BundleCommandList)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid secondary graphics command list");
		}
#endif

		const auto& bundle = static_cast<const BundleCommandList&>(secondary);

#ifndef NDEBUG
		if (bundle.IsOpen()) [[unlikely]]
		{
			throw std::invalid_argument("Secondary graphics command list is open");
		}
#endif

		commandList.ExecuteBundle(bundle.CommandList());
	}

	std::string_view GraphicsCommandList::Name() const noexcept
	{
		return commandList.Name();
	}

	void GraphicsCommandList::Name(const std::string_view name)
	{
		commandList.Name(name);
	}

	ID3D12GraphicsCommandList10& GraphicsCommandList::CommandList() const noexcept
	{
		return commandList.GetCommandList();
	}
}
