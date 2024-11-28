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
import PonyMath.Geometry;

import PonyDebug.Log;

import :Direct3D12IndexArray;
import :Direct3D12IndexFormat;
import :Direct3D12Mesh;
import :Direct3D12VertexArray;
import :Direct3D12VertexFormat;
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

		[[nodiscard("Pure function")]]
		virtual const Direct3D12VertexFormat& VertexFormat() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual const Direct3D12VertexFormat& VertexColorFormat() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual const Direct3D12IndexFormat& VertexIndexFormat() const noexcept override;

		[[nodiscard("Pure constructor")]]
		virtual std::shared_ptr<Direct3D12Mesh> CreateDirect3D12Mesh(const PonyMath::Geometry::Mesh& mesh) override;

		/// @brief Cleans out of dead meshes.
		void Clean() noexcept;

		Direct3D12MeshManager& operator =(const Direct3D12MeshManager&) = delete;
		Direct3D12MeshManager& operator =(Direct3D12MeshManager&&) = delete;

	private:
		/// @brief Creates a Direct3D12 vertex array.
		/// @param vertices Vertices source.
		/// @return Vertex array.
		[[nodiscard("Pure constructor")]]
		Direct3D12VertexArray CreateVertices(std::span<const PonyMath::Core::Vector3<float>> vertices) const;
		/// @brief Creates a Direct3D12 vertex color array.
		/// @param colors Colors source.
		/// @return Color array.
		[[nodiscard("Pure constructor")]]
		std::optional<Direct3D12VertexArray> CreateVertexColors(std::span<const PonyMath::Color::RGBA<float>> colors) const;
		/// @brief Creates a Direct3D12 index array.
		/// @param triangles Triangle source.
		/// @return Index array.
		[[nodiscard("Pure constructor")]]
		Direct3D12IndexArray CreateVertexIndices(std::span<const PonyMath::Core::Vector3<std::uint32_t>> triangles) const;

		static constexpr auto MeshVertexFormat = Direct3D12VertexFormat(4u, 3u, Direct3D12VertexDataType::Float); ///< Vertex format.
		static constexpr auto MeshVertexColorFormat = Direct3D12VertexFormat(4u, 4u, Direct3D12VertexDataType::Float); ///< Vertex color format.
		static constexpr auto MeshIndexFormat = Direct3D12IndexFormat(4); ///< Index format.

		/// @brief Upload heap properties.
		static constexpr auto UploadHeapProperties = D3D12_HEAP_PROPERTIES
		{
			.Type = D3D12_HEAP_TYPE_UPLOAD, // TODO: Add copy to gpu
			.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN,
			.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN,
			.CreationNodeMask = 0u,
			.VisibleNodeMask = 0u
		};

		IDirect3D12SystemContext* d3d12System; ///< Direct3D12 system context.

		std::vector<std::shared_ptr<Direct3D12Mesh>> meshes;
	};
}

namespace PonyEngine::Render
{
	Direct3D12MeshManager::Direct3D12MeshManager(IDirect3D12SystemContext& d3d12System) :
		d3d12System{&d3d12System}
	{
	}

	const Direct3D12VertexFormat& Direct3D12MeshManager::VertexFormat() const noexcept
	{
		return MeshVertexFormat;
	}

	const Direct3D12VertexFormat& Direct3D12MeshManager::VertexColorFormat() const noexcept
	{
		return MeshVertexColorFormat;
	}

	const Direct3D12IndexFormat& Direct3D12MeshManager::VertexIndexFormat() const noexcept
	{
		return MeshIndexFormat;
	}

	std::shared_ptr<Direct3D12Mesh> Direct3D12MeshManager::CreateDirect3D12Mesh(const PonyMath::Geometry::Mesh& mesh)
	{
		Direct3D12VertexArray vertices = CreateVertices(mesh.Vertices());
		std::optional<Direct3D12VertexArray> colors = CreateVertexColors(mesh.Colors());
		Direct3D12IndexArray indices = CreateVertexIndices(mesh.Triangles());

		const auto renderMesh = std::make_shared<Direct3D12Mesh>(vertices, colors ? &colors.value() : nullptr, indices);
		meshes.push_back(renderMesh);

		return renderMesh;
	}

	void Direct3D12MeshManager::Clean() noexcept
	{
		for (std::size_t i = meshes.size(); i-- > 0; )
		{
			if (meshes[i].use_count() <= 1)
			{
				meshes.erase(meshes.cbegin() + i);
			}
		}
	}

