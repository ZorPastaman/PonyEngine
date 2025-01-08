/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/ObjectBody.h"

export module PonyEngine.Render.Direct3D12.Detail:IGraphicsPipeline;

import <memory>;

import :RenderObject;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 graphics pipeline.
	class IGraphicsPipeline
	{
		INTERFACE_BODY(IGraphicsPipeline)

		/// @brief Adds a render task.
		/// @param renderObject Render object to render.
		virtual void AddRenderTask(const std::shared_ptr<RenderObject>& renderObject) = 0;
	};
}
