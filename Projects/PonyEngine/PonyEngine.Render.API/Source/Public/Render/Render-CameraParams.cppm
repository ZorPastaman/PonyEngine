/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:CameraParams;

import <cstdint>;

import PonyMath.Color;
import PonyMath.Core;
import PonyMath.Shape;

import :ClearValue;
import :Common;

export namespace PonyEngine::Render
{
	/// @brief Camera parameters.
	struct CameraParams final
	{
		PonyMath::Core::Matrix4x4<float> viewMatrix = PonyMath::Core::Matrix4x4<float>::Predefined::Identity; ///< View matrix.
		CameraProjection projection = Perspective{.fov = 60.f * PonyMath::Core::DegToRad<float>, .aspect = 16.f / 9.f, .nearPlane = 0.2f, .farPlane = 1000.f}; ///< Projection parameters.

		ClearValue clearValue; ///< Clear value.

		PonyMath::Shape::Rect<float> viewportRect = PonyMath::Shape::Rect<float>::Predefined::NormalizedFull; ///< Normalized viewport rect. It tells what part of a frame the camera writes to.

		std::int32_t sortingOrder = 0; ///< Sorting order.
	};
}
