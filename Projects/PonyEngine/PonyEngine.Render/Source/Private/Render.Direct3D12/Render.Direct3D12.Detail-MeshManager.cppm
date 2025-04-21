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

export module PonyEngine.Render.Direct3D12.Detail:MeshManager;

import <algorithm>;
import <cstddef>;
import <cstdint>;
import <memory>;
import <set>;
import <span>;
import <stdexcept>;
import <string>;
import <utility>;
import <vector>;

import PonyBase.Container;

import PonyDebug.Log;

import :ICopyPipeline;
import :IGraphicsPipeline;
import :IMeshManager;
import :ISubSystemContext;
import :Mesh;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 mesh manager.
	class MeshManager final : public IMeshManager
	{
	public:
		/// @brief Creates a @p MeshManager.
		/// @param d3d12System 
		[[nodiscard("Pure constructor")]]
		explicit MeshManager(ISubSystemContext& d3d12System);
		MeshManager(const MeshManager&) = delete;
		MeshManager(MeshManager&&) = delete;

		~MeshManager() noexcept = default;

		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<Mesh> CreateMesh(const std::shared_ptr<const Render::Mesh>& mesh) override;

		/// @brief Ticks the mesh manager.
		void Tick();

		/// @brief Clears the data.
		void Clear() noexcept;
		/// @brief Cleans out of dead meshes.
		void Clean() noexcept;

		MeshManager& operator =(const MeshManager&) = delete;
		MeshManager& operator =(MeshManager&&) = delete;

	private:
		/// @brief Mesh observer.
		class MeshObserver final : public IMeshObserver
		{
		public:
			/// @brief Creates a mesh observer with all fields false.
			[[nodiscard("Pure constructor")]]
			MeshObserver() noexcept;
			MeshObserver(const MeshObserver&) = delete;
			MeshObserver(MeshObserver&&) = delete;

			~MeshObserver() noexcept = default;

			virtual void OnMeshChanged() noexcept override;
			virtual void OnBufferChanged(std::uint32_t dataIndex, std::uint32_t bufferIndex) noexcept override;
			virtual void OnThreadGroupCountsChanged() noexcept override;
			virtual void OnBoundingBoxChanged() noexcept override;
			virtual void OnNameChanged() noexcept override;

			/// @brief Gets if the mesh changed.
			/// @return @a True if it's changed; @a false otherwise.
			[[nodiscard("Pure function")]]
			bool MeshChanged() const noexcept;
			/// @brief Gets changed buffers.
			/// @return Changed buffers. <data index, buffer index>.
			[[nodiscard("Pure function")]]
			const std::set<std::pair<std::uint32_t, std::uint32_t>>& ChangedBuffers() const noexcept;
			/// @brief Gets if the additional data changed.
			/// @return @a True if the additional data changed; @a false otherwise.
			[[nodiscard("Pure function")]]
			bool AdditionalDataChanged() const noexcept;
			/// @brief Gets if the name changed.
			/// @return @a True if the name changed; @a false otherwise.
			[[nodiscard("Pure function")]]
			bool NameChanged() const noexcept;

			/// @brief Sets all the fields to false.
			void Reset() noexcept;

			MeshObserver& operator =(const MeshObserver&) = delete;
			MeshObserver& operator =(MeshObserver&&) = delete;

		private:
			std::set<std::pair<std::uint32_t, std::uint32_t>> changedBuffers; ///< Changed buffers.
			bool meshChanged; ///< Is the mesh changed?
			bool additionalDataChanged; ///< Is the additional data changed?
			bool nameChanged; ///< Is the mesh name changed?
		};

		/// @brief Buffer info. Used to sort mesh buffers.
		struct BufferInfo final
		{
			const PonyBase::Container::Buffer* buffer; ///< Mesh buffer.
			std::uint64_t offset; ///< Offset in element indices.
			std::uint32_t dataTypeIndex; ///< Data type index.
			std::uint32_t bufferIndex; ///< Buffer index.
		};

		/// @brief Calculates a buffer order.
		/// @param source Mesh.
		/// @return Buffer infos in the order they must appear in a render buffer.
		[[nodiscard("Pure function")]]
		static std::vector<BufferInfo> CalculateBufferOrder(const Render::Mesh& source);
		/// @brief Calculates a buffer size by the buffer infos.
		/// @param bufferInfos Buffer infos.
		/// @return Required size.
		[[nodiscard("Pure function")]]
		static std::uint64_t CalculateBufferSize(std::span<const BufferInfo> bufferInfos) noexcept;

		/// @brief Updates the mesh.
		/// @param mesh Mesh to update.
		/// @param source Mesh source.
		/// @param observer Mesh observer.
		void UpdateMesh(Mesh& mesh, const Render::Mesh& source, const MeshObserver& observer) const;
		/// @brief Updates the mesh buffers.
		/// @param mesh Mesh to update.
		/// @param source Mesh source.
		/// @param observer Mesh observer.
		void UpdateBuffers(Mesh& mesh, const Render::Mesh& source, const MeshObserver& observer);
		/// @brief Updates the whole mesh buffer.
		/// @param mesh Mesh to update.
		/// @param source Mesh source.
		void UpdateBuffer(Mesh& mesh, const Render::Mesh& source);
		/// @brief Updates a mesh buffer.
		/// @param mesh Mesh to update.
		/// @param source Mesh source.
		/// @param dataIndex Data index.
		/// @param bufferIndex Buffer index.
		void UpdateBuffer(Mesh& mesh, const Render::Mesh& source, std::uint32_t dataIndex, std::uint32_t bufferIndex);
		/// @brief Updates the mesh additional data.
		/// @param mesh Mesh to update.
		/// @param source Mesh source.
		/// @param observer Mesh observer.
		static void UpdateAdditionalData(Mesh& mesh, const Render::Mesh& source, const MeshObserver& observer) noexcept;
		/// @brief Updates the mesh name.
		/// @param mesh Mesh to update.
		/// @param source Mesh source.
		/// @param observer Mesh observer.
		static void UpdateName(Mesh& mesh, const Render::Mesh& source, const MeshObserver& observer);

		/// @brief Adds a new mesh.
		/// @param mesh Mesh.
		/// @param source Mesh source.
		void Add(const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<const Render::Mesh>& source);
		/// @brief Removes a mesh.
		/// @param index Mesh index.
		void Remove(std::size_t index) noexcept;

		ISubSystemContext* d3d12System; ///< Direct3D12 system context.

		std::vector<std::shared_ptr<Mesh>> meshes; ///< Meshes.
		std::vector<std::shared_ptr<const Render::Mesh>> sources; ///< Mesh sources.
		std::vector<std::unique_ptr<MeshObserver>> observers; ///< Mesh observers.

		std::vector<std::shared_ptr<Buffer>> uploadBuffers; ///< Upload buffers.
	};
}

