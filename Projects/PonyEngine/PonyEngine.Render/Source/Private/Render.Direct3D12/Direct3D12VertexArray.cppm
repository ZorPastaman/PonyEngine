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

export module PonyEngine.Render.Direct3D12.Detail:Direct3D12VertexArray;

import :Direct3D12VertexFormat;

export namespace PonyEngine::Render
{
	/// @brief Direct3D12 vertex array.
	class Direct3D12VertexArray final
	{
	public:
		/// @brief Creates a @p Direct3D12VertexArray.
		/// @param vertexBuffer Vertex buffer.
		/// @param vertexFormat Vertex format.
		/// @param vertexCount Vertex count.
		[[nodiscard("Pure constructor")]]
		Direct3D12VertexArray(ID3D12Resource2& vertexBuffer, const Direct3D12VertexFormat& vertexFormat, UINT vertexCount) noexcept;
		[[nodiscard("Pure constructor")]]
		Direct3D12VertexArray(const Direct3D12VertexArray& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Direct3D12VertexArray(Direct3D12VertexArray&& other) noexcept = default;

		~Direct3D12VertexArray() noexcept = default;

		/// @brief Gets the vertex buffer.
		/// @return Vertex buffer.
		[[nodiscard("Pure function")]]
		ID3D12Resource2& VertexBuffer() noexcept;
		/// @brief Gets the vertex buffer.
		/// @return Vertex buffer.
		[[nodiscard("Pure function")]]
		const ID3D12Resource2& VertexBuffer() const noexcept;

		/// @brief Gets the vertex format.
		/// @return Vertex format.
		[[nodiscard("Pure function")]]
		const Direct3D12VertexFormat& VertexFormat() const noexcept;
		/// @brief Gets the vertex count.
		/// @return Vertex count.
		[[nodiscard("Pure function")]]
		UINT VertexCount() const noexcept;

		/// @brief Gets the array size.
		/// @return Array size.
		[[nodiscard("Pure function")]]
		UINT ArraySize() const noexcept;

		Direct3D12VertexArray& operator =(const Direct3D12VertexArray& other) noexcept = default;
		Direct3D12VertexArray& operator =(Direct3D12VertexArray&& other) noexcept = default;

	private:
		Microsoft::WRL::ComPtr<ID3D12Resource2> vertexBuffer; ///< Vertex buffer.
		Direct3D12VertexFormat vertexFormat; ///< Vertex format.
		UINT vertexCount; ///< Vertex count.
	};
}

namespace PonyEngine::Render
{
	Direct3D12VertexArray::Direct3D12VertexArray(ID3D12Resource2& vertexBuffer, const Direct3D12VertexFormat& vertexFormat, const UINT vertexCount) noexcept :
		vertexBuffer(&vertexBuffer),
		vertexFormat(vertexFormat),
		vertexCount{vertexCount}
	{
	}

	ID3D12Resource2& Direct3D12VertexArray::VertexBuffer() noexcept
	{
		return *vertexBuffer.Get();
	}

	const ID3D12Resource2& Direct3D12VertexArray::VertexBuffer() const noexcept
	{
		return *vertexBuffer.Get();
	}

	const Direct3D12VertexFormat& Direct3D12VertexArray::VertexFormat() const noexcept
	{
		return vertexFormat;
	}

	UINT Direct3D12VertexArray::VertexCount() const noexcept
	{
		return vertexCount;
	}

	UINT Direct3D12VertexArray::ArraySize() const noexcept
	{
		return vertexFormat.VertexSize() * vertexCount;
	}
}
