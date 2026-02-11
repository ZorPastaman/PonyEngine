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

#include "PonyEngine/RenderDevice/Windows/D3D12Framework.h"

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:Resource;

import std;

import PonyEngine.Platform.Windows;

import :ObjectUtility;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	class Resource final
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit Resource(ID3D12Resource2& resource) noexcept;
		[[nodiscard("Pure constructor")]]
		explicit Resource(Platform::Windows::ComPtr<ID3D12Resource2>&& resource) noexcept;
		Resource(const Resource&) = delete;
		Resource(Resource&&) = delete;

		~Resource() noexcept = default;

		[[nodiscard("Pure function")]]
		ID3D12Resource2& GetResource() const noexcept;

		void* Map(UINT subresourceIndex);
		void* Map(UINT subresourceIndex, SIZE_T offset, SIZE_T length);
		void* Map(UINT subresourceIndex, const D3D12_RANGE* range);
		void Unmap(UINT subresourceIndex) noexcept;
		void Unmap(UINT subresourceIndex, SIZE_T offset, SIZE_T length) noexcept;
		void Unmap(UINT subresourceIndex, const D3D12_RANGE* range) noexcept;

		std::string_view Name() const noexcept;
		void Name(std::string_view name);

		Resource& operator =(const Resource&) = delete;
		Resource& operator =(Resource&&) = delete;

	private:
		Platform::Windows::ComPtr<ID3D12Resource2> resource;

		std::string name;
	};
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	Resource::Resource(ID3D12Resource2& resource) noexcept :
		resource(&resource)
	{
	}

	Resource::Resource(Platform::Windows::ComPtr<ID3D12Resource2>&& resource) noexcept :
		resource(std::move(resource))
	{
		assert(this->resource && "The buffer resource is nullptr.");
	}

	ID3D12Resource2& Resource::GetResource() const noexcept
	{
		return *resource;
	}

	void* Resource::Map(const UINT subresourceIndex)
	{
		return Map(subresourceIndex, nullptr);
	}

	void* Resource::Map(const UINT subresourceIndex, const SIZE_T offset, const SIZE_T length)
	{
		const auto range = D3D12_RANGE{.Begin = offset, .End = offset + length};
		return Map(subresourceIndex, &range);
	}

	void* Resource::Map(const UINT subresourceIndex, const D3D12_RANGE* const range)
	{
		void* mapped;
		if (const HRESULT result = resource->Map(subresourceIndex, range, &mapped); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to map resource: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		return mapped;
	}

	void Resource::Unmap(const UINT subresourceIndex) noexcept
	{
		Unmap(subresourceIndex, nullptr);
	}

	void Resource::Unmap(const UINT subresourceIndex, const SIZE_T offset, const SIZE_T length) noexcept
	{
		const auto range = D3D12_RANGE{.Begin = offset, .End = offset + length};
		Unmap(subresourceIndex, &range);
	}

	void Resource::Unmap(const UINT subresourceIndex, const D3D12_RANGE* const range) noexcept
	{
		resource->Unmap(subresourceIndex, range);
	}

	std::string_view Resource::Name() const noexcept
	{
		return name;
	}

	void Resource::Name(const std::string_view name)
	{
		SetObjectName(*resource, name);

		try
		{
			this->name = name;
		}
		catch (...)
		{
			SetObjectName(*resource, this->name);
			throw;
		}
	}
}
