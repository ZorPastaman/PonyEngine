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
import :ICommandList;
import :IComputePipelineState;
import :IGraphicsPipelineState;
import :ISecondaryGraphicsCommandList;
import :ISamplerContainer;
import :IShaderDataContainer;
import :RasterRegion;
import :RenderTargetBinding;
import :ResolveMode;
import :SamplerBinding;
import :ShaderDataBinding;
import :StencilReference;
import :TextureBarrier;

export namespace PonyEngine::RenderDevice
{
	class IGraphicsCommandList : public ICommandList
	{
		PONY_INTERFACE_BODY(IGraphicsCommandList)

		void Barrier(std::span<const BufferBarrier> bufferBarriers);
		void Barrier(std::span<const TextureBarrier> textureBarriers);
		virtual void Barrier(std::span<const BufferBarrier> bufferBarriers, std::span<const TextureBarrier> textureBarriers) = 0;

		void SetRasterRegion(const RasterRegion& region);
		virtual void SetRasterRegions(std::span<const RasterRegion> regions) = 0;
		virtual void SetDepthBias(const DepthBias& bias) = 0;
		virtual void SetDepthBounds(const DepthRange& range) = 0;
		virtual void SetStencilReference(const StencilReference& reference) = 0;
		virtual void SetBlendFactor(const Math::ColorRGBA<float>& factor) = 0;

		virtual void BindTargets(std::span<const RenderTargetBinding> renderTargetBindings, const DepthStencilBinding* depthStencilBinding) = 0;
		virtual void BindTargets(const RenderTargetBinding* renderTargetBinding, std::uint8_t renderTargetCount, const DepthStencilBinding* depthStencilBinding) = 0;
		virtual void BindContainers(const IShaderDataContainer* shaderDataContainer, const ISamplerContainer* samplerContainer) = 0;
		virtual void BindPipelineState(const IGraphicsPipelineState& pipelineState) = 0;
		virtual void BindPipelineState(const IComputePipelineState& pipelineState) = 0;
		void BindGraphics(const ShaderDataBinding& shaderDataBinding);
		void BindGraphics(const SamplerBinding& samplerBinding);
		void BindGraphics(std::span<const ShaderDataBinding> shaderDataBindings);
		void BindGraphics(std::span<const SamplerBinding> samplerBindings);
		virtual void BindGraphics(std::span<const ShaderDataBinding> shaderDataBindings, std::span<const SamplerBinding> samplerBindings) = 0;
		void BindCompute(const ShaderDataBinding& shaderDataBinding);
		void BindCompute(const SamplerBinding& samplerBinding);
		void BindCompute(std::span<const ShaderDataBinding> shaderDataBindings);
		void BindCompute(std::span<const SamplerBinding> samplerBindings);
		virtual void BindCompute(std::span<const ShaderDataBinding> shaderDataBindings, std::span<const SamplerBinding> samplerBindings) = 0;

		void DispatchGraphics(std::uint32_t threadGroupCount);
		void DispatchGraphics(const Math::Vector1<std::uint32_t>& threadGroupCounts);
		void DispatchGraphics(const Math::Vector2<std::uint32_t>& threadGroupCounts);
		virtual void DispatchGraphics(const Math::Vector3<std::uint32_t>& threadGroupCounts) = 0;
		void DispatchCompute(std::uint32_t threadGroupCount);
		void DispatchCompute(const Math::Vector1<std::uint32_t>& threadGroupCounts);
		void DispatchCompute(const Math::Vector2<std::uint32_t>& threadGroupCounts);
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

		virtual void Resolve(const ITexture& source, ITexture& destination, ResolveMode mode = ResolveMode::Average) = 0;
		virtual void Resolve(const ITexture& source, ITexture& destination, const CopySubTextureRange& range, ResolveMode mode = ResolveMode::Average) = 0;
		virtual void Resolve(const ITexture& source, ITexture& destination, const BoxCopySubTextureRange& range, ResolveMode mode = ResolveMode::Average) = 0;

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
