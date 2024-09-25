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

export namespace PonyEngine::Render
{
	class Direct3D12Mesh final
	{
	public:
		[[nodiscard("Pure constructor")]]
		Direct3D12Mesh(const Microsoft::WRL::ComPtr<ID3D12Resource2>& vertexPositionResource, const Microsoft::WRL::ComPtr<ID3D12Resource2>& vertexColorResource, const Microsoft::WRL::ComPtr<ID3D12Resource2>& vertexIndexResource,
			const D3D12_VERTEX_BUFFER_VIEW& vertexPositionView, const D3D12_VERTEX_BUFFER_VIEW& vertexColorView, const D3D12_INDEX_BUFFER_VIEW& vertexIndexView) noexcept;
		[[nodiscard("Pure constructor")]]
		Direct3D12Mesh(const Direct3D12Mesh& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Direct3D12Mesh(Direct3D12Mesh&& other) noexcept = default;

		~Direct3D12Mesh() noexcept = default;

		[[nodiscard("Pure function")]]
		const D3D12_VERTEX_BUFFER_VIEW& VertexPositionView() const noexcept;
		[[nodiscard("Pure function")]]
		const D3D12_VERTEX_BUFFER_VIEW& VertexColorView() const noexcept;
		[[nodiscard("Pure function")]]
		const D3D12_INDEX_BUFFER_VIEW& VertexIndexView() const noexcept;

		Direct3D12Mesh& operator =(const Direct3D12Mesh& other) noexcept = default;
		Direct3D12Mesh& operator =(Direct3D12Mesh&& other) noexcept = default;

	private:
		Microsoft::WRL::ComPtr<ID3D12Resource2> vertexPositionResource;
		Microsoft::WRL::ComPtr<ID3D12Resource2> vertexColorResource;
		Microsoft::WRL::ComPtr<ID3D12Resource2> vertexIndexResource;

		D3D12_VERTEX_BUFFER_VIEW vertexPositionView;
		D3D12_VERTEX_BUFFER_VIEW vertexColorView;
		D3D12_INDEX_BUFFER_VIEW vertexIndexView;
	};
}

namespace PonyEngine::Render
{
	Direct3D12Mesh::Direct3D12Mesh(const Microsoft::WRL::ComPtr<ID3D12Resource2>& vertexPositionResource, const Microsoft::WRL::ComPtr<ID3D12Resource2>& vertexColorResource, const Microsoft::WRL::ComPtr<ID3D12Resource2>& vertexIndexResource,
		const D3D12_VERTEX_BUFFER_VIEW& vertexPositionView, const D3D12_VERTEX_BUFFER_VIEW& vertexColorView, const D3D12_INDEX_BUFFER_VIEW& vertexIndexView) noexcept :
		vertexPositionResource(vertexPositionResource),
		vertexColorResource(vertexColorResource),
		vertexIndexResource(vertexIndexResource),
		vertexPositionView(vertexPositionView),
		vertexColorView(vertexColorView),
		vertexIndexView(vertexIndexView)
	{
	}

	const D3D12_VERTEX_BUFFER_VIEW& Direct3D12Mesh::VertexPositionView() const noexcept
	{
		return vertexPositionView;
	}

	const D3D12_VERTEX_BUFFER_VIEW& Direct3D12Mesh::VertexColorView() const noexcept
	{
		return vertexColorView;
	}

	const D3D12_INDEX_BUFFER_VIEW& Direct3D12Mesh::VertexIndexView() const noexcept
	{
		return vertexIndexView;
	}
}
