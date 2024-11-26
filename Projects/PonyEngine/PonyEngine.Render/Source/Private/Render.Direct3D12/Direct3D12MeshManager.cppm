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

import <algorithm>;
import <cstddef>;
import <cstdint>;
import <cstring>;
import <memory>;
import <span>;
import <stdexcept>;
import <type_traits>;
import <unordered_map>;

import PonyBase.StringUtility;

import PonyMath.Color;
import PonyMath.Core;
import PonyMath.Geometry;

import PonyDebug.Log;

import PonyEngine.Render.Detail;

import :Direct3D12Mesh;
import :Direct3D12IndexArray;
import :Direct3D12VertexArray;
import :IDirect3D12MeshManagerPrivate;
import :IDirect3D12SystemContext;

export namespace PonyEngine::Render
{
	class Direct3D12MeshManager final : public IDirect3D12MeshManagerPrivate
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit Direct3D12MeshManager(IDirect3D12SystemContext& renderContext); // TODO: Add other constructors and destructor.

		[[nodiscard("Pure constructor")]]
		virtual std::shared_ptr<Direct3D12Mesh> CreateDirect3D12Mesh(const PonyMath::Geometry::Mesh& mesh) override;

	private:
		[[nodiscard("Pure constructor")]]
		Direct3D12VertexArray CreateVertices(std::span<const PonyMath::Core::Vector3<float>> vertices) const;
		[[nodiscard("Pure constructor")]]
		Direct3D12VertexArray CreateVertexColors(std::span<const PonyMath::Color::RGBA<float>> colors, std::size_t vertexCount) const;
		[[nodiscard("Pure constructor")]]
		Direct3D12IndexArray CreateVertexIndices(std::span<const PonyMath::Core::Vector3<std::uint32_t>> triangles) const;

		static constexpr auto HeapProperties = D3D12_HEAP_PROPERTIES
		{
			.Type = D3D12_HEAP_TYPE_UPLOAD,
			.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN,
			.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN,
			.CreationNodeMask = 0u,
			.VisibleNodeMask = 0u
		};

		IDirect3D12SystemContext* renderContext;
	};
}

namespace PonyEngine::Render
{
	Direct3D12MeshManager::Direct3D12MeshManager(IDirect3D12SystemContext& renderContext) :
		renderContext{&renderContext}
	{
	}

	std::shared_ptr<Direct3D12Mesh> Direct3D12MeshManager::CreateDirect3D12Mesh(const PonyMath::Geometry::Mesh& mesh)
	{
		PONY_LOG(renderContext->Logger(), PonyDebug::Log::LogType::Debug, "Create mesh vertices.");
		Direct3D12VertexArray vertices = CreateVertices(mesh.Vertices());
		PONY_LOG(renderContext->Logger(), PonyDebug::Log::LogType::Debug, "Mesh vertices created.");
		PONY_LOG(renderContext->Logger(), PonyDebug::Log::LogType::Debug, "Create mesh vertex colors.");
		Direct3D12VertexArray colors = CreateVertexColors(mesh.Colors(), mesh.VertexCount());
		PONY_LOG(renderContext->Logger(), PonyDebug::Log::LogType::Debug, "Mesh vertex colors created.");
		PONY_LOG(renderContext->Logger(), PonyDebug::Log::LogType::Debug, "Create mesh indices.");
		Direct3D12IndexArray indices = CreateVertexIndices(mesh.Triangles());
		PONY_LOG(renderContext->Logger(), PonyDebug::Log::LogType::Debug, "Mesh indices created.");

		return std::make_shared<Direct3D12Mesh>(vertices, &colors, indices);
	}

