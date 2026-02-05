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

export module PonyEngine.RenderDevice.D3D12.Impl.Windows:D3D12CopyCommandList;

import std;

import PonyEngine.Platform.Windows;
import PonyEngine.RenderDevice;

import :D3D12CommandList;

export namespace PonyEngine::RenderDevice::Windows
{
	class D3D12CopyCommandList final : public ICopyCommandList
	{
	public:
		[[nodiscard("Pure constructor")]]
		D3D12CopyCommandList(ID3D12CommandAllocator& allocator, ID3D12GraphicsCommandList10& commandList) noexcept;
		[[nodiscard("Pure constructor")]]
		D3D12CopyCommandList(Platform::Windows::ComPtr<ID3D12CommandAllocator>&& allocator, Platform::Windows::ComPtr<ID3D12GraphicsCommandList10>&& commandList) noexcept;
		D3D12CopyCommandList(const D3D12CopyCommandList&) = delete;
		D3D12CopyCommandList(D3D12CopyCommandList&&) = delete;

		~D3D12CopyCommandList() noexcept = default;

		virtual void Reset() override;
		virtual void Close() override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;
		virtual void Name(std::string_view name) override;

		[[nodiscard("Pure function")]]
		ID3D12GraphicsCommandList10& CommandList() const noexcept;

		D3D12CopyCommandList& operator =(const D3D12CopyCommandList&) = delete;
		D3D12CopyCommandList& operator =(D3D12CopyCommandList&&) = delete;

	private:
		D3D12CommandList commandList;
	};
}

namespace PonyEngine::RenderDevice::Windows
{
	D3D12CopyCommandList::D3D12CopyCommandList(ID3D12CommandAllocator& allocator, ID3D12GraphicsCommandList10& commandList) noexcept :
		commandList(allocator, commandList)
	{
	}

	D3D12CopyCommandList::D3D12CopyCommandList(Platform::Windows::ComPtr<ID3D12CommandAllocator>&& allocator,
		Platform::Windows::ComPtr<ID3D12GraphicsCommandList10>&& commandList) noexcept :
		commandList(std::move(allocator), std::move(commandList))
	{
	}

	void D3D12CopyCommandList::Reset()
	{
		commandList.Reset();
	}

	void D3D12CopyCommandList::Close()
	{
		commandList.Close();
	}

	std::string_view D3D12CopyCommandList::Name() const noexcept
	{
		return commandList.Name();
	}

	void D3D12CopyCommandList::Name(const std::string_view name)
	{
		commandList.Name(name);
	}

	ID3D12GraphicsCommandList10& D3D12CopyCommandList::CommandList() const noexcept
	{
		return commandList.CommandList();
	}
}
