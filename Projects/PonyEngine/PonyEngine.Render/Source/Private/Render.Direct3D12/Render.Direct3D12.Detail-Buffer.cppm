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

export namespace PonyEngine::Render::Direct3D12
{
	class Buffer final
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit Buffer(ID3D12Resource2& resource) noexcept;
		[[nodiscard("Pure constructor")]]
		Buffer(const Buffer& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Buffer(Buffer&& other) noexcept = default;

		~Buffer() noexcept = default;

		[[nodiscard("Pure function")]]
		ID3D12Resource2& Resource() noexcept;
		[[nodiscard("Pure function")]]
		const ID3D12Resource2& Resource() const noexcept;

		void GetData(void* data, std::size_t offset, std::size_t size) const noexcept;
		void GetData(PonyBase::Container::Buffer& buffer, std::size_t offset = 0) const noexcept;

		void SetData(const void* data, std::size_t offset, std::size_t size) noexcept;
		void SetData(const PonyBase::Container::Buffer& buffer, std::size_t offset = 0) noexcept;

		Buffer& operator =(const Buffer& other) noexcept = default;
		Buffer& operator =(Buffer&& other) noexcept = default;

	private:
		void CheckParams(const void* data, std::size_t offset, std::size_t size) const;
		[[nodiscard("Redundant call")]]
		void* Map() const;
		void Unmap() const;

		Microsoft::WRL::ComPtr<ID3D12Resource2> resource;
	};
}

namespace PonyEngine::Render::Direct3D12
{
	Buffer::Buffer(ID3D12Resource2& resource) noexcept :
		resource(&resource)
	{
	}

	ID3D12Resource2& Buffer::Resource() noexcept
	{
		return *resource.Get();
	}

	const ID3D12Resource2& Buffer::Resource() const noexcept
	{
		return *resource.Get();
	}

	void Buffer::GetData(void* const data, const std::size_t offset, const std::size_t size) const noexcept
	{
		CheckParams(data, offset, size);

		const void* const resourceData = Map();
		std::memcpy(data, static_cast<const std::byte*>(resourceData) + offset, size);
		Unmap();
	}

	void Buffer::GetData(PonyBase::Container::Buffer& buffer, const std::size_t offset) const noexcept
	{
		GetData(buffer.Data(), offset, buffer.Size());
	}

	void Buffer::SetData(const void* const data, const std::size_t offset, const std::size_t size) noexcept
	{
		CheckParams(data, offset, size);

		void* const resourceData = Map();
		std::memcpy(static_cast<std::byte*>(resourceData) + offset, data, size);
		Unmap();
	}

	void Buffer::SetData(const PonyBase::Container::Buffer& buffer, const std::size_t offset) noexcept
	{
		SetData(buffer.Data(), offset, buffer.Size());
	}

	void Buffer::CheckParams(const void* const data, const std::size_t offset, const std::size_t size) const
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
