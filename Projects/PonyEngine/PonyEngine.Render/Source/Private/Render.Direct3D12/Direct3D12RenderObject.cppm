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
	class Direct3D12RenderObject final
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit Direct3D12RenderObject(const Mesh& mesh) noexcept;
		[[nodiscard("Pure constructor")]]
		Direct3D12RenderObject(const Direct3D12RenderObject& other) noexcept;
		[[nodiscard("Pure constructor")]]
		Direct3D12RenderObject(Direct3D12RenderObject&& other) noexcept;

		~Direct3D12RenderObject() noexcept = default;

		[[nodiscard("Pure function")]]
		const Mesh& Mesh() const noexcept;

		Direct3D12RenderObject& operator =(const Direct3D12RenderObject& other) noexcept;
		Direct3D12RenderObject& operator =(Direct3D12RenderObject&& other) noexcept;

	private:
		const Render::Mesh* mesh;
	};
}

namespace PonyEngine::Render
{
	Direct3D12RenderObject::Direct3D12RenderObject(const Render::Mesh& mesh) noexcept :
		mesh{&mesh}
	{
	}

	Direct3D12RenderObject::Direct3D12RenderObject(const Direct3D12RenderObject& other) noexcept :
		mesh{other.mesh}
	{
	}

	Direct3D12RenderObject::Direct3D12RenderObject(Direct3D12RenderObject&& other) noexcept :
		mesh{other.mesh}
	{
	}

	const Mesh& Direct3D12RenderObject::Mesh() const noexcept
	{
		return *mesh;
	}

	Direct3D12RenderObject& Direct3D12RenderObject::operator =(const Direct3D12RenderObject& other) noexcept
	{
		mesh = other.mesh;

		return *this;
	}

	Direct3D12RenderObject& Direct3D12RenderObject::operator =(Direct3D12RenderObject&& other) noexcept
	{
		mesh = other.mesh;

		return *this;
	}
}
