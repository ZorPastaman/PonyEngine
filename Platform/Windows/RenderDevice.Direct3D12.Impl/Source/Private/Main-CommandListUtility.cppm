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

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:CommandListUtility;

import std;

import PonyEngine.RenderDevice;

import :TextureUtility;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	[[nodiscard("Pure function")]]
	constexpr D3D12_BARRIER_SYNC ToSync(PipelineStage stages) noexcept;
	[[nodiscard("Pure function")]]
	constexpr D3D12_BARRIER_ACCESS ToAccess(std::optional<ResourceAccess> accesses) noexcept;
	[[nodiscard("Pure function")]]
	constexpr D3D12_BARRIER_SUBRESOURCE_RANGE ToSubresourceRange(const MipRange& mipRange, const ArrayRange& arrayRange, AspectMask aspects,
		std::uint32_t resourceMipCount, std::uint32_t resourceArraySize) noexcept;
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	constexpr D3D12_BARRIER_SYNC ToSync(const PipelineStage stages) noexcept
	{
		auto sync = D3D12_BARRIER_SYNC_NONE;
		if (Any(PipelineStage::VertexShading, stages))
		{
			sync |= D3D12_BARRIER_SYNC_VERTEX_SHADING;
		}
		if (Any(PipelineStage::PixelShading, stages))
		{
			sync |= D3D12_BARRIER_SYNC_PIXEL_SHADING;
		}
		if (Any(PipelineStage::RenderTarget, stages))
		{
			sync |= D3D12_BARRIER_SYNC_RENDER_TARGET;
		}
		if (Any(PipelineStage::DepthStencil, stages))
		{
			sync |= D3D12_BARRIER_SYNC_DEPTH_STENCIL;
		}
		if (Any(PipelineStage::ComputeShading, stages))
		{
			sync |= D3D12_BARRIER_SYNC_COMPUTE_SHADING;
		}
		if (Any(PipelineStage::Copy, stages))
		{
			sync |= D3D12_BARRIER_SYNC_COPY;
		}
		if (Any(PipelineStage::Resolve, stages))
		{
			sync |= D3D12_BARRIER_SYNC_RESOLVE;
		}
		if (Any(PipelineStage::UnorderedAccessClearing, stages))
		{
			sync |= D3D12_BARRIER_SYNC_CLEAR_UNORDERED_ACCESS_VIEW;
		}

		return sync;
	}

	constexpr D3D12_BARRIER_ACCESS ToAccess(const std::optional<ResourceAccess> accesses) noexcept
	{
		if (!accesses)
		{
			return D3D12_BARRIER_ACCESS_NO_ACCESS;
		}

		auto access = D3D12_BARRIER_ACCESS_COMMON;
		if (Any(ResourceAccess::ConstantBuffer, *accesses))
		{
			access |= D3D12_BARRIER_ACCESS_CONSTANT_BUFFER;
		}
		if (Any(ResourceAccess::ShaderResource, *accesses))
		{
			access |= D3D12_BARRIER_ACCESS_SHADER_RESOURCE;
		}
		if (Any(ResourceAccess::UnorderedAccess, *accesses))
		{
			access |= D3D12_BARRIER_ACCESS_UNORDERED_ACCESS;
		}
		if (Any(ResourceAccess::RenderTarget, *accesses))
		{
			access |= D3D12_BARRIER_ACCESS_RENDER_TARGET;
		}
		if (Any(ResourceAccess::DepthStencilRead, *accesses))
		{
			access |= D3D12_BARRIER_ACCESS_DEPTH_STENCIL_READ;
		}
		if (Any(ResourceAccess::DepthStencilWrite, *accesses))
		{
			access |= D3D12_BARRIER_ACCESS_DEPTH_STENCIL_WRITE;
		}
		if (Any(ResourceAccess::CopySource, *accesses))
		{
			access |= D3D12_BARRIER_ACCESS_COPY_SOURCE;
		}
		if (Any(ResourceAccess::CopyDestination, *accesses))
		{
			access |= D3D12_BARRIER_ACCESS_COPY_DEST;
		}
		if (Any(ResourceAccess::ResolveSource, *accesses))
		{
			access |= D3D12_BARRIER_ACCESS_RESOLVE_SOURCE;
		}
		if (Any(ResourceAccess::ResolveDestination, *accesses))
		{
			access |= D3D12_BARRIER_ACCESS_RESOLVE_DEST;
		}

		return access;
	}

	constexpr D3D12_BARRIER_SUBRESOURCE_RANGE ToSubresourceRange(const MipRange& mipRange, const ArrayRange& arrayRange, const AspectMask aspects,
		const std::uint32_t resourceMipCount, const std::uint32_t resourceArraySize) noexcept
	{
		return D3D12_BARRIER_SUBRESOURCE_RANGE
		{
			.IndexOrFirstMipLevel = static_cast<UINT>(mipRange.mostDetailedMipIndex),
			.NumMipLevels = static_cast<UINT>(mipRange.mipCount.value_or(resourceMipCount - mipRange.mostDetailedMipIndex)),
			.FirstArraySlice = static_cast<UINT>(arrayRange.firstArrayIndex),
			.NumArraySlices = static_cast<UINT>(arrayRange.arrayCount.value_or(resourceArraySize - arrayRange.firstArrayIndex)),
			.FirstPlane = ToFirstPlaneIndex(aspects),
			.NumPlanes = ToPlaneCount(aspects)
		};
	}
}
