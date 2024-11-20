/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Direct3D12.Detail:Direct3D12MeshHandle;

import <cstddef>;

export namespace PonyEngine::Render
{
	struct Direct3D12MeshHandle final
	{
		[[nodiscard("Pure operator")]]
		bool operator ==(const Direct3D12MeshHandle& other) const noexcept = default;

		std::size_t id;
	};

	struct Direct3D12MeshHandleHash final
	{
		[[nodiscard("Pure operator")]]
		std::size_t operator ()(const Direct3D12MeshHandle& handle) const noexcept;
	};
}

namespace PonyEngine::Render
{
	std::size_t Direct3D12MeshHandleHash::operator ()(const Direct3D12MeshHandle& handle) const noexcept
	{
		return handle.id;
	}
}
