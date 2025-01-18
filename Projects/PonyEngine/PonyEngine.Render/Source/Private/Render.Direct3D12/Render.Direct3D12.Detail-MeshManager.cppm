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
import :IMeshManagerPrivate;
import :ISubSystemContext;
import :Mesh;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 mesh manager.
	class MeshManager final : public IMeshManagerPrivate
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
		virtual std::shared_ptr<Mesh> CreateDirect3D12Mesh(const std::shared_ptr<const Render::Mesh>& mesh) override;

		void Tick();

		/// @brief Cleans out of dead meshes.
		void Clean() noexcept;

		MeshManager& operator =(const MeshManager&) = delete;
		MeshManager& operator =(MeshManager&&) = delete;

	private:
		[[nodiscard("Pure function")]]
		Mesh CreateMesh(const Render::Mesh& mesh) const;
		[[nodiscard("Pure function")]]
		static D3D12_RESOURCE_DESC1 CreateBufferDesc(UINT64 bufferSize) noexcept;
		[[nodiscard("Pure function")]]
		static Microsoft::WRL::ComPtr<ID3D12Resource2> CreateUploadBuffer(ID3D12Device10& device, const D3D12_RESOURCE_DESC1& bufferDesc, const PonyBase::Container::Buffer& sourceBuffer);
		[[nodiscard("Pure function")]]
		static Microsoft::WRL::ComPtr<ID3D12Resource2> CreateGpuBuffer(ID3D12Device10& device, const D3D12_RESOURCE_DESC1& bufferDesc);
		static void CreateSrv(ID3D12Device10& device, const D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle, ID3D12Resource2& gpuBuffer, const PonyBase::Container::Buffer& sourceBuffer);

		struct SourceState final
		{
			std::unordered_map<std::string, std::vector<std::size_t>> bufferVersions;
			std::size_t meshVersion;
		};

		[[nodiscard("Pure function")]]
		static SourceState CreateSourceData(const Render::Mesh& mesh);

		void UpdateMesh(Mesh& mesh, const Render::Mesh& source, SourceState& sourceState) const;
		void UpdateBuffers(Mesh& mesh, const Render::Mesh& source, SourceState& sourceState) const;

		static constexpr D3D12_DESCRIPTOR_HEAP_TYPE DescHeapType = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV; ///< Descriptor heap type.
		/// @brief Upload heap properties.
		static constexpr auto UploadHeapProperties = D3D12_HEAP_PROPERTIES
		{
			.Type = D3D12_HEAP_TYPE_UPLOAD,
			.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN,
			.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN,
			.CreationNodeMask = 0u,
			.VisibleNodeMask = 0u
		};
		/// @brief Gpu heap properties.
		static constexpr auto GpuHeapProperties = D3D12_HEAP_PROPERTIES
		{
			.Type = D3D12_HEAP_TYPE_DEFAULT,
			.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN,
			.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN,
			.CreationNodeMask = 0u,
			.VisibleNodeMask = 0u
		};


		ISubSystemContext* d3d12System; ///< Direct3D12 system context.

		std::vector<std::shared_ptr<Mesh>> meshes; ///< Meshes.
		std::vector<std::shared_ptr<const Render::Mesh>> sources;
		std::vector<SourceState> sourceStates;
	};
}

namespace PonyEngine::Render::Direct3D12
{
	MeshManager::MeshManager(ISubSystemContext& d3d12System) :
		d3d12System{&d3d12System}
	{
	}

	std::shared_ptr<Mesh> MeshManager::CreateDirect3D12Mesh(const std::shared_ptr<const Render::Mesh>& mesh)
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
		const auto sourceData = CreateSourceData(*mesh);
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
		for (std::size_t meshIndex = 0; meshIndex < sourceStates.size(); ++meshIndex)
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

