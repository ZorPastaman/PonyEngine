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

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:ComputeCommandList;

import std;

import PonyEngine.Platform.Windows;
import PonyEngine.RenderDevice;

import :CommandList;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	class ComputeCommandList final : public IComputeCommandList
	{
	public:
		[[nodiscard("Pure constructor")]]
		ComputeCommandList(ID3D12CommandAllocator& allocator, ID3D12GraphicsCommandList10& commandList) noexcept;
		[[nodiscard("Pure constructor")]]
		ComputeCommandList(Platform::Windows::ComPtr<ID3D12CommandAllocator>&& allocator, Platform::Windows::ComPtr<ID3D12GraphicsCommandList10>&& commandList) noexcept;
		ComputeCommandList(const ComputeCommandList&) = delete;
		ComputeCommandList(ComputeCommandList&&) = delete;

		~ComputeCommandList() noexcept = default;

		virtual void Reset() override;
		virtual void Close() override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;
		virtual void Name(std::string_view name) override;

		[[nodiscard("Pure function")]]
		ID3D12GraphicsCommandList10& CommandList() const noexcept;

		ComputeCommandList& operator =(const ComputeCommandList&) = delete;
		ComputeCommandList& operator =(ComputeCommandList&&) = delete;

	private:
		class CommandList commandList;
	};
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	ComputeCommandList::ComputeCommandList(ID3D12CommandAllocator& allocator, ID3D12GraphicsCommandList10& commandList) noexcept :
		commandList(allocator, commandList)
	{
	}

	ComputeCommandList::ComputeCommandList(Platform::Windows::ComPtr<ID3D12CommandAllocator>&& allocator,
		Platform::Windows::ComPtr<ID3D12GraphicsCommandList10>&& commandList) noexcept :
		commandList(std::move(allocator), std::move(commandList))
	{
	}

	void ComputeCommandList::Reset()
	{
		commandList.Reset();
	}

	void ComputeCommandList::Close()
	{
		commandList.Close();
	}

	std::string_view ComputeCommandList::Name() const noexcept
	{
		return commandList.Name();
	}

	void ComputeCommandList::Name(const std::string_view name)
	{
		commandList.Name(name);
	}

	ID3D12GraphicsCommandList10& ComputeCommandList::CommandList() const noexcept
	{
		return commandList.GetCommandList();
	}
}
