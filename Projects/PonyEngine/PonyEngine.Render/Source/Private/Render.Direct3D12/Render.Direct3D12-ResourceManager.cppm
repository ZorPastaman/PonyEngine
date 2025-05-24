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

#include "PonyDebug/Log/Log.h"

export module PonyEngine.Render.Direct3D12:ResourceManager;

import <algorithm>;
import <cstddef>;
import <cstdint>;
import <memory>;
import <stdexcept>;
import <type_traits>;
import <unordered_map>;
import <utility>;
import <vector>;

import :HeapType;
import :IResourceManager;
import :IRenderSystemContext;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 resource manager.
	class ResourceManager final : public IResourceManager
	{
	public:
		/// @brief Creates a @p ResourceManager.
		/// @param d3d12System Direct3D12 system context.
		[[nodiscard("Pure constructor")]]
		explicit ResourceManager(IRenderSystemContext& d3d12System) noexcept;
		[[nodiscard("Pure constructor")]]
		ResourceManager(const ResourceManager&) = delete;
		[[nodiscard("Pure constructor")]]
		ResourceManager(ResourceManager&&) = delete;

		~ResourceManager() noexcept = default;

		[[nodiscard("Redendant call")]]
		virtual std::shared_ptr<Buffer> CreateBuffer(std::uint64_t size, HeapType heapType) override;

		[[nodiscard("Redendant call")]]
		virtual std::shared_ptr<Texture> CreateTexture1D(std::uint64_t width, DXGI_FORMAT format, DXGI_SAMPLE_DESC sampleDesc, HeapType heapType) override;
		[[nodiscard("Redendant call")]]
		virtual std::shared_ptr<Texture> CreateTexture2D(std::uint64_t width, std::uint32_t height, DXGI_FORMAT format, DXGI_SAMPLE_DESC sampleDesc, HeapType heapType) override;
		[[nodiscard("Redendant call")]]
		virtual std::shared_ptr<Texture> CreateTexture3D(std::uint64_t width, std::uint32_t height, std::uint16_t depth, DXGI_FORMAT format, DXGI_SAMPLE_DESC sampleDesc, HeapType heapType) override;

		[[nodiscard("Redendant call")]]
		virtual std::pair<std::shared_ptr<Buffer>, D3D12_PLACED_SUBRESOURCE_FOOTPRINT> CreateTextureBuffer1D(std::uint64_t width, 
			DXGI_FORMAT format, DXGI_SAMPLE_DESC sampleDesc, HeapType heapType) override;
		[[nodiscard("Redendant call")]]
		virtual std::pair<std::shared_ptr<Buffer>, D3D12_PLACED_SUBRESOURCE_FOOTPRINT> CreateTextureBuffer2D(std::uint64_t width, std::uint32_t height, 
			DXGI_FORMAT format, DXGI_SAMPLE_DESC sampleDesc, HeapType heapType) override;
		[[nodiscard("Redendant call")]]
		virtual std::pair<std::shared_ptr<Buffer>, D3D12_PLACED_SUBRESOURCE_FOOTPRINT> CreateTextureBuffer3D(std::uint64_t width, std::uint32_t height, std::uint16_t depth, 
			DXGI_FORMAT format, DXGI_SAMPLE_DESC sampleDesc, HeapType heapType) override;

		[[nodiscard("Redendant call")]]
		virtual std::shared_ptr<Texture> CreateRenderTarget(std::uint64_t width, std::uint32_t height, DXGI_FORMAT format, DXGI_SAMPLE_DESC sampleDesc, const PonyMath::Color::RGBA<float>& clearColor) override;
		[[nodiscard("Redendant call")]]
		virtual std::shared_ptr<Texture> CreateDepthStencil(std::uint64_t width, std::uint32_t height, DXGI_FORMAT format, DXGI_SAMPLE_DESC sampleDesc, D3D12_DEPTH_STENCIL_VALUE depthStencilValue) override;

		/// @brief Cleans out of dead resources.
		void Clean() noexcept;

		ResourceManager& operator =(const ResourceManager&) = delete;
		ResourceManager& operator =(ResourceManager&&) = delete;

	private:
		/// @brief Gets a Direct3D12 heap properties.
		/// @param heapType Heap type.
		/// @return Direct3D12 heap properties.
		[[nodiscard("Pure function")]]
		static D3D12_HEAP_PROPERTIES GetHeapProperties(HeapType heapType) noexcept;
		/// @brief Gets a Direct3D12 heap type.
		/// @param heapType Heap type.
		/// @return Direct3D12 heap type.
		[[nodiscard("Pure function")]]
		static D3D12_HEAP_TYPE GetHeapType(HeapType heapType) noexcept;

		/// @brief Gets a buffer resource description.
		/// @param size Buffer size.
		/// @return Buffer resource description.
		[[nodiscard("Pure function")]]
		static D3D12_RESOURCE_DESC1 GetBufferResourceDescription(std::uint64_t size) noexcept;
		/// @brief Gets a texture resource description.
		/// @param dimension Dimension.
		/// @param width Width.
		/// @param height Height.
		/// @param depth Depth.
		/// @param format Pixel format.
		/// @param sampleDesc Sample description.
		/// @param renderTarget Is it a render target?
		/// @param depthStencil Is it a depth stencil?
		/// @return Texture resource description.
		[[nodiscard("Pure function")]]
		static D3D12_RESOURCE_DESC1 GetTextureResourceDescription(D3D12_RESOURCE_DIMENSION dimension, std::uint64_t width, std::uint32_t height, std::uint16_t depth, 
			DXGI_FORMAT format, DXGI_SAMPLE_DESC sampleDesc, bool renderTarget, bool depthStencil) noexcept;

		/// @brief Creates a texture.
		/// @param resourceDesc Texture resource description.
		/// @param heapType Heap type.
		/// @param layout Initial barrier layout.
		/// @param clearValue Clear value.
		/// @return Texture.
		[[nodiscard("Redendant call")]]
		std::shared_ptr<Texture> CreateTexture(const D3D12_RESOURCE_DESC1& resourceDesc, HeapType heapType, D3D12_BARRIER_LAYOUT layout, const D3D12_CLEAR_VALUE* clearValue);
		/// @brief Creates a texture buffer for copying.
		/// @param resourceDesc Texture resource description.
		/// @param heapType Heap type.
		/// @return Texture buffer and its footprint.
		[[nodiscard("Redendant call")]]
		std::pair<std::shared_ptr<Buffer>, D3D12_PLACED_SUBRESOURCE_FOOTPRINT> CreateTextureBuffer(const D3D12_RESOURCE_DESC1& resourceDesc, HeapType heapType);

		IRenderSystemContext* d3d12System; ///< Direct3D12 system context.

		std::vector<std::shared_ptr<Resource>> resources; ///< Resources
	};
}

