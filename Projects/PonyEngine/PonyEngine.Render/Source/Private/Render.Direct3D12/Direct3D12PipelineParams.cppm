/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Direct3D12.Detail:Direct3D12PipelineParams;

import <optional>;

import :Direct3D12InputElementParams;

export namespace PonyEngine::Render
{
	struct Direct3D12PipelineParams final
	{
		Direct3D12InputElementParams vertexInputParams;
		std::optional<Direct3D12InputElementParams> vertexColorInputParams;
	};
}
