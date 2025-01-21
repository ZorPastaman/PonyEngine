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

export namespace PonyEngine::Render
{
	struct CameraParams final
	{
		PonyMath::Core::Matrix4x4<float> viewMatrix = PonyMath::Core::Matrix4x4<float>::Predefined::Identity; ///< View matrix.
		PonyMath::Core::Matrix4x4<float> projectionMatrix = PonyMath::Core::PerspectiveMatrix(60.f * PonyMath::Core::DegToRad<float>, 16.f / 9.f, 0.2f, 1000.f); ///< Projection matrix.

		PonyMath::Color::RGBA<float> clearColor = PonyMath::Color::RGBA<float>::Predefined::Black;

		PonyMath::Shape::Rect<float> viewportRect = PonyMath::Shape::Rect<float>::Predefined::NormalizedFull;

		std::int32_t sortingOrder = 0;
	};
}
