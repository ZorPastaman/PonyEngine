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

export module PonyEngine.RenderDevice.D3D12.Impl.Windows:D3D12CommandQueue;

import std;

import PonyEngine.Platform.Windows;
import PonyEngine.RenderDevice.Ext;

import :D3D12Utility;

export namespace PonyEngine::RenderDevice::Windows
{
	class D3D12CommandQueue final
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit D3D12CommandQueue(ID3D12CommandQueue& commandQueue) noexcept;
		[[nodiscard("Pure constructor")]]
		explicit D3D12CommandQueue(Platform::Windows::ComPtr<ID3D12CommandQueue>&& commandQueue) noexcept;
		D3D12CommandQueue(const D3D12CommandQueue&) = delete;
		D3D12CommandQueue(D3D12CommandQueue&&) = delete;

		~D3D12CommandQueue() noexcept = default;

		[[nodiscard("Pure function")]]
		ID3D12CommandQueue& CommandQueue() noexcept;
		[[nodiscard("Pure function")]]
		const ID3D12CommandQueue& CommandQueue() const noexcept;

		void Execute(std::span<ID3D12CommandList* const> commandLists);

		void SetName(std::string_view name);

		D3D12CommandQueue& operator =(const D3D12CommandQueue&) = delete;
		D3D12CommandQueue& operator =(D3D12CommandQueue&&) = delete;

	private:
		Platform::Windows::ComPtr<ID3D12CommandQueue> commandQueue;
	};
}

namespace PonyEngine::RenderDevice::Windows
{
	D3D12CommandQueue::D3D12CommandQueue(ID3D12CommandQueue& commandQueue) noexcept :
		commandQueue(&commandQueue)
	{
	}

	D3D12CommandQueue::D3D12CommandQueue(Platform::Windows::ComPtr<ID3D12CommandQueue>&& commandQueue) noexcept :
		commandQueue(std::move(commandQueue))
	{
		assert(this->commandQueue && "The command queue is nullptr.");
	}

	ID3D12CommandQueue& D3D12CommandQueue::CommandQueue() noexcept
	{
		return *commandQueue;
	}

	const ID3D12CommandQueue& D3D12CommandQueue::CommandQueue() const noexcept
	{
		return *commandQueue;
	}

	void D3D12CommandQueue::Execute(const std::span<ID3D12CommandList* const> commandLists)
	{
		if (commandLists.size() > std::numeric_limits<UINT>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Command lists span is too large");
		}

		commandQueue->ExecuteCommandLists(static_cast<UINT>(commandLists.size()), commandLists.data());
	}

	void D3D12CommandQueue::SetName(const std::string_view name)
	{
		SetObjectName(*commandQueue, name);
	}
}
