/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Object/Body.h"

export module PonyEngine.RenderDevice:IGraphicsCommandList;

import std;

import PonyEngine.Math;

import :BufferBarrier;
import :CopyableFootprint;
import :DepthBias;
import :DepthRange;
import :DepthStencilBinding;
import :IBuffer;
import :ICommandList;
import :IComputePipelineState;
import :IDepthStencilContainer;
import :IGraphicsPipelineState;
import :IRenderTargetContainer;
import :ISecondaryGraphicsCommandList;
import :ISamplerContainer;
import :IShaderDataContainer;
import :ITexture;
import :RasterRegion;
import :RenderTargetBinding;
import :ResolveMode;
import :SamplerBinding;
import :ShaderDataBinding;
import :StencilReference;
import :TextureBarrier;

export namespace PonyEngine::RenderDevice
{
	/// @brief Graphics command list.
	class IGraphicsCommandList : public ICommandList
	{
		PONY_INTERFACE_BODY(IGraphicsCommandList)

		/// @brief Sets the barriers.
		/// @param bufferBarriers Buffer barriers.
		void Barrier(std::span<const BufferBarrier> bufferBarriers);
		/// @brief Sets the barriers.
		/// @param textureBarriers Texture barriers.
		void Barrier(std::span<const TextureBarrier> textureBarriers);
		/// @brief Sets the barriers.
		/// @param bufferBarriers Buffer barriers.
		/// @param textureBarriers Texture barriers.
		virtual void Barrier(std::span<const BufferBarrier> bufferBarriers, std::span<const TextureBarrier> textureBarriers) = 0;

		/// @brief Sets the raster region.
		/// @param region Raster region.
		void SetRasterRegion(const RasterRegion& region);
		/// @brief Sets the raster regions.
		/// @param regions Raster regions.
		virtual void SetRasterRegions(std::span<const RasterRegion> regions) = 0;
		/// @brief Sets the depth bias.
		/// @param bias Depth bias.
		virtual void SetDepthBias(const DepthBias& bias) = 0;
		/// @brief Sets the depth range.
		/// @param range Depth range.
		virtual void SetDepthBounds(const DepthRange& range) = 0;
		/// @brief Sets the stencil reference.
		/// @param reference Stencil reference.
		virtual void SetStencilReference(const StencilReference& reference) = 0;
		/// @brief Sets the blend factor.
		/// @param factor Blend factor.
		virtual void SetBlendFactor(const Math::ColorRGBA<float>& factor) = 0;

