/***************************************************
 * MIT License                                     *
 *                                                 *
 * right (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

#include "PonyEngine/RenderDevice/Windows/D3D12Framework.h"

export module PonyEngine.RenderDevice.D3D12.Impl.Windows:D3D12CommandList;

import std;

import PonyEngine.Platform.Windows;
import PonyEngine.RenderDevice;

import :D3D12ObjectUtility;

export namespace PonyEngine::RenderDevice::Windows
{
	class D3D12CommandList final
	{
	public:
		[[nodiscard("Pure constructor")]]
		D3D12CommandList(ID3D12CommandAllocator& allocator, ID3D12GraphicsCommandList10& commandList) noexcept;
		[[nodiscard("Pure constructor")]]
		D3D12CommandList(Platform::Windows::ComPtr<ID3D12CommandAllocator>&& allocator, Platform::Windows::ComPtr<ID3D12GraphicsCommandList10>&& commandList) noexcept;
		D3D12CommandList(const D3D12CommandList&) = delete;
		D3D12CommandList(D3D12CommandList&&) = delete;

		~D3D12CommandList() noexcept = default;

		[[nodiscard("Pure function")]]
		ID3D12GraphicsCommandList10& CommandList() const noexcept;

		void Reset();
		void Close();

		void SetName(std::string_view name);

		D3D12CommandList& operator =(const D3D12CommandList&) = delete;
		D3D12CommandList& operator =(D3D12CommandList&&) = delete;

	private:
		Platform::Windows::ComPtr<ID3D12CommandAllocator> allocator;
		Platform::Windows::ComPtr<ID3D12GraphicsCommandList10> commandList;
	};
}

namespace PonyEngine::RenderDevice::Windows
{
	D3D12CommandList::D3D12CommandList(ID3D12CommandAllocator& allocator, ID3D12GraphicsCommandList10& commandList) noexcept :
		allocator(&allocator),
		commandList(&commandList)
	{
	}

	D3D12CommandList::D3D12CommandList(Platform::Windows::ComPtr<ID3D12CommandAllocator>&& allocator,
		Platform::Windows::ComPtr<ID3D12GraphicsCommandList10>&& commandList) noexcept :
		allocator(std::move(allocator)),
		commandList(std::move(commandList))
	{
		assert(this->allocator && "The allocator is nullptr.");
		assert(this->commandList && "The command list is nullptr.");
	}

	ID3D12GraphicsCommandList10& D3D12CommandList::CommandList() const noexcept
	{
		return *commandList;
	}

	void D3D12CommandList::Reset()
	{
		if (const HRESULT result = allocator->Reset(); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to reset command allocator: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		if (const HRESULT result = commandList->Reset(allocator.Get(), nullptr); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to reset command list: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
	}

	void D3D12CommandList::Close()
	{
		if (const HRESULT result = commandList->Close(); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to close command list: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
	}

	void D3D12CommandList::SetName(const std::string_view name)
	{
		SetObjectName(*allocator, name);
		SetObjectName(*commandList, name);
	}
}
