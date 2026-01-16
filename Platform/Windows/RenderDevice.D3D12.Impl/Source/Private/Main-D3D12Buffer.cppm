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

export module PonyEngine.RenderDevice.D3D12.Impl.Windows:D3D12Buffer;

import std;

import PonyEngine.Platform.Windows;
import PonyEngine.RenderDevice;

import :D3D12Utility;

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

		virtual void SetName(std::string_view name) override;

		[[nodiscard("Pure function")]]
		ID3D12Resource2& Resource() noexcept;
		[[nodiscard("Pure function")]]
		const ID3D12Resource2& Resource() const noexcept;

		D3D12Buffer& operator =(const D3D12Buffer&) = delete;
		D3D12Buffer& operator =(D3D12Buffer&&) = delete;

	private:
		Platform::Windows::ComPtr<ID3D12Resource2> resource;

		std::uint64_t size;
		BufferUsage usage;
	};
}

namespace PonyEngine::RenderDevice::Windows
{
	D3D12Buffer::D3D12Buffer(ID3D12Resource2& resource, const std::uint64_t size, const BufferUsage usage) noexcept :
		resource(&resource),
		size{size},
		usage{usage}
	{
	}

	D3D12Buffer::D3D12Buffer(Platform::Windows::ComPtr<ID3D12Resource2>&& resource, const std::uint64_t size, const BufferUsage usage) noexcept :
		resource(std::move(resource)),
		size{size},
		usage{usage}
	{
		assert(this->resource && "The buffer resource is nullptr.");
	}

	std::uint64_t D3D12Buffer::Size() const noexcept
	{
		return size;
	}

	BufferUsage D3D12Buffer::Usage() const noexcept
	{
		return usage;
	}

	void D3D12Buffer::SetName(const std::string_view name)
	{
		SetObjectName(*resource, name);
	}

	ID3D12Resource2& D3D12Buffer::Resource() noexcept
	{
		return *resource;
	}

	const ID3D12Resource2& D3D12Buffer::Resource() const noexcept
	{
		return *resource;
	}
}
