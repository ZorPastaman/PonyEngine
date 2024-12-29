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
		virtual std::shared_ptr<Direct3D12Mesh> CreateDirect3D12Mesh(const Mesh& mesh) override;

		/// @brief Cleans out of dead meshes.
		void Clean() noexcept;

		Direct3D12MeshManager& operator =(const Direct3D12MeshManager&) = delete;
		Direct3D12MeshManager& operator =(Direct3D12MeshManager&&) = delete;

	private:
		static constexpr D3D12_DESCRIPTOR_HEAP_TYPE descHeapType = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV; ///< Descriptor heap type.
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
	};
}

namespace PonyEngine::Render
{
	Direct3D12MeshManager::Direct3D12MeshManager(IDirect3D12SystemContext& d3d12System) :
		d3d12System{&d3d12System}
	{
	}

	std::shared_ptr<Direct3D12Mesh> Direct3D12MeshManager::CreateDirect3D12Mesh(const Mesh& mesh)
	{
		ID3D12Device10& device = d3d12System->Device();
		const auto heapDesc = D3D12_DESCRIPTOR_HEAP_DESC
		{
			.Type = descHeapType,
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
		const UINT handleIncrement = device.GetDescriptorHandleIncrementSize(descHeapType);

		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource2>> uploadBuffers;
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource2>> gpuBuffers;
		std::unordered_map<std::string, D3D12_GPU_DESCRIPTOR_HANDLE> handles;
		for (const auto& [dataType, bufferTable] : mesh.BufferTables())
		{
			for (const auto& buffer : bufferTable)
			{
				const auto bufferDesc = D3D12_RESOURCE_DESC1
				{
					.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER,
					.Alignment = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT,
					.Width = static_cast<UINT64>(buffer.Size()),
					.Height = 1u,
					.DepthOrArraySize = 1u,
					.MipLevels = 1u,
					.Format = DXGI_FORMAT_UNKNOWN,
					.SampleDesc = DXGI_SAMPLE_DESC{.Count = 1u, .Quality = 0u},
					.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR,
					.Flags = D3D12_RESOURCE_FLAG_NONE,
					.SamplerFeedbackMipRegion = D3D12_MIP_REGION{}
				};

				uploadBuffers.push_back(Microsoft::WRL::ComPtr<ID3D12Resource2>());
				Microsoft::WRL::ComPtr<ID3D12Resource2>& uploadBuffer = uploadBuffers.back();
				if (const HRESULT result = d3d12System->Device().CreateCommittedResource3(&UploadHeapProperties, D3D12_HEAP_FLAG_NONE, &bufferDesc, D3D12_BARRIER_LAYOUT_UNDEFINED,
					nullptr, nullptr, 0, nullptr, IID_PPV_ARGS(uploadBuffer.GetAddressOf())); FAILED(result)) [[unlikely]]
				{
					throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to create upload mesh buffer with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
				}
				void* data;
				if (const HRESULT result = uploadBuffer->Map(0, nullptr, &data); FAILED(result)) [[unlikely]]
				{
					throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to map mesh buffer with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
				}
				std::memcpy(data, buffer.Data(), buffer.Size());
				uploadBuffer->Unmap(0, nullptr);

				gpuBuffers.push_back(Microsoft::WRL::ComPtr<ID3D12Resource2>());
				Microsoft::WRL::ComPtr<ID3D12Resource2>& gpuBuffer = gpuBuffers.back();
				if (const HRESULT result = d3d12System->Device().CreateCommittedResource3(&GpuHeapProperties, D3D12_HEAP_FLAG_NONE, &bufferDesc, D3D12_BARRIER_LAYOUT_UNDEFINED,
					nullptr, nullptr, 0, nullptr, IID_PPV_ARGS(gpuBuffer.GetAddressOf())); FAILED(result)) [[unlikely]]
				{
					throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to create gpu mesh buffer with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
				}

				d3d12System->CopyPipeline().AddBufferCopyTask(*uploadBuffer.Get(), *gpuBuffer.Get());

				const auto srvDesc = D3D12_SHADER_RESOURCE_VIEW_DESC
				{
					.Format = DXGI_FORMAT_UNKNOWN,
					.ViewDimension = D3D12_SRV_DIMENSION_BUFFER,
					.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING,
					.Buffer = D3D12_BUFFER_SRV
					{
						.FirstElement = 0UL,
						.NumElements = static_cast<UINT>(buffer.Count()),
						.StructureByteStride = static_cast<UINT>(buffer.Stride()),
						.Flags = D3D12_BUFFER_SRV_FLAG_NONE
					}
				};
				device.CreateShaderResourceView(gpuBuffer.Get(), &srvDesc, cpuHandle);

				if (!handles.contains(dataType))
				{
					handles[dataType] = gpuHandle;
				}

				cpuHandle.ptr += handleIncrement;
				gpuHandle.ptr += handleIncrement;
			}
		}

		const auto renderMesh = std::make_shared<Direct3D12Mesh>(gpuBuffers, heap, handles, mesh.ThreadGroupCounts());
		meshes.push_back(renderMesh);
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Mesh created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(renderMesh.get()));

		return renderMesh;
	}

	void Direct3D12MeshManager::Clean() noexcept
	{
		for (std::size_t i = meshes.size(); i-- > 0; )
		{
			if (meshes[i].use_count() <= 1)
			{
				PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Destroy mesh at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(meshes[i].get()));
				meshes.erase(meshes.cbegin() + i);
				PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Mesh destroyed.");
			}
		}
	}
}
