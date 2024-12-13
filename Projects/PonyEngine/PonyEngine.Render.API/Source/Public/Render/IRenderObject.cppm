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

export module PonyEngine.Render:IRenderObject;

import PonyMath.Core;

export namespace PonyEngine::Render
{
	/// @brief Render object.
	class IRenderObject
	{
		INTERFACE_BODY(IRenderObject)

		/// @brief Gets the translation-rotation-scaling matrix of the object.
		/// @return Translation-rotation-scaling matrix.
		[[nodiscard("Pure function")]]
		virtual PonyMath::Core::Matrix4x4<float> ModelMatrix() const noexcept = 0;
		/// @brief Sets the translation-rotation-scaling matrix of the object.
		/// @param matrix Translation-rotation-scaling matrix.
		virtual void ModelMatrix(const PonyMath::Core::Matrix4x4<float>& matrix) noexcept = 0;
	};
}
