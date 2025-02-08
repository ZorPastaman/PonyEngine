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
import <cstring>;
import <memory>;
import <optional>;
import <set>;
import <span>;
import <stdexcept>;
import <type_traits>;
import <vector>;

import PonyBase.Container;
import PonyBase.Utility;

import PonyMath.Color;
import PonyMath.Core;

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

		void Tick();

		void Clear() noexcept;

		/// @brief Cleans out of dead meshes.
		void Clean() noexcept;

		MeshManager& operator =(const MeshManager&) = delete;
		MeshManager& operator =(MeshManager&&) = delete;

	private:
		class MeshObserver final : public IMeshObserver
		{
		public:
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

			[[nodiscard("Pure function")]]
			bool MeshChanged() const noexcept;
			[[nodiscard("Pure function")]]
			const std::set<std::pair<std::uint32_t, std::uint32_t>>& ChangedBuffers() const noexcept;
			[[nodiscard("Pure function")]]
			bool ThreadGroupCountsChanged() const noexcept;
			[[nodiscard("Pure function")]]
			bool NameChanged() const noexcept;

			void Reset() noexcept;

			MeshObserver& operator =(const MeshObserver&) = delete;
			MeshObserver& operator =(MeshObserver&&) = delete;

		private:
			std::set<std::pair<std::uint32_t, std::uint32_t>> changedBuffers;
			bool meshChanged;
			bool threadGroupCountsChanged;
			bool boundingBoxChanged;
			bool nameChanged;
		};

		struct CopyTask final
		{
			std::shared_ptr<Buffer> uploadBuffer;
			Buffer* gpuBuffer;
		};

		void UpdateMeshes();
		void CopyBuffers();

		void UpdateMesh(Mesh& mesh, const Render::Mesh& source, const MeshObserver& observer) const;
		void UpdateBuffers(Mesh& mesh, const Render::Mesh& source, const MeshObserver& observer);
		void UpdateBuffer(Mesh& mesh, const Render::Mesh& source, std::uint32_t dataIndex, std::uint32_t bufferIndex);
		static void UpdateThreadGroupCounts(Mesh& mesh, const Render::Mesh& source, const MeshObserver& observer) noexcept;
		static void UpdateName(Mesh& mesh, const Render::Mesh& source, const MeshObserver& observer);

		void Add(const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<const Render::Mesh>& source);
		void Remove(std::size_t index) noexcept;

		static constexpr D3D12_DESCRIPTOR_HEAP_TYPE DescHeapType = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV; ///< Descriptor heap type.

		ISubSystemContext* d3d12System; ///< Direct3D12 system context.

		std::vector<std::shared_ptr<Mesh>> meshes; ///< Meshes.
		std::vector<std::shared_ptr<const Render::Mesh>> sources;
		std::vector<std::unique_ptr<MeshObserver>> observers;

		std::vector<CopyTask> copyTasks;
	};
}

