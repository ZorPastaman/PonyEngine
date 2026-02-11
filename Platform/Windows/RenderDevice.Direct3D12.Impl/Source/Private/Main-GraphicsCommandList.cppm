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

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:GraphicsCommandList;

import std;

import PonyEngine.Platform.Windows;
import PonyEngine.RenderDevice;

import :CommandList;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	class GraphicsCommandList final : public IGraphicsCommandList
	{
	public:
		[[nodiscard("Pure constructor")]]
		GraphicsCommandList(ID3D12CommandAllocator& allocator, ID3D12GraphicsCommandList10& commandList) noexcept;
		[[nodiscard("Pure constructor")]]
		GraphicsCommandList(Platform::Windows::ComPtr<ID3D12CommandAllocator>&& allocator, Platform::Windows::ComPtr<ID3D12GraphicsCommandList10>&& commandList) noexcept;
		GraphicsCommandList(const GraphicsCommandList&) = delete;
		GraphicsCommandList(GraphicsCommandList&&) = delete;

		~GraphicsCommandList() noexcept = default;

		virtual void Reset() override;
		virtual void Close() override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;
		virtual void Name(std::string_view name) override;

		[[nodiscard("Pure function")]]
		ID3D12GraphicsCommandList10& CommandList() const noexcept;

		GraphicsCommandList& operator =(const GraphicsCommandList&) = delete;
		GraphicsCommandList& operator =(GraphicsCommandList&&) = delete;

	private:
		class CommandList commandList;
	};
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	GraphicsCommandList::GraphicsCommandList(ID3D12CommandAllocator& allocator, ID3D12GraphicsCommandList10& commandList) noexcept :
		commandList(allocator, commandList)
	{
	}

	GraphicsCommandList::GraphicsCommandList(Platform::Windows::ComPtr<ID3D12CommandAllocator>&& allocator, 
		Platform::Windows::ComPtr<ID3D12GraphicsCommandList10>&& commandList) noexcept :
		commandList(std::move(allocator), std::move(commandList))
	{
	}

	void GraphicsCommandList::Reset()
	{
		commandList.Reset();
	}

	void GraphicsCommandList::Close()
	{
		commandList.Close();
	}

	std::string_view GraphicsCommandList::Name() const noexcept
	{
		return commandList.Name();
	}

	void GraphicsCommandList::Name(const std::string_view name)
	{
		commandList.Name(name);
	}

	ID3D12GraphicsCommandList10& GraphicsCommandList::CommandList() const noexcept
	{
		return commandList.GetCommandList();
	}
}
