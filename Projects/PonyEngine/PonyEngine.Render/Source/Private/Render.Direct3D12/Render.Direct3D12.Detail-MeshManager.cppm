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
			std::unordered_map<std::string, std::vector<std::uint64_t>> bufferVersions;
			std::uint64_t meshVersion;
		};

		[[nodiscard("Pure function")]]
		Mesh CreateMesh(const Render::Mesh& mesh);

		[[nodiscard("Pure function")]]
		static SourceState CreateSourceData(const Render::Mesh& mesh);

		void UpdateMesh(Mesh& mesh, const Render::Mesh& source, SourceState& sourceState);
		void UpdateBuffers(Mesh& mesh, const Render::Mesh& source, SourceState& sourceState);

		static constexpr D3D12_DESCRIPTOR_HEAP_TYPE DescHeapType = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV; ///< Descriptor heap type.

		ISubSystemContext* d3d12System; ///< Direct3D12 system context.

		std::vector<std::shared_ptr<Mesh>> meshes; ///< Meshes.
		std::vector<std::shared_ptr<const Render::Mesh>> sources; // TODO: Try to use weak_ptr
		std::vector<SourceState> sourceStates;

		std::vector<std::shared_ptr<Buffer>> uploadBuffers;
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

		const auto renderMesh = std::make_shared<Mesh>(CreateMesh(*mesh));
		const SourceState sourceData = CreateSourceData(*mesh);
		meshes.reserve(meshes.size() + 1);
		sources.reserve(sources.size() + 1);
		sourceStates.reserve(sourceStates.size() + 1);
		meshes.push_back(renderMesh);
		sources.push_back(mesh);
		sourceStates.push_back(sourceData);
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Mesh created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(renderMesh.get()));

		return renderMesh;
	}

	void MeshManager::Tick()
	{
		for (std::size_t meshIndex = 0; meshIndex < meshes.size(); ++meshIndex)
		{
			const std::shared_ptr<Mesh>& mesh = meshes[meshIndex];
			const std::shared_ptr<const Render::Mesh>& source = sources[meshIndex];
			SourceState& sourceState = sourceStates[meshIndex];

			if (sourceState.meshVersion != source->MeshVersion())
			{
				UpdateMesh(*mesh, *source, sourceState);
			}
			else
			{
				UpdateBuffers(*mesh, *source, sourceState);
			}

			std::ranges::copy(source->ThreadGroupCounts(), mesh->ThreadGroupCounts().begin());
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
				meshes.erase(meshes.cbegin() + i);
				sources.erase(sources.cbegin() + i);
				sourceStates.erase(sourceStates.begin() + i);
				PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Mesh destroyed.");
			}
		}
	}

	Mesh MeshManager::CreateMesh(const Render::Mesh& mesh)
	{
		std::vector<std::string> dataTypes;
		std::vector<UINT> bufferOffsets; // TODO: Check if all the buffer counts are UINT or std::uint32_t - including render mesh and usual mesh.
		std::vector<std::shared_ptr<Buffer>> buffers;
		const std::shared_ptr<DescriptorHeap> heap = d3d12System->DescriptorHeapManager().CreateDescriptorHeap(DescHeapType, static_cast<UINT>(mesh.BufferCount()), false);

		for (const std::string& dataType : mesh.DataTypes())
		{
			dataTypes.push_back(dataType);
			bufferOffsets.push_back(static_cast<UINT>(buffers.size()));

			for (const PonyBase::Container::Buffer& sourceBuffer : mesh.FindBufferTable(dataType))
			{
				const std::shared_ptr<Buffer> uploadBuffer = d3d12System->ResourceManager().CreateBuffer(sourceBuffer.Size(), HeapType::Upload);
				uploadBuffer->SetData(sourceBuffer);
				uploadBuffers.push_back(uploadBuffer);
				const std::shared_ptr<Buffer> gpuBuffer = d3d12System->ResourceManager().CreateBuffer(sourceBuffer.Size(), HeapType::Default);
				buffers.push_back(gpuBuffer);
				d3d12System->CopyPipeline().AddCopyTask(*uploadBuffer, *gpuBuffer); // TODO: Do it in tick

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

		return Mesh(dataTypes, bufferOffsets, buffers, heap, mesh.ThreadGroupCounts());
	}

	MeshManager::SourceState MeshManager::CreateSourceData(const Render::Mesh& mesh)
	{
		auto sourceData = SourceState{.meshVersion = mesh.MeshVersion()};
		for (const std::string& dataType : mesh.DataTypes())
		{
			const std::span<const std::uint64_t> versions = mesh.BufferVersions(dataType);
			sourceData.bufferVersions[dataType] = std::vector<std::uint64_t>(versions.begin(), versions.end());
		}

		return sourceData;
	}

	void MeshManager::UpdateMesh(Mesh& mesh, const Render::Mesh& source, SourceState& sourceState)
	{
		mesh = CreateMesh(source);
		sourceState = CreateSourceData(source);
	}

	void MeshManager::UpdateBuffers(Mesh& mesh, const Render::Mesh& source, SourceState& sourceState)
	{
		for (auto& [dataType, bufferVersions] : sourceState.bufferVersions)
		{
			for (std::size_t bufferIndex = 0; bufferIndex < bufferVersions.size(); ++bufferIndex)
			{
				if (const std::uint64_t bufferVersion = source.BufferVersion(dataType, bufferIndex).value(); bufferVersions[bufferIndex] != bufferVersion)
				{
					const PonyBase::Container::Buffer* const sourceBuffer = source.FindBuffer(dataType, bufferIndex);

					const std::shared_ptr<Buffer> uploadBuffer = d3d12System->ResourceManager().CreateBuffer(sourceBuffer->Size(), HeapType::Upload);
					uploadBuffer->SetData(*sourceBuffer);
					uploadBuffers.push_back(uploadBuffer);
					const std::shared_ptr<Buffer>& gpuBuffer = mesh.BufferShared(mesh.FindDataIndex(dataType).value(), bufferIndex);
					d3d12System->CopyPipeline().AddCopyTask(*uploadBuffer, *gpuBuffer);

					bufferVersions[bufferIndex] = bufferVersion;
				}
			}
		}
	}
}
