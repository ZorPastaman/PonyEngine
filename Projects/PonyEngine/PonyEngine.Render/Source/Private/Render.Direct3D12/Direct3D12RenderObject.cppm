/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Direct3D12:Direct3D12RenderObject;

import <cstddef>;

import PonyEngine.Render;

export namespace PonyEngine::Render
{
	class Direct3D12RenderObject final : public IRenderObject
	{
	public:
		[[nodiscard("Pure constructor")]]
		Direct3D12RenderObject(const Render::Mesh& mesh, std::size_t id) noexcept;
		[[nodiscard("Pure constructor")]]
		Direct3D12RenderObject(const Direct3D12RenderObject& other) noexcept;
		[[nodiscard("Pure constructor")]]
		Direct3D12RenderObject(Direct3D12RenderObject&& other) noexcept;

		~Direct3D12RenderObject() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual std::size_t Id() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual const Render::Mesh& Mesh() const noexcept override;

		Direct3D12RenderObject& operator =(const Direct3D12RenderObject& other) noexcept;
		Direct3D12RenderObject& operator =(Direct3D12RenderObject&& other) noexcept;

	private:
		const Render::Mesh* mesh;
		std::size_t id; // TODO: remove id. It isn't needed with unique_ptr
	};
}

namespace PonyEngine::Render
{
	Direct3D12RenderObject::Direct3D12RenderObject(const Render::Mesh& mesh, const std::size_t id) noexcept :
		mesh{&mesh},
		id{id}
	{
	}

	Direct3D12RenderObject::Direct3D12RenderObject(const Direct3D12RenderObject& other) noexcept :
		mesh{other.mesh},
		id{other.id}
	{
	}

	Direct3D12RenderObject::Direct3D12RenderObject(Direct3D12RenderObject&& other) noexcept :
		mesh{other.mesh},
		id{other.id}
	{
	}

	std::size_t Direct3D12RenderObject::Id() const noexcept
	{
		return id;
	}

	const Mesh& Direct3D12RenderObject::Mesh() const noexcept
	{
		return *mesh;
	}

	Direct3D12RenderObject& Direct3D12RenderObject::operator =(const Direct3D12RenderObject& other) noexcept
	{
		mesh = other.mesh;
		id = other.id;

		return *this;
	}

	Direct3D12RenderObject& Direct3D12RenderObject::operator =(Direct3D12RenderObject&& other) noexcept
	{
		mesh = other.mesh;
		id = other.id;

		return *this;
	}
}
