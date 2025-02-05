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
import :Pipeline;
import :Resource;
import :Texture;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 copy pipeline.
	class CopyPipeline final : public Pipeline, public ICopyPipeline
	{
	public:
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
		enum class ResourceType : std::uint8_t
		{
			Buffer,
			Texture
		};

		/// @brief Copy task.
		struct CopyTask final
		{
			Resource* source; ///< Copy source.
			Resource* destination; ///< Copy destination.
			ResourceType resourceType;
		};

		/// @brief Populates begin to copy barriers.
		void PushBeginToCopyBarriers();
		/// @brief Populates copy to end barriers.
		void PushCopyToEndBarriers();

		/// @brief Populates copies.
		void PopulateCopies();

		void AddBufferBeforeBarriers(const CopyTask& copyTask);
		void AddBufferAfterBarriers(const CopyTask& copyTask);

		void AddTextureBeforeBarriers(const CopyTask& copyTask);
		void AddTextureAfterBarriers(const CopyTask& copyTask);

		std::vector<CopyTask> copyTasks; ///< Copy tasks.
	};
}

namespace PonyEngine::Render::Direct3D12
{
	CopyPipeline::CopyPipeline(ISubSystemContext& d3d12System, const INT commandQueuePriority) :
		Pipeline(d3d12System, commandQueuePriority, D3D12_COMMAND_LIST_TYPE_COPY)
	{
	}

	void CopyPipeline::AddCopyTask(Buffer& source, Buffer& destination)
	{
		const auto copyTask = CopyTask
		{
			.source = &source,
			.destination = &destination,
			.resourceType = ResourceType::Buffer
		};
		copyTasks.push_back(copyTask);
	}

	void CopyPipeline::AddCopyTask(Texture& source, Texture& destination)
	{
		const auto copyTask = CopyTask
		{
			.source = &source,
			.destination = &destination,
			.resourceType = ResourceType::Texture
		};
		copyTasks.push_back(copyTask);
	}

	void CopyPipeline::PopulateCommands()
	{
		ResetLists();
		PushBeginToCopyBarriers();
		PopulateBarriers();
		PopulateCopies();
		PushCopyToEndBarriers();
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
		copyTasks.clear();
	}

	void CopyPipeline::PushBeginToCopyBarriers()
	{
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
	}

	void CopyPipeline::PopulateCopies()
	{
		for (const CopyTask& copyTask : copyTasks)
		{
			CommandList().CopyResource(&copyTask.destination->Data(), &copyTask.source->Data());
		}
	}

	void CopyPipeline::PushCopyToEndBarriers()
	{
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
		AddBarrier(sourceBarrier);
		AddBarrier(destinationBarrier);
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
		AddBarrier(sourceBarrier);
		AddBarrier(destinationBarrier);
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
		AddBarrier(sourceBarrier);
		AddBarrier(destinationBarrier);
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
		AddBarrier(sourceBarrier);
		AddBarrier(destinationBarrier);
	}
}
