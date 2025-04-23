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
import <unordered_set>;
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
			std::uint32_t sourceSubresource, std::uint32_t destinationSubresource, 
			std::uint32_t destinationX, std::uint32_t destinationY, std::uint32_t destinationZ, const std::optional<D3D12_BOX>& sourceBox) override;
		virtual void AddCopyTask(Buffer& source, Texture& destination,
			const D3D12_PLACED_SUBRESOURCE_FOOTPRINT& sourceFootprint, std::uint32_t destinationSubresource,
			std::uint32_t destinationX, std::uint32_t destinationY, std::uint32_t destinationZ) override;
		virtual void AddCopyTask(Texture& source, Buffer& destination, 
			std::uint32_t sourceSubresource, const D3D12_PLACED_SUBRESOURCE_FOOTPRINT& destinationFootprint, const std::optional<D3D12_BOX>& sourceBox) override;

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
		/// @brief Adds buffer barriers that go after copying.
		void AddBufferAfterBarriers();
		/// @brief Adds texture barriers that go before copying.
		void AddTextureBeforeBarriers();
		/// @brief Adds texture barriers that go after copying.
		void AddTextureAfterBarriers();

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

		std::unordered_set<Buffer*> bufferCopySources; ///< Buffer copy sources.
		std::unordered_set<Buffer*> bufferCopyDestinations; ///< Buffer copy destinations.
		std::unordered_set<Texture*> textureCopySources; ///< Texture copy sources.
		std::unordered_set<Texture*> textureCopyDestinations; ///< Texture copy destinations.
	};
}

namespace PonyEngine::Render::Direct3D12
{
	CopyPipeline::CopyPipeline(ISubSystemContext& d3d12System, const INT commandQueuePriority) :
		Pipeline(d3d12System, commandQueuePriority, D3D12_COMMAND_LIST_TYPE_COPY),
		d3d12System{&d3d12System}
	{
		bufferCopyTasks.reserve(64);
		bufferRegionCopyTasks.reserve(64);
		textureCopyTasks.reserve(64);
		textureRegionCopyTasks.reserve(64);

		bufferCopySources.reserve(128);
		bufferCopyDestinations.reserve(128);
		textureCopySources.reserve(128);
		textureCopyDestinations.reserve(128);
	}

	void CopyPipeline::AddCopyTask(Buffer& source, Buffer& destination)
	{
		bufferCopySources.insert(&source);
		bufferCopyDestinations.insert(&destination);
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
		bufferCopySources.insert(&source);
		bufferCopyDestinations.insert(&destination);
		const auto copyTask = BufferRegionCopyTask
		{
			.source = &source,
			.destination = &destination,
			.sourceOffset = sourceOffset,
			.destinationOffset = destinationOffset,
			.size = size
		};
		bufferRegionCopyTasks.push_back(copyTask);
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Verbose, "Buffer region copy task added. From: '0x{:X}', To: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(&source), reinterpret_cast<std::uintptr_t>(&destination));
	}

	void CopyPipeline::AddCopyTask(Texture& source, Texture& destination)
	{
		textureCopySources.insert(&source);
		textureCopyDestinations.insert(&destination);
		const auto copyTask = CopyTask
		{
			.source = &source,
			.destination = &destination
		};
		textureCopyTasks.push_back(copyTask);
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Verbose, "Texture copy task added. From: '0x{:X}', To: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(&source), reinterpret_cast<std::uintptr_t>(&destination));
	}

	void CopyPipeline::AddCopyTask(Texture& source, Texture& destination,
		const std::uint32_t sourceSubresource, const std::uint32_t destinationSubresource,
		const std::uint32_t destinationX, const std::uint32_t destinationY, const std::uint32_t destinationZ, const std::optional<D3D12_BOX>& sourceBox)
	{
		textureCopySources.insert(&source);
		textureCopyDestinations.insert(&destination);
		const auto copyTask = TextureRegionCopyTask
		{
			.source = D3D12_TEXTURE_COPY_LOCATION
			{
				.pResource = &source.Data(),
				.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX,
				.SubresourceIndex = sourceSubresource
			},
			.destination = D3D12_TEXTURE_COPY_LOCATION
			{
				.pResource = &destination.Data(),
				.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX,
				.SubresourceIndex = destinationSubresource
			},
			.destinationX = destinationX,
			.destinationY = destinationY,
			.destinationZ = destinationZ,
			.sourceBox = sourceBox
		};
		textureRegionCopyTasks.push_back(copyTask);
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Verbose, "Texture region copy task added. From: '0x{:X}', To: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(&source), reinterpret_cast<std::uintptr_t>(&destination));
	}

