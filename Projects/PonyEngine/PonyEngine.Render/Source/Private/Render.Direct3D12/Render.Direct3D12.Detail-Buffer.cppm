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

export module PonyEngine.Render.Direct3D12.Detail:Buffer;

import <cstddef>;
import <stdexcept>;

import PonyBase.Container;
import PonyBase.Utility;

import :Resource;

export namespace PonyEngine::Render::Direct3D12
{
	class Buffer final : public Resource
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit Buffer(ID3D12Resource2& resource) noexcept;
		Buffer(const Buffer&) = delete;
		Buffer(Buffer&&) = delete;

		virtual ~Buffer() noexcept override = default;

		void GetData(void* data, std::size_t size, std::size_t offset = 0) const noexcept;
		void GetData(PonyBase::Container::Buffer& buffer, std::size_t offset = 0) const noexcept;

		void SetData(const void* data, std::size_t size, std::size_t offset = 0) noexcept;
		void SetData(const PonyBase::Container::Buffer& buffer, std::size_t offset = 0) noexcept;

		Buffer& operator =(const Buffer&) = delete;
		Buffer& operator =(Buffer&&) = delete;

	private:
		void CheckParams(const void* data, std::size_t size, std::size_t offset) const;

		[[nodiscard("Redundant call")]]
		void* Map() const;
		void Unmap() const;
	};
}

namespace PonyEngine::Render::Direct3D12
{
	Buffer::Buffer(ID3D12Resource2& resource) noexcept :
		Resource(resource)
	{
		assert(resource.GetDesc1().Dimension == D3D12_RESOURCE_DIMENSION_BUFFER && "The resource has a wrong dimension.");
	}

	void Buffer::GetData(void* const data, const std::size_t size, const std::size_t offset) const noexcept
	{
		CheckParams(data, size, offset);

		const void* const resourceData = Map();
		std::memcpy(data, static_cast<const std::byte*>(resourceData) + offset, size);
		Unmap();
	}

	void Buffer::GetData(PonyBase::Container::Buffer& buffer, const std::size_t offset) const noexcept
	{
		GetData(buffer.Data(), buffer.Size(), offset);
	}

	void Buffer::SetData(const void* const data, const std::size_t size, const std::size_t offset) noexcept
	{
		CheckParams(data, size, offset);

		void* const resourceData = Map();
		std::memcpy(static_cast<std::byte*>(resourceData) + offset, data, size);
		Unmap();
	}

	void Buffer::SetData(const PonyBase::Container::Buffer& buffer, const std::size_t offset) noexcept
	{
		SetData(buffer.Data(), buffer.Size(), offset);
	}

	void Buffer::CheckParams(const void* const data, const std::size_t size, const std::size_t offset) const
	{
		assert(data && "The data is nullptr.");
		if (offset + size > resource->GetDesc1().Width)
		{
			throw std::out_of_range("Out of bounds.");
		}
	}

	void* Buffer::Map() const
	{
		void* resourceData;
		if (const HRESULT result = resource->Map(0, nullptr, &resourceData); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to map buffer with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		return resourceData;
	}

	void Buffer::Unmap() const
	{
		resource->Unmap(0, nullptr);
	}
}
