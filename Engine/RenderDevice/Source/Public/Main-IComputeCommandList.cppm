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

export module PonyEngine.RenderDevice:IComputeCommandList;

import std;

import PonyEngine.Math;

import :BufferBarrier;
import :CopyableFootprint;
import :IBuffer;
import :ICommandList;
import :IComputePipelineState;
import :ISamplerContainer;
import :IShaderDataContainer;
import :ITexture;
import :SamplerBinding;
import :ShaderDataBinding;
import :SubTextureRange;
import :TextureBarrier;

export namespace PonyEngine::RenderDevice
{
	/// @brief Compute command list.
	class IComputeCommandList : public ICommandList
	{
		PONY_INTERFACE_BODY(IComputeCommandList)

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
		/// @brief Binds the compute pipeline state.
		/// @param pipelineState Compute pipeline state to bind.
		virtual void BindPipelineState(const IComputePipelineState& pipelineState) = 0;
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
	};
}

namespace PonyEngine::RenderDevice
{
	void IComputeCommandList::Barrier(const std::span<const BufferBarrier> bufferBarriers)
	{
		Barrier(bufferBarriers, std::span<const TextureBarrier>());
	}

	void IComputeCommandList::Barrier(const std::span<const TextureBarrier> textureBarriers)
	{
		Barrier(std::span<const BufferBarrier>(), textureBarriers);
	}

	void IComputeCommandList::BindContainers()
	{
		BindContainers(nullptr, nullptr);
	}

	void IComputeCommandList::BindContainers(const IShaderDataContainer& shaderDataContainer)
	{
		BindContainers(&shaderDataContainer, nullptr);
	}

	void IComputeCommandList::BindContainers(const ISamplerContainer& samplerContainer)
	{
		BindContainers(nullptr, &samplerContainer);
	}

	void IComputeCommandList::BindCompute(const ShaderDataBinding& shaderDataBinding)
	{
		BindCompute(std::span(&shaderDataBinding, 1uz));
	}

	void IComputeCommandList::BindCompute(const SamplerBinding& samplerBinding)
	{
		BindCompute(std::span(&samplerBinding, 1uz));
	}

	void IComputeCommandList::BindCompute(const std::span<const ShaderDataBinding> shaderDataBindings)
	{
		BindCompute(shaderDataBindings, std::span<const SamplerBinding>());
	}

	void IComputeCommandList::BindCompute(const std::span<const SamplerBinding> samplerBindings)
	{
		BindCompute(std::span<const ShaderDataBinding>(), samplerBindings);
	}

	void IComputeCommandList::DispatchCompute(const std::uint32_t threadGroupCount)
	{
		DispatchCompute(Math::Vector3<std::uint32_t>(threadGroupCount, 1u, 1u));
	}

	void IComputeCommandList::DispatchCompute(const Math::Vector1<std::uint32_t>& threadGroupCounts)
	{
		DispatchCompute(Math::Vector3<std::uint32_t>(threadGroupCounts.X(), 1u, 1u));
	}

	void IComputeCommandList::DispatchCompute(const Math::Vector2<std::uint32_t>& threadGroupCounts)
	{
		DispatchCompute(Math::Vector3<std::uint32_t>(threadGroupCounts.X(), threadGroupCounts.Y(), 1u));
	}
}
