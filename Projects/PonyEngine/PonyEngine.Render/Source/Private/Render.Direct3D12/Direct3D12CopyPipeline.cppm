/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/Direct3D12/Framework.h"

#include "PonyDebug/Log/Log.h"

export module PonyEngine.Render.Direct3D12.Detail:Direct3D12CopyPipeline;

import <array>;
import <cstdint>;
import <stdexcept>;
import <type_traits>;
import <vector>;

import PonyBase.COMUtility;
import PonyBase.StringUtility;

import PonyDebug.Log;

import :IDirect3D12CopyPipeline;
import :IDirect3D12SystemContext;

export namespace PonyEngine::Render
{
	/// @brief Direct3D12 copy pipeline.
	class Direct3D12CopyPipeline final : public IDirect3D12CopyPipeline
	{
	public:
		[[nodiscard("Pure constructor")]]
		Direct3D12CopyPipeline(IDirect3D12SystemContext& d3d12System, INT commandQueuePriority);
		Direct3D12CopyPipeline(const Direct3D12CopyPipeline&) = delete;
		Direct3D12CopyPipeline(Direct3D12CopyPipeline&&) = delete;

		~Direct3D12CopyPipeline() noexcept;

		virtual void AddCopyTask(ID3D12Resource2& source, ID3D12Resource2& destination) override;

		/// @brief Gets the main command queue.
		/// @return Command queue.
		[[nodiscard("Pure function")]]
		ID3D12CommandQueue& CommandQueue() noexcept;
		/// @brief Gets the main command queue.
		/// @return Command queue.
		[[nodiscard("Pure function")]]
		const ID3D12CommandQueue& CommandQueue() const noexcept;

		/// @brief Populates commands.
		void PopulateCommands();
		/// @brief Executes populated commands.
		void Execute();
		/// @brief Clears copy tasks. Must be called only after finishing execution.
		void Clear() noexcept;

		Direct3D12CopyPipeline& operator =(const Direct3D12CopyPipeline&) = delete;
		Direct3D12CopyPipeline& operator =(Direct3D12CopyPipeline&&) = delete;

	private:
		/// @brief Copy task.
		struct CopyTask final
		{
			Microsoft::WRL::ComPtr<ID3D12Resource2> source; ///< Copy source.
			Microsoft::WRL::ComPtr<ID3D12Resource2> destination; ///< Copy destination.
		};

		/// @brief Resets command lists.
		void ResetLists();
		/// @brief Populates resource barriers to make resources ready for copying.
		void PopulateResourceBarriersIn();
		/// @brief Copies.
		void Copy();
		/// @brief Populates resource barriers back.
		void PopulateResourceBarriersOut();
		/// @brief Closes command lists.
		void CloseLists();

		GUID guid; ///< Copy pipeline guid.

		IDirect3D12SystemContext* d3d12System; ///< Direct3D12 system context.

		Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue; ///< Copy command queue.
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator; ///< Copy command allocator.
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList7> commandList; ///< Copy command list.

		std::vector<CopyTask> copyTasks; ///< Copy tasks.

		std::vector<D3D12_RESOURCE_BARRIER> resourceBarriers; ///< Resource barriers cache.
	};

	Direct3D12CopyPipeline::Direct3D12CopyPipeline(IDirect3D12SystemContext& d3d12System, const INT commandQueuePriority) :
		guid{PonyBase::Utility::AcquireGuid()},
		d3d12System{&d3d12System}
	{
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Copy pipeline guid: '{}'.", PonyBase::Utility::ToString(guid));

		constexpr D3D12_COMMAND_LIST_TYPE commandListType = D3D12_COMMAND_LIST_TYPE_COPY;

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Acquire copy command queue. Priority: '{}'.", commandQueuePriority);
		const auto commandQueueDescription = D3D12_COMMAND_QUEUE_DESC
		{
			.Type = commandListType,
			.Priority = commandQueuePriority,
			.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE,
			.NodeMask = 0u
		};
		ID3D12Device10& device = this->d3d12System->Device();
		if (const HRESULT result = device.CreateCommandQueue1(&commandQueueDescription, guid, IID_PPV_ARGS(commandQueue.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire copy command queue with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Copy command queue acquired at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(commandQueue.Get()));

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Acquire copy command allocator.");
		if (const HRESULT result = device.CreateCommandAllocator(commandListType, IID_PPV_ARGS(commandAllocator.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire copy command allocator with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Copy command allocator acquired at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(commandAllocator.Get()));

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Acquire copy command list.");
		if (const HRESULT result = device.CreateCommandList1(0, commandListType, D3D12_COMMAND_LIST_FLAG_NONE, IID_PPV_ARGS(commandList.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire copy command list with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Copy command list acquired at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(commandList.Get()));
	}

	Direct3D12CopyPipeline::~Direct3D12CopyPipeline() noexcept
	{
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Release copy command list.");
		commandList.Reset();
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Copy command list released.");

		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Release copy command allocator.");
		commandAllocator.Reset();
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Copy command allocator released.");

		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Release copy command queue.");
		commandQueue.Reset();
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Copy command queue released.");
	}

	void Direct3D12CopyPipeline::AddCopyTask(ID3D12Resource2& source, ID3D12Resource2& destination)
	{
		copyTasks.push_back(CopyTask{.source = &source, .destination = &destination});
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Debug, "Copy task added. Source: '0x{:X}'; Destination: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(&source), reinterpret_cast<std::uintptr_t>(&destination));
	}

	ID3D12CommandQueue& Direct3D12CopyPipeline::CommandQueue() noexcept
	{
		return *commandQueue.Get();
	}

	const ID3D12CommandQueue& Direct3D12CopyPipeline::CommandQueue() const noexcept
	{
		return *commandQueue.Get();
	}

	void Direct3D12CopyPipeline::PopulateCommands()
	{
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Verbose, "Reset command lists.");
		ResetLists();
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Verbose, "Populate resource barriers in.");
		PopulateResourceBarriersIn();
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Verbose, "Copy.");
		Copy();
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Verbose, "Populate resource barriers out.");
		PopulateResourceBarriersOut();
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Verbose, "Close command lists.");
		CloseLists();
	}

	void Direct3D12CopyPipeline::Execute()
	{
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Verbose, "Execute command lists.");
		const auto commandLists = std::array<ID3D12CommandList*, 1> { commandList.Get() };
		commandQueue->ExecuteCommandLists(static_cast<UINT>(commandLists.size()), commandLists.data());
	}

