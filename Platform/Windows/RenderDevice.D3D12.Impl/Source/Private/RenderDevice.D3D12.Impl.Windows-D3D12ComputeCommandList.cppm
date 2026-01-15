/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Render/Windows/D3D12Framework.h"

export module PonyEngine.RenderDevice.D3D12.Impl.Windows:D3D12ComputeCommandList;

import std;

import PonyEngine.Platform.Windows;
import PonyEngine.RenderDevice;

import :D3D12CommandList;

export namespace PonyEngine::Render::Windows
{
	class D3D12ComputeCommandList final : public IComputeCommandList
	{
	public:
		[[nodiscard("Pure constructor")]]
		D3D12ComputeCommandList(ID3D12CommandAllocator& allocator, ID3D12GraphicsCommandList10& commandList) noexcept;
		[[nodiscard("Pure constructor")]]
		D3D12ComputeCommandList(Platform::Windows::ComPtr<ID3D12CommandAllocator>&& allocator, Platform::Windows::ComPtr<ID3D12GraphicsCommandList10>&& commandList) noexcept;
		D3D12ComputeCommandList(const D3D12ComputeCommandList&) = delete;
		D3D12ComputeCommandList(D3D12ComputeCommandList&&) = delete;

		~D3D12ComputeCommandList() noexcept = default;

		virtual void Reset() override;
		virtual void Close() override;

		virtual void SetName(std::string_view name) override;

		[[nodiscard("Pure function")]]
		ID3D12GraphicsCommandList10& CommandList() const noexcept;

		D3D12ComputeCommandList& operator =(const D3D12ComputeCommandList&) = delete;
		D3D12ComputeCommandList& operator =(D3D12ComputeCommandList&&) = delete;

	private:
		D3D12CommandList commandList;
	};
}

namespace PonyEngine::Render::Windows
{
	D3D12ComputeCommandList::D3D12ComputeCommandList(ID3D12CommandAllocator& allocator, ID3D12GraphicsCommandList10& commandList) noexcept :
		commandList(allocator, commandList)
	{
	}

	D3D12ComputeCommandList::D3D12ComputeCommandList(Platform::Windows::ComPtr<ID3D12CommandAllocator>&& allocator,
		Platform::Windows::ComPtr<ID3D12GraphicsCommandList10>&& commandList) noexcept :
		commandList(std::move(allocator), std::move(commandList))
	{
	}

	void D3D12ComputeCommandList::Reset()
	{
		commandList.Reset();
	}

	void D3D12ComputeCommandList::Close()
	{
		commandList.Close();
	}

	void D3D12ComputeCommandList::SetName(const std::string_view name)
	{
		commandList.SetName(name);
	}

	ID3D12GraphicsCommandList10& D3D12ComputeCommandList::CommandList() const noexcept
	{
		return commandList.CommandList();
	}
}
