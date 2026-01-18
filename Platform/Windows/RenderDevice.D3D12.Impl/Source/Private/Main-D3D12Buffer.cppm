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

export module PonyEngine.RenderDevice.D3D12.Impl.Windows:D3D12Buffer;

import std;

import PonyEngine.Platform.Windows;
import PonyEngine.RenderDevice;

import :D3D12Resource;

export namespace PonyEngine::RenderDevice::Windows
{
	class D3D12Buffer final : public IBuffer
	{
	public:
		[[nodiscard("Pure constructor")]]
		D3D12Buffer(ID3D12Resource2& resource, std::uint64_t size, BufferUsage usage) noexcept;
		[[nodiscard("Pure constructor")]]
		D3D12Buffer(Platform::Windows::ComPtr<ID3D12Resource2>&& resource, std::uint64_t size, BufferUsage usage) noexcept;
		D3D12Buffer(const D3D12Buffer&) = delete;
		D3D12Buffer(D3D12Buffer&&) = delete;

		~D3D12Buffer() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual std::uint64_t Size() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual BufferUsage Usage() const noexcept override;

		virtual void* Map() override;
		virtual void* Map(std::uint64_t offset, std::uint64_t length) override;
		virtual void Unmap() override;
		virtual void Unmap(std::uint64_t offset, std::uint64_t length) override;

		virtual void SetName(std::string_view name) override;

		[[nodiscard("Pure function")]]
		ID3D12Resource2& Resource() noexcept;
		[[nodiscard("Pure function")]]
		const ID3D12Resource2& Resource() const noexcept;

		D3D12Buffer& operator =(const D3D12Buffer&) = delete;
		D3D12Buffer& operator =(D3D12Buffer&&) = delete;

	private:
		D3D12Resource resource;

		std::uint64_t size;
		BufferUsage usage;
	};
}

namespace PonyEngine::RenderDevice::Windows
{
	D3D12Buffer::D3D12Buffer(ID3D12Resource2& resource, const std::uint64_t size, const BufferUsage usage) noexcept :
		resource(resource),
		size{size},
		usage{usage}
	{
	}

	D3D12Buffer::D3D12Buffer(Platform::Windows::ComPtr<ID3D12Resource2>&& resource, const std::uint64_t size, const BufferUsage usage) noexcept :
		resource(std::move(resource)),
		size{size},
		usage{usage}
	{
	}

	std::uint64_t D3D12Buffer::Size() const noexcept
	{
		return size;
	}

	BufferUsage D3D12Buffer::Usage() const noexcept
	{
		return usage;
	}

	void* D3D12Buffer::Map()
	{
		return resource.Map(0u);
	}

	void* D3D12Buffer::Map(const std::uint64_t offset, const std::uint64_t length)
	{
		return resource.Map(0u, static_cast<SIZE_T>(offset), static_cast<SIZE_T>(length));
	}

	void D3D12Buffer::Unmap()
	{
		resource.Unmap(0u);
	}

	void D3D12Buffer::Unmap(const std::uint64_t offset, const std::uint64_t length)
	{
		resource.Unmap(0u, static_cast<SIZE_T>(offset), static_cast<SIZE_T>(length));
	}

	void D3D12Buffer::SetName(const std::string_view name)
	{
		resource.SetName(name);
	}

	ID3D12Resource2& D3D12Buffer::Resource() noexcept
	{
		return resource.Resource();
	}

	const ID3D12Resource2& D3D12Buffer::Resource() const noexcept
	{
		return resource.Resource();
	}
}
