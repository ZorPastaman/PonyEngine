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

		/// @brief Gets the main frame parameters.
		/// @return Main frame parameters.
		[[nodiscard("Pure function")]]
		virtual const FrameParams& MainFrameParams() const noexcept = 0;

		/// @brief Adds the @p camera.
		/// @param camera Camera to add.
		virtual void AddCamera(Camera& camera) = 0;
		/// @brief Removes the @p camera.
		/// @param camera Camera to remove.
		virtual void RemoveCamera(Camera& camera) = 0;

		/// @brief Adds the @p renderObject.
		/// @param renderObject Render object to add.
		virtual void AddRenderObject(RenderObject& renderObject) = 0;
		/// @brief Removes the @p renderObject.
		/// @param renderObject Render object to remove.
		virtual void RemoveRenderObject(RenderObject& renderObject) = 0;
	};
}