	Direct3D12VertexArray Direct3D12MeshManager::CreateVertices(const std::span<const PonyMath::Core::Vector3<float>> vertices) const
	{
		const UINT vertexCount = static_cast<UINT>(vertices.size());
		const std::size_t vertexBufferSize = MeshVertexFormat.VertexSize() * vertexCount;

		const auto vertexBufferDesc = D3D12_RESOURCE_DESC1
		{
			.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER,
			.Alignment = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT,
			.Width = static_cast<UINT64>(vertexBufferSize),
			.Height = 1u,
			.DepthOrArraySize = 1u,
			.MipLevels = 1u,
			.Format = DXGI_FORMAT_UNKNOWN,
			.SampleDesc = DXGI_SAMPLE_DESC{.Count = 1u, .Quality = 0u},
			.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR,
			.Flags = D3D12_RESOURCE_FLAG_NONE,
			.SamplerFeedbackMipRegion = D3D12_MIP_REGION{}
		};

		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Create upload vertex buffer.");
		Microsoft::WRL::ComPtr<ID3D12Resource2> uploadVertexBuffer;
		if (const HRESULT result = d3d12System->Device().CreateCommittedResource3(&UploadHeapProperties, D3D12_HEAP_FLAG_NONE, &vertexBufferDesc, D3D12_BARRIER_LAYOUT_UNDEFINED, nullptr, nullptr, 0, nullptr, IID_PPV_ARGS(uploadVertexBuffer.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to create vertex buffer with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		void* vertexData;
		if (const HRESULT result = uploadVertexBuffer->Map(0, nullptr, &vertexData); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to map vertex buffer with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		std::memcpy(vertexData, vertices.data(), vertexBufferSize);
		uploadVertexBuffer->Unmap(0, nullptr);
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Upload vertex buffer created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(uploadVertexBuffer.Get()));

		return Direct3D12VertexArray(*uploadVertexBuffer.Get(), MeshVertexFormat, vertexCount);
	}

	std::optional<Direct3D12VertexArray> Direct3D12MeshManager::CreateVertexColors(const std::span<const PonyMath::Color::RGBA<float>> colors) const
	{
		if (colors.size() == 0)
		{
			return std::nullopt;
		}

		const UINT colorCount = static_cast<UINT>(colors.size());
		const std::size_t colorBufferSize = MeshVertexColorFormat.VertexSize() * colorCount;

		const auto colorBufferDesc = D3D12_RESOURCE_DESC1
		{
			.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER,
			.Alignment = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT,
			.Width = static_cast<UINT64>(colorBufferSize),
			.Height = 1u,
			.DepthOrArraySize = 1u,
			.MipLevels = 1u,
			.Format = DXGI_FORMAT_UNKNOWN,
			.SampleDesc = DXGI_SAMPLE_DESC{.Count = 1u, .Quality = 0u},
			.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR,
			.Flags = D3D12_RESOURCE_FLAG_NONE,
			.SamplerFeedbackMipRegion = D3D12_MIP_REGION{}
		};

		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Create upload vertex color buffer.");
		Microsoft::WRL::ComPtr<ID3D12Resource2> uploadColorBuffer;
		if (const HRESULT result = d3d12System->Device().CreateCommittedResource3(&UploadHeapProperties, D3D12_HEAP_FLAG_NONE, &colorBufferDesc, D3D12_BARRIER_LAYOUT_UNDEFINED, nullptr, nullptr, 0, nullptr, IID_PPV_ARGS(uploadColorBuffer.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to create vertex color buffer with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		void* colorData;
		if (const HRESULT result = uploadColorBuffer->Map(0, nullptr, &colorData); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to map vertex color buffer with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		std::memcpy(colorData, colors.data(), colorBufferSize);
		uploadColorBuffer->Unmap(0, nullptr);
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Upload vertex color buffer created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(uploadColorBuffer.Get()));

		return Direct3D12VertexArray(*uploadColorBuffer.Get(), MeshVertexColorFormat, colorCount);
	}

	Direct3D12IndexArray Direct3D12MeshManager::CreateVertexIndices(const std::span<const PonyMath::Core::Vector3<std::uint32_t>> triangles) const
	{
		const UINT indexCount = static_cast<UINT>(triangles.size() * PonyMath::Core::Vector3<std::uint32_t>::ComponentCount);
		const std::size_t indexBufferSize = MeshIndexFormat.IndexSize() * indexCount;

		const auto indexBufferDesc = D3D12_RESOURCE_DESC1
		{
			.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER,
			.Alignment = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT,
			.Width = static_cast<UINT64>(indexBufferSize),
			.Height = 1u,
			.DepthOrArraySize = 1u,
			.MipLevels = 1u,
			.Format = DXGI_FORMAT_UNKNOWN,
			.SampleDesc = DXGI_SAMPLE_DESC{.Count = 1u, .Quality = 0u},
			.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR,
			.Flags = D3D12_RESOURCE_FLAG_NONE,
			.SamplerFeedbackMipRegion = D3D12_MIP_REGION{}
		};

		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Create upload index buffer.");
		Microsoft::WRL::ComPtr<ID3D12Resource2> uploadIndexBuffer;
		if (const HRESULT result = d3d12System->Device().CreateCommittedResource3(&UploadHeapProperties, D3D12_HEAP_FLAG_NONE, &indexBufferDesc, D3D12_BARRIER_LAYOUT_UNDEFINED, nullptr, nullptr, 0, nullptr, IID_PPV_ARGS(uploadIndexBuffer.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to create index buffer with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		void* indexData;
		if (const HRESULT result = uploadIndexBuffer->Map(0, nullptr, &indexData); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to map index buffer with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		std::memcpy(indexData, triangles.data(), indexBufferSize);
		uploadIndexBuffer->Unmap(0, nullptr);
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Upload index buffer created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(uploadIndexBuffer.Get()));

		return Direct3D12IndexArray(*uploadIndexBuffer.Get(), MeshIndexFormat, indexCount);
	}
}
