/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:IRenderObject;

import <cstddef>;

import :Mesh;

export namespace PonyEngine::Render
{
	class IRenderObject
	{
	public:
		IRenderObject(const IRenderObject&) = delete;
		IRenderObject(IRenderObject&&) = delete;

		[[nodiscard("Pure function")]]
		virtual std::size_t Id() const noexcept = 0;

		[[nodiscard("Pure function")]]
		virtual const Mesh& Mesh() const noexcept = 0;

		IRenderObject& operator =(const IRenderObject&) = delete;
		IRenderObject& operator =(IRenderObject&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IRenderObject() noexcept = default;

		~IRenderObject() noexcept = default;
	};
}
