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

import <optional>;
import <string>;
import <string_view>;

import :Direct3D12IndexArray;
import :Direct3D12IndexFormat;
import :Direct3D12VertexArray;
import :Direct3D12Utility;

export namespace PonyEngine::Render
{
	/// @brief Direct3D12 mesh.
	class Direct3D12Mesh final
	{
	public:
		/// @brief Creates a @p Direct3D12Mesh.
		/// @param vertexArray Vertex array.
		/// @param vertexColorArray Vertex color array. It may be @a nullptr if the mesh doesn't contain vertex colors.
		/// @param vertexIndexArray Vertex index array.
		[[nodiscard("Pure constructor")]]
		Direct3D12Mesh(Direct3D12VertexArray& vertexArray, Direct3D12VertexArray* vertexColorArray, Direct3D12IndexArray& vertexIndexArray) noexcept;
		[[nodiscard("Pure constructor")]]
		Direct3D12Mesh(const Direct3D12Mesh& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Direct3D12Mesh(Direct3D12Mesh&& other) noexcept = default;

		~Direct3D12Mesh() noexcept = default;

		/// @brief Gets the vertex buffer.
		/// @return Vertex buffer.
		[[nodiscard("Pure function")]]
		ID3D12Resource2& VertexBuffer() noexcept;
		/// @brief Gets the vertex buffer.
		/// @return Vertex buffer.
		[[nodiscard("Pure function")]]
		const ID3D12Resource2& VertexBuffer() const noexcept;
		/// @brief Gets the vertex color buffer.
		/// @return Vertex color buffer.
		[[nodiscard("Pure function")]]
		ID3D12Resource2* VertexColorBuffer() noexcept;
		/// @brief Gets the vertex color buffer.
		/// @return Vertex color buffer.
		[[nodiscard("Pure function")]]
		const ID3D12Resource2* VertexColorBuffer() const noexcept;
		/// @brief Gets the vertex index buffer.
		/// @return Vertex index buffer.
		[[nodiscard("Pure function")]]
		ID3D12Resource2& VertexIndexBuffer() noexcept;
		/// @brief Gets the vertex index buffer.
		/// @return Vertex index buffer.
		[[nodiscard("Pure function")]]
		const ID3D12Resource2& VertexIndexBuffer() const noexcept;

		/// @brief Gets the vertex buffer view.
		/// @return Vertex buffer view.
		[[nodiscard("Pure function")]]
		const D3D12_VERTEX_BUFFER_VIEW& VertexBufferView() const noexcept;
		/// @brief Gets the vertex color buffer view.
		/// @return Vertex color buffer view. May be @a nullopt if the mesh doesn't contain vertex colors.
		[[nodiscard("Pure function")]]
		const std::optional<D3D12_VERTEX_BUFFER_VIEW>& VertexColorBufferView() const noexcept;
		/// @brief Gets the vertex index buffer view.
		/// @return Vertex index buffer view.
		[[nodiscard("Pure function")]]
		const D3D12_INDEX_BUFFER_VIEW& VertexIndexBufferView() const noexcept;

		/// @brief Gets the index count.
		/// @return Index count.
		[[nodiscard("Pure function")]]
		UINT IndexCount() const noexcept;

		/// @brief Sets the name to the mesh components.
		/// @param name Name.
		void Name(std::string_view name);

		Direct3D12Mesh& operator =(const Direct3D12Mesh& other) noexcept = default;
		Direct3D12Mesh& operator =(Direct3D12Mesh&& other) noexcept = default;

	private:
		Microsoft::WRL::ComPtr<ID3D12Resource2> vertexBuffer; ///< Vertex buffer.
		Microsoft::WRL::ComPtr<ID3D12Resource2> vertexColorBuffer; ///< Vertex color buffer.
		Microsoft::WRL::ComPtr<ID3D12Resource2> vertexIndexBuffer; ///< Vertex index buffer.

		D3D12_VERTEX_BUFFER_VIEW vertexBufferView; ///< Vertex buffer view.
		std::optional<D3D12_VERTEX_BUFFER_VIEW> vertexColorBufferView; ///< Vertex color buffer view.
		D3D12_INDEX_BUFFER_VIEW vertexIndexBufferView; ///< Vertex index buffer view.

		UINT indexCount; ///< Index count.
	};
}

namespace PonyEngine::Render
{
	Direct3D12Mesh::Direct3D12Mesh(Direct3D12VertexArray& vertexArray, Direct3D12VertexArray* vertexColorArray, Direct3D12IndexArray& vertexIndexArray) noexcept :
		vertexBuffer(&vertexArray.VertexBuffer()),
		vertexColorBuffer(vertexColorArray ? &vertexColorArray->VertexBuffer() : nullptr),
		vertexIndexBuffer(&vertexIndexArray.IndexBuffer()),
		vertexBufferView
		{
			.BufferLocation = vertexBuffer->GetGPUVirtualAddress(),
			.SizeInBytes = vertexArray.ArraySize(),
			.StrideInBytes = vertexArray.VertexFormat().VertexSize()
		},
		vertexColorBufferView(
			vertexColorArray 
				? D3D12_VERTEX_BUFFER_VIEW
				{
					.BufferLocation = vertexColorBuffer->GetGPUVirtualAddress(),
					.SizeInBytes = vertexColorArray->ArraySize(),
					.StrideInBytes = vertexColorArray->VertexFormat().VertexSize()
				} 
				: std::optional<D3D12_VERTEX_BUFFER_VIEW>(std::nullopt)
		),
		vertexIndexBufferView
		{
			.BufferLocation = vertexIndexBuffer->GetGPUVirtualAddress(),
			.SizeInBytes = vertexIndexArray.ArraySize(),
			.Format = vertexIndexArray.IndexFormat().IndexFormat()
		},
		indexCount{vertexIndexArray.IndexCount()}
	{
	}