		/// @brief Unbinds RTVs and a DSV.
		void BindTargets();
		/// @brief Binds the RTV and unbinds a DSV.
		/// @param renderTargetBinding RTV to bind.
		void BindTargets(const RenderTargetBinding& renderTargetBinding);
		/// @brief Binds the RTVs and unbinds a DSV.
		/// @param renderTargetBindings RTVs to bind.
		void BindTargets(std::span<const RenderTargetBinding> renderTargetBindings);
		/// @brief Unbinds RTVs and bind the DSV.
		/// @param depthStencilBinding DSV to bind.
		void BindTargets(const DepthStencilBinding& depthStencilBinding);
		/// @brief Binds the RTV and DSV.
		/// @param renderTargetBinding RTV to bind.
		/// @param depthStencilBinding DSV to bind.
		void BindTargets(const RenderTargetBinding& renderTargetBinding, const DepthStencilBinding& depthStencilBinding);
		/// @brief Binds the RTVs.
		/// @param renderTargetBinding First RTV to bind.
		/// @param renderTargetCount How many RTVs to bind?
		/// @remark It binds RTVs that lie in a row in the container.
		void BindTargets(const RenderTargetBinding& renderTargetBinding, std::uint8_t renderTargetCount);
		/// @brief Binds the RTVs and the DSV.
		/// @param renderTargetBindings RTVs to bind.
		/// @param depthStencilBinding DSV to bind.
		virtual void BindTargets(std::span<const RenderTargetBinding> renderTargetBindings, const DepthStencilBinding* depthStencilBinding) = 0;
		/// @brief Binds the RTVs and the DSV.
		/// @param renderTargetBinding First RTV to bind.
		/// @param renderTargetCount How many RTVs to bind?
		/// @param depthStencilBinding DSV to bind.
		virtual void BindTargets(const RenderTargetBinding* renderTargetBinding, std::uint8_t renderTargetCount, const DepthStencilBinding* depthStencilBinding) = 0;
		/// @brief Unbinds all the containers.
		void BindContainers();
		/// @brief Binds the shader data container and unbinds a sampler container.
		/// @param shaderDataContainer Shader data container to bind. Must be shader visible.
		void BindContainers(const IShaderDataContainer& shaderDataContainer);
		/// @brief Binds the sampler container and unbinds a shader data container.
		/// @param samplerContainer Sampler container to bind. Must be shader visible.
		void BindContainers(const ISamplerContainer& samplerContainer);
		/// @brief Binds the containers.
		/// @param shaderDataContainer Shader data container to bind. Must be shader visible.
		/// @param samplerContainer Sampler container to bind. Must be shader visible.
		virtual void BindContainers(const IShaderDataContainer* shaderDataContainer, const ISamplerContainer* samplerContainer) = 0;
		/// @brief Binds the graphics pipeline state.
		/// @param pipelineState 
		virtual void BindPipelineState(const IGraphicsPipelineState& pipelineState) = 0;
		/// @brief Binds the compute pipeline state.
		/// @param pipelineState Compute pipeline state to bind.
		virtual void BindPipelineState(const IComputePipelineState& pipelineState) = 0;
		/// @brief Binds a view from a currently bound shader data container to a currently bound graphics pipeline state.
		/// @param shaderDataBinding Shader data binding.
		void BindGraphics(const ShaderDataBinding& shaderDataBinding);
		/// @brief Binds a sampler a currently bound sampler container to a currently bound graphics pipeline state.
		/// @param samplerBinding Sampler binding.
		void BindGraphics(const SamplerBinding& samplerBinding);
		/// @brief Binds views from a currently bound shader data container to a currently bound graphics pipeline state.
		/// @param shaderDataBindings Shader data bindings.
		void BindGraphics(std::span<const ShaderDataBinding> shaderDataBindings);
		/// @brief Binds samplers a currently bound sampler container to a currently bound graphics pipeline state.
		/// @param samplerBindings Sampler bindings.
		void BindGraphics(std::span<const SamplerBinding> samplerBindings);
		/// @brief Binds views from a currently bound shader data container and samplers from a currently bound sampler container to a currently bound compute pipeline state.
		/// @param shaderDataBindings Shader data bindings.
		/// @param samplerBindings Sampler bindings.
		virtual void BindGraphics(std::span<const ShaderDataBinding> shaderDataBindings, std::span<const SamplerBinding> samplerBindings) = 0;
		/// @brief Binds a view from a currently bound shader data container to a currently bound compute pipeline state.
		/// @param shaderDataBinding Shader data binding.
		void BindCompute(const ShaderDataBinding& shaderDataBinding);
		/// @brief Binds a sampler a currently bound sampler container to a currently bound compute pipeline state.
		/// @param samplerBinding Sampler binding.
		void BindCompute(const SamplerBinding& samplerBinding);
		/// @brief Binds views from a currently bound shader data container to a currently bound compute pipeline state.
		/// @param shaderDataBindings Shader data bindings.
		void BindCompute(std::span<const ShaderDataBinding> shaderDataBindings);
		/// @brief Binds samplers a currently bound sampler container to a currently bound compute pipeline state.
		/// @param samplerBindings Sampler bindings.
		void BindCompute(std::span<const SamplerBinding> samplerBindings);
		/// @brief Binds views from a currently bound shader data container and samplers from a currently bound sampler container to a currently bound compute pipeline state.
		/// @param shaderDataBindings Shader data bindings.
		/// @param samplerBindings Sampler bindings.
		virtual void BindCompute(std::span<const ShaderDataBinding> shaderDataBindings, std::span<const SamplerBinding> samplerBindings) = 0;

