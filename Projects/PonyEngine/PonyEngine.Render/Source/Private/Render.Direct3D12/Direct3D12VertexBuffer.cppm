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

export module PonyEngine.Render.Direct3D12:Direct3D12VertexBuffer;

export namespace PonyEngine::Render
{
	class Direct3D12VertexBuffer final
	{
	public:
		[[nodiscard("Pure constructor")]]
		Direct3D12VertexBuffer(ID3D12Resource2* verticesResource, UINT vertexSize, UINT vertexCount) noexcept;
		[[nodiscard("Pure constructor")]]
		Direct3D12VertexBuffer(const Direct3D12VertexBuffer& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Direct3D12VertexBuffer(Direct3D12VertexBuffer&& other) noexcept = default;

		~Direct3D12VertexBuffer() noexcept = default;

		[[nodiscard("Pure function")]]
		ID3D12Resource2* GetVerticesResource() const noexcept;

		[[nodiscard("Pure function")]]
		UINT VertexSize() const noexcept;
		[[nodiscard("Pure function")]]
		UINT VertexCount() const noexcept;

		Direct3D12VertexBuffer& operator =(const Direct3D12VertexBuffer& other) noexcept = default;
		Direct3D12VertexBuffer& operator =(Direct3D12VertexBuffer&& other) noexcept = default;

	private:
		Microsoft::WRL::ComPtr<ID3D12Resource2> verticesResource;
		UINT vertexSize;
		UINT vertexCount;
	};
}

namespace PonyEngine::Render
{
	Direct3D12VertexBuffer::Direct3D12VertexBuffer(ID3D12Resource2* const verticesResource, const UINT vertexSize, const UINT vertexCount) noexcept :
		verticesResource(verticesResource),
		vertexSize{vertexSize},
		vertexCount{vertexCount}
	{
	}

	ID3D12Resource2* Direct3D12VertexBuffer::GetVerticesResource() const noexcept
	{
		return verticesResource.Get();
	}

	UINT Direct3D12VertexBuffer::VertexSize() const noexcept
	{
		return vertexSize;
	}

	UINT Direct3D12VertexBuffer::VertexCount() const noexcept
	{
		return vertexCount;
	}
}
