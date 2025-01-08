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

import :ICopyPipeline;
import :ISubSystemContext;
import :ObjectUtility;

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

		virtual void AddBufferCopyTask(ID3D12Resource2& source, ID3D12Resource2& destination) override;
		virtual void AddTextureCopyTask(ID3D12Resource2& source, ID3D12Resource2& destination) override;

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
		/// @brief Copy task.
		struct CopyTask final
		{
			Microsoft::WRL::ComPtr<ID3D12Resource2> source; ///< Copy source.
			Microsoft::WRL::ComPtr<ID3D12Resource2> destination; ///< Copy destination.
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

		/// @brief Populates barrier groups.
		void PopulateBarrierGroups();

		GUID guid; ///< Copy pipeline guid.

		ISubSystemContext* d3d12System; ///< Direct3D12 system context.

		Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue; ///< Copy command queue.
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator; ///< Copy command allocator.
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList7> commandList; ///< Copy command list.

		std::vector<CopyTask> bufferCopyTasks; ///< Buffer copy tasks.
		std::vector<CopyTask> textureCopyTasks; ///< Buffer copy tasks.

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

	void CopyPipeline::AddBufferCopyTask(ID3D12Resource2& source, ID3D12Resource2& destination)
	{
		bufferCopyTasks.push_back(CopyTask{.source = &source, .destination = &destination});
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Debug, "Buffer copy task added. Source: '0x{:X}'; Destination: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(&source), reinterpret_cast<std::uintptr_t>(&destination));
	}

	void CopyPipeline::AddTextureCopyTask(ID3D12Resource2& source, ID3D12Resource2& destination)
	{
		textureCopyTasks.push_back(CopyTask{.source = &source, .destination = &destination});
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
		bufferCopyTasks.clear();
		textureCopyTasks.clear();
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
		bufferBarriers.reserve(bufferCopyTasks.size() * 2);
		for (const auto& [source, destination] : bufferCopyTasks)
		{
			const auto sourceBarrier = D3D12_BUFFER_BARRIER
			{
				.SyncBefore = D3D12_BARRIER_SYNC_NONE,
				.SyncAfter = D3D12_BARRIER_SYNC_COPY,
				.AccessBefore = D3D12_BARRIER_ACCESS_NO_ACCESS,
				.AccessAfter = D3D12_BARRIER_ACCESS_COPY_SOURCE,
				.pResource = source.Get(),
				.Offset = 0UL,
				.Size = UINT64_MAX
			};
			const auto destinationBarrier = D3D12_BUFFER_BARRIER
			{
				.SyncBefore = D3D12_BARRIER_SYNC_NONE,
				.SyncAfter = D3D12_BARRIER_SYNC_COPY,
				.AccessBefore = D3D12_BARRIER_ACCESS_NO_ACCESS,
				.AccessAfter = D3D12_BARRIER_ACCESS_COPY_DEST,
				.pResource = destination.Get(),
				.Offset = 0UL,
				.Size = UINT64_MAX
			};
			bufferBarriers.push_back(sourceBarrier);
			bufferBarriers.push_back(destinationBarrier);
		}

		textureBarriers.clear();
		textureBarriers.reserve(textureCopyTasks.size() * 2);
		for (const auto& [source, destination] : textureCopyTasks)
		{
			const auto sourceBarrier = D3D12_TEXTURE_BARRIER
			{
				.SyncBefore = D3D12_BARRIER_SYNC_NONE,
				.SyncAfter = D3D12_BARRIER_SYNC_COPY,
				.AccessBefore = D3D12_BARRIER_ACCESS_NO_ACCESS,
				.AccessAfter = D3D12_BARRIER_ACCESS_COPY_SOURCE,
				.LayoutBefore = D3D12_BARRIER_LAYOUT_COMMON,
				.LayoutAfter = D3D12_BARRIER_LAYOUT_COPY_SOURCE,
				.pResource = source.Get(),
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
				.pResource = destination.Get(),
				.Subresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
				.Flags = D3D12_TEXTURE_BARRIER_FLAG_NONE
			};
			textureBarriers.push_back(sourceBarrier);
			textureBarriers.push_back(destinationBarrier);
		}

		PopulateBarrierGroups();
	}

	void CopyPipeline::PopulateCopies()
	{
		for (const auto& [source, destination] : bufferCopyTasks)
		{
			commandList->CopyResource(destination.Get(), source.Get());
		}

		for (const auto& [source, destination] : textureCopyTasks)
		{
			commandList->CopyResource(destination.Get(), source.Get());
		}
	}

	void CopyPipeline::PopulateCopyToEndBarriers()
	{
		bufferBarriers.clear();
		for (const auto& [source, destination] : bufferCopyTasks)
		{
			const auto sourceBarrier = D3D12_BUFFER_BARRIER
			{
				.SyncBefore = D3D12_BARRIER_SYNC_COPY,
				.SyncAfter = D3D12_BARRIER_SYNC_NONE,
				.AccessBefore = D3D12_BARRIER_ACCESS_COPY_SOURCE,
				.AccessAfter = D3D12_BARRIER_ACCESS_NO_ACCESS,
				.pResource = source.Get(),
				.Offset = 0UL,
				.Size = UINT64_MAX
			};
			const auto destinationBarrier = D3D12_BUFFER_BARRIER
			{
				.SyncBefore = D3D12_BARRIER_SYNC_COPY,
				.SyncAfter = D3D12_BARRIER_SYNC_NONE,
				.AccessBefore = D3D12_BARRIER_ACCESS_COPY_DEST,
				.AccessAfter = D3D12_BARRIER_ACCESS_NO_ACCESS,
				.pResource = destination.Get(),
				.Offset = 0UL,
				.Size = UINT64_MAX
			};
			bufferBarriers.push_back(sourceBarrier);
			bufferBarriers.push_back(destinationBarrier);
		}

		textureBarriers.clear();
		for (const auto& [source, destination] : textureCopyTasks)
		{
			const auto sourceBarrier = D3D12_TEXTURE_BARRIER
			{
				.SyncBefore = D3D12_BARRIER_SYNC_COPY,
				.SyncAfter = D3D12_BARRIER_SYNC_NONE,
				.AccessBefore = D3D12_BARRIER_ACCESS_COPY_SOURCE,
				.AccessAfter = D3D12_BARRIER_ACCESS_NO_ACCESS,
				.LayoutBefore = D3D12_BARRIER_LAYOUT_COPY_SOURCE,
				.LayoutAfter = D3D12_BARRIER_LAYOUT_COMMON,
				.pResource = source.Get(),
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
				.pResource = destination.Get(),
				.Subresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
				.Flags = D3D12_TEXTURE_BARRIER_FLAG_NONE
			};
			textureBarriers.push_back(sourceBarrier);
			textureBarriers.push_back(destinationBarrier);
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