		/// @brief Dispatches a graphics command.
		/// @param threadGroupCount X thread group count.
		/// @remark Y and Z thread group counts are set to 1.
		/// @note The command list mush have a valid graphics pipeline state and all its required descriptor sets must be bound.
		void DispatchGraphics(std::uint32_t threadGroupCount);
		/// @brief Dispatches a graphics command.
		/// @param threadGroupCounts X thread group count.
		/// @remark Y and Z thread group counts are set to 1.
		/// @note The command list mush have a valid graphics pipeline state and all its required descriptor sets must be bound.
		void DispatchGraphics(const Math::Vector1<std::uint32_t>& threadGroupCounts);
		/// @brief Dispatches a graphics command.
		/// @param threadGroupCounts X and Y thread group counts.
		/// @remark Z thread group count is set to 1.
		/// @note The command list mush have a valid graphics pipeline state and all its required descriptor sets must be bound.
		void DispatchGraphics(const Math::Vector2<std::uint32_t>& threadGroupCounts);
		/// @brief Dispatches a graphics command.
		/// @param threadGroupCounts X, Y and Z thread group counts.
		/// @note The command list mush have a valid graphics pipeline state and all its required descriptor sets must be bound.
		virtual void DispatchGraphics(const Math::Vector3<std::uint32_t>& threadGroupCounts) = 0;
		/// @brief Dispatches a compute command.
		/// @param threadGroupCount X thread group count.
		/// @remark Y and Z thread group counts are set to 1.
		/// @note The command list mush have a valid compute pipeline state and all its required descriptor sets must be bound.
		void DispatchCompute(std::uint32_t threadGroupCount);
		/// @brief Dispatches a compute command.
		/// @param threadGroupCounts X thread group count.
		/// @remark Y and Z thread group counts are set to 1.
		/// @note The command list mush have a valid compute pipeline state and all its required descriptor sets must be bound.
		void DispatchCompute(const Math::Vector1<std::uint32_t>& threadGroupCounts);
		/// @brief Dispatches a compute command.
		/// @param threadGroupCounts X and Y thread group counts.
		/// @remark Z thread group count is set to 1.
		/// @note The command list mush have a valid compute pipeline state and all its required descriptor sets must be bound.
		void DispatchCompute(const Math::Vector2<std::uint32_t>& threadGroupCounts);
		/// @brief Dispatches a compute command.
		/// @param threadGroupCounts X, Y and Z thread group counts.
		/// @note The command list mush have a valid compute pipeline state and all its required descriptor sets must be bound.
		virtual void DispatchCompute(const Math::Vector3<std::uint32_t>& threadGroupCounts) = 0;

