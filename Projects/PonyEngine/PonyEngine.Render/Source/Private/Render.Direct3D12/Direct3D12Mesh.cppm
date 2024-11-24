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

export module PonyEngine.Render.Direct3D12.Detail:Direct3D12Mesh;

import :Direct3D12IndexArray;
import :Direct3D12IndexFormat;
import :Direct3D12VertexArray;

export namespace PonyEngine::Render
{
	class Direct3D12Mesh final
	{
	public:
		[[nodiscard("Pure constructor")]]
		Direct3D12Mesh(Direct3D12VertexArray& vertexArray, Direct3D12VertexArray& vertexColorArray, Direct3D12IndexArray& vertexIndexArray) noexcept;
		[[nodiscard("Pure constructor")]]
		Direct3D12Mesh(const Direct3D12Mesh& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Direct3D12Mesh(Direct3D12Mesh&& other) noexcept = default;

		~Direct3D12Mesh() noexcept = default;

		[[nodiscard("Pure function")]]
		const D3D12_VERTEX_BUFFER_VIEW& VertexBufferView() const noexcept;
		[[nodiscard("Pure function")]]
		const D3D12_VERTEX_BUFFER_VIEW& VertexColorBufferView() const noexcept; // TODO: Make it optional
		[[nodiscard("Pure function")]]
		const D3D12_INDEX_BUFFER_VIEW& VertexIndexBufferView() const noexcept;
		[[nodiscard("Pure function")]]
		UINT IndexCount() const noexcept;

		Direct3D12Mesh& operator =(const Direct3D12Mesh& other) noexcept = default;
		Direct3D12Mesh& operator =(Direct3D12Mesh&& other) noexcept = default;

	private:
		Microsoft::WRL::ComPtr<ID3D12Resource2> vertexBuffer;
		Microsoft::WRL::ComPtr<ID3D12Resource2> vertexColorBuffer;
		Microsoft::WRL::ComPtr<ID3D12Resource2> vertexIndexBuffer;

		D3D12_VERTEX_BUFFER_VIEW vertexBufferView;
		D3D12_VERTEX_BUFFER_VIEW vertexColorBufferView;
		D3D12_INDEX_BUFFER_VIEW vertexIndexView;

		UINT indexCount;
	};
}

namespace PonyEngine::Render
{
	Direct3D12Mesh::Direct3D12Mesh(Direct3D12VertexArray& vertexArray, Direct3D12VertexArray& vertexColorArray, Direct3D12IndexArray& vertexIndexArray) noexcept :
		vertexBuffer(&vertexArray.VertexBuffer()),
		vertexColorBuffer(&vertexColorArray.VertexBuffer()),
		vertexIndexBuffer(&vertexIndexArray.IndexBuffer()),
		vertexBufferView{.BufferLocation = vertexBuffer->GetGPUVirtualAddress(), .SizeInBytes = vertexArray.VertexSize() * vertexArray.VertexCount(), .StrideInBytes = vertexArray.VertexSize()},
		vertexColorBufferView{.BufferLocation = vertexColorBuffer->GetGPUVirtualAddress(), .SizeInBytes = vertexColorArray.VertexSize() * vertexColorArray.VertexCount(), .StrideInBytes = vertexColorArray.VertexSize()},
		vertexIndexView{.BufferLocation = vertexIndexBuffer->GetGPUVirtualAddress(), .SizeInBytes = vertexIndexArray.IndexSize() * vertexIndexArray.IndexCount(), .Format = vertexIndexArray.IndexFormat()},
		indexCount{vertexIndexArray.IndexCount()}
	{
	}

	const D3D12_VERTEX_BUFFER_VIEW& Direct3D12Mesh::VertexBufferView() const noexcept
	{
		return vertexBufferView;
	}

	const D3D12_VERTEX_BUFFER_VIEW& Direct3D12Mesh::VertexColorBufferView() const noexcept
	{
		return vertexColorBufferView;
	}

	const D3D12_INDEX_BUFFER_VIEW& Direct3D12Mesh::VertexIndexBufferView() const noexcept
	{
		return vertexIndexView;
	}

	UINT Direct3D12Mesh::IndexCount() const noexcept
	{
		return indexCount;
	}
}