	void CopyPipeline::AddCopyTask(Buffer& source, Texture& destination,
		const D3D12_PLACED_SUBRESOURCE_FOOTPRINT& sourceFootprint, const std::uint32_t destinationSubresource,
		const std::uint32_t destinationX, const std::uint32_t destinationY, const std::uint32_t destinationZ)
	{
		bufferCopySources.insert(&source);
		textureCopyDestinations.insert(&destination);
		const auto copyTask = TextureRegionCopyTask
		{
			.source = D3D12_TEXTURE_COPY_LOCATION
			{
				.pResource = &source.Data(),
				.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT,
				.PlacedFootprint = sourceFootprint
			},
			.destination = D3D12_TEXTURE_COPY_LOCATION
			{
				.pResource = &destination.Data(),
				.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX,
				.SubresourceIndex = destinationSubresource
			},
			.destinationX = destinationX,
			.destinationY = destinationY,
			.destinationZ = destinationZ,
			.sourceBox = std::nullopt
		};
		textureRegionCopyTasks.push_back(copyTask);
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Verbose, "Texture region copy task added. Buffer to texture. From: '0x{:X}', To: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(&source), reinterpret_cast<std::uintptr_t>(&destination));
	}

	void CopyPipeline::AddCopyTask(Texture& source, Buffer& destination,
		const std::uint32_t sourceSubresource, const D3D12_PLACED_SUBRESOURCE_FOOTPRINT& destinationFootprint, 
		const std::optional<D3D12_BOX>& sourceBox)
	{
		textureCopySources.insert(&source);
		bufferCopyDestinations.insert(&destination);
		const auto copyTask = TextureRegionCopyTask
		{
			.source = D3D12_TEXTURE_COPY_LOCATION
			{
				.pResource = &source.Data(),
				.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX,
				.PlacedFootprint = sourceSubresource
			},
			.destination = D3D12_TEXTURE_COPY_LOCATION
			{
				.pResource = &destination.Data(),
				.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT,
				.PlacedFootprint = destinationFootprint
			},
			.destinationX = 0u,
			.destinationY = 0u,
			.destinationZ = 0u,
			.sourceBox = sourceBox
		};
		textureRegionCopyTasks.push_back(copyTask);
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Verbose, "Texture region copy task added. Texture to buffer. From: '0x{:X}', To: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(&source), reinterpret_cast<std::uintptr_t>(&destination));
	}

	void CopyPipeline::PopulateCommands()
	{
		ResetLists();
		AddBufferBeforeBarriers();
		AddTextureBeforeBarriers();
		PopulateBarriers();
		PopulateCopies(bufferCopyTasks);
		PopulateBufferRegionCopies();
		PopulateCopies(textureCopyTasks);
		PopulateTextureRegionCopies();
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
		bufferRegionCopyTasks.clear();
		textureCopyTasks.clear();
		textureRegionCopyTasks.clear();

		bufferCopySources.clear();
		bufferCopyDestinations.clear();
		textureCopySources.clear();
		textureCopyDestinations.clear();
	}

	void CopyPipeline::AddBufferBeforeBarriers()
	{
		for (Buffer* buffer : bufferCopySources)
		{
			const auto barrier = D3D12_BUFFER_BARRIER
			{
				.SyncBefore = D3D12_BARRIER_SYNC_NONE,
				.SyncAfter = D3D12_BARRIER_SYNC_COPY,
				.AccessBefore = D3D12_BARRIER_ACCESS_NO_ACCESS,
				.AccessAfter = D3D12_BARRIER_ACCESS_COPY_SOURCE,
				.pResource = &buffer->Data(),
				.Offset = 0UL,
				.Size = UINT64_MAX
			};
			AddBarrier(barrier);
		}

		for (Buffer* buffer : bufferCopyDestinations)
		{
			const auto barrier = D3D12_BUFFER_BARRIER
			{
				.SyncBefore = D3D12_BARRIER_SYNC_NONE,
				.SyncAfter = D3D12_BARRIER_SYNC_COPY,
				.AccessBefore = D3D12_BARRIER_ACCESS_NO_ACCESS,
				.AccessAfter = D3D12_BARRIER_ACCESS_COPY_DEST,
				.pResource = &buffer->Data(),
				.Offset = 0UL,
				.Size = UINT64_MAX
			};
			AddBarrier(barrier);
		}
	}

