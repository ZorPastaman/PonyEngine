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
import <vector>;

import :IResourceManager;
import :ISubSystemContext;
import :HeapType;

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
		virtual std::shared_ptr<Buffer> CreateBuffer(UINT64 size, HeapType heapType) override;

		[[nodiscard("Redendant call")]]
		virtual std::shared_ptr<Texture> CreateTexture1D(UINT64 width, DXGI_FORMAT format, DXGI_SAMPLE_DESC sampleDesc, HeapType heapType) override;
		[[nodiscard("Redendant call")]]
		virtual std::shared_ptr<Texture> CreateTexture2D(UINT64 width, UINT height, DXGI_FORMAT format, DXGI_SAMPLE_DESC sampleDesc, HeapType heapType) override;
		[[nodiscard("Redendant call")]]
		virtual std::shared_ptr<Texture> CreateTexture3D(UINT64 width, UINT height, UINT16 depth, DXGI_FORMAT format, DXGI_SAMPLE_DESC sampleDesc, HeapType heapType) override;
		[[nodiscard("Redendant call")]]
		virtual std::shared_ptr<Texture> CreateRenderTarget(UINT64 width, UINT height, DXGI_FORMAT format, DXGI_SAMPLE_DESC sampleDesc, const PonyMath::Color::RGBA<FLOAT>& clearColor) override;
		[[nodiscard("Redendant call")]]
		virtual std::shared_ptr<Texture> CreateDepthStencil(UINT64 width, UINT height, DXGI_FORMAT format, DXGI_SAMPLE_DESC sampleDesc, D3D12_DEPTH_STENCIL_VALUE depthStencilValue) override;

		void Clean() noexcept;

		ResourceManager& operator =(const ResourceManager&) = delete;
		ResourceManager& operator =(ResourceManager&&) = delete;

	private:
		[[nodiscard("Pure function")]]
		static D3D12_HEAP_PROPERTIES GetHeapProperties(HeapType heapType) noexcept;
		[[nodiscard("Pure function")]]
		static D3D12_HEAP_TYPE GetHeapType(HeapType heapType) noexcept;

		[[nodiscard("Redendant call")]]
		std::shared_ptr<Texture> CreateTexture(D3D12_RESOURCE_DIMENSION dimension, UINT64 width, UINT height, UINT16 depth, DXGI_FORMAT format, DXGI_SAMPLE_DESC sampleDesc, HeapType placement);

		ISubSystemContext* d3d12System;

		std::vector<std::shared_ptr<Resource>> resources;
	};
}

namespace PonyEngine::Render::Direct3D12
{
	ResourceManager::ResourceManager(ISubSystemContext& d3d12System) noexcept :
		d3d12System{&d3d12System}
	{
	}

	std::shared_ptr<Buffer> ResourceManager::CreateBuffer(const UINT64 size, const HeapType heapType)
	{
		const auto heapProperties = GetHeapProperties(heapType);
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

		const auto buffer = std::make_shared<Buffer>(*resource.Get());
		resources.push_back(buffer);

		return buffer;
	}

	std::shared_ptr<Texture> ResourceManager::CreateTexture1D(const UINT64 width, const DXGI_FORMAT format, const DXGI_SAMPLE_DESC sampleDesc, const HeapType heapType)
	{
		const auto texture = CreateTexture(D3D12_RESOURCE_DIMENSION_TEXTURE1D, width, 1u, 1u, format, sampleDesc, heapType);
		resources.push_back(texture);

		return texture;
	}

	std::shared_ptr<Texture> ResourceManager::CreateTexture2D(const UINT64 width, const UINT height, const DXGI_FORMAT format, const DXGI_SAMPLE_DESC sampleDesc, const HeapType heapType)
	{
		const auto texture = CreateTexture(D3D12_RESOURCE_DIMENSION_TEXTURE1D, width, height, 1u, format, sampleDesc, heapType);
		resources.push_back(texture);

		return texture;
	}

	std::shared_ptr<Texture> ResourceManager::CreateTexture3D(const UINT64 width, const UINT height, const UINT16 depth, const DXGI_FORMAT format, const DXGI_SAMPLE_DESC sampleDesc, const HeapType heapType)
	{
		const auto texture = CreateTexture(D3D12_RESOURCE_DIMENSION_TEXTURE1D, width, height, depth, format, sampleDesc, heapType);
		resources.push_back(texture);

		return texture;
	}

