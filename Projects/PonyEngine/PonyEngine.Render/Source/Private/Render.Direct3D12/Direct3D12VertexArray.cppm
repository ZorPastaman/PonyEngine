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

export namespace PonyEngine::Render
{
	class Direct3D12VertexArray final
	{
	public:
		[[nodiscard("Pure constructor")]]
		Direct3D12VertexArray(ID3D12Resource2& vertexBuffer, UINT vertexSize, UINT vertexCount) noexcept;
		[[nodiscard("Pure constructor")]]
		Direct3D12VertexArray(const Direct3D12VertexArray& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Direct3D12VertexArray(Direct3D12VertexArray&& other) noexcept = default;

		~Direct3D12VertexArray() noexcept = default;

		[[nodiscard("Pure function")]]
		ID3D12Resource2& VertexBuffer() noexcept;
		[[nodiscard("Pure function")]]
		const ID3D12Resource2& VertexBuffer() const noexcept;

		[[nodiscard("Pure function")]]
		UINT VertexSize() const noexcept;
		[[nodiscard("Pure function")]]
		UINT VertexCount() const noexcept;

		Direct3D12VertexArray& operator =(const Direct3D12VertexArray& other) noexcept = default;
		Direct3D12VertexArray& operator =(Direct3D12VertexArray&& other) noexcept = default;

	private:
		Microsoft::WRL::ComPtr<ID3D12Resource2> vertexBuffer;
		UINT vertexSize;
		UINT vertexCount;
	};
}

namespace PonyEngine::Render
{
	Direct3D12VertexArray::Direct3D12VertexArray(ID3D12Resource2& vertexBuffer, const UINT vertexSize, const UINT vertexCount) noexcept :
		vertexBuffer(&vertexBuffer),
		vertexSize{vertexSize},
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

	UINT Direct3D12VertexArray::VertexSize() const noexcept
	{
		return vertexSize;
	}

	UINT Direct3D12VertexArray::VertexCount() const noexcept
	{
		return vertexCount;
	}
}
