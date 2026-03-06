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
	constexpr D3D12_BARRIER_SYNC ToSync(PipelineStageMask stages) noexcept;
	[[nodiscard("Pure function")]]
	constexpr D3D12_BARRIER_ACCESS ToAccess(std::optional<ResourceAccessMask> accesses) noexcept;
	[[nodiscard("Pure function")]]
	constexpr D3D12_BARRIER_SUBRESOURCE_RANGE ToSubresourceRange(const MipRange& mipRange, const ArrayRange& arrayRange, AspectMask aspects,
		std::uint8_t resourceMipCount, std::uint16_t resourceArraySize) noexcept;
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	constexpr D3D12_BARRIER_SYNC ToSync(const PipelineStageMask stages) noexcept
	{
		auto sync = D3D12_BARRIER_SYNC_NONE;
		if (Any(PipelineStageMask::VertexShading, stages))
		{
			sync |= D3D12_BARRIER_SYNC_VERTEX_SHADING;
		}
		if (Any(PipelineStageMask::PixelShading, stages))
		{
			sync |= D3D12_BARRIER_SYNC_PIXEL_SHADING;
		}
		if (Any(PipelineStageMask::RenderTarget, stages))
		{
			sync |= D3D12_BARRIER_SYNC_RENDER_TARGET;
		}
		if (Any(PipelineStageMask::DepthStencil, stages))
		{
			sync |= D3D12_BARRIER_SYNC_DEPTH_STENCIL;
		}
		if (Any(PipelineStageMask::ComputeShading, stages))
		{
			sync |= D3D12_BARRIER_SYNC_COMPUTE_SHADING;
		}
		if (Any(PipelineStageMask::Copy, stages))
		{
			sync |= D3D12_BARRIER_SYNC_COPY;
		}
		if (Any(PipelineStageMask::Resolve, stages))
		{
			sync |= D3D12_BARRIER_SYNC_RESOLVE;
		}
		if (Any(PipelineStageMask::UnorderedAccessClearing, stages))
		{
			sync |= D3D12_BARRIER_SYNC_CLEAR_UNORDERED_ACCESS_VIEW;
		}

		return sync;
	}

	constexpr D3D12_BARRIER_ACCESS ToAccess(const std::optional<ResourceAccessMask> accesses) noexcept
	{
		if (!accesses)
		{
			return D3D12_BARRIER_ACCESS_NO_ACCESS;
		}

		auto access = D3D12_BARRIER_ACCESS_COMMON;
		if (Any(ResourceAccessMask::ConstantBuffer, *accesses))
		{
			access |= D3D12_BARRIER_ACCESS_CONSTANT_BUFFER;
		}
		if (Any(ResourceAccessMask::ShaderResource, *accesses))
		{
			access |= D3D12_BARRIER_ACCESS_SHADER_RESOURCE;
		}
		if (Any(ResourceAccessMask::UnorderedAccess, *accesses))
		{
			access |= D3D12_BARRIER_ACCESS_UNORDERED_ACCESS;
		}
		if (Any(ResourceAccessMask::RenderTarget, *accesses))
		{
			access |= D3D12_BARRIER_ACCESS_RENDER_TARGET;
		}
		if (Any(ResourceAccessMask::DepthStencilRead, *accesses))
		{
			access |= D3D12_BARRIER_ACCESS_DEPTH_STENCIL_READ;
		}
		if (Any(ResourceAccessMask::DepthStencilWrite, *accesses))
		{
			access |= D3D12_BARRIER_ACCESS_DEPTH_STENCIL_WRITE;
		}
		if (Any(ResourceAccessMask::CopySource, *accesses))
		{
			access |= D3D12_BARRIER_ACCESS_COPY_SOURCE;
		}
		if (Any(ResourceAccessMask::CopyDestination, *accesses))
		{
			access |= D3D12_BARRIER_ACCESS_COPY_DEST;
		}
		if (Any(ResourceAccessMask::ResolveSource, *accesses))
		{
			access |= D3D12_BARRIER_ACCESS_RESOLVE_SOURCE;
		}
		if (Any(ResourceAccessMask::ResolveDestination, *accesses))
		{
			access |= D3D12_BARRIER_ACCESS_RESOLVE_DEST;
		}

		return access;
	}

	constexpr D3D12_BARRIER_SUBRESOURCE_RANGE ToSubresourceRange(const MipRange& mipRange, const ArrayRange& arrayRange, const AspectMask aspects,
		const std::uint8_t resourceMipCount, const std::uint16_t resourceArraySize) noexcept
	{
		return D3D12_BARRIER_SUBRESOURCE_RANGE
		{
			.IndexOrFirstMipLevel = mipRange.mostDetailedMipIndex,
			.NumMipLevels = mipRange.mipCount.value_or(resourceMipCount - mipRange.mostDetailedMipIndex),
			.FirstArraySlice = arrayRange.firstArrayIndex,
			.NumArraySlices = arrayRange.arrayCount.value_or(resourceArraySize - arrayRange.firstArrayIndex),
			.FirstPlane = ToFirstPlaneIndex(aspects),
			.NumPlanes = ToPlaneCount(aspects)
		};
	}
}