namespace PonyEngine::Render::Direct3D12
{
	MeshManager::MeshObserver::MeshObserver() noexcept :
		meshChanged{true},
		additionalDataChanged{true},
		nameChanged{true}
	{
	}

	void MeshManager::MeshObserver::OnMeshChanged() noexcept
	{
		changedBuffers.clear();
		meshChanged = true;
	}

	void MeshManager::MeshObserver::OnBufferChanged(std::uint32_t dataIndex, std::uint32_t bufferIndex) noexcept
	{
		if (!meshChanged)
		{
			changedBuffers.insert(std::pair(dataIndex, bufferIndex));
		}
	}

	void MeshManager::MeshObserver::OnThreadGroupCountsChanged() noexcept
	{
		additionalDataChanged = true;
	}

	void MeshManager::MeshObserver::OnBoundingBoxChanged() noexcept
	{
		additionalDataChanged = true;
	}

	void MeshManager::MeshObserver::OnNameChanged() noexcept
	{
		nameChanged = true;
	}

	bool MeshManager::MeshObserver::MeshChanged() const noexcept
	{
		return nameChanged;
	}

	const std::set<std::pair<std::uint32_t, std::uint32_t>>& MeshManager::MeshObserver::ChangedBuffers() const noexcept
	{
		return changedBuffers;
	}

	bool MeshManager::MeshObserver::AdditionalDataChanged() const noexcept
	{
		return additionalDataChanged;
	}

	bool MeshManager::MeshObserver::NameChanged() const noexcept
	{
		return nameChanged;
	}

	void MeshManager::MeshObserver::Reset() noexcept
	{
		changedBuffers.clear();
		meshChanged = false;
		additionalDataChanged = false;
		nameChanged = false;
	}

	MeshManager::MeshManager(ISubSystemContext& d3d12System) :
		d3d12System{&d3d12System}
	{
	}

	std::shared_ptr<Mesh> MeshManager::CreateMesh(const std::shared_ptr<const Render::Mesh>& mesh)
	{
		if (!mesh) [[unlikely]]
		{
			throw std::invalid_argument("Mesh is nullptr.");
		}

		for (std::size_t i = 0; i < sources.size(); ++i)
		{
			if (sources[i].get() == mesh.get())
			{
				PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Mesh reused at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(meshes[i].get()));
				return meshes[i];
			}
		}

