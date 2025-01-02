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

export module PonyEngine.Render.Direct3D12.Detail:Direct3D12MeshManager;

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
import PonyBase.StringUtility;

import PonyMath.Color;
import PonyMath.Core;

import PonyDebug.Log;

import :Direct3D12IndexArray;
import :Direct3D12IndexFormat;
import :Direct3D12Mesh;
import :Direct3D12VertexArray;
import :Direct3D12VertexFormat;
import :IDirect3D12CopyPipeline;
import :IDirect3D12GraphicsPipeline;
import :IDirect3D12MeshManagerPrivate;
import :IDirect3D12SystemContext;

export namespace PonyEngine::Render
{
	/// @brief Direct3D12 mesh manager.
	class Direct3D12MeshManager final : public IDirect3D12MeshManagerPrivate
	{
	public:
		/// @brief Creates a @p Direct3D12MeshManager.
		/// @param d3d12System 
		[[nodiscard("Pure constructor")]]
		explicit Direct3D12MeshManager(IDirect3D12SystemContext& d3d12System);
		Direct3D12MeshManager(const Direct3D12MeshManager&) = delete;
		Direct3D12MeshManager(Direct3D12MeshManager&&) = delete;

		~Direct3D12MeshManager() noexcept = default;

		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<Direct3D12Mesh> CreateDirect3D12Mesh(const std::shared_ptr<const Mesh>& mesh) override;

		void Tick();

		/// @brief Cleans out of dead meshes.
		void Clean() noexcept;

		Direct3D12MeshManager& operator =(const Direct3D12MeshManager&) = delete;
		Direct3D12MeshManager& operator =(Direct3D12MeshManager&&) = delete;

	private:
		[[nodiscard("Pure function")]]
		Direct3D12Mesh CreateMesh(const Mesh& mesh) const;
		[[nodiscard("Pure function")]]
		static D3D12_RESOURCE_DESC1 CreateBufferDesc(UINT64 bufferSize) noexcept;
		[[nodiscard("Pure function")]]
		static Microsoft::WRL::ComPtr<ID3D12Resource2> CreateUploadBuffer(ID3D12Device10& device, const D3D12_RESOURCE_DESC1& bufferDesc, const PonyBase::Container::Buffer& sourceBuffer);
		[[nodiscard("Pure function")]]
		static Microsoft::WRL::ComPtr<ID3D12Resource2> CreateGpuBuffer(ID3D12Device10& device, const D3D12_RESOURCE_DESC1& bufferDesc);
		static void CreateSrv(ID3D12Device10& device, const D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle, ID3D12Resource2& gpuBuffer, const PonyBase::Container::Buffer& sourceBuffer);

		struct SourceData final
		{
			std::shared_ptr<const Mesh> mesh;
			std::unordered_map<std::string, std::vector<std::size_t>> bufferVersions;
			std::size_t meshVersion;
		};

		[[nodiscard("Pure function")]]
		static SourceData CreateSourceData(const std::shared_ptr<const Mesh>& mesh);

		void UpdateMesh(Direct3D12Mesh& mesh, SourceData& sourceData) const;
		void UpdateBuffers(Direct3D12Mesh& mesh, SourceData& sourceData) const;

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

		IDirect3D12SystemContext* d3d12System; ///< Direct3D12 system context.

		std::vector<std::shared_ptr<Direct3D12Mesh>> meshes; ///< Meshes.
		std::vector<SourceData> meshSources;
	};
}

namespace PonyEngine::Render
{
	Direct3D12MeshManager::Direct3D12MeshManager(IDirect3D12SystemContext& d3d12System) :
		d3d12System{&d3d12System}
	{
	}

	std::shared_ptr<Direct3D12Mesh> Direct3D12MeshManager::CreateDirect3D12Mesh(const std::shared_ptr<const Mesh>& mesh)
	{
		const auto renderMesh = std::make_shared<Direct3D12Mesh>(CreateMesh(*mesh));
		const auto sourceData = CreateSourceData(mesh);
		meshes.reserve(meshes.size() + 1);
		meshSources.reserve(meshes.size() + 1);
		meshes.push_back(renderMesh);
		meshSources.push_back(sourceData);
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Mesh created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(renderMesh.get()));

