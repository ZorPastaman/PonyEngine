/***************************************************
* MIT License                                     *
*                                                 *
* Copyright (c) 2023-present Vladimir Popov       *
*                                                 *
* Email: zor1994@gmail.com                        *
* Repo: https://github.com/ZorPastaman/PonyEngine *
***************************************************/

module;

#include <cassert>

#include "PonyBase/Core/Direct3D12/Framework.h"

export module PonyEngine.Render.Direct3D12.Detail:ResourceManager;

import <memory>;

import :IResourceManager;
import :ISubSystemContext;
import :ResourcePlacement;

export namespace PonyEngine::Render::Direct3D12
{
	class ResourceManager final : public IResourceManager
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit ResourceManager(ISubSystemContext& d3d12System) noexcept;
		[[nodiscard("Pure constructor")]]
		ResourceManager(const ResourceManager&) = delete;
		[[nodiscard("Pure constructor")]]
		ResourceManager(ResourceManager&&) = delete;

		~ResourceManager() noexcept = default;

		[[nodiscard("Redendant call")]]
		virtual std::shared_ptr<Buffer> CreateBuffer(UINT64 size, ResourcePlacement placement) override;

		ResourceManager& operator =(const ResourceManager&) = delete;
		ResourceManager& operator =(ResourceManager&&) = delete;

	private:
		[[nodiscard("Pure function")]]
		static D3D12_HEAP_TYPE GetHeapType(ResourcePlacement placement) noexcept;

		ISubSystemContext* d3d12System;
	};
}

namespace PonyEngine::Render::Direct3D12
{
	ResourceManager::ResourceManager(ISubSystemContext& d3d12System) noexcept :
		d3d12System{&d3d12System}
	{
	}

	std::shared_ptr<Buffer> ResourceManager::CreateBuffer(const UINT64 size, const ResourcePlacement placement)
	{
		const auto heapProperties = D3D12_HEAP_PROPERTIES
		{
			.Type = GetHeapType(placement),
			.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN,
			.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN,
			.CreationNodeMask = 0u,
			.VisibleNodeMask = 0u
		};
		const auto resourceDesc = D3D12_RESOURCE_DESC1
		{
			.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER,
			.Alignment = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT,
			.Width = size,
			.Height = 1u,
			.DepthOrArraySize = 1u,
			.MipLevels = 1u,
			.Format = DXGI_FORMAT_UNKNOWN,
			.SampleDesc = DXGI_SAMPLE_DESC{.Count = 1u, .Quality = 0u},
			.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR,
			.Flags = D3D12_RESOURCE_FLAG_NONE,
			.SamplerFeedbackMipRegion = D3D12_MIP_REGION{}
		};

		Microsoft::WRL::ComPtr<ID3D12Resource2> resource;
		if (const HRESULT result = d3d12System->Device().CreateCommittedResource3(&heapProperties, D3D12_HEAP_FLAG_NONE, &resourceDesc, D3D12_BARRIER_LAYOUT_UNDEFINED,
			nullptr, nullptr, 0, nullptr, IID_PPV_ARGS(resource.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to create buffer resource with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		return std::make_shared<Buffer>(*resource.Get());
	}

	D3D12_HEAP_TYPE ResourceManager::GetHeapType(const ResourcePlacement placement) noexcept
	{
		switch (placement)
		{
		case ResourcePlacement::CPU:
			return D3D12_HEAP_TYPE_UPLOAD;
		case ResourcePlacement::GPU:
			return D3D12_HEAP_TYPE_DEFAULT;
		default: [[unlikely]]
			assert(false && "The resource placement is incorrect.");
			return D3D12_HEAP_TYPE_UPLOAD;
		}
	}
}
