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

export module PonyEngine.Render.Direct3D12.Detail:IDirect3D12GraphicsPipeline;

import <memory>;

import :Direct3D12RenderObject;

export namespace PonyEngine::Render
{
	/// @brief Direct3D12 graphics pipeline.
	class IDirect3D12GraphicsPipeline
	{
		INTERFACE_BODY(IDirect3D12GraphicsPipeline)

		/// @brief Adds a render task.
		/// @param renderObject Render object to render.
		virtual void AddRenderTask(const std::shared_ptr<Direct3D12RenderObject>& renderObject) = 0;
	};
}