		const auto renderMesh = std::make_shared<Mesh>();
		Add(renderMesh, mesh);
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Mesh created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(renderMesh.get()));

		return renderMesh;
	}

	void MeshManager::Tick()
	{
		for (std::size_t i = 0; i < meshes.size(); ++i)
		{
			Mesh& mesh = *meshes[i];
			const Render::Mesh& source = *sources[i];
			MeshObserver& observer = *observers[i];

			UpdateMesh(mesh, source, observer);
			UpdateBuffers(mesh, source, observer);
			UpdateAdditionalData(mesh, source, observer);
			UpdateName(mesh, source, observer);

			observer.Reset();
		}
	}

	void MeshManager::Clear() noexcept
	{
		uploadBuffers.clear();
	}

	void MeshManager::Clean() noexcept
	{
		for (std::size_t i = meshes.size(); i-- > 0; )
		{
			if (meshes[i].use_count() <= 1L)
			{
				PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Destroy mesh at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(meshes[i].get()));
				Remove(i);
				PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Mesh destroyed.");
			}
		}
	}

	std::vector<MeshManager::BufferInfo> MeshManager::CalculateBufferOrder(const Render::Mesh& source)
	{
		std::vector<BufferInfo> answer;
		answer.reserve(source.BufferCount());
		for (std::uint32_t dataTypeIndex = 0u; dataTypeIndex < source.DataTypeCount(); ++dataTypeIndex)
		{
			for (std::uint32_t bufferIndex = 0u; bufferIndex < source.BufferCount(dataTypeIndex); ++bufferIndex)
			{
				answer.push_back(BufferInfo{.buffer = &source.Buffer(dataTypeIndex, bufferIndex), .offset = 0ULL, .dataTypeIndex = dataTypeIndex, .bufferIndex = bufferIndex});
			}
		}

		std::ranges::sort(answer, [](const BufferInfo& left, const BufferInfo& right) { return left.buffer->Stride() > right.buffer->Stride(); });

		for (std::size_t i = 1; i < answer.size(); ++i)
		{
			const BufferInfo& prev = answer[i - 1];
			const std::uint64_t prevEnd = prev.offset * prev.buffer->Stride() + static_cast<std::uint64_t>(prev.buffer->Size());
			answer[i].offset = PonyMath::Core::DivideCeil(prevEnd, static_cast<std::uint64_t>(answer[i].buffer->Stride()));
		}

		return answer;
	}

	std::uint64_t MeshManager::CalculateBufferSize(const std::span<const BufferInfo> bufferInfos) noexcept
	{
		if (bufferInfos.size() == 0)
		{
			return 1ULL;
		}

		const BufferInfo& last = bufferInfos[bufferInfos.size() - 1];

		return last.offset * last.buffer->Stride() + last.buffer->Size();
	}

	void MeshManager::UpdateMesh(Mesh& mesh, const Render::Mesh& source, const MeshObserver& observer) const
	{
		if (!observer.MeshChanged()) [[likely]]
		{
			return;
		}

		const std::vector<BufferInfo> bufferInfos = CalculateBufferOrder(source);
		std::shared_ptr<Buffer> buffer = d3d12System->ResourceManager().CreateBuffer(CalculateBufferSize(bufferInfos), HeapType::Default);
		std::shared_ptr<DescriptorHeap> heap = d3d12System->DescriptorHeapManager().CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, static_cast<std::uint32_t>(bufferInfos.size()), false);

		std::vector<std::string> dataTypes;
		std::vector<std::vector<std::uint64_t>> bufferOffsets;
		std::vector<std::uint32_t> heapIndices;
		dataTypes.reserve(source.DataTypeCount());
		bufferOffsets.reserve(source.DataTypeCount());
		heapIndices.reserve(source.DataTypeCount());
		for (std::uint32_t i = 0u; i < source.DataTypeCount(); ++i)
		{
			bufferOffsets.push_back(std::vector<std::uint64_t>(source.BufferCount(i)));
		}

		for (const BufferInfo& bufferInfo : bufferInfos)
		{
			bufferOffsets[bufferInfo.dataTypeIndex][bufferInfo.bufferIndex] = bufferInfo.offset;
		}

		for (std::uint32_t dataIndex = 0u, heapIndex = 0u; dataIndex < source.DataTypeCount(); ++dataIndex)
		{
			dataTypes.push_back(std::string(source.DataType(dataIndex)));
			heapIndices.push_back(heapIndex);

			for (std::uint32_t bufferIndex = 0u; bufferIndex < source.BufferCount(dataIndex); ++bufferIndex, ++heapIndex)
			{
				const PonyBase::Container::Buffer& sourceBuffer = source.Buffer(dataIndex, bufferIndex);
				const auto srvDesc = D3D12_SHADER_RESOURCE_VIEW_DESC
				{
					.Format = DXGI_FORMAT_UNKNOWN,
					.ViewDimension = D3D12_SRV_DIMENSION_BUFFER,
					.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING,
					.Buffer = D3D12_BUFFER_SRV
					{
						.FirstElement = bufferOffsets[dataIndex][bufferIndex],
						.NumElements = static_cast<UINT>(sourceBuffer.Count()),
						.StructureByteStride = static_cast<UINT>(sourceBuffer.Stride()),
						.Flags = D3D12_BUFFER_SRV_FLAG_NONE
					}
				};
				d3d12System->Device().CreateShaderResourceView(&buffer->Data(), &srvDesc, heap->CpuHandle(heapIndex));
			}
		}

		for (const BufferInfo& bufferInfo : bufferInfos)
		{
			bufferOffsets[bufferInfo.dataTypeIndex][bufferInfo.bufferIndex] = bufferInfo.offset * bufferInfo.buffer->Stride();
		}

		mesh = Mesh(std::move(buffer), std::move(heap), std::move(dataTypes), std::move(bufferOffsets), std::move(heapIndices), source.ThreadGroupCounts().Span(), source.BoundingBox());
	}

	void MeshManager::UpdateBuffers(Mesh& mesh, const Render::Mesh& source, const MeshObserver& observer)
	{
		if (observer.MeshChanged()) [[unlikely]]
		{
			UpdateBuffer(mesh, source);
		}
		else [[likely]]
		{
			for (const auto [dataIndex, bufferIndex] : observer.ChangedBuffers())
			{
				UpdateBuffer(mesh, source, dataIndex, bufferIndex);
			}
		}
	}

	void MeshManager::UpdateBuffer(Mesh& mesh, const Render::Mesh& source)
	{
		Buffer& gpuBuffer = *mesh.Buffer();
		const std::uint64_t size = gpuBuffer.Data().GetDesc1().Width;
		const std::shared_ptr<Buffer> uploadBuffer = d3d12System->ResourceManager().CreateBuffer(size, HeapType::Upload);
		uploadBuffers.push_back(uploadBuffer);

		for (std::uint32_t dataIndex = 0u; dataIndex < mesh.DataCount(); ++dataIndex)
		{
			for (std::uint32_t bufferIndex = 0u; bufferIndex < mesh.BufferCount(dataIndex); ++bufferIndex)
			{
				const PonyBase::Container::Buffer& buffer = source.Buffer(dataIndex, bufferIndex);
				uploadBuffer->SetData(buffer.Data(), buffer.Size(), mesh.BufferOffset(dataIndex, bufferIndex));
			}
		}

		d3d12System->CopyPipeline().AddCopyTask(*uploadBuffer, gpuBuffer);
	}

	void MeshManager::UpdateBuffer(Mesh& mesh, const Render::Mesh& source, const std::uint32_t dataIndex, const std::uint32_t bufferIndex)
	{
		const PonyBase::Container::Buffer& sourceBuffer = source.Buffer(dataIndex, bufferIndex);
		const std::shared_ptr<Buffer> uploadBuffer = d3d12System->ResourceManager().CreateBuffer(sourceBuffer.Size(), HeapType::Upload);
		uploadBuffer->SetData(sourceBuffer);
		uploadBuffers.push_back(uploadBuffer);

		Buffer& gpuBuffer = *mesh.Buffer();
		d3d12System->CopyPipeline().AddCopyTask(*uploadBuffer, gpuBuffer, 0ULL, mesh.BufferOffset(dataIndex, bufferIndex), sourceBuffer.Size());
	}

	void MeshManager::UpdateAdditionalData(Mesh& mesh, const Render::Mesh& source, const MeshObserver& observer) noexcept
	{
		if (observer.AdditionalDataChanged()) [[unlikely]]
		{
			mesh.ThreadGroupCounts() = source.ThreadGroupCounts();
			mesh.BoundingBox() = source.BoundingBox();
		}
	}

	void MeshManager::UpdateName(Mesh& mesh, const Render::Mesh& source, const MeshObserver& observer)
	{
		if (observer.NameChanged()) [[unlikely]]
		{
			mesh.Name(source.Name());
		}
	}

	void MeshManager::Add(const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<const Render::Mesh>& source)
	{
		const std::size_t currentSize = meshes.size();

		try
		{
			meshes.push_back(mesh);
			sources.push_back(source);
			observers.push_back(std::make_unique<MeshObserver>());
			source->AddObserver(*observers.back());
		}
		catch (...)
		{
			meshes.resize(currentSize);
			sources.resize(currentSize);
			observers.resize(currentSize);

			throw;
		}
	}

	void MeshManager::Remove(const std::size_t index) noexcept
	{
		sources[index]->RemoveObserver(*observers[index]);

		meshes.erase(meshes.cbegin() + index);
		sources.erase(sources.cbegin() + index);
		observers.erase(observers.cbegin() + index);
	}
}
