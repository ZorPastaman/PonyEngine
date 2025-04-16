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

import :Camera;
import :FrameParams;
import :RenderObject;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 graphics pipeline.
	class IGraphicsPipeline
	{
		INTERFACE_BODY(IGraphicsPipeline)

		[[nodiscard("Pure function")]]
		virtual const FrameParams& MainFrameParams() const noexcept = 0;

		virtual void AddCamera(Camera& camera) = 0;
		virtual void RemoveCamera(Camera& camera) = 0;

		/// @brief Adds a render object.
		/// @param renderObject Render object to render.
		virtual void AddRenderObject(RenderObject& renderObject) = 0;
		virtual void RemoveRenderObject(RenderObject& renderObject) = 0;
	};
}