		/// @brief Clears an RTV.
		/// @param container RTV container.
		/// @param viewIndex View index of the @p container.
		/// @param color Clear color.
		/// @param rects Rects to clear. If empty, the whole texture will be cleared.
		virtual void ClearRTV(const IRenderTargetContainer& container, std::uint32_t viewIndex, const Math::ColorRGBA<float>& color,
			std::span<const Math::CornerRect<std::uint32_t>> rects = std::span<const Math::CornerRect<std::uint32_t>>()) = 0;
		/// @brief Clears a DSV.
		/// @param container DSV container.
		/// @param viewIndex View index of the @p container.
		/// @param depth Clear depth. If nullopt, the depth isn't cleared.
		/// @param stencil Clear stencil. If nullopt, the stencil isn't cleared.
		/// @param rects Rects to clear. If empty, the whole texture will be cleared.
		virtual void ClearDSV(const IDepthStencilContainer& container, std::uint32_t viewIndex, std::optional<float> depth, std::optional<std::uint8_t> stencil,
			std::span<const Math::CornerRect<std::uint32_t>> rects = std::span<const Math::CornerRect<std::uint32_t>>()) = 0;
		/// @brief Clears a UAV.
		/// @param buffer Buffer to clear.
		/// @param gpuViewIndex View index of a currently bound shader data container. Must be a valid UAV to the @p buffer.
		/// @param cpuContainer Not shader visible shader data container.
		/// @param cpuViewIndex View index of the @p cpuContainer. Must be a valid UAV to the @p buffer.
		/// @param values Clear values.
		virtual void ClearUAV(const IBuffer& buffer, std::uint32_t gpuViewIndex, const IShaderDataContainer& cpuContainer, std::uint32_t cpuViewIndex,
			const Math::Vector4<std::uint32_t>& values) = 0;
		/// @brief Clears a UAV.
		/// @param texture Texture to clear.
		/// @param gpuViewIndex View index of a currently bound shader data container. Must be a valid UAV to the @p texture.
		/// @param cpuContainer Not shader visible shader data container.
		/// @param cpuViewIndex View index of the @p cpuContainer. Must be a valid UAV to the @p texture.
		/// @param values Clear values.
		/// @param rects Rects to clear. If empty, the whole texture will be cleared.
		virtual void ClearUAV(const ITexture& texture, std::uint32_t gpuViewIndex, const IShaderDataContainer& cpuContainer, std::uint32_t cpuViewIndex,
			const Math::Vector4<std::uint32_t>& values, std::span<const Math::CornerRect<std::uint32_t>> rects = std::span<const Math::CornerRect<std::uint32_t>>()) = 0;
		/// @brief Clears a UAV.
		/// @param buffer Buffer resource to clear.
		/// @param gpuViewIndex View index of a currently bound shader data container. Must be a valid UAV to the @p buffer.
		/// @param cpuContainer Not shader visible shader data container.
		/// @param cpuViewIndex View index of the @p cpuContainer. Must be a valid UAV to the @p buffer.
		/// @param values Clear values.
		virtual void ClearUAV(const IBuffer& buffer, std::uint32_t gpuViewIndex, const IShaderDataContainer& cpuContainer, std::uint32_t cpuViewIndex,
			const Math::Vector4<float>& values) = 0;
		/// @brief Clears a UAV.
		/// @param texture Texture to clear.
		/// @param gpuViewIndex View index of a currently bound shader data container. Must be a valid UAV to the @p texture.
		/// @param cpuContainer Not shader visible shader data container.
		/// @param cpuViewIndex View index of the @p cpuContainer. Must be a valid UAV to the @p texture.
		/// @param values Clear values.
		/// @param rects Rects to clear. If empty, the whole texture will be cleared.
		virtual void ClearUAV(const ITexture& texture, std::uint32_t gpuViewIndex, const IShaderDataContainer& cpuContainer, std::uint32_t cpuViewIndex,
			const Math::Vector4<float>& values, std::span<const Math::CornerRect<std::uint32_t>> rects = std::span<const Math::CornerRect<std::uint32_t>>()) = 0;

		/// @brief Copies from the buffer to the other buffer.
		/// @param source Source buffer.
		/// @param destination Destination buffer.
		/// @note The buffers must have the same size.
		virtual void Copy(const IBuffer& source, IBuffer& destination) = 0;
		/// @brief Copies from the buffer region to the other buffer.
		/// @param source Source buffer.
		/// @param destination Destination buffer.
		/// @param ranges Copy ranges.
		virtual void Copy(const IBuffer& source, IBuffer& destination, std::span<const CopyBufferRange> ranges) = 0;
		/// @brief Copies from the texture to the other texture.
		/// @param source Source texture.
		/// @param destination Destination texture.
		/// @note The textures must have the same layout.
		virtual void Copy(const ITexture& source, ITexture& destination) = 0;
		/// @brief Copies from the texture to the other texture.
		/// @param source Source texture.
		/// @param destination Destination texture.
		/// @param range Sub-texture range.
		/// @note The texture must have compatible layouts.
		virtual void Copy(const ITexture& source, ITexture& destination, const CopySubTextureRange& range) = 0;
		/// @brief Copies from the texture to the other texture.
		/// @param source Source texture.
		/// @param destination Destination texture.
		/// @param range Sub-texture range with a box description.
		/// @note The texture must have compatible layouts.
		virtual void Copy(const ITexture& source, ITexture& destination, const BoxCopySubTextureRange& range) = 0;
		/// @brief Copies from the texture buffer to the texture.
		/// @param source Source texture buffer.
		/// @param destination Destination texture.
		/// @param footprints Copyable footprints. Must be valid for the both @p source and @p destination.
		virtual void Copy(const IBuffer& source, ITexture& destination, std::span<const CopyableFootprint> footprints) = 0;
		/// @brief Copies from the texture buffer to the texture.
		/// @param source Source texture buffer.
		/// @param destination Destination texture.
		/// @param footprints Copyable footprints. Must be valid for the both @p source and @p destination.
		/// @param range Sub-texture range.
		virtual void Copy(const IBuffer& source, ITexture& destination, std::span<const CopyableFootprint> footprints, const FootprintedCopySubTextureRange& range) = 0;
		/// @brief Copies from the texture buffer to the texture.
		/// @param source Source texture buffer.
		/// @param destination Destination texture.
		/// @param footprints Copyable footprints. Must be valid for the both @p source and @p destination.
		/// @param range Sub-texture range with a box description.
		virtual void Copy(const IBuffer& source, ITexture& destination, std::span<const CopyableFootprint> footprints, const FootprintedBoxCopySubTextureRange& range) = 0;
		/// @brief Copies from the texture to the texture buffer.
		/// @param source Source texture.
		/// @param destination Destination texture buffer.
		/// @param footprints Copyable footprints. Must be valid for the both @p source and @p destination.
		virtual void Copy(const ITexture& source, IBuffer& destination, std::span<const CopyableFootprint> footprints) = 0;
		/// @brief Copies from the texture to the texture buffer.
		/// @param source Source texture.
		/// @param destination Destination texture buffer.
		/// @param footprints Copyable footprints. Must be valid for the both @p source and @p destination.
		/// @param range Sub-texture range.
		virtual void Copy(const ITexture& source, IBuffer& destination, std::span<const CopyableFootprint> footprints, const FootprintedCopySubTextureRange& range) = 0;
		/// @brief Copies from the texture to the texture buffer.
		/// @param source Source texture.
		/// @param destination Destination texture buffer.
		/// @param footprints Copyable footprints. Must be valid for the both @p source and @p destination.
		/// @param range Sub-texture range with a box description.
		virtual void Copy(const ITexture& source, IBuffer& destination, std::span<const CopyableFootprint> footprints, const FootprintedBoxCopySubTextureRange& range) = 0;

