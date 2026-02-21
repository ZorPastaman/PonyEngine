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

import :BufferBarrier;
import :CopyableFootprint;
import :ICommandList;
import :IComputePipelineState;
import :ISamplerContainer;
import :IShaderDataContainer;
import :SamplerBinding;
import :ShaderDataBinding;
import :TextureBarrier;

export namespace PonyEngine::RenderDevice
{
	class IComputeCommandList : public ICommandList
	{
		PONY_INTERFACE_BODY(IComputeCommandList)

		void Barrier(std::span<const BufferBarrier> bufferBarriers);
		void Barrier(std::span<const TextureBarrier> textureBarriers);
		virtual void Barrier(std::span<const BufferBarrier> bufferBarriers, std::span<const TextureBarrier> textureBarriers) = 0;

		virtual void BindContainers(const IShaderDataContainer* shaderDataContainer, const ISamplerContainer* samplerContainer) = 0;
		virtual void BindPipelineState(const IComputePipelineState& pipelineState) = 0;
		void BindCompute(const ShaderDataBinding& shaderDataBinding);
		void BindCompute(const SamplerBinding& samplerBinding);
		void BindCompute(std::span<const ShaderDataBinding> shaderDataBindings);
		void BindCompute(std::span<const SamplerBinding> samplerBindings);
		virtual void BindCompute(std::span<const ShaderDataBinding> shaderDataBindings, std::span<const SamplerBinding> samplerBindings) = 0;

		virtual void DispatchCompute(const Math::Vector3<std::uint32_t>& threadGroupCounts) = 0;

		virtual void Copy(const IBuffer& source, IBuffer& destination) = 0;
		virtual void Copy(const IBuffer& source, IBuffer& destination, std::uint64_t sourceOffset, std::uint64_t destinationOffset, std::uint64_t size) = 0;
		virtual void Copy(const ITexture& source, ITexture& destination) = 0;
		virtual void Copy(const ITexture& source, ITexture& destination, const CopySubTextureRange& range) = 0;
		virtual void Copy(const ITexture& source, ITexture& destination, const BoxCopySubTextureRange& range) = 0;
		virtual void Copy(const IBuffer& source, ITexture& destination, std::span<const CopyableFootprint> footprints) = 0;
		virtual void Copy(const IBuffer& source, ITexture& destination, std::span<const CopyableFootprint> footprints, const FootprintedCopySubTextureRange& range) = 0;
		virtual void Copy(const IBuffer& source, ITexture& destination, std::span<const CopyableFootprint> footprints, const FootprintedBoxCopySubTextureRange& range) = 0;
		virtual void Copy(const ITexture& source, IBuffer& destination, std::span<const CopyableFootprint> footprints) = 0;
		virtual void Copy(const ITexture& source, IBuffer& destination, std::span<const CopyableFootprint> footprints, const FootprintedCopySubTextureRange& range) = 0;
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
}
