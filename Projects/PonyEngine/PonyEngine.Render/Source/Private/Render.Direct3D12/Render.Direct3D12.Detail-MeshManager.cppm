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
		struct SourceState final
		{
			std::vector<std::vector<std::uint64_t>> bufferVersions;
			std::uint64_t meshVersion;
			std::uint32_t threadGroupCountsVersion;
			std::uint64_t nameVersion;
		};

		struct CopyTask final
		{
			std::shared_ptr<Buffer> uploadBuffer;
			Buffer* gpuBuffer;
		};

		void UpdateMeshes();
		void CopyBuffers();

		void UpdateMesh(Mesh& mesh, const Render::Mesh& source, SourceState& sourceState);
		void UpdateBuffers(Mesh& mesh, const Render::Mesh& source, SourceState& sourceState);
		void UpdateThreadGroupCounts(Mesh& mesh, const Render::Mesh& source, SourceState& sourceState) noexcept;
		void UpdateName(Mesh& mesh, const Render::Mesh& source, SourceState& sourceState);

		void Add(const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<const Render::Mesh>& source);
		void Remove(std::size_t index) noexcept;

		static constexpr D3D12_DESCRIPTOR_HEAP_TYPE DescHeapType = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV; ///< Descriptor heap type.

		ISubSystemContext* d3d12System; ///< Direct3D12 system context.

		std::vector<std::shared_ptr<Mesh>> meshes; ///< Meshes.
		std::vector<std::shared_ptr<const Render::Mesh>> sources;
		std::vector<SourceState> sourceStates;

		std::vector<CopyTask> copyTasks;
	};
}

namespace PonyEngine::Render::Direct3D12
{
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
			const std::shared_ptr<Mesh>& mesh = meshes[i];
			const std::shared_ptr<const Render::Mesh>& source = sources[i];
			SourceState& sourceState = sourceStates[i];

			UpdateMesh(*mesh, *source, sourceState);
			UpdateBuffers(*mesh, *source, sourceState);
			UpdateThreadGroupCounts(*mesh, *source, sourceState);
			UpdateName(*mesh, *source, sourceState);
		}
	}

	void MeshManager::CopyBuffers()
	{
		for (const CopyTask& copyTask : copyTasks)
		{
			d3d12System->CopyPipeline().AddCopyTask(*copyTask.uploadBuffer, *copyTask.gpuBuffer);
		}
	}

	void MeshManager::UpdateMesh(Mesh& mesh, const Render::Mesh& source, SourceState& sourceState)
	{
		if (sourceState.meshVersion == source.MeshVersion())
		{
			return;
		}

		std::vector<std::string> dataTypes;
		std::vector<UINT> bufferOffsets;
		std::vector<std::vector<std::uint64_t>> bufferVersions;
		std::vector<std::shared_ptr<Buffer>> buffers;
		const std::shared_ptr<DescriptorHeap> heap = d3d12System->DescriptorHeapManager().CreateDescriptorHeap(DescHeapType, static_cast<UINT>(source.BufferCount()), false);

		for (std::uint32_t i = 0; i < source.DataTypeCount(); ++i)
		{
			dataTypes.push_back(std::string(source.DataType(i)));
			bufferOffsets.push_back(static_cast<UINT>(buffers.size()));
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
				d3d12System->Device().CreateShaderResourceView(&gpuBuffer->Data(), &srvDesc, heap->CpuHandle(static_cast<UINT>(buffers.size()) - 1u));
			}
		}

		mesh = Mesh(dataTypes, bufferOffsets, buffers, heap);
		sourceState.meshVersion = source.MeshVersion();
		sourceState.bufferVersions = std::move(bufferVersions);
	}

	void MeshManager::UpdateBuffers(Mesh& mesh, const Render::Mesh& source, SourceState& sourceState)
	{
		for (std::uint32_t dataIndex = 0u; dataIndex < sourceState.bufferVersions.size(); ++dataIndex)
		{
			std::vector<std::uint64_t>& bufferVersions = sourceState.bufferVersions[dataIndex];
			for (std::uint32_t bufferIndex = 0u; bufferIndex < bufferVersions.size(); ++bufferIndex)
			{
				if (const std::uint64_t bufferVersion = source.BufferVersion(dataIndex, bufferIndex); bufferVersions[bufferIndex] != bufferVersion)
				{
					const PonyBase::Container::Buffer& sourceBuffer = source.Buffer(dataIndex, bufferIndex);
					const std::shared_ptr<Buffer> uploadBuffer = d3d12System->ResourceManager().CreateBuffer(static_cast<UINT64>(sourceBuffer.Size()), HeapType::Upload);
					uploadBuffer->SetData(sourceBuffer);
					Buffer& gpuBuffer = mesh.Buffer(dataIndex, bufferIndex);
					copyTasks.push_back(CopyTask{.uploadBuffer = uploadBuffer, .gpuBuffer = &gpuBuffer});

					bufferVersions[bufferIndex] = bufferVersion;
				}
			}
		}
	}

	void MeshManager::UpdateThreadGroupCounts(Mesh& mesh, const Render::Mesh& source, SourceState& sourceState) noexcept
	{
		if (sourceState.threadGroupCountsVersion == source.ThreadGroupCountsVersion())
		{
			return;
		}

		std::ranges::copy(source.ThreadGroupCounts(), mesh.ThreadGroupCounts().begin());
		sourceState.threadGroupCountsVersion = source.ThreadGroupCountsVersion();
	}

	void MeshManager::UpdateName(Mesh& mesh, const Render::Mesh& source, SourceState& sourceState)
	{
		if (sourceState.nameVersion == source.NameVersion())
		{
			return;
		}

		mesh.Name(source.Name());
		sourceState.nameVersion = source.NameVersion();
	}

	void MeshManager::Add(const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<const Render::Mesh>& source)
	{
		const std::size_t currentSize = meshes.size();

		try
		{
			meshes.push_back(mesh);
			sources.push_back(source);
			sourceStates.push_back(SourceState{});
		}
		catch (...)
		{
			meshes.resize(currentSize);
			sources.resize(currentSize);
			sourceStates.resize(currentSize);

			throw;
		}
	}

	void MeshManager::Remove(const std::size_t index) noexcept
	{
		meshes.erase(meshes.cbegin() + index);
		sources.erase(sources.cbegin() + index);
		sourceStates.erase(sourceStates.cbegin() + index);
	}
}