		return renderMesh;
	}

	void Direct3D12MeshManager::Tick()
	{
		for (std::size_t meshIndex = 0; meshIndex < meshSources.size(); ++meshIndex)
		{
			const std::shared_ptr<Direct3D12Mesh>& mesh = meshes[meshIndex];
			SourceData& sourceData = meshSources[meshIndex];

			if (sourceData.meshVersion != sourceData.mesh->MeshVersion())
			{
				UpdateMesh(*mesh, sourceData);
			}
			else
			{
				UpdateBuffers(*mesh, sourceData);
			}

			std::ranges::copy(sourceData.mesh->ThreadGroupCounts(), mesh->ThreadGroupCounts().begin());
		}
	}

	void Direct3D12MeshManager::Clean() noexcept
	{
		for (std::size_t i = meshes.size(); i-- > 0; )
		{
			if (meshes[i].use_count() <= 1)
			{
				PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Destroy mesh at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(meshes[i].get()));
				meshes.erase(meshes.cbegin() + i);
				meshSources.erase(meshSources.begin() + i);
				PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Mesh destroyed.");
			}
		}
	}

	Direct3D12Mesh Direct3D12MeshManager::CreateMesh(const Mesh& mesh) const
	{
		ID3D12Device10& device = d3d12System->Device();
		const auto heapDesc = D3D12_DESCRIPTOR_HEAP_DESC
		{
			.Type = DescHeapType,
			.NumDescriptors = static_cast<UINT>(mesh.BufferCount()),
			.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE,
			.NodeMask = 0u
		};
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> heap;
		if (const HRESULT result = device.CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(heap.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to create mesh descriptor heap with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle = heap->GetCPUDescriptorHandleForHeapStart();
		D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle = heap->GetGPUDescriptorHandleForHeapStart();
		const UINT handleIncrement = device.GetDescriptorHandleIncrementSize(DescHeapType);

		IDirect3D12CopyPipeline& copyPipeline = d3d12System->CopyPipeline();
		std::unordered_map<std::string, std::pair<std::vector<Microsoft::WRL::ComPtr<ID3D12Resource2>>, D3D12_GPU_DESCRIPTOR_HANDLE>> data;
		for (const std::string& dataType : mesh.DataTypes())
		{
			const D3D12_GPU_DESCRIPTOR_HANDLE gpuStartHandle = gpuHandle;

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

				CreateSrv(device, cpuHandle, *gpuBuffer.Get(), sourceBuffer);

				cpuHandle.ptr += handleIncrement;
				gpuHandle.ptr += handleIncrement;
			}

			data[dataType] = std::pair(buffers, gpuStartHandle);
		}

		return Direct3D12Mesh(data, *heap.Get(), mesh.ThreadGroupCounts());
	}

	D3D12_RESOURCE_DESC1 Direct3D12MeshManager::CreateBufferDesc(const UINT64 bufferSize) noexcept
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

	Microsoft::WRL::ComPtr<ID3D12Resource2> Direct3D12MeshManager::CreateUploadBuffer(ID3D12Device10& device, const D3D12_RESOURCE_DESC1& bufferDesc, const PonyBase::Container::Buffer& sourceBuffer)
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

	Microsoft::WRL::ComPtr<ID3D12Resource2> Direct3D12MeshManager::CreateGpuBuffer(ID3D12Device10& device, const D3D12_RESOURCE_DESC1& bufferDesc)
	{
		Microsoft::WRL::ComPtr<ID3D12Resource2> gpuBuffer;
		if (const HRESULT result = device.CreateCommittedResource3(&GpuHeapProperties, D3D12_HEAP_FLAG_NONE, &bufferDesc, D3D12_BARRIER_LAYOUT_UNDEFINED,
			nullptr, nullptr, 0, nullptr, IID_PPV_ARGS(gpuBuffer.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to create gpu mesh buffer with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		return gpuBuffer;
	}

	void Direct3D12MeshManager::CreateSrv(ID3D12Device10& device, const D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle, ID3D12Resource2& gpuBuffer, const PonyBase::Container::Buffer& sourceBuffer)
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

	Direct3D12MeshManager::SourceData Direct3D12MeshManager::CreateSourceData(const std::shared_ptr<const Mesh>& mesh)
	{
		auto sourceData = SourceData{ .mesh = mesh, .meshVersion = mesh->MeshVersion() };
		for (const std::string& dataType : mesh->DataTypes())
		{
			const std::span<const std::size_t> versions = mesh->BufferVersions(dataType);
			sourceData.bufferVersions[dataType] = std::vector<std::size_t>(versions.begin(), versions.end());
		}

		return sourceData;
	}

	void Direct3D12MeshManager::UpdateMesh(Direct3D12Mesh& mesh, SourceData& sourceData) const
	{
		mesh = CreateMesh(*sourceData.mesh);
		sourceData = CreateSourceData(sourceData.mesh);
	}

	void Direct3D12MeshManager::UpdateBuffers(Direct3D12Mesh& mesh, SourceData& sourceData) const
	{
		for (auto& [dataType, bufferVersions] : sourceData.bufferVersions)
		{
			for (std::size_t bufferIndex = 0; bufferIndex < bufferVersions.size(); ++bufferIndex)
			{
				if (bufferVersions[bufferIndex] != sourceData.mesh->BufferVersion(dataType, bufferIndex))
				{
					const PonyBase::Container::Buffer* const sourceBuffer = sourceData.mesh->FindBuffer(dataType, bufferIndex);

					const D3D12_RESOURCE_DESC1 bufferDesc = CreateBufferDesc(static_cast<UINT64>(sourceBuffer->Size()));
					Microsoft::WRL::ComPtr<ID3D12Resource2> uploadBuffer = CreateUploadBuffer(d3d12System->Device(), bufferDesc, *sourceBuffer);
					ID3D12Resource2* const gpuBuffer = mesh.FindBuffer(dataType, bufferIndex);
					d3d12System->CopyPipeline().AddBufferCopyTask(*uploadBuffer.Get(), *gpuBuffer);

					bufferVersions[bufferIndex] = sourceData.mesh->BufferVersion(dataType, bufferIndex).value();
				}
			}
		}
	}
}
