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

export module PonyEngine.Render:IRenderView;

import PonyMath.Core;
import PonyMath.Utility;

export namespace PonyEngine::Render
{
	/// @brief Render view.
	class IRenderView
	{
		INTERFACE_BODY(IRenderView)

		/// @brief Gets the view translation-rotation-scaling matrix.
		/// @return View matrix.
		[[nodiscard("Pure function")]]
		virtual PonyMath::Core::Matrix4x4<float> ViewMatrix() const noexcept = 0;
		/// @brief Sets the view translation-rotation-scaling matrix.
		/// @param matrix View matrix.
		virtual void ViewMatrix(const PonyMath::Core::Matrix4x4<float>& matrix) noexcept = 0;

		/// @brief Gets the projection matrix.
		/// @return Projection matrix.
		[[nodiscard("Pure function")]]
		virtual PonyMath::Core::Matrix4x4<float> ProjectionMatrix() const noexcept = 0;
		/// @brief Sets the projection matrix.
		/// @param matrix Projection matrix.
		virtual void ProjectionMatrix(const PonyMath::Core::Matrix4x4<float>& matrix) noexcept = 0;
	};
}