	std::shared_ptr<Texture> ResourceManager::CreateRenderTarget(const UINT64 width, const UINT height, const DXGI_FORMAT format, const DXGI_SAMPLE_DESC sampleDesc, const PonyMath::Color::RGBA<FLOAT>& clearColor)
	{
		const auto heapProperties = GetHeapProperties(HeapType::Default);
		const auto resourceDesc = D3D12_RESOURCE_DESC1
		{
			.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D,
			.Alignment = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT,
			.Width = width,
			.Height = height,
			.DepthOrArraySize = 1u,
			.MipLevels = 1u,
			.Format = format,
			.SampleDesc = sampleDesc,
			.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN,
			.Flags = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET,
			.SamplerFeedbackMipRegion = D3D12_MIP_REGION{}
		};
		auto clearValue = D3D12_CLEAR_VALUE
		{
			.Format = format
		};
		std::memcpy(clearValue.Color, clearColor.Span().data(), sizeof(PonyMath::Color::RGBA<FLOAT>));

		Microsoft::WRL::ComPtr<ID3D12Resource2> resource;
		if (const HRESULT result = d3d12System->Device().CreateCommittedResource3(&heapProperties, D3D12_HEAP_FLAG_NONE, &resourceDesc, D3D12_BARRIER_LAYOUT_PRESENT,
			&clearValue, nullptr, 0, nullptr, IID_PPV_ARGS(resource.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to create render target resource with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		const auto renderTarget = std::make_shared<Texture>(*resource.Get());
		resources.push_back(renderTarget);

		return renderTarget;
	}

	std::shared_ptr<Texture> ResourceManager::CreateDepthStencil(const UINT64 width, const UINT height, const DXGI_FORMAT format, const DXGI_SAMPLE_DESC sampleDesc, const D3D12_DEPTH_STENCIL_VALUE depthStencilValue)
	{
		const auto heapProperties = GetHeapProperties(HeapType::Default);
		const auto resourceDesc = D3D12_RESOURCE_DESC1
		{
			.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D,
			.Alignment = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT,
			.Width = width,
			.Height = height,
			.DepthOrArraySize = 1u,
			.MipLevels = 1u,
			.Format = format,
			.SampleDesc = sampleDesc,
			.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN,
			.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL,
			.SamplerFeedbackMipRegion = D3D12_MIP_REGION{}
		};
		const auto clearValue = D3D12_CLEAR_VALUE
		{
			.Format = format,
			.DepthStencil = depthStencilValue
		};

		Microsoft::WRL::ComPtr<ID3D12Resource2> resource;
		if (const HRESULT result = d3d12System->Device().CreateCommittedResource3(&heapProperties, D3D12_HEAP_FLAG_NONE, &resourceDesc, D3D12_BARRIER_LAYOUT_DEPTH_STENCIL_READ,
			&clearValue, nullptr, 0, nullptr, IID_PPV_ARGS(resource.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to create depth stencil resource with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		const auto depthStencil = std::make_shared<Texture>(*resource.Get());
		resources.push_back(depthStencil);

		return depthStencil;
	}

	void ResourceManager::Clean() noexcept
	{
		for (std::size_t i = resources.size(); i-- > 0; )
		{
			if (resources[i].use_count() <= 1L)
			{
				resources.erase(resources.cbegin() + i);
			}
		}
	}

	D3D12_HEAP_PROPERTIES ResourceManager::GetHeapProperties(const HeapType heapType) noexcept
	{
		return D3D12_HEAP_PROPERTIES
		{
			.Type = GetHeapType(heapType),
			.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN,
			.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN,
			.CreationNodeMask = 0u,
			.VisibleNodeMask = 0u
		};
	}

	D3D12_HEAP_TYPE ResourceManager::GetHeapType(const HeapType heapType) noexcept
	{
		switch (heapType)
		{
		case HeapType::Default:
			return D3D12_HEAP_TYPE_DEFAULT;
		case HeapType::Upload:
			return D3D12_HEAP_TYPE_UPLOAD;
		case HeapType::Readback:
			return D3D12_HEAP_TYPE_READBACK;
		default: [[unlikely]]
			assert(false && "The resource heapType is incorrect.");
			return D3D12_HEAP_TYPE_UPLOAD;
		}
	}

	std::shared_ptr<Texture> ResourceManager::CreateTexture(const D3D12_RESOURCE_DIMENSION dimension, const UINT64 width, const UINT height, const UINT16 depth, 
		const DXGI_FORMAT format, const DXGI_SAMPLE_DESC sampleDesc, const HeapType placement)
	{
		const auto heapProperties = GetHeapProperties(placement);
		const auto resourceDesc = D3D12_RESOURCE_DESC1
		{
			.Dimension = dimension,
			.Alignment = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT,
			.Width = width,
			.Height = height,
			.DepthOrArraySize = depth,
			.MipLevels = 1u,
			.Format = format,
			.SampleDesc = sampleDesc,
			.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN,
			.Flags = D3D12_RESOURCE_FLAG_NONE,
			.SamplerFeedbackMipRegion = D3D12_MIP_REGION{}
		};

		Microsoft::WRL::ComPtr<ID3D12Resource2> resource;
		if (const HRESULT result = d3d12System->Device().CreateCommittedResource3(&heapProperties, D3D12_HEAP_FLAG_NONE, &resourceDesc, D3D12_BARRIER_LAYOUT_COMMON,
			nullptr, nullptr, 0, nullptr, IID_PPV_ARGS(resource.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to create texture resource with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		return std::make_shared<Texture>(*resource.Get());
	}
}