	void MeshManager::Clean() noexcept
	{
		for (std::size_t i = meshes.size(); i-- > 0; )
		{
			if (meshes[i].use_count() <= 1)
			{
				PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Destroy mesh at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(meshes[i].get()));
				meshes.erase(meshes.cbegin() + i);
				sources.erase(sources.cbegin() + i);
				sourceStates.erase(sourceStates.begin() + i);
				PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Mesh destroyed.");
			}
		}
	}

	Mesh MeshManager::CreateMesh(const Render::Mesh& mesh) const
	{
		const std::shared_ptr<DescriptorHeap> heap = d3d12System->DescriptorHeapManager().CreateDescriptorHeap(DescHeapType, static_cast<UINT>(mesh.BufferCount()), DescriptorHeapVisibility::CPU);

		ID3D12Device10& device = d3d12System->Device();
		ICopyPipeline& copyPipeline = d3d12System->CopyPipeline();
		std::unordered_map<std::string, std::pair<std::vector<Microsoft::WRL::ComPtr<ID3D12Resource2>>, UINT>> data;
		UINT handleIndex = 0u;
		for (const std::string& dataType : mesh.DataTypes())
		{
			const UINT startHandleIndex = handleIndex;
			const std::span<const PonyBase::Container::Buffer> bufferTable = mesh.FindBufferTable(dataType);
			auto buffers = std::vector<Microsoft::WRL::ComPtr<ID3D12Resource2>>();
			buffers.reserve(bufferTable.size());
			for (const PonyBase::Container::Buffer& sourceBuffer : bufferTable)
			{
				const D3D12_RESOURCE_DESC1 bufferDesc = CreateBufferDesc(static_cast<UINT64>(sourceBuffer.Size()));
				Microsoft::WRL::ComPtr<ID3D12Resource2> uploadBuffer = CreateUploadBuffer(device, bufferDesc, sourceBuffer);
				Microsoft::WRL::ComPtr<ID3D12Resource2> gpuBuffer = CreateGpuBuffer(device, bufferDesc);
				copyPipeline.AddBufferCopyTask(*uploadBuffer.Get(), *gpuBuffer.Get());
				buffers.push_back(gpuBuffer);

				CreateSrv(device, heap->CpuHandle(handleIndex), *gpuBuffer.Get(), sourceBuffer);

				++handleIndex;
			}

			data[dataType] = std::pair(buffers, startHandleIndex);
		}

		return Mesh(data, heap, mesh.ThreadGroupCounts());
	}

	D3D12_RESOURCE_DESC1 MeshManager::CreateBufferDesc(const UINT64 bufferSize) noexcept
	{
		return D3D12_RESOURCE_DESC1
		{
			.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER,
			.Alignment = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT,
			.Width = bufferSize,
			.Height = 1u,
			.DepthOrArraySize = 1u,
			.MipLevels = 1u,
			.Format = DXGI_FORMAT_UNKNOWN,
			.SampleDesc = DXGI_SAMPLE_DESC{.Count = 1u, .Quality = 0u},
			.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR,
			.Flags = D3D12_RESOURCE_FLAG_NONE,
			.SamplerFeedbackMipRegion = D3D12_MIP_REGION{}
		};
	}

	Microsoft::WRL::ComPtr<ID3D12Resource2> MeshManager::CreateUploadBuffer(ID3D12Device10& device, const D3D12_RESOURCE_DESC1& bufferDesc, const PonyBase::Container::Buffer& sourceBuffer)
	{
		Microsoft::WRL::ComPtr<ID3D12Resource2> uploadBuffer;
		if (const HRESULT result = device.CreateCommittedResource3(&UploadHeapProperties, D3D12_HEAP_FLAG_NONE, &bufferDesc, D3D12_BARRIER_LAYOUT_UNDEFINED,
			nullptr, nullptr, 0, nullptr, IID_PPV_ARGS(uploadBuffer.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to create upload mesh buffer with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		void* data;
		if (const HRESULT result = uploadBuffer->Map(0, nullptr, &data); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to map mesh buffer with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		std::memcpy(data, sourceBuffer.Data(), sourceBuffer.Size());
		uploadBuffer->Unmap(0, nullptr);

		return uploadBuffer;
	}

	Microsoft::WRL::ComPtr<ID3D12Resource2> MeshManager::CreateGpuBuffer(ID3D12Device10& device, const D3D12_RESOURCE_DESC1& bufferDesc)
	{
		Microsoft::WRL::ComPtr<ID3D12Resource2> gpuBuffer;
		if (const HRESULT result = device.CreateCommittedResource3(&GpuHeapProperties, D3D12_HEAP_FLAG_NONE, &bufferDesc, D3D12_BARRIER_LAYOUT_UNDEFINED,
			nullptr, nullptr, 0, nullptr, IID_PPV_ARGS(gpuBuffer.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to create gpu mesh buffer with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		return gpuBuffer;
	}

	void MeshManager::CreateSrv(ID3D12Device10& device, const D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle, ID3D12Resource2& gpuBuffer, const PonyBase::Container::Buffer& sourceBuffer)
	{
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
		device.CreateShaderResourceView(&gpuBuffer, &srvDesc, cpuHandle);
	}

	MeshManager::SourceState MeshManager::CreateSourceData(const Render::Mesh& mesh)
	{
		auto sourceData = SourceState{.meshVersion = mesh.MeshVersion()};
		for (const std::string& dataType : mesh.DataTypes())
		{
			const std::span<const std::size_t> versions = mesh.BufferVersions(dataType);
			sourceData.bufferVersions[dataType] = std::vector<std::size_t>(versions.begin(), versions.end());
		}

		return sourceData;
	}

	void MeshManager::UpdateMesh(Mesh& mesh, const Render::Mesh& source, SourceState& sourceState) const
	{
		mesh = CreateMesh(source);
		sourceState = CreateSourceData(source);
	}

	void MeshManager::UpdateBuffers(Mesh& mesh, const Render::Mesh& source, SourceState& sourceState) const
	{
		for (auto& [dataType, bufferVersions] : sourceState.bufferVersions)
		{
			for (std::size_t bufferIndex = 0; bufferIndex < bufferVersions.size(); ++bufferIndex)
			{
				if (bufferVersions[bufferIndex] != source.BufferVersion(dataType, bufferIndex))
				{
					const PonyBase::Container::Buffer* const sourceBuffer = source.FindBuffer(dataType, bufferIndex);

					const D3D12_RESOURCE_DESC1 bufferDesc = CreateBufferDesc(static_cast<UINT64>(sourceBuffer->Size()));
					Microsoft::WRL::ComPtr<ID3D12Resource2> uploadBuffer = CreateUploadBuffer(d3d12System->Device(), bufferDesc, *sourceBuffer);
					ID3D12Resource2* const gpuBuffer = mesh.FindBuffer(dataType, bufferIndex);
					d3d12System->CopyPipeline().AddBufferCopyTask(*uploadBuffer.Get(), *gpuBuffer);

					bufferVersions[bufferIndex] = source.BufferVersion(dataType, bufferIndex).value();
				}
			}
		}
	}
}
