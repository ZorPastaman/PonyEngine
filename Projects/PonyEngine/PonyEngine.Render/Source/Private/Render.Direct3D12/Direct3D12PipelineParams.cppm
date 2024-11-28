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
	/// @brief Direct3D12 pipeline parameters.
	struct Direct3D12PipelineParams final
	{
		Direct3D12InputElementParams vertexInputParams; ///< Vertex input parameters.
		std::optional<Direct3D12InputElementParams> vertexColorInputParams; ///< Vertex color input parameters. May be @a nullopt if it's not supported.
	};
}
