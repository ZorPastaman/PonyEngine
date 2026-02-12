/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:ComputePipelineStateParams;

import std;

export namespace PonyEngine::RenderDevice
{
	struct ComputePipelineStateParams final
	{
		std::span<const std::byte> computeShader;
	};
}
