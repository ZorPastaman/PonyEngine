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

export module PonyEngine.Render.Direct3D12:Direct3D12Mesh;

import :Direct3D12IndexBuffer;
import :Direct3D12IndexFormat;
import :Direct3D12VertexBuffer;

export namespace PonyEngine::Render
{
	class Direct3D12Mesh final
	{
	public:
		[[nodiscard("Pure constructor")]]
		Direct3D12Mesh(const Direct3D12VertexBuffer& vertices, const Direct3D12VertexBuffer& vertexColors, const Direct3D12IndexBuffer& vertexIndices) noexcept;
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
		Direct3D12VertexBuffer vertices;
		Direct3D12VertexBuffer vertexColors;
		Direct3D12IndexBuffer vertexIndices;

		D3D12_VERTEX_BUFFER_VIEW verticesView;
		D3D12_VERTEX_BUFFER_VIEW vertexColorsView;
		D3D12_INDEX_BUFFER_VIEW vertexIndicesView;
	};
}

namespace PonyEngine::Render
{
	Direct3D12Mesh::Direct3D12Mesh(const Direct3D12VertexBuffer& vertices, const Direct3D12VertexBuffer& vertexColors, const Direct3D12IndexBuffer& vertexIndices) noexcept :
		vertices(vertices),
		vertexColors(vertexColors),
		vertexIndices(vertexIndices),
		verticesView{.BufferLocation = this->vertices.GetVertexResource()->GetGPUVirtualAddress(), .SizeInBytes = this->vertices.VertexSize() * this->vertices.VertexCount(), .StrideInBytes = this->vertices.VertexSize()},
		vertexColorsView{.BufferLocation = this->vertexColors.GetVertexResource()->GetGPUVirtualAddress(), .SizeInBytes = this->vertexColors.VertexSize() * this->vertexColors.VertexCount(), .StrideInBytes = this->vertexColors.VertexSize()},
		vertexIndicesView{.BufferLocation = this->vertexIndices.GetIndexResource()->GetGPUVirtualAddress(), .SizeInBytes = this->vertexIndices.IndexSize() * this->vertexIndices.IndexCount(), .Format = this->vertexIndices.IndexFormat()}
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
		return vertexIndices.IndexCount();
	}
}