	void Direct3D12CopyPipeline::Clear() noexcept
	{
		copyTasks.clear();
	}

	void Direct3D12CopyPipeline::ResetLists()
	{
		if (const HRESULT result = commandAllocator->Reset(); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to reset command allocator with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		if (const HRESULT result = commandList->Reset(commandAllocator.Get(), nullptr); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to reset command list with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
	}

	void Direct3D12CopyPipeline::PopulateResourceBarriersIn()
	{
		if (copyTasks.empty())
		{
			return;
		}

		resourceBarriers.clear();
		resourceBarriers.reserve(copyTasks.size() * 2);
		for (const CopyTask& copyTask : copyTasks)
		{
			const auto copySourceBarrier = D3D12_RESOURCE_BARRIER
			{
				.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
				.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE,
				.Transition = D3D12_RESOURCE_TRANSITION_BARRIER
				{
					.pResource = copyTask.source.Get(),
					.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
					.StateBefore = D3D12_RESOURCE_STATE_COMMON,
					.StateAfter = D3D12_RESOURCE_STATE_COPY_SOURCE
				}
			};
			resourceBarriers.push_back(copySourceBarrier);
			const auto copyDestinationBarrier = D3D12_RESOURCE_BARRIER
			{
				.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
				.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE,
				.Transition = D3D12_RESOURCE_TRANSITION_BARRIER
				{
					.pResource = copyTask.destination.Get(),
					.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
					.StateBefore = D3D12_RESOURCE_STATE_COMMON,
					.StateAfter = D3D12_RESOURCE_STATE_COPY_DEST
				}
			};
			resourceBarriers.push_back(copyDestinationBarrier);
		}

		commandList->ResourceBarrier(static_cast<UINT>(resourceBarriers.size()), resourceBarriers.data());
	}

	void Direct3D12CopyPipeline::Copy()
	{
		for (const CopyTask& copyTask : copyTasks)
		{
			commandList->CopyResource(copyTask.destination.Get(), copyTask.source.Get());
		}
	}

	void Direct3D12CopyPipeline::PopulateResourceBarriersOut()
	{
		if (copyTasks.empty())
		{
			return;
		}

		resourceBarriers.clear();
		for (const CopyTask& copyTask : copyTasks)
		{
			const auto copySourceBarrier = D3D12_RESOURCE_BARRIER
			{
				.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
				.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE,
				.Transition = D3D12_RESOURCE_TRANSITION_BARRIER
				{
					.pResource = copyTask.source.Get(),
					.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
					.StateBefore = D3D12_RESOURCE_STATE_COPY_SOURCE,
					.StateAfter = D3D12_RESOURCE_STATE_COMMON
				}
			};
			resourceBarriers.push_back(copySourceBarrier);
			const auto copyDestinationBarrier = D3D12_RESOURCE_BARRIER
			{
				.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
				.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE,
				.Transition = D3D12_RESOURCE_TRANSITION_BARRIER
				{
					.pResource = copyTask.destination.Get(),
					.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
					.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST,
					.StateAfter = D3D12_RESOURCE_STATE_COMMON
				}
			};
			resourceBarriers.push_back(copyDestinationBarrier);
		}

		commandList->ResourceBarrier(static_cast<UINT>(resourceBarriers.size()), resourceBarriers.data());
	}

	void Direct3D12CopyPipeline::CloseLists()
	{
		if (const HRESULT result = commandList->Close(); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to close command list with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
	}
}
