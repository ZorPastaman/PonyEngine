/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:RenderViewParams;

import <optional>;

import PonyMath.Core;
import PonyMath.Utility;

export namespace PonyEngine::Render
{
	/// @brief Render view parameters.
	struct RenderViewParams final
	{
		PonyMath::Core::Matrix4x4<float> viewMatrix = PonyMath::Core::Matrix4x4<float>::Predefined::Identity; ///< View matrix.
		PonyMath::Core::Matrix4x4<float> projectionMatrix = PonyMath::Core::PerspectiveMatrix(60.f * PonyMath::Core::DegToRad<float>, 16.f / 9.f, 0.2f, 1000.f); ///< Projection matrix.
		std::optional<PonyMath::Utility::Resolution<unsigned int>> resolution = {}; ///< Render resolution. If it's @a nullopt, the render resolution will be the same as a window resolution.
	};
}
