/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:BufferParams;

import std;

import :BufferUsage;

export namespace PonyEngine::Render
{
	struct BufferParams final
	{
		std::uint64_t size;
		BufferUsage usage = BufferUsage::ShaderResource;
	};
}