	void CopyPipeline::AddBufferAfterBarriers()
	{
		for (Buffer* buffer : bufferCopySources)
		{
			const auto barrier = D3D12_BUFFER_BARRIER
			{
				.SyncBefore = D3D12_BARRIER_SYNC_COPY,
				.SyncAfter = D3D12_BARRIER_SYNC_NONE,
				.AccessBefore = D3D12_BARRIER_ACCESS_COPY_SOURCE,
				.AccessAfter = D3D12_BARRIER_ACCESS_NO_ACCESS,
				.pResource = &buffer->Data(),
				.Offset = 0UL,
				.Size = UINT64_MAX
			};
			AddBarrier(barrier);
		}

		for (Buffer* buffer : bufferCopyDestinations)
		{
			const auto barrier = D3D12_BUFFER_BARRIER
			{
				.SyncBefore = D3D12_BARRIER_SYNC_COPY,
				.SyncAfter = D3D12_BARRIER_SYNC_NONE,
				.AccessBefore = D3D12_BARRIER_ACCESS_COPY_DEST,
				.AccessAfter = D3D12_BARRIER_ACCESS_NO_ACCESS,
				.pResource = &buffer->Data(),
				.Offset = 0UL,
				.Size = UINT64_MAX
			};
			AddBarrier(barrier);
		}
	}

	void CopyPipeline::AddTextureBeforeBarriers()
	{
		for (Texture* texture : textureCopySources)
		{
			const auto barrier = D3D12_TEXTURE_BARRIER
			{
				.SyncBefore = D3D12_BARRIER_SYNC_NONE,
				.SyncAfter = D3D12_BARRIER_SYNC_COPY,
				.AccessBefore = D3D12_BARRIER_ACCESS_NO_ACCESS,
				.AccessAfter = D3D12_BARRIER_ACCESS_COPY_SOURCE,
				.LayoutBefore = D3D12_BARRIER_LAYOUT_COMMON,
				.LayoutAfter = D3D12_BARRIER_LAYOUT_COPY_SOURCE,
				.pResource = &texture->Data(),
				.Subresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
				.Flags = D3D12_TEXTURE_BARRIER_FLAG_NONE
			};
			AddBarrier(barrier);
		}

		for (Texture* texture : textureCopyDestinations)
		{
			const auto barrier = D3D12_TEXTURE_BARRIER
			{
				.SyncBefore = D3D12_BARRIER_SYNC_NONE,
				.SyncAfter = D3D12_BARRIER_SYNC_COPY,
				.AccessBefore = D3D12_BARRIER_ACCESS_NO_ACCESS,
				.AccessAfter = D3D12_BARRIER_ACCESS_COPY_DEST,
				.LayoutBefore = D3D12_BARRIER_LAYOUT_COMMON,
				.LayoutAfter = D3D12_BARRIER_LAYOUT_COPY_DEST,
				.pResource = &texture->Data(),
				.Subresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
				.Flags = D3D12_TEXTURE_BARRIER_FLAG_NONE
			};
			AddBarrier(barrier);
		}
	}

	void CopyPipeline::AddTextureAfterBarriers()
	{
		for (Texture* texture : textureCopySources)
		{
			const auto barrier = D3D12_TEXTURE_BARRIER
			{
				.SyncBefore = D3D12_BARRIER_SYNC_COPY,
				.SyncAfter = D3D12_BARRIER_SYNC_NONE,
				.AccessBefore = D3D12_BARRIER_ACCESS_COPY_SOURCE,
				.AccessAfter = D3D12_BARRIER_ACCESS_NO_ACCESS,
				.LayoutBefore = D3D12_BARRIER_LAYOUT_COPY_SOURCE,
				.LayoutAfter = D3D12_BARRIER_LAYOUT_COMMON,
				.pResource = &texture->Data(),
				.Subresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
				.Flags = D3D12_TEXTURE_BARRIER_FLAG_NONE
			};
			AddBarrier(barrier);
		}

		for (Texture* texture : textureCopyDestinations)
		{
			const auto barrier = D3D12_TEXTURE_BARRIER
			{
				.SyncBefore = D3D12_BARRIER_SYNC_COPY,
				.SyncAfter = D3D12_BARRIER_SYNC_NONE,
				.AccessBefore = D3D12_BARRIER_ACCESS_COPY_DEST,
				.AccessAfter = D3D12_BARRIER_ACCESS_NO_ACCESS,
				.LayoutBefore = D3D12_BARRIER_LAYOUT_COPY_DEST,
				.LayoutAfter = D3D12_BARRIER_LAYOUT_COMMON,
				.pResource = &texture->Data(),
				.Subresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
				.Flags = D3D12_TEXTURE_BARRIER_FLAG_NONE
			};
			AddBarrier(barrier);
		}
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
