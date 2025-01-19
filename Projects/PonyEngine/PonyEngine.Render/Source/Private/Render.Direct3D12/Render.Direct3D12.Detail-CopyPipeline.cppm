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

#include "PonyBase/Core/Direct3D12/Framework.h"

#include "PonyDebug/Log/Log.h"

export module PonyEngine.Render.Direct3D12.Detail:CopyPipeline;

import <array>;
import <cstdint>;
import <stdexcept>;
import <string>;
import <string_view>;
import <type_traits>;
import <vector>;

import PonyBase.Utility.COM;

import PonyDebug.Log;

import :Buffer;
import :ICopyPipeline;
import :ISubSystemContext;
import :ObjectUtility;
import :Resource;
import :Texture;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 copy pipeline.
	class CopyPipeline final : public ICopyPipeline
	{
	public:
		[[nodiscard("Pure constructor")]]
		CopyPipeline(ISubSystemContext& d3d12System, INT commandQueuePriority);
		CopyPipeline(const CopyPipeline&) = delete;
		CopyPipeline(CopyPipeline&&) = delete;

		~CopyPipeline() noexcept;

		virtual void AddCopyTask(const std::shared_ptr<Buffer>& source, const std::shared_ptr<Buffer>& destination) override;
		virtual void AddCopyTask(const std::shared_ptr<Texture>& source, const std::shared_ptr<Texture>& destination) override;

		/// @brief Gets the main command queue.
		/// @return Command queue.
		[[nodiscard("Pure function")]]
		ID3D12CommandQueue& CommandQueue() noexcept;
		/// @brief Gets the main command queue.
		/// @return Command queue.
		[[nodiscard("Pure function")]]
		const ID3D12CommandQueue& CommandQueue() const noexcept;

		/// @brief Sets name to its components.
		/// @param name Name.
		void Name(std::string_view name);

		/// @brief Populates commands.
		void PopulateCommands();
		/// @brief Executes populated commands.
		void Execute();
		/// @brief Clears copy tasks. Must be called only after finishing execution.
		void Clear() noexcept;

		CopyPipeline& operator =(const CopyPipeline&) = delete;
		CopyPipeline& operator =(CopyPipeline&&) = delete;

	private:
		enum class ResourceType : std::uint8_t
		{
			Buffer,
			Texture
		};

		/// @brief Copy task.
		struct CopyTask final
		{
			std::shared_ptr<Resource> source; ///< Copy source.
			std::shared_ptr<Resource> destination; ///< Copy destination.
			ResourceType resourceType;
		};

		/// @brief Resets command lists.
		void ResetLists();
		/// @brief Populates begin to copy barriers.
		void PopulateBeginToCopyBarriers();
		/// @brief Populates copies.
		void PopulateCopies();
		/// @brief Populates copy to end barriers.
		void PopulateCopyToEndBarriers();
		/// @brief Closes command lists.
		void CloseLists();

		void AddBufferBeforeBarriers(const CopyTask& copyTask);
		void AddBufferAfterBarriers(const CopyTask& copyTask);

		void AddTextureBeforeBarriers(const CopyTask& copyTask);
		void AddTextureAfterBarriers(const CopyTask& copyTask);

		/// @brief Populates barrier groups.
		void PopulateBarrierGroups();

		GUID guid; ///< Copy pipeline guid.

		ISubSystemContext* d3d12System; ///< Direct3D12 system context.

		Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue; ///< Copy command queue.
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator; ///< Copy command allocator.
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList7> commandList; ///< Copy command list.

		std::vector<CopyTask> copyTasks; ///< Copy tasks.

		std::vector<D3D12_BUFFER_BARRIER> bufferBarriers; ///< Buffer barriers cache.
		std::vector<D3D12_TEXTURE_BARRIER> textureBarriers; ///< Buffer barriers cache.
	};
}

