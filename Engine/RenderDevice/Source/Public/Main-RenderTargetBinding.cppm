/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:RenderTargetBinding;

import std;

import :IRenderTargetContainer;

export namespace PonyEngine::RenderDevice
{
	struct RenderTargetBinding final
	{
		const IRenderTargetContainer* container = nullptr;
		std::uint32_t index = 0u;
	};
}
