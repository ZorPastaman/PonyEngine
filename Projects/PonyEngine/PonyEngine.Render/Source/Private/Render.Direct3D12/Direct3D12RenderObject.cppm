/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Direct3D12:Direct3D12RenderObject;

import <utility>;

import :Direct3D12Mesh;

export namespace PonyEngine::Render
{
	class Direct3D12RenderObject final
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit Direct3D12RenderObject(const Direct3D12Mesh& meshResource) noexcept;
		[[nodiscard("Pure constructor")]]
		Direct3D12RenderObject(const Direct3D12RenderObject& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Direct3D12RenderObject(Direct3D12RenderObject&& other) noexcept = default;

		~Direct3D12RenderObject() noexcept = default;

		[[nodiscard("Pure function")]]
		const Direct3D12Mesh& MeshResource() const noexcept;

		Direct3D12RenderObject& operator =(const Direct3D12RenderObject& other) noexcept = default;
		Direct3D12RenderObject& operator =(Direct3D12RenderObject&& other) noexcept = default;

	private:
		Direct3D12Mesh meshResource;
	};
}

namespace PonyEngine::Render
{
	Direct3D12RenderObject::Direct3D12RenderObject(const Direct3D12Mesh& meshResource) noexcept :
		meshResource(meshResource)
	{
	}

	const Direct3D12Mesh& Direct3D12RenderObject::MeshResource() const noexcept
	{
		return meshResource;
	}
}