		/// @brief Resolves the texture into the other texture.
		/// @param source Source texture. Must have a sample count greater than 1.
		/// @param destination Destination texture. Must have a sample count equal 1.
		/// @param mode Resolve mode.
		/// @note The textures must have all the parameters identical except for sample counts.
		virtual void Resolve(const ITexture& source, ITexture& destination, ResolveMode mode = ResolveMode::Average) = 0;
		/// @brief Resolves the texture into the other texture.
		/// @param source Source texture. Must have a sample count greater than 1.
		/// @param destination Destination texture. Must have a sample count equal 1.
		/// @param range Sub-texture range.
		/// @param mode Resolve mode.
		/// @note The textures must have all the parameters identical except for sample counts.
		virtual void Resolve(const ITexture& source, ITexture& destination, const CopySubTextureRange& range, ResolveMode mode = ResolveMode::Average) = 0;
		/// @brief Resolves the texture into the other texture.
		/// @param source Source texture. Must have a sample count greater than 1.
		/// @param destination Destination texture. Must have a sample count equal 1.
		/// @param range Sub-texture range with a rect description.
		/// @param mode Resolve mode.
		/// @note The textures must have all the parameters identical except for sample counts.
		virtual void Resolve(const ITexture& source, ITexture& destination, const RectCopySubTextureRange& range, ResolveMode mode = ResolveMode::Average) = 0;

		/// @brief Executes the secondary graphics command list.
		/// @param secondary Command list to execute. Must be closed.
		virtual void Execute(const ISecondaryGraphicsCommandList& secondary) = 0;
	};
}

namespace PonyEngine::RenderDevice
{
	void IGraphicsCommandList::Barrier(const std::span<const BufferBarrier> bufferBarriers)
	{
		Barrier(bufferBarriers, std::span<const TextureBarrier>());
	}

	void IGraphicsCommandList::Barrier(const std::span<const TextureBarrier> textureBarriers)
	{
		Barrier(std::span<const BufferBarrier>(), textureBarriers);
	}

	void IGraphicsCommandList::SetRasterRegion(const RasterRegion& region)
	{
		SetRasterRegions(std::span(&region, 1uz));
	}

	void IGraphicsCommandList::BindTargets()
	{
		BindTargets(nullptr, 0u, nullptr);
	}

	void IGraphicsCommandList::BindTargets(const RenderTargetBinding& renderTargetBinding)
	{
		BindTargets(&renderTargetBinding, 1u, nullptr);
	}

	void IGraphicsCommandList::BindTargets(const std::span<const RenderTargetBinding> renderTargetBindings)
	{
		BindTargets(renderTargetBindings, nullptr);
	}

