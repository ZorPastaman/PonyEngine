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

import <cstdint>;
import <vector>;

import PonyBase.Utility.COM;

import PonyDebug.Log;

import :Buffer;
import :ICopyPipeline;
import :ISubSystemContext;
import :Pipeline;
import :Resource;
import :Texture;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 copy pipeline.
	class CopyPipeline final : public Pipeline, public ICopyPipeline
	{
	public:
		/// @brief Creates a copy pipeline.
		/// @param d3d12System Direct3D12 system context.
		/// @param commandQueuePriority Command queue priority.
		[[nodiscard("Pure constructor")]]
		CopyPipeline(ISubSystemContext& d3d12System, INT commandQueuePriority);
		CopyPipeline(const CopyPipeline&) = delete;
		CopyPipeline(CopyPipeline&&) = delete;

		virtual ~CopyPipeline() noexcept override = default;

		virtual void AddCopyTask(Buffer& source, Buffer& destination) override;
		virtual void AddCopyTask(Texture& source, Texture& destination) override;

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
			Resource* source; ///< Copy source.
			Resource* destination; ///< Copy destination.
		};

		/// @brief Adds buffer barriers that go before copying.
		void AddBufferBeforeBarriers();
		/// @brief Adds buffer barriers that go after copying.
		void AddBufferAfterBarriers();

		/// @brief Adds texture barriers that go before copying.
		void AddTextureBeforeBarriers();
		/// @brief Adds texture barriers that go after copying.
		void AddTextureAfterBarriers();

		/// @brief Populates copies.
		/// @param copyTasks Copy tasks to populate.
		void PopulateCopies(const std::vector<CopyTask>& copyTasks);

		ISubSystemContext* d3d12System; ///< Direct3D12 system context.

		std::vector<CopyTask> bufferCopyTasks; ///< Buffer copy tasks.
		std::vector<CopyTask> textureCopyTasks; ///< Texture copy tasks.
	};
}

namespace PonyEngine::Render::Direct3D12
{
	CopyPipeline::CopyPipeline(ISubSystemContext& d3d12System, const INT commandQueuePriority) :
		Pipeline(d3d12System, commandQueuePriority, D3D12_COMMAND_LIST_TYPE_COPY),
		d3d12System{&d3d12System}
	{
		bufferCopyTasks.reserve(64);
		textureCopyTasks.reserve(64);
	}

	void CopyPipeline::AddCopyTask(Buffer& source, Buffer& destination)
	{
		const auto copyTask = CopyTask
		{
			.source = &source,
			.destination = &destination
		};
		bufferCopyTasks.push_back(copyTask);
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Verbose, "Buffer copy task added. From: '0x{:X}', To: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(&source), reinterpret_cast<std::uintptr_t>(&destination));
	}

	void CopyPipeline::AddCopyTask(Texture& source, Texture& destination)
	{
		const auto copyTask = CopyTask
		{
			.source = &source,
			.destination = &destination
		};
		textureCopyTasks.push_back(copyTask);
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Verbose, "Texture copy task added. From: '0x{:X}', To: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(&source), reinterpret_cast<std::uintptr_t>(&destination));
	}

	void CopyPipeline::PopulateCommands()
	{
		ResetLists();
		AddBufferBeforeBarriers();
		AddTextureBeforeBarriers();
		PopulateBarriers();
		PopulateCopies(bufferCopyTasks);
		PopulateCopies(textureCopyTasks);
		AddBufferAfterBarriers();
		AddTextureAfterBarriers();
		PopulateBarriers();
		CloseLists();
	}

	void CopyPipeline::Execute()
	{
		ID3D12CommandList* const copyList = &CommandList();
		CommandQueue().ExecuteCommandLists(1u, &copyList);
	}

	void CopyPipeline::Clear() noexcept
	{
		bufferCopyTasks.clear();
		textureCopyTasks.clear();
	}

	void CopyPipeline::AddBufferBeforeBarriers()
	{
		for (const auto& [source, destination] : bufferCopyTasks)
		{
			const auto sourceBarrier = D3D12_BUFFER_BARRIER
			{
				.SyncBefore = D3D12_BARRIER_SYNC_NONE,
				.SyncAfter = D3D12_BARRIER_SYNC_COPY,
				.AccessBefore = D3D12_BARRIER_ACCESS_NO_ACCESS,
				.AccessAfter = D3D12_BARRIER_ACCESS_COPY_SOURCE,
				.pResource = &source->Data(),
				.Offset = 0UL,
				.Size = UINT64_MAX
			};
			const auto destinationBarrier = D3D12_BUFFER_BARRIER
			{
				.SyncBefore = D3D12_BARRIER_SYNC_NONE,
				.SyncAfter = D3D12_BARRIER_SYNC_COPY,
				.AccessBefore = D3D12_BARRIER_ACCESS_NO_ACCESS,
				.AccessAfter = D3D12_BARRIER_ACCESS_COPY_DEST,
				.pResource = &destination->Data(),
				.Offset = 0UL,
				.Size = UINT64_MAX
			};
			AddBarrier(sourceBarrier);
			AddBarrier(destinationBarrier);
		}
	}

	void CopyPipeline::AddBufferAfterBarriers()
	{
		for (const auto& [source, destination] : bufferCopyTasks)
		{
			const auto sourceBarrier = D3D12_BUFFER_BARRIER
			{
				.SyncBefore = D3D12_BARRIER_SYNC_COPY,
				.SyncAfter = D3D12_BARRIER_SYNC_NONE,
				.AccessBefore = D3D12_BARRIER_ACCESS_COPY_SOURCE,
				.AccessAfter = D3D12_BARRIER_ACCESS_NO_ACCESS,
				.pResource = &source->Data(),
				.Offset = 0UL,
				.Size = UINT64_MAX
			};
			const auto destinationBarrier = D3D12_BUFFER_BARRIER
			{
				.SyncBefore = D3D12_BARRIER_SYNC_COPY,
				.SyncAfter = D3D12_BARRIER_SYNC_NONE,
				.AccessBefore = D3D12_BARRIER_ACCESS_COPY_DEST,
				.AccessAfter = D3D12_BARRIER_ACCESS_NO_ACCESS,
				.pResource = &destination->Data(),
				.Offset = 0UL,
				.Size = UINT64_MAX
			};
			AddBarrier(sourceBarrier);
			AddBarrier(destinationBarrier);
		}
	}

	void CopyPipeline::AddTextureBeforeBarriers()
	{
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
				.pResource = &source->Data(),
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
				.pResource = &destination->Data(),
				.Subresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
				.Flags = D3D12_TEXTURE_BARRIER_FLAG_NONE
			};
			AddBarrier(sourceBarrier);
			AddBarrier(destinationBarrier);
		}
	}

	void CopyPipeline::AddTextureAfterBarriers()
	{
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
				.pResource = &source->Data(),
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
				.pResource = &destination->Data(),
				.Subresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
				.Flags = D3D12_TEXTURE_BARRIER_FLAG_NONE
			};
			AddBarrier(sourceBarrier);
			AddBarrier(destinationBarrier);
		}
	}

	void CopyPipeline::PopulateCopies(const std::vector<CopyTask>& copyTasks)
	{
		for (const auto& [source, destination] : copyTasks)
		{
			CommandList().CopyResource(&destination->Data(), &source->Data());
		}
	}
}