namespace PonyEngine::Render::Direct3D12
{
	CopyPipeline::CopyPipeline(ISubSystemContext& d3d12System, const INT commandQueuePriority) :
		guid{PonyBase::Utility::COM::AcquireGuid()},
		d3d12System{&d3d12System}
	{
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Copy pipeline guid: '{}'.", PonyBase::Utility::COM::ToString(guid));

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
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Copy command queue acquired.");

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Acquire copy command allocator.");
		if (const HRESULT result = device.CreateCommandAllocator(commandListType, IID_PPV_ARGS(commandAllocator.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire copy command allocator with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Copy command allocator acquired.");

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Acquire copy command list.");
		if (const HRESULT result = device.CreateCommandList1(0, commandListType, D3D12_COMMAND_LIST_FLAG_NONE, IID_PPV_ARGS(commandList.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire copy command list with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Copy command list acquired.");
	}

	CopyPipeline::~CopyPipeline() noexcept
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

	void CopyPipeline::AddCopyTask(const std::shared_ptr<Buffer>& source, const std::shared_ptr<Buffer>& destination)
	{
		const auto copyTask = CopyTask
		{
			.source = source,
			.destination = destination,
			.resourceType = ResourceType::Buffer
		};
		copyTasks.push_back(copyTask);
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Debug, "Buffer copy task added. Source: '0x{:X}'; Destination: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(&source), reinterpret_cast<std::uintptr_t>(&destination));
	}

	void CopyPipeline::AddCopyTask(const std::shared_ptr<Texture>& source, const std::shared_ptr<Texture>& destination)
	{
		const auto copyTask = CopyTask
		{
			.source = source,
			.destination = destination,
			.resourceType = ResourceType::Texture
		};
		copyTasks.push_back(copyTask);
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Debug, "Texture copy task added. Source: '0x{:X}'; Destination: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(&source), reinterpret_cast<std::uintptr_t>(&destination));
	}

	ID3D12CommandQueue& CopyPipeline::CommandQueue() noexcept
	{
		return *commandQueue.Get();
	}

	const ID3D12CommandQueue& CopyPipeline::CommandQueue() const noexcept
	{
		return *commandQueue.Get();
	}

	void CopyPipeline::Name(const std::string_view name)
	{
		constexpr std::string_view commandQueueName = " - CommandQueue";
		constexpr std::string_view commandAllocatorName = " - CommandAllocator";
		constexpr std::string_view commandListName = " - CommandList";

		auto componentName = std::string();
		componentName.reserve(name.size() + commandAllocatorName.size());

		componentName.append(name).append(commandQueueName);
		SetName(*commandQueue.Get(), componentName);

		componentName.clear();
		componentName.append(name).append(commandAllocatorName);
		SetName(*commandAllocator.Get(), componentName);

		componentName.clear();
		componentName.append(name).append(commandListName);
		SetName(*commandList.Get(), componentName);
	}

	void CopyPipeline::PopulateCommands()
	{
		ResetLists();
		PopulateBeginToCopyBarriers();
		PopulateCopies();
		PopulateCopyToEndBarriers();
		CloseLists();
	}

	void CopyPipeline::Execute()
	{
		const auto commandLists = std::array<ID3D12CommandList*, 1> { commandList.Get() };
		commandQueue->ExecuteCommandLists(static_cast<UINT>(commandLists.size()), commandLists.data());
	}

	void CopyPipeline::Clear() noexcept
	{
		copyTasks.clear();
	}

	void CopyPipeline::ResetLists()
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

	void CopyPipeline::PopulateBeginToCopyBarriers()
	{
		bufferBarriers.clear();
		textureBarriers.clear();
		for (const CopyTask& copyTask : copyTasks)
		{
			switch (copyTask.resourceType)
			{
			case ResourceType::Buffer:
				AddBufferBeforeBarriers(copyTask);
				break;
			case ResourceType::Texture:
				AddTextureBeforeBarriers(copyTask);
				break;
			default: [[unlikely]]
				assert(false && "Unexpected resource type.");
			}
		}

		PopulateBarrierGroups();
	}

	void CopyPipeline::PopulateCopies()
	{
		for (const CopyTask& copyTask : copyTasks)
		{
			commandList->CopyResource(&copyTask.destination->Data(), &copyTask.source->Data());
		}
	}

	void CopyPipeline::PopulateCopyToEndBarriers()
	{
		bufferBarriers.clear();
		textureBarriers.clear();
		for (const CopyTask& copyTask : copyTasks)
		{
			switch (copyTask.resourceType)
			{
			case ResourceType::Buffer:
				AddBufferAfterBarriers(copyTask);
				break;
			case ResourceType::Texture:
				AddTextureAfterBarriers(copyTask);
				break;
			default: [[unlikely]]
				assert(false && "Unexpected resource type.");
			}
		}

		PopulateBarrierGroups();
	}

	void CopyPipeline::CloseLists()
	{
		if (const HRESULT result = commandList->Close(); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to close command list with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
	}

	void CopyPipeline::AddBufferBeforeBarriers(const CopyTask& copyTask)
	{
		const auto sourceBarrier = D3D12_BUFFER_BARRIER
		{
			.SyncBefore = D3D12_BARRIER_SYNC_NONE,
			.SyncAfter = D3D12_BARRIER_SYNC_COPY,
			.AccessBefore = D3D12_BARRIER_ACCESS_NO_ACCESS,
			.AccessAfter = D3D12_BARRIER_ACCESS_COPY_SOURCE,
			.pResource = &copyTask.source->Data(),
			.Offset = 0UL,
			.Size = UINT64_MAX
		};
		const auto destinationBarrier = D3D12_BUFFER_BARRIER
		{
			.SyncBefore = D3D12_BARRIER_SYNC_NONE,
			.SyncAfter = D3D12_BARRIER_SYNC_COPY,
			.AccessBefore = D3D12_BARRIER_ACCESS_NO_ACCESS,
			.AccessAfter = D3D12_BARRIER_ACCESS_COPY_DEST,
			.pResource = &copyTask.destination->Data(),
			.Offset = 0UL,
			.Size = UINT64_MAX
		};
		bufferBarriers.push_back(sourceBarrier);
		bufferBarriers.push_back(destinationBarrier);
	}

	void CopyPipeline::AddBufferAfterBarriers(const CopyTask& copyTask)
	{
		const auto sourceBarrier = D3D12_BUFFER_BARRIER
		{
			.SyncBefore = D3D12_BARRIER_SYNC_COPY,
			.SyncAfter = D3D12_BARRIER_SYNC_NONE,
			.AccessBefore = D3D12_BARRIER_ACCESS_COPY_SOURCE,
			.AccessAfter = D3D12_BARRIER_ACCESS_NO_ACCESS,
			.pResource = &copyTask.source->Data(),
			.Offset = 0UL,
			.Size = UINT64_MAX
		};
		const auto destinationBarrier = D3D12_BUFFER_BARRIER
		{
			.SyncBefore = D3D12_BARRIER_SYNC_COPY,
			.SyncAfter = D3D12_BARRIER_SYNC_NONE,
			.AccessBefore = D3D12_BARRIER_ACCESS_COPY_DEST,
			.AccessAfter = D3D12_BARRIER_ACCESS_NO_ACCESS,
			.pResource = &copyTask.destination->Data(),
			.Offset = 0UL,
			.Size = UINT64_MAX
		};
		bufferBarriers.push_back(sourceBarrier);
		bufferBarriers.push_back(destinationBarrier);
	}

	void CopyPipeline::AddTextureBeforeBarriers(const CopyTask& copyTask)
	{
		const auto sourceBarrier = D3D12_TEXTURE_BARRIER
		{
			.SyncBefore = D3D12_BARRIER_SYNC_NONE,
			.SyncAfter = D3D12_BARRIER_SYNC_COPY,
			.AccessBefore = D3D12_BARRIER_ACCESS_NO_ACCESS,
			.AccessAfter = D3D12_BARRIER_ACCESS_COPY_SOURCE,
			.LayoutBefore = D3D12_BARRIER_LAYOUT_COMMON,
			.LayoutAfter = D3D12_BARRIER_LAYOUT_COPY_SOURCE,
			.pResource = &copyTask.source->Data(),
			.Subresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
			.Flags = D3D12_TEXTURE_BARRIER_FLAG_NONE
		};
		const auto destinationBarrier = D3D12_TEXTURE_BARRIER
		{
			.SyncBefore = D3D12_BARRIER_SYNC_NONE,
			.SyncAfter = D3D12_BARRIER_SYNC_COPY,
			.AccessBefore = D3D12_BARRIER_ACCESS_NO_ACCESS,
			.AccessAfter = D3D12_BARRIER_ACCESS_COPY_DEST,
			.LayoutBefore = D3D12_BARRIER_LAYOUT_COMMON,
			.LayoutAfter = D3D12_BARRIER_LAYOUT_COPY_DEST,
			.pResource = &copyTask.destination->Data(),
			.Subresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
			.Flags = D3D12_TEXTURE_BARRIER_FLAG_NONE
		};
		textureBarriers.push_back(sourceBarrier);
		textureBarriers.push_back(destinationBarrier);
	}

	void CopyPipeline::AddTextureAfterBarriers(const CopyTask& copyTask)
	{
		const auto sourceBarrier = D3D12_TEXTURE_BARRIER
		{
			.SyncBefore = D3D12_BARRIER_SYNC_COPY,
			.SyncAfter = D3D12_BARRIER_SYNC_NONE,
			.AccessBefore = D3D12_BARRIER_ACCESS_COPY_SOURCE,
			.AccessAfter = D3D12_BARRIER_ACCESS_NO_ACCESS,
			.LayoutBefore = D3D12_BARRIER_LAYOUT_COPY_SOURCE,
			.LayoutAfter = D3D12_BARRIER_LAYOUT_COMMON,
			.pResource = &copyTask.source->Data(),
			.Subresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
			.Flags = D3D12_TEXTURE_BARRIER_FLAG_NONE
		};
		const auto destinationBarrier = D3D12_TEXTURE_BARRIER
		{
			.SyncBefore = D3D12_BARRIER_SYNC_COPY,
			.SyncAfter = D3D12_BARRIER_SYNC_NONE,
			.AccessBefore = D3D12_BARRIER_ACCESS_COPY_DEST,
			.AccessAfter = D3D12_BARRIER_ACCESS_NO_ACCESS,
			.LayoutBefore = D3D12_BARRIER_LAYOUT_COPY_DEST,
			.LayoutAfter = D3D12_BARRIER_LAYOUT_COMMON,
			.pResource = &copyTask.destination->Data(),
			.Subresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
			.Flags = D3D12_TEXTURE_BARRIER_FLAG_NONE
		};
		textureBarriers.push_back(sourceBarrier);
		textureBarriers.push_back(destinationBarrier);
	}

	void CopyPipeline::PopulateBarrierGroups()
	{
		auto barrierGroups = std::array<D3D12_BARRIER_GROUP, 2>();
		UINT32 count = 0u;
		if (bufferBarriers.size() > 0)
		{
			barrierGroups[count++] = D3D12_BARRIER_GROUP
			{
				.Type = D3D12_BARRIER_TYPE_BUFFER,
				.NumBarriers = static_cast<UINT32>(bufferBarriers.size()),
				.pBufferBarriers = bufferBarriers.data()
			};
		}
		if (textureBarriers.size() > 0)
		{
			barrierGroups[count++] = D3D12_BARRIER_GROUP
			{
				.Type = D3D12_BARRIER_TYPE_TEXTURE,
				.NumBarriers = static_cast<UINT32>(textureBarriers.size()),
				.pTextureBarriers = textureBarriers.data()
			};
		}

		if (count > 0u)
		{
			commandList->Barrier(count, barrierGroups.data());
		}
	}
}