	void IGraphicsCommandList::BindTargets(const DepthStencilBinding& depthStencilBinding)
	{
		BindTargets(nullptr, 0, &depthStencilBinding);
	}

	void IGraphicsCommandList::BindTargets(const RenderTargetBinding& renderTargetBinding, const DepthStencilBinding& depthStencilBinding)
	{
		BindTargets(std::span<const RenderTargetBinding>(&renderTargetBinding, 1uz), &depthStencilBinding);
	}

	void IGraphicsCommandList::BindTargets(const RenderTargetBinding& renderTargetBinding, const std::uint8_t renderTargetCount)
	{
		BindTargets(&renderTargetBinding, renderTargetCount, nullptr);
	}

	void IGraphicsCommandList::BindContainers()
	{
		BindContainers(nullptr, nullptr);
	}

	void IGraphicsCommandList::BindContainers(const IShaderDataContainer& shaderDataContainer)
	{
		BindContainers(&shaderDataContainer, nullptr);
	}

	void IGraphicsCommandList::BindContainers(const ISamplerContainer& samplerContainer)
	{
		BindContainers(nullptr, &samplerContainer);
	}

	void IGraphicsCommandList::BindGraphics(const ShaderDataBinding& shaderDataBinding)
	{
		BindGraphics(std::span(&shaderDataBinding, 1uz));
	}

	void IGraphicsCommandList::BindGraphics(const SamplerBinding& samplerBinding)
	{
		BindGraphics(std::span(&samplerBinding, 1uz));
	}

	void IGraphicsCommandList::BindGraphics(const std::span<const ShaderDataBinding> shaderDataBindings)
	{
		BindGraphics(shaderDataBindings, std::span<const SamplerBinding>());
	}

	void IGraphicsCommandList::BindGraphics(const std::span<const SamplerBinding> samplerBindings)
	{
		BindGraphics(std::span<const ShaderDataBinding>(), samplerBindings);
	}

	void IGraphicsCommandList::BindCompute(const ShaderDataBinding& shaderDataBinding)
	{
		BindCompute(std::span(&shaderDataBinding, 1uz));
	}

	void IGraphicsCommandList::BindCompute(const SamplerBinding& samplerBinding)
	{
		BindCompute(std::span(&samplerBinding, 1uz));
	}

	void IGraphicsCommandList::BindCompute(const std::span<const ShaderDataBinding> shaderDataBindings)
	{
		BindCompute(shaderDataBindings, std::span<const SamplerBinding>());
	}

	void IGraphicsCommandList::BindCompute(const std::span<const SamplerBinding> samplerBindings)
	{
		BindCompute(std::span<const ShaderDataBinding>(), samplerBindings);
	}

	void IGraphicsCommandList::DispatchGraphics(const std::uint32_t threadGroupCount)
	{
		DispatchGraphics(Math::Vector3<std::uint32_t>(threadGroupCount, 1u, 1u));
	}

	void IGraphicsCommandList::DispatchGraphics(const Math::Vector1<std::uint32_t>& threadGroupCounts)
	{
		DispatchGraphics(Math::Vector3<std::uint32_t>(threadGroupCounts.X(), 1u, 1u));
	}

	void IGraphicsCommandList::DispatchGraphics(const Math::Vector2<std::uint32_t>& threadGroupCounts)
	{
		DispatchGraphics(Math::Vector3<std::uint32_t>(threadGroupCounts.X(), threadGroupCounts.Y(), 1u));
	}

	void IGraphicsCommandList::DispatchCompute(const std::uint32_t threadGroupCount)
	{
		DispatchCompute(Math::Vector3<std::uint32_t>(threadGroupCount, 1u, 1u));
	}

	void IGraphicsCommandList::DispatchCompute(const Math::Vector1<std::uint32_t>& threadGroupCounts)
	{
		DispatchCompute(Math::Vector3<std::uint32_t>(threadGroupCounts.X(), 1u, 1u));
	}

	void IGraphicsCommandList::DispatchCompute(const Math::Vector2<std::uint32_t>& threadGroupCounts)
	{
		DispatchCompute(Math::Vector3<std::uint32_t>(threadGroupCounts.X(), threadGroupCounts.Y(), 1u));
	}
}
