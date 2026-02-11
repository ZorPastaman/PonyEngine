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

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:BundleCommandList;

import std;

import PonyEngine.Platform.Windows;
import PonyEngine.RenderDevice;

import :CommandList;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	class BundleCommandList final : public ISecondaryGraphicsCommandList
	{
	public:
		[[nodiscard("Pure constructor")]]
		BundleCommandList(ID3D12CommandAllocator& allocator, ID3D12GraphicsCommandList10& commandList) noexcept;
		[[nodiscard("Pure constructor")]]
		BundleCommandList(Platform::Windows::ComPtr<ID3D12CommandAllocator>&& allocator, Platform::Windows::ComPtr<ID3D12GraphicsCommandList10>&& commandList) noexcept;
		BundleCommandList(const BundleCommandList&) = delete;
		BundleCommandList(BundleCommandList&&) = delete;

		~BundleCommandList() noexcept = default;

		virtual void Reset() override;
		virtual void Close() override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;
		virtual void Name(std::string_view name) override;

		[[nodiscard("Pure function")]]
		ID3D12GraphicsCommandList10& CommandList() const noexcept;

		BundleCommandList& operator =(const BundleCommandList&) = delete;
		BundleCommandList& operator =(BundleCommandList&&) = delete;

	private:
		class CommandList commandList;
	};
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	BundleCommandList::BundleCommandList(ID3D12CommandAllocator& allocator, ID3D12GraphicsCommandList10& commandList) noexcept :
		commandList(allocator, commandList)
	{
	}

	BundleCommandList::BundleCommandList(Platform::Windows::ComPtr<ID3D12CommandAllocator>&& allocator,
		Platform::Windows::ComPtr<ID3D12GraphicsCommandList10>&& commandList) noexcept :
		commandList(std::move(allocator), std::move(commandList))
	{
	}

	void BundleCommandList::Reset()
	{
		commandList.Reset();
	}

	void BundleCommandList::Close()
	{
		commandList.Close();
	}

	std::string_view BundleCommandList::Name() const noexcept
	{
		return commandList.Name();
	}

	void BundleCommandList::Name(const std::string_view name)
	{
		commandList.Name(name);
	}

	ID3D12GraphicsCommandList10& BundleCommandList::CommandList() const noexcept
	{
		return commandList.GetCommandList();
	}
}