	Direct3D12VertexArray Direct3D12MeshManager::CreateVertices(const std::span<const PonyMath::Core::Vector3<float>> vertices) const
	{
		constexpr UINT vertexSize = sizeof(PonyMath::Core::Vector3<float>);
		const UINT vertexCount = static_cast<UINT>(vertices.size());
		const std::size_t vertexBufferSize = vertexSize * vertexCount;
		const auto verticesDescription = D3D12_RESOURCE_DESC1
		{
			.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER,
			.Alignment = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT,
			.Width = vertexBufferSize,
			.Height = 1u,
			.DepthOrArraySize = 1u,
			.MipLevels = 1u,
			.Format = DXGI_FORMAT_UNKNOWN,
			.SampleDesc = DXGI_SAMPLE_DESC{.Count = 1u, .Quality = 0u},
			.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR,
			.Flags = D3D12_RESOURCE_FLAG_NONE,
			.SamplerFeedbackMipRegion = D3D12_MIP_REGION{}
		};

		Microsoft::WRL::ComPtr<ID3D12Resource2> verticesResource;
		if (const HRESULT result = renderContext->Device().CreateCommittedResource3(&HeapProperties, D3D12_HEAP_FLAG_NONE, &verticesDescription, D3D12_BARRIER_LAYOUT_UNDEFINED, nullptr, nullptr, 0, nullptr, IID_PPV_ARGS(verticesResource.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to create vertices resource with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		void* verticesData;
		if (const HRESULT result = verticesResource->Map(0, nullptr, &verticesData); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to map vertices resource with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		std::memcpy(verticesData, vertices.data(), vertexBufferSize);
		verticesResource->Unmap(0, nullptr);

		return Direct3D12VertexArray(*verticesResource.Get(), vertexSize, vertexCount);
	}

	Direct3D12VertexArray Direct3D12MeshManager::CreateVertexColors(const std::span<const PonyMath::Color::RGBA<float>> colors, const std::size_t vertexCount) const
	{
		constexpr UINT colorSize = sizeof(PonyMath::Color::RGBA<float>);
		const UINT colorCount = static_cast<UINT>(colors.size() > 0 ? colors.size() : vertexCount);
		const std::size_t colorBufferSize = colorSize * colorCount;
		const auto colorsDescription = D3D12_RESOURCE_DESC1
		{
			.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER,
			.Alignment = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT,
			.Width = colorBufferSize,
			.Height = 1u,
			.DepthOrArraySize = 1u,
			.MipLevels = 1u,
			.Format = DXGI_FORMAT_UNKNOWN,
			.SampleDesc = DXGI_SAMPLE_DESC{.Count = 1u, .Quality = 0u},
			.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR,
			.Flags = D3D12_RESOURCE_FLAG_NONE,
			.SamplerFeedbackMipRegion = D3D12_MIP_REGION{}
		};

		Microsoft::WRL::ComPtr<ID3D12Resource2> colorsResource;
		if (const HRESULT result = renderContext->Device().CreateCommittedResource3(&HeapProperties, D3D12_HEAP_FLAG_NONE, &colorsDescription, D3D12_BARRIER_LAYOUT_UNDEFINED, nullptr, nullptr, 0, nullptr, IID_PPV_ARGS(colorsResource.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to create vertex colors resource with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		void* colorsData;
		if (const HRESULT result = colorsResource->Map(0, nullptr, &colorsData); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to map vertices resource with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		if (colors.size() > 0)
		{
			std::memcpy(colorsData, colors.data(), colorBufferSize);
		}
		else
		{
			std::fill_n(static_cast<PonyMath::Color::RGBA<float>*>(colorsData), colorCount, PonyMath::Color::RGBA<float>::Predefined::White);
		}
		colorsResource->Unmap(0, nullptr);

		return Direct3D12VertexArray(*colorsResource.Get(), colorSize, colorCount);
	}

	Direct3D12IndexArray Direct3D12MeshManager::CreateVertexIndices(const std::span<const PonyMath::Core::Vector3<std::uint32_t>> triangles) const
	{
		constexpr std::size_t indexSize = sizeof(std::uint32_t);
		const UINT indexCount = static_cast<UINT>(triangles.size() * PonyMath::Core::Vector3<std::uint32_t>::ComponentCount);
		const std::size_t indexBufferSize = indexSize * indexCount;
		const auto indicesDescription = D3D12_RESOURCE_DESC1
		{
			.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER,
			.Alignment = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT,
			.Width = indexBufferSize,
			.Height = 1u,
			.DepthOrArraySize = 1u,
			.MipLevels = 1u,
			.Format = DXGI_FORMAT_UNKNOWN,
			.SampleDesc = DXGI_SAMPLE_DESC{.Count = 1u, .Quality = 0u},
			.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR,
			.Flags = D3D12_RESOURCE_FLAG_NONE,
			.SamplerFeedbackMipRegion = D3D12_MIP_REGION{}
		};

		Microsoft::WRL::ComPtr<ID3D12Resource2> indicesResource;
		if (const HRESULT result = renderContext->Device().CreateCommittedResource3(&HeapProperties, D3D12_HEAP_FLAG_NONE, &indicesDescription, D3D12_BARRIER_LAYOUT_UNDEFINED, nullptr, nullptr, 0, nullptr, IID_PPV_ARGS(indicesResource.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to create vertex indices resource with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		void* indicesData;
		if (const HRESULT result = indicesResource->Map(0, nullptr, &indicesData); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to map vertex indices resource with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		std::memcpy(indicesData, triangles.data(), indexBufferSize);
		indicesResource->Unmap(0, nullptr);

		return Direct3D12IndexArray(*indicesResource.Get(), Direct3D12IndexFormat(indexSize), indexCount);
	}
}
