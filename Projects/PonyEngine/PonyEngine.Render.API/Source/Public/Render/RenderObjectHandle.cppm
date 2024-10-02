/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:RenderObjectHandle;

import <cstddef>;

export namespace PonyEngine::Render
{
	struct RenderObjectHandle final // TODO: Think about unique_handle that automatically closes handle. And make handle struct universal.
	{
		[[nodiscard("Pure operator")]]
		bool operator ==(const RenderObjectHandle& other) const noexcept = default;

		std::size_t id;
	};

	struct RenderObjectHandleHash final
	{
		[[nodiscard("Pure operator")]]
		std::size_t operator ()(const RenderObjectHandle& handle) const noexcept;
	};
}

namespace PonyEngine::Render
{
	std::size_t RenderObjectHandleHash::operator ()(const RenderObjectHandle& handle) const noexcept
	{
		return handle.id;
	}
}
