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

export module PonyEngine.Render.Direct3D12.Implementation:Direct3D12Mesh;

import :Direct3D12IndexBuffer;
import :Direct3D12IndexFormat;
import :Direct3D12VertexBuffer;

export namespace PonyEngine::Render
{
	class Direct3D12Mesh final
	{
	public:
		[[nodiscard("Pure constructor")]]
		Direct3D12Mesh(const Direct3D12VertexBuffer& verticesBuffer, const Direct3D12VertexBuffer& vertexColorsBuffer, const Direct3D12IndexBuffer& vertexIndicesBuffer) noexcept;
		[[nodiscard("Pure constructor")]]
		Direct3D12Mesh(const Direct3D12Mesh& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Direct3D12Mesh(Direct3D12Mesh&& other) noexcept = default;

		~Direct3D12Mesh() noexcept = default;

		[[nodiscard("Pure function")]]
		const D3D12_VERTEX_BUFFER_VIEW& VerticesView() const noexcept;
		[[nodiscard("Pure function")]]
		const D3D12_VERTEX_BUFFER_VIEW& VertexColorsView() const noexcept;
		[[nodiscard("Pure function")]]
		const D3D12_INDEX_BUFFER_VIEW& VertexIndicesView() const noexcept;
		[[nodiscard("Pure function")]]
		UINT IndexCount() const noexcept;

		Direct3D12Mesh& operator =(const Direct3D12Mesh& other) noexcept = default;
		Direct3D12Mesh& operator =(Direct3D12Mesh&& other) noexcept = default;

	private:
		Microsoft::WRL::ComPtr<ID3D12Resource2> vertices;
		Microsoft::WRL::ComPtr<ID3D12Resource2> vertexColors;
		Microsoft::WRL::ComPtr<ID3D12Resource2> vertexIndices;

		D3D12_VERTEX_BUFFER_VIEW verticesView;
		D3D12_VERTEX_BUFFER_VIEW vertexColorsView;
		D3D12_INDEX_BUFFER_VIEW vertexIndicesView;

		UINT indexCount;
	};
}

namespace PonyEngine::Render
{
	Direct3D12Mesh::Direct3D12Mesh(const Direct3D12VertexBuffer& verticesBuffer, const Direct3D12VertexBuffer& vertexColorsBuffer, const Direct3D12IndexBuffer& vertexIndicesBuffer) noexcept :
		vertices(verticesBuffer.GetVerticesResource()),
		vertexColors(vertexColorsBuffer.GetVerticesResource()),
		vertexIndices(vertexIndicesBuffer.GetIndicesResource()),
		verticesView{.BufferLocation = vertices->GetGPUVirtualAddress(), .SizeInBytes = verticesBuffer.VertexSize() * verticesBuffer.VertexCount(), .StrideInBytes = verticesBuffer.VertexSize()},
		vertexColorsView{.BufferLocation = vertexColors->GetGPUVirtualAddress(), .SizeInBytes = vertexColorsBuffer.VertexSize() * vertexColorsBuffer.VertexCount(), .StrideInBytes = vertexColorsBuffer.VertexSize()},
		vertexIndicesView{.BufferLocation = vertexIndices->GetGPUVirtualAddress(), .SizeInBytes = vertexIndicesBuffer.IndexSize() * vertexIndicesBuffer.IndexCount(), .Format = vertexIndicesBuffer.IndexFormat()},
		indexCount{vertexIndicesBuffer.IndexCount()}
	{
	}

	const D3D12_VERTEX_BUFFER_VIEW& Direct3D12Mesh::VerticesView() const noexcept
	{
		return verticesView;
	}

	const D3D12_VERTEX_BUFFER_VIEW& Direct3D12Mesh::VertexColorsView() const noexcept
	{
		return vertexColorsView;
	}

	const D3D12_INDEX_BUFFER_VIEW& Direct3D12Mesh::VertexIndicesView() const noexcept
	{
		return vertexIndicesView;
	}

	UINT Direct3D12Mesh::IndexCount() const noexcept
	{
		return indexCount;
	}
}