namespace PonyEngine::Render::Direct3D12
{
	/// @brief Map of a heap type to a Direct3D12 heap type.
	const std::unordered_map<HeapType, D3D12_HEAP_TYPE> HeapTypes
	{
		{ HeapType::Default, D3D12_HEAP_TYPE_DEFAULT },
		{ HeapType::Upload, D3D12_HEAP_TYPE_UPLOAD },
		{ HeapType::Readback, D3D12_HEAP_TYPE_READBACK }
	};

	ResourceManager::ResourceManager(IRenderSystemContext& d3d12System) noexcept :
		d3d12System{&d3d12System}
	{
	}

	std::shared_ptr<Buffer> ResourceManager::CreateBuffer(const std::uint64_t size, const HeapType heapType)
	{
		const D3D12_HEAP_PROPERTIES heapProperties = GetHeapProperties(heapType);
		const D3D12_RESOURCE_DESC1 resourceDesc = GetBufferResourceDescription(size);
		Microsoft::WRL::ComPtr<ID3D12Resource2> resource;
		if (const HRESULT result = d3d12System->Device().CreateCommittedResource3(&heapProperties, D3D12_HEAP_FLAG_NONE, &resourceDesc, D3D12_BARRIER_LAYOUT_UNDEFINED,
			nullptr, nullptr, 0, nullptr, IID_PPV_ARGS(resource.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to create buffer resource with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		const auto buffer = std::make_shared<Buffer>(*resource.Get());
		resources.push_back(buffer);
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Buffer created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(buffer.get()));

		return buffer;
	}

	std::shared_ptr<Texture> ResourceManager::CreateTexture1D(const std::uint64_t width, const DXGI_FORMAT format, const DXGI_SAMPLE_DESC sampleDesc, const HeapType heapType)
	{
		const D3D12_RESOURCE_DESC1 description = GetTextureResourceDescription(D3D12_RESOURCE_DIMENSION_TEXTURE1D, width, 1u, 1u, format, sampleDesc, false, false);

		return  CreateTexture(description, heapType, D3D12_BARRIER_LAYOUT_COMMON, nullptr);
	}

	std::shared_ptr<Texture> ResourceManager::CreateTexture2D(const std::uint64_t width, const std::uint32_t height, const DXGI_FORMAT format, const DXGI_SAMPLE_DESC sampleDesc, const HeapType heapType)
	{
		const D3D12_RESOURCE_DESC1 description = GetTextureResourceDescription(D3D12_RESOURCE_DIMENSION_TEXTURE2D, width, height, 1u, format, sampleDesc, false, false);

		return CreateTexture(description, heapType, D3D12_BARRIER_LAYOUT_COMMON, nullptr);
	}

	std::shared_ptr<Texture> ResourceManager::CreateTexture3D(const std::uint64_t width, const std::uint32_t height, const std::uint16_t depth, const DXGI_FORMAT format, const DXGI_SAMPLE_DESC sampleDesc, const HeapType heapType)
	{
		const D3D12_RESOURCE_DESC1 description = GetTextureResourceDescription(D3D12_RESOURCE_DIMENSION_TEXTURE3D, width, height, depth, format, sampleDesc, false, false);

		return CreateTexture(description, heapType, D3D12_BARRIER_LAYOUT_COMMON, nullptr);
	}

	std::pair<std::shared_ptr<Buffer>, D3D12_PLACED_SUBRESOURCE_FOOTPRINT> ResourceManager::CreateTextureBuffer1D(const std::uint64_t width, 
		const DXGI_FORMAT format, const DXGI_SAMPLE_DESC sampleDesc, const HeapType heapType)
	{
		const D3D12_RESOURCE_DESC1 description = GetTextureResourceDescription(D3D12_RESOURCE_DIMENSION_TEXTURE1D, width, 1u, 1u, format, sampleDesc, false, false);

		return CreateTextureBuffer(description, heapType);
	}

	std::pair<std::shared_ptr<Buffer>, D3D12_PLACED_SUBRESOURCE_FOOTPRINT> ResourceManager::CreateTextureBuffer2D(const std::uint64_t width, const std::uint32_t height,
		const DXGI_FORMAT format, const DXGI_SAMPLE_DESC sampleDesc, const HeapType heapType)
	{
		const D3D12_RESOURCE_DESC1 description = GetTextureResourceDescription(D3D12_RESOURCE_DIMENSION_TEXTURE2D, width, height, 1u, format, sampleDesc, false, false);

		return CreateTextureBuffer(description, heapType);
	}

	std::pair<std::shared_ptr<Buffer>, D3D12_PLACED_SUBRESOURCE_FOOTPRINT> ResourceManager::CreateTextureBuffer3D(const std::uint64_t width, const std::uint32_t height, const std::uint16_t depth, 
		const DXGI_FORMAT format, const DXGI_SAMPLE_DESC sampleDesc, const HeapType heapType)
	{
		const D3D12_RESOURCE_DESC1 description = GetTextureResourceDescription(D3D12_RESOURCE_DIMENSION_TEXTURE3D, width, height, depth, format, sampleDesc, false, false);

		return CreateTextureBuffer(description, heapType);
	}

	std::shared_ptr<Texture> ResourceManager::CreateRenderTarget(const std::uint64_t width, const std::uint32_t height, const DXGI_FORMAT format, const DXGI_SAMPLE_DESC sampleDesc, const PonyMath::Color::RGBA<float>& clearColor)
	{
		const D3D12_RESOURCE_DESC1 description = GetTextureResourceDescription(D3D12_RESOURCE_DIMENSION_TEXTURE2D, width, height, 1u, format, sampleDesc, true, false);
		const auto clearValue = D3D12_CLEAR_VALUE
		{
			.Format = format,
			.Color = { clearColor.R(), clearColor.G(), clearColor.B(), clearColor.A() }
		};

		return CreateTexture(description, HeapType::Default, D3D12_BARRIER_LAYOUT_PRESENT, &clearValue);
	}

	std::shared_ptr<Texture> ResourceManager::CreateDepthStencil(const std::uint64_t width, const std::uint32_t height, const DXGI_FORMAT format, const DXGI_SAMPLE_DESC sampleDesc, const D3D12_DEPTH_STENCIL_VALUE depthStencilValue)
	{
		const D3D12_RESOURCE_DESC1 description = GetTextureResourceDescription(D3D12_RESOURCE_DIMENSION_TEXTURE2D, width, height, 1u, format, sampleDesc, false, true);
		const auto clearValue = D3D12_CLEAR_VALUE
		{
			.Format = format,
			.DepthStencil = depthStencilValue
		};

		return CreateTexture(description, HeapType::Default, D3D12_BARRIER_LAYOUT_DEPTH_STENCIL_READ, &clearValue);
	}

	void ResourceManager::Clean() noexcept
	{
		for (std::size_t i = resources.size(); i-- > 0; )
		{
			if (const std::shared_ptr<Resource>& resource = resources[i]; resource.use_count() <= 1L)
			{
				PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Destroy resource at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(resource.get()));
				resources.erase(resources.cbegin() + i);
				PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Resource destroyed.");
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
		if (const auto position = HeapTypes.find(heapType); position != HeapTypes.cend()) [[likely]]
		{
			return position->second;
		}

		assert(false && "The resource heapType is incorrect.");
		return D3D12_HEAP_TYPE_UPLOAD;
	}

	D3D12_RESOURCE_DESC1 ResourceManager::GetBufferResourceDescription(const std::uint64_t size) noexcept
	{
		return D3D12_RESOURCE_DESC1
		{
			.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER,
			.Alignment = 0ULL,
			.Width = static_cast<UINT64>(size),
			.Height = 1u,
			.DepthOrArraySize = 1u,
			.MipLevels = 1u,
			.Format = DXGI_FORMAT_UNKNOWN,
			.SampleDesc = DXGI_SAMPLE_DESC{.Count = 1u, .Quality = 0u},
			.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR,
			.Flags = D3D12_RESOURCE_FLAG_NONE,
			.SamplerFeedbackMipRegion = D3D12_MIP_REGION{}
		};
	}

	D3D12_RESOURCE_DESC1 ResourceManager::GetTextureResourceDescription(const D3D12_RESOURCE_DIMENSION dimension,
		const std::uint64_t width, const std::uint32_t height, const std::uint16_t depth, const DXGI_FORMAT format, const DXGI_SAMPLE_DESC sampleDesc,
		const bool renderTarget, const bool depthStencil) noexcept
	{
		D3D12_RESOURCE_FLAGS flags = D3D12_RESOURCE_FLAG_NONE;
		if (renderTarget)
		{
			flags |= D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;
		}
		if (depthStencil)
		{
			flags |= D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
		}

		return D3D12_RESOURCE_DESC1
		{
			.Dimension = dimension,
			.Alignment = 0ULL,
			.Width = static_cast<UINT64>(width),
			.Height = static_cast<UINT>(height),
			.DepthOrArraySize = static_cast<UINT16>(depth),
			.MipLevels = 1u,
			.Format = format,
			.SampleDesc = sampleDesc,
			.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN,
			.Flags = flags,
			.SamplerFeedbackMipRegion = D3D12_MIP_REGION{}
		};
	}

	std::shared_ptr<Texture> ResourceManager::CreateTexture(const D3D12_RESOURCE_DESC1& resourceDesc, const HeapType heapType, 
		const D3D12_BARRIER_LAYOUT layout, const D3D12_CLEAR_VALUE* const clearValue)
	{
		const auto heapProperties = GetHeapProperties(heapType);
		Microsoft::WRL::ComPtr<ID3D12Resource2> resource;
		if (const HRESULT result = d3d12System->Device().CreateCommittedResource3(&heapProperties, D3D12_HEAP_FLAG_NONE, &resourceDesc, layout,
			clearValue, nullptr, 0, nullptr, IID_PPV_ARGS(resource.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to create texture resource with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		const auto texture = std::make_shared<Texture>(*resource.Get());
		resources.push_back(texture);
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Texture created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(texture.get()));

		return texture;
	}

	std::pair<std::shared_ptr<Buffer>, D3D12_PLACED_SUBRESOURCE_FOOTPRINT> ResourceManager::CreateTextureBuffer(const D3D12_RESOURCE_DESC1& resourceDesc, const HeapType heapType)
	{
		D3D12_PLACED_SUBRESOURCE_FOOTPRINT footprint;
		UINT64 bufferSize = 0;
		d3d12System->Device().GetCopyableFootprints1(&resourceDesc, 0u, 1u, 0u, &footprint, nullptr, nullptr, &bufferSize);
		const std::shared_ptr<Buffer> buffer = CreateBuffer(bufferSize, heapType);

		return std::pair(buffer, footprint);
	}
}
