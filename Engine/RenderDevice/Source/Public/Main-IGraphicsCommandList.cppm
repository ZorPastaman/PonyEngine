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
import :ICommandList;
import :ISecondaryGraphicsCommandList;
import :ResolveMode;
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

		virtual void SetDepthBias(const DepthBias& bias) = 0;
		virtual void SetDepthBounds(float min, float max) = 0;
		virtual void SetStencilReference(const StencilReference& reference) = 0;

		virtual void DispatchMesh(const Math::Vector3<std::uint32_t>& threadGroupCounts) = 0;
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

		virtual void Execute(ISecondaryGraphicsCommandList& secondary) = 0;
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
}
