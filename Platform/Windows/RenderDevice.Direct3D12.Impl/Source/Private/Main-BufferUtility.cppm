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

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:BufferUtility;

import std;

import PonyEngine.RenderDevice;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	[[nodiscard("Pure function")]]
	constexpr D3D12_HEAP_FLAGS ToHeapFlags(BufferUsage usage, bool notZeroed) noexcept;

	[[nodiscard("Pure function")]]
	constexpr D3D12_RESOURCE_DESC1 ToResourceDesc(const BufferParams& params) noexcept;
	[[nodiscard("Pure function")]]
	constexpr D3D12_RESOURCE_FLAGS ToResourceFlags(BufferUsage usage) noexcept;

	[[nodiscard("Pure function")]]
	constexpr D3D12_CONSTANT_BUFFER_VIEW_DESC ToCBVDesc(D3D12_GPU_VIRTUAL_ADDRESS address, const CBVParams& params) noexcept;
	[[nodiscard("Pure function")]]
	constexpr D3D12_SHADER_RESOURCE_VIEW_DESC ToSRVDesc(const BufferSRVParams& params) noexcept;
	[[nodiscard("Pure function")]]
	constexpr D3D12_UNORDERED_ACCESS_VIEW_DESC ToUAVDesc(const BufferUAVParams& params) noexcept;
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	constexpr D3D12_HEAP_FLAGS ToHeapFlags(const BufferUsage usage, const bool notZeroed) noexcept
	{
		auto flags = D3D12_HEAP_FLAG_NONE;
		if (notZeroed)
		{
			flags |= D3D12_HEAP_FLAG_CREATE_NOT_ZEROED;
		}
		if (Any(BufferUsage::UnorderedAccess, usage))
		{
			flags |= D3D12_HEAP_FLAG_ALLOW_SHADER_ATOMICS;
		}

		return flags;
	}

	constexpr D3D12_RESOURCE_DESC1 ToResourceDesc(const BufferParams& params) noexcept
	{
		return D3D12_RESOURCE_DESC1
		{
			.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER,
			.Alignment = 0ull,
			.Width = params.size,
			.Height = 1u,
			.DepthOrArraySize = 1u,
			.MipLevels = 1u,
			.Format = DXGI_FORMAT_UNKNOWN,
			.SampleDesc = DXGI_SAMPLE_DESC{.Count = 1u, .Quality = 0u},
			.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR,
			.Flags = ToResourceFlags(params.usage),
			.SamplerFeedbackMipRegion = D3D12_MIP_REGION{}
		};
	}

	constexpr D3D12_RESOURCE_FLAGS ToResourceFlags(const BufferUsage usage) noexcept
	{
		return Any(BufferUsage::UnorderedAccess, usage) ? D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS : D3D12_RESOURCE_FLAG_NONE;
	}

	constexpr D3D12_CONSTANT_BUFFER_VIEW_DESC ToCBVDesc(const D3D12_GPU_VIRTUAL_ADDRESS address, const CBVParams& params) noexcept
	{
		return D3D12_CONSTANT_BUFFER_VIEW_DESC
		{
			.BufferLocation = address + params.offset,
			.SizeInBytes = params.size
		};
	}

	constexpr D3D12_SHADER_RESOURCE_VIEW_DESC ToSRVDesc(const BufferSRVParams& params) noexcept
	{
		return D3D12_SHADER_RESOURCE_VIEW_DESC
		{
			.Format = DXGI_FORMAT_UNKNOWN,
			.ViewDimension = D3D12_SRV_DIMENSION_BUFFER,
			.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING,
			.Buffer = D3D12_BUFFER_SRV
			{
				.FirstElement = params.firstElementIndex,
				.NumElements = params.elementCount,
				.StructureByteStride = params.stride,
				.Flags = params.raw ? D3D12_BUFFER_SRV_FLAG_RAW : D3D12_BUFFER_SRV_FLAG_NONE
			}
		};
	}

	constexpr D3D12_UNORDERED_ACCESS_VIEW_DESC ToUAVDesc(const BufferUAVParams& params) noexcept
	{
		return D3D12_UNORDERED_ACCESS_VIEW_DESC
		{
			.Format = DXGI_FORMAT_UNKNOWN,
			.ViewDimension = D3D12_UAV_DIMENSION_BUFFER,
			.Buffer = D3D12_BUFFER_UAV
			{
				.FirstElement = params.firstElementIndex,
				.NumElements = params.elementCount,
				.StructureByteStride = params.stride,
				.CounterOffsetInBytes = 0ull,
				.Flags = params.raw ? D3D12_BUFFER_UAV_FLAG_RAW : D3D12_BUFFER_UAV_FLAG_NONE
			}
		};
	}
}
