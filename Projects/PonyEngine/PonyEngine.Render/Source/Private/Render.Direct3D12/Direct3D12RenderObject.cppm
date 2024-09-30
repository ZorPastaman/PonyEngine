/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

export module PonyEngine.Render.Direct3D12:Direct3D12RenderObject;

import <cstddef>;
import <utility>;

import PonyEngine.Render;

import :Direct3D12Mesh;

export namespace PonyEngine::Render
{
	class Direct3D12RenderObject final
	{
	public:
		[[nodiscard("Pure constructor")]]
		Direct3D12RenderObject(std::size_t id, const Mesh& mesh, const Direct3D12Mesh& meshResource) noexcept;
		[[nodiscard("Pure constructor")]]
		Direct3D12RenderObject(const Direct3D12RenderObject& other) noexcept;
		[[nodiscard("Pure constructor")]]
		Direct3D12RenderObject(Direct3D12RenderObject&& other) noexcept;

		~Direct3D12RenderObject() noexcept = default;

		[[nodiscard("Pure function")]]
		std::size_t Id() const noexcept;

		[[nodiscard("Pure function")]]
		const Mesh& Mesh() const noexcept;
		[[nodiscard("Pure function")]]
		const Direct3D12Mesh& MeshResource() const noexcept;

		Direct3D12RenderObject& operator =(const Direct3D12RenderObject& other) noexcept;
		Direct3D12RenderObject& operator =(Direct3D12RenderObject&& other) noexcept;

	private:
		Render::Mesh mesh;
		Direct3D12Mesh meshResource;

		std::size_t id;
	};
}

namespace PonyEngine::Render
{
	Direct3D12RenderObject::Direct3D12RenderObject(const std::size_t id, const Render::Mesh& mesh, const Direct3D12Mesh& meshResource) noexcept :
		mesh(mesh),
		meshResource(meshResource),
		id{id}
	{
	}

	Direct3D12RenderObject::Direct3D12RenderObject(const Direct3D12RenderObject& other) noexcept :
		mesh{other.mesh},
		meshResource(other.meshResource),
		id{other.id}
	{
	}

	Direct3D12RenderObject::Direct3D12RenderObject(Direct3D12RenderObject&& other) noexcept :
		mesh{other.mesh},
		meshResource(std::move(other.meshResource)),
		id{other.id}
	{
	}

	std::size_t Direct3D12RenderObject::Id() const noexcept
	{
		return id;
	}

	const Mesh& Direct3D12RenderObject::Mesh() const noexcept
	{
		return mesh;
	}

	const Direct3D12Mesh& Direct3D12RenderObject::MeshResource() const noexcept
	{
		return meshResource;
	}

	Direct3D12RenderObject& Direct3D12RenderObject::operator =(const Direct3D12RenderObject& other) noexcept
	{
		mesh = other.mesh;
		meshResource = other.meshResource;

		return *this;
	}

	Direct3D12RenderObject& Direct3D12RenderObject::operator =(Direct3D12RenderObject&& other) noexcept
	{
		mesh = std::move(other.mesh);
		meshResource = std::move(other.meshResource);

		return *this;
	}
}