namespace PonyEngine::Render::Direct3D12
{
	MeshManager::MeshObserver::MeshObserver() noexcept :
		meshChanged{true},
		threadGroupCountsChanged{true},
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
		threadGroupCountsChanged = true;
	}

	void MeshManager::MeshObserver::OnBoundingBoxChanged() noexcept
	{
		boundingBoxChanged = true;
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

	bool MeshManager::MeshObserver::ThreadGroupCountsChanged() const noexcept
	{
		return threadGroupCountsChanged;
	}

	bool MeshManager::MeshObserver::NameChanged() const noexcept
	{
		return nameChanged;
	}

	void MeshManager::MeshObserver::Reset() noexcept
	{
		changedBuffers.clear();
		meshChanged = false;
		threadGroupCountsChanged = false;
		boundingBoxChanged = false;
		nameChanged = false;
	}

	MeshManager::MeshManager(ISubSystemContext& d3d12System) :
		d3d12System{&d3d12System}
	{
	}

	std::shared_ptr<Mesh> MeshManager::CreateMesh(const std::shared_ptr<const Render::Mesh>& mesh)
	{
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
		UpdateMeshes();
		CopyBuffers();
	}

	void MeshManager::Clear() noexcept
	{
		copyTasks.clear();
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

	void MeshManager::UpdateMeshes()
	{
		for (std::size_t i = 0; i < meshes.size(); ++i)
		{
			Mesh& mesh = *meshes[i];
			const Render::Mesh& source = *sources[i];
			MeshObserver& observer = *observers[i];

			UpdateMesh(mesh, source, observer);
			UpdateBuffers(mesh, source, observer);
			UpdateThreadGroupCounts(mesh, source, observer);
			UpdateName(mesh, source, observer);

			observer.Reset();
		}
	}

	void MeshManager::CopyBuffers()
	{
		for (const CopyTask& copyTask : copyTasks)
		{
			d3d12System->CopyPipeline().AddCopyTask(*copyTask.uploadBuffer, *copyTask.gpuBuffer);
		}
	}

	void MeshManager::UpdateMesh(Mesh& mesh, const Render::Mesh& source, const MeshObserver& observer) const
	{
		if (!observer.MeshChanged()) [[likely]]
		{
			return;
		}

		std::vector<std::string> dataTypes;
		std::vector<std::uint32_t> bufferOffsets;
		std::vector<std::vector<std::uint64_t>> bufferVersions;
		std::vector<std::shared_ptr<Buffer>> buffers;
		const std::shared_ptr<DescriptorHeap> heap = d3d12System->DescriptorHeapManager().CreateDescriptorHeap(DescHeapType, source.BufferCount(), false);

		for (std::uint32_t i = 0; i < source.DataTypeCount(); ++i)
		{
			dataTypes.push_back(std::string(source.DataType(i)));
			bufferOffsets.push_back(static_cast<std::uint32_t>(buffers.size()));
			bufferVersions.push_back(std::vector<std::uint64_t>(source.BufferCount(i)));

			for (const PonyBase::Container::Buffer& sourceBuffer : source.BufferTable(i))
			{
				const std::shared_ptr<Buffer> gpuBuffer = d3d12System->ResourceManager().CreateBuffer(sourceBuffer.Size(), HeapType::Default);
				buffers.push_back(gpuBuffer);

				const auto srvDesc = D3D12_SHADER_RESOURCE_VIEW_DESC
				{
					.Format = DXGI_FORMAT_UNKNOWN,
					.ViewDimension = D3D12_SRV_DIMENSION_BUFFER,
					.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING,
					.Buffer = D3D12_BUFFER_SRV
					{
						.FirstElement = 0UL,
						.NumElements = static_cast<UINT>(sourceBuffer.Count()),
						.StructureByteStride = static_cast<UINT>(sourceBuffer.Stride()),
						.Flags = D3D12_BUFFER_SRV_FLAG_NONE
					}
				};
				d3d12System->Device().CreateShaderResourceView(&gpuBuffer->Data(), &srvDesc, heap->CpuHandle(static_cast<std::uint32_t>(buffers.size()) - 1u));
			}
		}

		mesh = Mesh(dataTypes, bufferOffsets, buffers, heap);
	}

	void MeshManager::UpdateBuffers(Mesh& mesh, const Render::Mesh& source, const MeshObserver& observer)
	{
		if (observer.MeshChanged()) [[unlikely]]
		{
			for (std::uint32_t dataIndex = 0; dataIndex < source.DataTypeCount(); ++dataIndex)
			{
				for (std::uint32_t bufferIndex = 0; bufferIndex < source.BufferCount(dataIndex); ++bufferIndex)
				{
					UpdateBuffer(mesh, source, dataIndex, bufferIndex);
				}
			}
		}
		else [[likely]]
		{
			for (const auto [dataIndex, bufferIndex] : observer.ChangedBuffers())
			{
				UpdateBuffer(mesh, source, dataIndex, bufferIndex);
			}
		}
	}

	void MeshManager::UpdateBuffer(Mesh& mesh, const Render::Mesh& source, const std::uint32_t dataIndex, const std::uint32_t bufferIndex)
	{
		const PonyBase::Container::Buffer& sourceBuffer = source.Buffer(dataIndex, bufferIndex);

		const std::shared_ptr<Buffer> uploadBuffer = d3d12System->ResourceManager().CreateBuffer(static_cast<std::uint64_t>(sourceBuffer.Size()), HeapType::Upload);
		uploadBuffer->SetData(sourceBuffer);

		Buffer& gpuBuffer = mesh.Buffer(dataIndex, bufferIndex);

		copyTasks.push_back(CopyTask{.uploadBuffer = uploadBuffer, .gpuBuffer = &gpuBuffer});
	}

	void MeshManager::UpdateThreadGroupCounts(Mesh& mesh, const Render::Mesh& source, const MeshObserver& observer) noexcept
	{
		if (observer.ThreadGroupCountsChanged()) [[unlikely]]
		{
			mesh.ThreadGroupCounts() = source.ThreadGroupCounts();
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
