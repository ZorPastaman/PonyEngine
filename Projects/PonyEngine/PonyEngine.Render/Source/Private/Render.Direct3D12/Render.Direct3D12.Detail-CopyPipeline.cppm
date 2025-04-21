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
import <optional>;
import <variant>;
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
		virtual void AddCopyTask(Buffer& source, Buffer& destination, std::uint64_t sourceOffset, std::uint64_t destinationOffset, std::uint64_t size) override;

		virtual void AddCopyTask(Texture& source, Texture& destination) override;
		virtual void AddCopyTask(Texture& source, Texture& destination,
			const std::variant<D3D12_PLACED_SUBRESOURCE_FOOTPRINT, UINT>& sourceInfo, const std::variant<D3D12_PLACED_SUBRESOURCE_FOOTPRINT, UINT>& destinationInfo,
			std::uint32_t destinationX, std::uint32_t destinationY, std::uint32_t destinationZ, const std::optional<D3D12_BOX>& sourceBox) override;

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

		/// @brief Buffer region copy task.
		struct BufferRegionCopyTask final
		{
			Buffer* source; ///< Source.
			Buffer* destination; ///< Destination.
			std::uint64_t sourceOffset; ///< Source offset.
			std::uint64_t destinationOffset; ///< Destination offset.
			std::uint64_t size; ///< Copy size.
		};

		/// @brief Texture region copy task.
		struct TextureRegionCopyTask final
		{
			D3D12_TEXTURE_COPY_LOCATION source; ///< Source location.
			D3D12_TEXTURE_COPY_LOCATION destination; ///< Destination location.
			std::uint32_t destinationX; ///< Destination x-coordinate.
			std::uint32_t destinationY; ///< Destination y-coordinate.
			std::uint32_t destinationZ; ///< Destination z-coordinate.
			std::optional<D3D12_BOX> sourceBox; ///< Source box.
		};

		/// @brief Adds buffer barriers that go before copying.
		void AddBufferBeforeBarriers();
		/// @brief Adds buffer region barriers that go before copying.
		void AddBufferRegionBeforeBarriers();
		/// @brief Adds buffer barriers that go before copying.
		/// @param source Source.
		/// @param destination Destination.
		void AddBufferBeforeBarriers(ID3D12Resource& source, ID3D12Resource& destination);
		/// @brief Adds buffer barriers that go after copying.
		void AddBufferAfterBarriers();
		/// @brief Adds buffer region barriers that go after copying.
		void AddBufferRegionAfterBarriers();
		/// @brief Adds buffer barriers that go after copying.
		/// @param source Source.
		/// @param destination Destination.
		void AddBufferAfterBarriers(ID3D12Resource& source, ID3D12Resource& destination);

		/// @brief Adds texture barriers that go before copying.
		void AddTextureBeforeBarriers();
		/// @brief Adds texture region barriers that go before copying.
		void AddTextureRegionBeforeBarriers();
		/// @brief Adds texture barriers that go before copying.
		/// @param source Source.
		/// @param destination Destination.
		void AddTextureBeforeBarriers(ID3D12Resource& source, ID3D12Resource& destination);
		/// @brief Adds texture barriers that go after copying.
		void AddTextureAfterBarriers();
		/// @brief Adds texture region barriers that go after copying.
		void AddTextureRegionAfterBarriers();
		/// @brief Adds texture barriers that go after copying.
		/// @param source Source.
		/// @param destination Destination.
		void AddTextureAfterBarriers(ID3D12Resource& source, ID3D12Resource& destination);

		/// @brief Populates copies.
		/// @param copyTasks Copy tasks to populate.
		void PopulateCopies(const std::vector<CopyTask>& copyTasks);
		/// @brief Populates buffer region copies.
		void PopulateBufferRegionCopies();
		/// @brief Populates texture region copies.
		void PopulateTextureRegionCopies();

		ISubSystemContext* d3d12System; ///< Direct3D12 system context.

		std::vector<CopyTask> bufferCopyTasks; ///< Buffer copy tasks.
		std::vector<BufferRegionCopyTask> bufferRegionCopyTasks; ///< Buffer region copy tasks.
		std::vector<CopyTask> textureCopyTasks; ///< Texture copy tasks.
		std::vector<TextureRegionCopyTask> textureRegionCopyTasks; ///< Texture region copy tasks.
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

	void CopyPipeline::AddCopyTask(Buffer& source, Buffer& destination, const std::uint64_t sourceOffset, const std::uint64_t destinationOffset, const std::uint64_t size)
	{
		const auto copyTask = BufferRegionCopyTask
		{
			.source = &source,
			.destination = &destination,
			.sourceOffset = sourceOffset,
			.destinationOffset = destinationOffset,
			.size = size
		};
		bufferRegionCopyTasks.push_back(copyTask);
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

	void CopyPipeline::AddCopyTask(Texture& source, Texture& destination,
		const std::variant<D3D12_PLACED_SUBRESOURCE_FOOTPRINT, UINT>& sourceInfo, const std::variant<D3D12_PLACED_SUBRESOURCE_FOOTPRINT, UINT>& destinationInfo, 
		const std::uint32_t destinationX, const std::uint32_t destinationY, const std::uint32_t destinationZ, const std::optional<D3D12_BOX>& sourceBox)
	{
		auto sourceLocation = D3D12_TEXTURE_COPY_LOCATION{.pResource = &source.Data()};
		if (sourceInfo.index() == 0)
		{
			sourceLocation.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
			sourceLocation.PlacedFootprint = std::get<0>(sourceInfo);
		}
		else
		{
			sourceLocation.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
			sourceLocation.SubresourceIndex = std::get<1>(sourceInfo);
		}

		auto destinationLocation = D3D12_TEXTURE_COPY_LOCATION{.pResource = &destination.Data()};
		if (destinationInfo.index() == 0)
		{
			destinationLocation.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
			destinationLocation.PlacedFootprint = std::get<0>(destinationInfo);
		}
		else
		{
			destinationLocation.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
			destinationLocation.SubresourceIndex = std::get<1>(destinationInfo);
		}

		const auto copyTask = TextureRegionCopyTask
		{
			.source = sourceLocation,
			.destination = destinationLocation,
			.destinationX = destinationX,
			.destinationY = destinationY,
			.destinationZ = destinationZ,
			.sourceBox = sourceBox
		};
		textureRegionCopyTasks.push_back(copyTask);
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Verbose, "Texture copy task added. From: '0x{:X}', To: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(&source), reinterpret_cast<std::uintptr_t>(&destination));
	}

	void CopyPipeline::PopulateCommands()
	{
		ResetLists();
		AddBufferBeforeBarriers();
		AddBufferRegionBeforeBarriers();
		AddTextureBeforeBarriers();
		AddTextureRegionBeforeBarriers();
		PopulateBarriers();
		PopulateCopies(bufferCopyTasks);
		PopulateBufferRegionCopies();
		PopulateCopies(textureCopyTasks);
		PopulateTextureRegionCopies();
		AddBufferAfterBarriers();
		AddBufferRegionAfterBarriers();
		AddTextureAfterBarriers();
		AddTextureRegionAfterBarriers();
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
		bufferRegionCopyTasks.clear();
		textureCopyTasks.clear();
		textureRegionCopyTasks.clear();
	}

	void CopyPipeline::AddBufferBeforeBarriers()
	{
		for (const auto& [source, destination] : bufferCopyTasks)
		{
			AddBufferBeforeBarriers(source->Data(), destination->Data());
		}
	}

	void CopyPipeline::AddBufferRegionBeforeBarriers()
	{
		for (const BufferRegionCopyTask& copyTask : bufferRegionCopyTasks)
		{
			AddBufferBeforeBarriers(copyTask.source->Data(), copyTask.destination->Data());
		}
	}

	void CopyPipeline::AddBufferBeforeBarriers(ID3D12Resource& source, ID3D12Resource& destination)
	{
		const auto sourceBarrier = D3D12_BUFFER_BARRIER
		{
			.SyncBefore = D3D12_BARRIER_SYNC_NONE,
			.SyncAfter = D3D12_BARRIER_SYNC_COPY,
			.AccessBefore = D3D12_BARRIER_ACCESS_NO_ACCESS,
			.AccessAfter = D3D12_BARRIER_ACCESS_COPY_SOURCE,
			.pResource = &source,
			.Offset = 0UL,
			.Size = UINT64_MAX
		};
		const auto destinationBarrier = D3D12_BUFFER_BARRIER
		{
			.SyncBefore = D3D12_BARRIER_SYNC_NONE,
			.SyncAfter = D3D12_BARRIER_SYNC_COPY,
			.AccessBefore = D3D12_BARRIER_ACCESS_NO_ACCESS,
			.AccessAfter = D3D12_BARRIER_ACCESS_COPY_DEST,
			.pResource = &destination,
			.Offset = 0UL,
			.Size = UINT64_MAX
		};
		AddBarrier(sourceBarrier);
		AddBarrier(destinationBarrier);
	}

	void CopyPipeline::AddBufferAfterBarriers()
	{
		for (const auto& [source, destination] : bufferCopyTasks)
		{
			AddBufferAfterBarriers(source->Data(), destination->Data());
		}
	}

	void CopyPipeline::AddBufferRegionAfterBarriers()
	{
		for (const BufferRegionCopyTask& copyTask : bufferRegionCopyTasks)
		{
			AddBufferAfterBarriers(copyTask.source->Data(), copyTask.destination->Data());
		}
	}

	void CopyPipeline::AddBufferAfterBarriers(ID3D12Resource& source, ID3D12Resource& destination)
	{
		const auto sourceBarrier = D3D12_BUFFER_BARRIER
		{
			.SyncBefore = D3D12_BARRIER_SYNC_COPY,
			.SyncAfter = D3D12_BARRIER_SYNC_NONE,
			.AccessBefore = D3D12_BARRIER_ACCESS_COPY_SOURCE,
			.AccessAfter = D3D12_BARRIER_ACCESS_NO_ACCESS,
			.pResource = &source,
			.Offset = 0UL,
			.Size = UINT64_MAX
		};
		const auto destinationBarrier = D3D12_BUFFER_BARRIER
		{
			.SyncBefore = D3D12_BARRIER_SYNC_COPY,
			.SyncAfter = D3D12_BARRIER_SYNC_NONE,
			.AccessBefore = D3D12_BARRIER_ACCESS_COPY_DEST,
			.AccessAfter = D3D12_BARRIER_ACCESS_NO_ACCESS,
			.pResource = &destination,
			.Offset = 0UL,
			.Size = UINT64_MAX
		};
		AddBarrier(sourceBarrier);
		AddBarrier(destinationBarrier);
	}

	void CopyPipeline::AddTextureBeforeBarriers()
	{
		for (const auto& [source, destination] : textureCopyTasks)
		{
			AddTextureBeforeBarriers(source->Data(), destination->Data());
		}
	}

	void CopyPipeline::AddTextureRegionBeforeBarriers()
	{
		for (const TextureRegionCopyTask& copyTask : textureRegionCopyTasks)
		{
			AddTextureBeforeBarriers(*copyTask.source.pResource, *copyTask.destination.pResource);
		}
	}

	void CopyPipeline::AddTextureBeforeBarriers(ID3D12Resource& source, ID3D12Resource& destination)
	{
		const auto sourceBarrier = D3D12_TEXTURE_BARRIER
		{
			.SyncBefore = D3D12_BARRIER_SYNC_NONE,
			.SyncAfter = D3D12_BARRIER_SYNC_COPY,
			.AccessBefore = D3D12_BARRIER_ACCESS_NO_ACCESS,
			.AccessAfter = D3D12_BARRIER_ACCESS_COPY_SOURCE,
			.LayoutBefore = D3D12_BARRIER_LAYOUT_COMMON,
			.LayoutAfter = D3D12_BARRIER_LAYOUT_COPY_SOURCE,
			.pResource = &source,
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
			.pResource = &destination,
			.Subresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
			.Flags = D3D12_TEXTURE_BARRIER_FLAG_NONE
		};
		AddBarrier(sourceBarrier);
		AddBarrier(destinationBarrier);
	}

	void CopyPipeline::AddTextureAfterBarriers()
	{
		for (const auto& [source, destination] : textureCopyTasks)
		{
			AddTextureAfterBarriers(source->Data(), destination->Data());
		}
	}

	void CopyPipeline::AddTextureRegionAfterBarriers()
	{
		for (const TextureRegionCopyTask& copyTask : textureRegionCopyTasks)
		{
			AddTextureAfterBarriers(*copyTask.source.pResource, *copyTask.destination.pResource);
		}
	}

	void CopyPipeline::AddTextureAfterBarriers(ID3D12Resource& source, ID3D12Resource& destination)
	{
		const auto sourceBarrier = D3D12_TEXTURE_BARRIER
		{
			.SyncBefore = D3D12_BARRIER_SYNC_COPY,
			.SyncAfter = D3D12_BARRIER_SYNC_NONE,
			.AccessBefore = D3D12_BARRIER_ACCESS_COPY_SOURCE,
			.AccessAfter = D3D12_BARRIER_ACCESS_NO_ACCESS,
			.LayoutBefore = D3D12_BARRIER_LAYOUT_COPY_SOURCE,
			.LayoutAfter = D3D12_BARRIER_LAYOUT_COMMON,
			.pResource = &source,
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
			.pResource = &destination,
			.Subresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
			.Flags = D3D12_TEXTURE_BARRIER_FLAG_NONE
		};
		AddBarrier(sourceBarrier);
		AddBarrier(destinationBarrier);
	}

	void CopyPipeline::PopulateCopies(const std::vector<CopyTask>& copyTasks)
	{
		for (const auto& [source, destination] : copyTasks)
		{
			CommandList().CopyResource(&destination->Data(), &source->Data());
		}
	}

	void CopyPipeline::PopulateBufferRegionCopies()
	{
		for (const BufferRegionCopyTask& copyTask : bufferRegionCopyTasks)
		{
			CommandList().CopyBufferRegion(&copyTask.destination->Data(), copyTask.destinationOffset, &copyTask.source->Data(), copyTask.sourceOffset, copyTask.size);
		}
	}

	void CopyPipeline::PopulateTextureRegionCopies()
	{
		for (const TextureRegionCopyTask& copyTask : textureRegionCopyTasks)
		{
			CommandList().CopyTextureRegion(&copyTask.destination, copyTask.destinationX, copyTask.destinationY, copyTask.destinationZ, &copyTask.source, copyTask.sourceBox ? &copyTask.sourceBox.value() : nullptr);
		}
	}
}
