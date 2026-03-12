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

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:CommandQueue;

import std;

import PonyEngine.Platform.Windows;

import :ObjectUtility;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	/// @brief Command queue.
	class CommandQueue final
	{
	public:
		/// @brief Creates a command queue.
		/// @param commandQueue Command queue.
		[[nodiscard("Pure constructor")]]
		explicit CommandQueue(ID3D12CommandQueue& commandQueue) noexcept;
		/// @brief Creates a command queue.
		/// @param commandQueue Command queue.
		[[nodiscard("Pure constructor")]]
		explicit CommandQueue(Platform::Windows::ComPtr<ID3D12CommandQueue>&& commandQueue) noexcept;
		CommandQueue(const CommandQueue&) = delete;
		CommandQueue(CommandQueue&&) = delete;

		~CommandQueue() noexcept = default;

		/// @brief Gets the command queue.
		/// @return Command queue.
		[[nodiscard("Pure function")]]
		ID3D12CommandQueue& GetCommandQueue() noexcept;
		/// @brief Gets the command queue.
		/// @return Command queue.
		[[nodiscard("Pure function")]]
		const ID3D12CommandQueue& GetCommandQueue() const noexcept;

		/// @brief Executes command lists.
		/// @param commandLists Command lists to execute.
		/// @param beforeFences Fences that are waited for.
		/// @param afterFences Fences that are signaled.
		void Execute(std::span<ID3D12CommandList* const> commandLists, 
			std::span<const std::pair<ID3D12Fence*, UINT64>> beforeFences, std::span<const std::pair<ID3D12Fence*, UINT64>> afterFences);

		/// @brief Sets the name.
		/// @param name Name to set.
		void SetName(std::string_view name);

		CommandQueue& operator =(const CommandQueue&) = delete;
		CommandQueue& operator =(CommandQueue&&) = delete;

	private:
		Platform::Windows::ComPtr<ID3D12CommandQueue> commandQueue; ///< Command queue.
	};
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	CommandQueue::CommandQueue(ID3D12CommandQueue& commandQueue) noexcept :
		commandQueue(&commandQueue)
	{
	}

	CommandQueue::CommandQueue(Platform::Windows::ComPtr<ID3D12CommandQueue>&& commandQueue) noexcept :
		commandQueue(std::move(commandQueue))
	{
		assert(this->commandQueue && "The command queue is nullptr.");
	}

	ID3D12CommandQueue& CommandQueue::GetCommandQueue() noexcept
	{
		return *commandQueue;
	}

	const ID3D12CommandQueue& CommandQueue::GetCommandQueue() const noexcept
	{
		return *commandQueue;
	}

	void CommandQueue::Execute(const std::span<ID3D12CommandList* const> commandLists,
		const std::span<const std::pair<ID3D12Fence*, UINT64>> beforeFences, const std::span<const std::pair<ID3D12Fence*, UINT64>> afterFences)
	{
#ifndef NDEBUG
		if (commandLists.size() > std::numeric_limits<UINT>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Command lists span is too large");
		}
#endif

		for (const auto [fence, fenceValue] : beforeFences)
		{
			if (const HRESULT result = commandQueue->Wait(fence, fenceValue); FAILED(result)) [[unlikely]]
			{
				throw std::runtime_error(std::format("Failed to set wait fence: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
			}
		}

		if (!commandLists.empty()) [[likely]]
		{
			commandQueue->ExecuteCommandLists(static_cast<UINT>(commandLists.size()), commandLists.data());
		}

		for (const auto [fence, fenceValue] : afterFences)
		{
			if (const HRESULT result = commandQueue->Signal(fence, fenceValue); FAILED(result)) [[unlikely]]
			{
				throw std::runtime_error(std::format("Failed to set signal fence: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
			}
		}
	}

	void CommandQueue::SetName(const std::string_view name)
	{
		SetObjectName(*commandQueue, name);
	}
}
