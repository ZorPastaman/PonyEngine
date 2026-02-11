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
	class Buffer final : public IBuffer
	{
	public:
		[[nodiscard("Pure constructor")]]
		Buffer(ID3D12Resource2& resource, std::uint64_t size, BufferUsage usage) noexcept;
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
		virtual void* Map(std::uint64_t offset, std::uint64_t length) override;
		virtual void Unmap() override;
		virtual void Unmap(std::uint64_t offset, std::uint64_t length) override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;
		virtual void Name(std::string_view name) override;

		[[nodiscard("Pure function")]]
		ID3D12Resource2& Resource() const noexcept;

		Buffer& operator =(const Buffer&) = delete;
		Buffer& operator =(Buffer&&) = delete;

	private:
		void ValidateRange(std::uint64_t offset, std::uint64_t length) const;

		class Resource resource;

		std::uint64_t size;
		BufferUsage usage;
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

	void* Buffer::Map(const std::uint64_t offset, const std::uint64_t length)
	{
		ValidateRange(offset, length);

		return resource.Map(0u, static_cast<SIZE_T>(offset), static_cast<SIZE_T>(length));
	}

	void Buffer::Unmap()
	{
		resource.Unmap(0u);
	}

	void Buffer::Unmap(const std::uint64_t offset, const std::uint64_t length)
	{
		ValidateRange(offset, length);

		resource.Unmap(0u, static_cast<SIZE_T>(offset), static_cast<SIZE_T>(length));
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

	void Buffer::ValidateRange(const std::uint64_t offset, const std::uint64_t length) const
	{
#ifndef NDEBUG
		if (offset + length > size) [[unlikely]]
		{
			throw std::out_of_range("Out of range");
		}
#endif
	}
}
