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

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:Buffer;

import std;

import PonyEngine.Platform.Windows;
import PonyEngine.RenderDevice;

import :Resource;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	/// @brief Buffer wrapper.
	class Buffer final : public IBuffer
	{
	public:
		/// @brief Creates a buffer wrapper.
		/// @param resource Buffer resource.
		/// @param size Buffer size.
		/// @param usage Buffer usage.
		[[nodiscard("Pure constructor")]]
		Buffer(ID3D12Resource2& resource, std::uint64_t size, BufferUsage usage) noexcept;
		/// @brief Creates a buffer wrapper.
		/// @param resource Buffer resource.
		/// @param size Buffer size.
		/// @param usage Buffer usage.
		[[nodiscard("Pure constructor")]]
		Buffer(Platform::Windows::ComPtr<ID3D12Resource2>&& resource, std::uint64_t size, BufferUsage usage) noexcept;
		Buffer(const Buffer&) = delete;
		Buffer(Buffer&&) = delete;

		~Buffer() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual std::uint64_t Size() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual BufferUsage Usage() const noexcept override;

		virtual void* Map() override;
		virtual void* Map(const BufferRange& range) override;
		virtual void Unmap() override;
		virtual void Unmap(const BufferRange& range) override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;
		virtual void Name(std::string_view name) override;

		/// @brief Gets the buffer resource.
		/// @return Buffer resource.
		[[nodiscard("Pure function")]]
		ID3D12Resource2& Resource() const noexcept;

		Buffer& operator =(const Buffer&) = delete;
		Buffer& operator =(Buffer&&) = delete;

	private:
		/// @brief Validates a range.
		/// @param range Range
		void ValidateRange(const BufferRange& range) const;

		class Resource resource; ///< Buffer resource.

		std::uint64_t size; ///< Buffer size.
		BufferUsage usage; ///< Buffer usage.
	};
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	Buffer::Buffer(ID3D12Resource2& resource, const std::uint64_t size, const BufferUsage usage) noexcept :
		resource(resource),
		size{size},
		usage{usage}
	{
	}

	Buffer::Buffer(Platform::Windows::ComPtr<ID3D12Resource2>&& resource, const std::uint64_t size, const BufferUsage usage) noexcept :
		resource(std::move(resource)),
		size{size},
		usage{usage}
	{
	}

	std::uint64_t Buffer::Size() const noexcept
	{
		return size;
	}

	BufferUsage Buffer::Usage() const noexcept
	{
		return usage;
	}

	void* Buffer::Map()
	{
		return resource.Map(0u);
	}

	void* Buffer::Map(const BufferRange& range)
	{
		ValidateRange(range);
		return resource.Map(0u, static_cast<SIZE_T>(range.offset), static_cast<SIZE_T>(range.size));
	}

	void Buffer::Unmap()
	{
		resource.Unmap(0u);
	}

	void Buffer::Unmap(const BufferRange& range)
	{
		ValidateRange(range);
		resource.Unmap(0u, static_cast<SIZE_T>(range.offset), static_cast<SIZE_T>(range.size));
	}

	std::string_view Buffer::Name() const noexcept
	{
		return resource.Name();
	}

	void Buffer::Name(const std::string_view name)
	{
		resource.Name(name);
	}

	ID3D12Resource2& Buffer::Resource() const noexcept
	{
		return resource.GetResource();
	}

	void Buffer::ValidateRange(const BufferRange& range) const
	{
#ifndef NDEBUG
		if (range.offset + range.size > size) [[unlikely]]
		{
			throw std::out_of_range("Out of range");
		}
#endif
	}
}
