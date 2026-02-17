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

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:DescriptorHeapUtility;

import std;

import PonyEngine.RenderDevice;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	[[nodiscard("Pure function")]]
	constexpr D3D12_DESCRIPTOR_HEAP_DESC ToDescriptorHeapDesc(const ShaderDataContainerParams& params) noexcept;
	[[nodiscard("Pure function")]]
	constexpr D3D12_DESCRIPTOR_HEAP_DESC ToDescriptorHeapDesc(const RenderTargetContainerParams& params) noexcept;
	[[nodiscard("Pure function")]]
	constexpr D3D12_DESCRIPTOR_HEAP_DESC ToDescriptorHeapDesc(const DepthStencilContainerParams& params) noexcept;
	[[nodiscard("Pure function")]]
	constexpr D3D12_DESCRIPTOR_HEAP_DESC ToDescriptorHeapDesc(const SamplerContainerParams& params) noexcept;
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	constexpr D3D12_DESCRIPTOR_HEAP_DESC ToDescriptorHeapDesc(const ShaderDataContainerParams& params) noexcept
	{
		return D3D12_DESCRIPTOR_HEAP_DESC
		{
			.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,
			.NumDescriptors = params.size,
			.Flags = params.shaderVisible ? D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE : D3D12_DESCRIPTOR_HEAP_FLAG_NONE,
			.NodeMask = 0u
		};
	}

	constexpr D3D12_DESCRIPTOR_HEAP_DESC ToDescriptorHeapDesc(const RenderTargetContainerParams& params) noexcept
	{
		return D3D12_DESCRIPTOR_HEAP_DESC
		{
			.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV,
			.NumDescriptors = params.size,
			.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE,
			.NodeMask = 0u
		};
	}

	constexpr D3D12_DESCRIPTOR_HEAP_DESC ToDescriptorHeapDesc(const DepthStencilContainerParams& params) noexcept
	{
		return D3D12_DESCRIPTOR_HEAP_DESC
		{
			.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV,
			.NumDescriptors = params.size,
			.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE,
			.NodeMask = 0u
		};
	}

	constexpr D3D12_DESCRIPTOR_HEAP_DESC ToDescriptorHeapDesc(const SamplerContainerParams& params) noexcept
	{
		return D3D12_DESCRIPTOR_HEAP_DESC
		{
			.Type = D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER,
			.NumDescriptors = params.size,
			.Flags = params.shaderVisible ? D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE : D3D12_DESCRIPTOR_HEAP_FLAG_NONE,
			.NodeMask = 0u
		};
	}
}