	ID3D12Resource2& Direct3D12Mesh::VertexBuffer() noexcept
	{
		return *vertexBuffer.Get();
	}

	const ID3D12Resource2& Direct3D12Mesh::VertexBuffer() const noexcept
	{
		return *vertexBuffer.Get();
	}

	ID3D12Resource2* Direct3D12Mesh::VertexColorBuffer() noexcept
	{
		return vertexColorBuffer.Get();
	}

	const ID3D12Resource2* Direct3D12Mesh::VertexColorBuffer() const noexcept
	{
		return vertexColorBuffer.Get();
	}

	ID3D12Resource2& Direct3D12Mesh::VertexIndexBuffer() noexcept
	{
		return *vertexIndexBuffer.Get();
	}

	const ID3D12Resource2& Direct3D12Mesh::VertexIndexBuffer() const noexcept
	{
		return *vertexIndexBuffer.Get();
	}

	const D3D12_VERTEX_BUFFER_VIEW& Direct3D12Mesh::VertexBufferView() const noexcept
	{
		return vertexBufferView;
	}

	const std::optional<D3D12_VERTEX_BUFFER_VIEW>& Direct3D12Mesh::VertexColorBufferView() const noexcept
	{
		return vertexColorBufferView;
	}

	const D3D12_INDEX_BUFFER_VIEW& Direct3D12Mesh::VertexIndexBufferView() const noexcept
	{
		return vertexIndexBufferView;
	}

	UINT Direct3D12Mesh::IndexCount() const noexcept
	{
		return indexCount;
	}

	void Direct3D12Mesh::Name(const std::string_view name)
	{
		constexpr std::string_view vertexName = " - VertexBuffer";
		constexpr std::string_view colorName = " - ColorBuffer";
		constexpr std::string_view indexName = " - IndexBuffer";

		auto componentName = std::string();
		componentName.reserve(name.size() + vertexName.size());

		componentName.append(name).append(vertexName);
		SetName(*vertexBuffer.Get(), componentName);

		if (vertexColorBuffer)
		{
			componentName.erase();
			componentName.append(name).append(colorName);
			SetName(*vertexColorBuffer.Get(), componentName);
		}

		componentName.erase();
		componentName.append(name).append(indexName);
		SetName(*vertexIndexBuffer.Get(), componentName);
	}
}
