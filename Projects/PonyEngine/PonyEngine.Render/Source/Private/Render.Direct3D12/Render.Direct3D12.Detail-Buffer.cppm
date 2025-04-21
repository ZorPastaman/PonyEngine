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
import <cstring>;
import <stdexcept>;

import PonyBase.Container;

import :Resource;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 buffer.
	class Buffer final : public Resource
	{
	public:
		/// @brief Creates a buffer.
		/// @param resource Resource. Must have a buffer dimension.
		[[nodiscard("Pure constructor")]]
		explicit Buffer(ID3D12Resource2& resource) noexcept;
		[[nodiscard("Pure constructor")]]
		Buffer(const Buffer& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Buffer(Buffer&& other) noexcept = default;

		virtual ~Buffer() noexcept override = default;

		/// @brief Gets the buffer data.
		/// @note @p size + @p offset mustn't exceed the buffer size.
		/// @note The buffer must be cpu accessible.
		/// @param data Output. Mustn't be nullptr.
		/// @param size Read size.
		/// @param offset Read offset.
		void GetData(void* data, std::size_t size, std::size_t offset = 0) const;
		/// @brief Gets the buffer data.
		/// @note @p size + @p offset mustn't exceed the buffer size.
		/// @note The buffer must be cpu accessible.
		/// @param buffer Output.
		/// @param offset Read offset.
		void GetData(PonyBase::Container::Buffer& buffer, std::size_t offset = 0) const;

		/// @brief Sets the buffer data.
		/// @note @p size + @p offset mustn't exceed the buffer size.
		/// @note The buffer must be cpu accessible.
		/// @param data Input. Mustn't be nullptr.
		/// @param size Write size.
		/// @param offset Write offset.
		void SetData(const void* data, std::size_t size, std::size_t offset = 0);
		/// @brief Sets the buffer data.
		/// @note @p size + @p offset mustn't exceed the buffer size.
		/// @note The buffer must be cpu accessible.
		/// @param buffer Input.
		/// @param offset Write offset.
		void SetData(const PonyBase::Container::Buffer& buffer, std::size_t offset = 0);

		Buffer& operator =(const Buffer& other) noexcept = default;
		Buffer& operator =(Buffer&& other) noexcept = default;

	private:
		/// @brief Checks if the parameters are correct.
		/// @param data Input/Output.
		/// @param size Read/Write size.
		/// @param offset Read/Write offset.
		void CheckParams(const void* data, std::size_t size, std::size_t offset) const;
	};
}

namespace PonyEngine::Render::Direct3D12
{
	Buffer::Buffer(ID3D12Resource2& resource) noexcept :
		Resource(resource)
	{
		assert(resource.GetDesc1().Dimension == D3D12_RESOURCE_DIMENSION_BUFFER && "The resource has a wrong dimension.");
	}

	void Buffer::GetData(void* const data, const std::size_t size, const std::size_t offset) const
	{
		CheckParams(data, size, offset);

		const void* const resourceData = Map();
		std::memcpy(data, static_cast<const std::byte*>(resourceData) + offset, size);
		Unmap();
	}

	void Buffer::GetData(PonyBase::Container::Buffer& buffer, const std::size_t offset) const
	{
		GetData(buffer.Data(), buffer.Size(), offset);
	}

	void Buffer::SetData(const void* const data, const std::size_t size, const std::size_t offset)
	{
		CheckParams(data, size, offset);

		void* const resourceData = Map();
		std::memcpy(static_cast<std::byte*>(resourceData) + offset, data, size);
		Unmap();
	}

	void Buffer::SetData(const PonyBase::Container::Buffer& buffer, const std::size_t offset)
	{
		SetData(buffer.Data(), buffer.Size(), offset);
	}

	void Buffer::CheckParams(const void* const data, const std::size_t size, const std::size_t offset) const
	{
		if (!data) [[unlikely]]
		{
			throw std::invalid_argument("Data is nullptr.");
		}

		if (offset + size > resource->GetDesc1().Width) [[unlikely]]
		{
			throw std::out_of_range("Out of bounds.");
		}
	}
}
