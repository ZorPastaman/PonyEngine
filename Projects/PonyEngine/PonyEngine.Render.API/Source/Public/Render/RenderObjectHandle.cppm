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
		std::size_t id;
	};
}
