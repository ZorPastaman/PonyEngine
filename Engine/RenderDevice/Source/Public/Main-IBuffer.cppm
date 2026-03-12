/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Object/Body.h"

export module PonyEngine.RenderDevice:IBuffer;

import std;

import :BufferRange;
import :BufferUsage;
import :IResource;

export namespace PonyEngine::RenderDevice
{
	/// @brief Buffer.
	class IBuffer : public IResource
	{
		PONY_INTERFACE_BODY(IBuffer)

		/// @brief Gets the buffer size.
		/// @return Buffer size.
		[[nodiscard("Pure function")]]
		virtual std::uint64_t Size() const noexcept = 0;
		/// @brief Gets the buffer usage.
		/// @return Buffer usage.
		[[nodiscard("Pure function")]]
		virtual BufferUsage Usage() const noexcept = 0;

		/// @brief Maps the whole buffer.
		/// @return Buffer data.
		virtual void* Map() = 0;
		/// @brief Maps the buffer range.
		/// @param offset Buffer data offset in bytes.
		/// @param size Buffer data size in bytes.
		/// @return Buffer data.
		void* Map(std::uint64_t offset, std::uint64_t size);
		/// @brief Maps the buffer range.
		/// @param range Buffer range.
		/// @return Buffer data.
		virtual void* Map(const BufferRange& range) = 0;
		/// @brief Unmaps the whole buffer.
		virtual void Unmap() = 0;
		/// @brief Unmaps the buffer range.
		/// @param offset Buffer data offset in bytes.
		/// @param size Buffer data size in bytes.
		void Unmap(std::uint64_t offset, std::uint64_t size);
		/// @brief Unmaps the buffer range.
		/// @param range Buffer range.
		virtual void Unmap(const BufferRange& range) = 0;
	};
}

namespace PonyEngine::RenderDevice
{
	void* IBuffer::Map(const std::uint64_t offset, const std::uint64_t size)
	{
		return Map(BufferRange{.offset = offset, .size = size});
	}

	void IBuffer::Unmap(const std::uint64_t offset, const std::uint64_t size)
	{
		Unmap(BufferRange{.offset = offset, .size = size});
	}
}
