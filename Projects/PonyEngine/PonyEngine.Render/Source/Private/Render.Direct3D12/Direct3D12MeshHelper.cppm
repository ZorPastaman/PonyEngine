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

export module PonyEngine.Render.Direct3D12:Direct3D12MeshHelper;

import <algorithm>;
import <cstddef>;
import <cstdint>;
import <cstring>;
import <span>;

import PonyBase.Geometry;
import PonyBase.Math;
import PonyBase.StringUtility;

import :Direct3D12Mesh;
import :Direct3D12VertexBuffer;

export namespace PonyEngine::Render
{
	[[nodiscard("Pure constructor")]]
	Direct3D12Mesh CreateDirect3D12Mesh(ID3D12Device10* device, const PonyBase::Geometry::Mesh& mesh);
}

namespace PonyEngine::Render
{
	[[nodiscard("Pure constructor")]]
	Direct3D12VertexBuffer CreateVertices(const D3D12_HEAP_PROPERTIES& heapProperties, ID3D12Device10* device, std::span<const PonyBase::Math::Vector3<float>> vertices);
	[[nodiscard("Pure constructor")]]
	Direct3D12VertexBuffer CreateVertexColors(const D3D12_HEAP_PROPERTIES& heapProperties, ID3D12Device10* device, std::span<const PonyBase::Math::RGBA<float>> colors, std::size_t vertexCount);
	[[nodiscard("Pure constructor")]]
	Direct3D12IndexBuffer CreateVertexIndices(const D3D12_HEAP_PROPERTIES& heapProperties, ID3D12Device10* device, std::span<const PonyBase::Math::Vector3<std::uint32_t>> triangles);

	Direct3D12Mesh CreateDirect3D12Mesh(ID3D12Device10* const device, const PonyBase::Geometry::Mesh& mesh)
	{
		constexpr auto heapProperties = D3D12_HEAP_PROPERTIES
		{
			.Type = D3D12_HEAP_TYPE_UPLOAD,
			.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN,
			.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN,
			.CreationNodeMask = 0u,
			.VisibleNodeMask = 0u
		};

		const Direct3D12VertexBuffer vertices = CreateVertices(heapProperties, device, mesh.Vertices());
		const Direct3D12VertexBuffer colors = CreateVertexColors(heapProperties, device, mesh.Colors(), mesh.VertexCount());
		const Direct3D12IndexBuffer indices = CreateVertexIndices(heapProperties, device, mesh.Triangles());

		return Direct3D12Mesh(vertices, colors, indices);
	}

	Direct3D12VertexBuffer CreateVertices(const D3D12_HEAP_PROPERTIES& heapProperties, ID3D12Device10* const device, const std::span<const PonyBase::Math::Vector3<float>> vertices)
	{
		constexpr UINT vertexSize = sizeof(PonyBase::Math::Vector3<float>);
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
		if (const HRESULT result = device->CreateCommittedResource3(&heapProperties, D3D12_HEAP_FLAG_NONE, &verticesDescription, D3D12_BARRIER_LAYOUT_UNDEFINED, nullptr, nullptr, 0, nullptr, IID_PPV_ARGS(verticesResource.GetAddressOf())); FAILED(result)) [[unlikely]]
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

		return Direct3D12VertexBuffer(verticesResource, vertexSize, vertexCount);
	}

	Direct3D12VertexBuffer CreateVertexColors(const D3D12_HEAP_PROPERTIES& heapProperties, ID3D12Device10* const device, const std::span<const PonyBase::Math::RGBA<float>> colors, const std::size_t vertexCount)
	{
		constexpr UINT colorSize = sizeof(PonyBase::Math::RGBA<float>);
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
		if (const HRESULT result = device->CreateCommittedResource3(&heapProperties, D3D12_HEAP_FLAG_NONE, &colorsDescription, D3D12_BARRIER_LAYOUT_UNDEFINED, nullptr, nullptr, 0, nullptr, IID_PPV_ARGS(colorsResource.GetAddressOf())); FAILED(result)) [[unlikely]]
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
			std::fill_n(static_cast<PonyBase::Math::RGBA<float>*>(colorsData), colorCount, PonyBase::Math::RGBA<float>::Predefined::White);
		}
		colorsResource->Unmap(0, nullptr);

		return Direct3D12VertexBuffer(colorsResource, colorSize, colorCount);
	}

	Direct3D12IndexBuffer CreateVertexIndices(const D3D12_HEAP_PROPERTIES& heapProperties, ID3D12Device10* const device, const std::span<const PonyBase::Math::Vector3<std::uint32_t>> triangles)
	{
		constexpr std::size_t indexSize = sizeof(std::uint32_t);
		const UINT indexCount = static_cast<UINT>(triangles.size() * PonyBase::Math::Vector3<std::uint32_t>::ComponentCount);
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
		if (const HRESULT result = device->CreateCommittedResource3(&heapProperties, D3D12_HEAP_FLAG_NONE, &indicesDescription, D3D12_BARRIER_LAYOUT_UNDEFINED, nullptr, nullptr, 0, nullptr, IID_PPV_ARGS(indicesResource.GetAddressOf())); FAILED(result)) [[unlikely]]
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

		return Direct3D12IndexBuffer(indicesResource, Direct3D12IndexFormat(indexSize), indexCount);
	}
}
