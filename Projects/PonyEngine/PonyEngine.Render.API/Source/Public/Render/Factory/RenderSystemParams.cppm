/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Factory:RenderSystemParams;

import <optional>;

import PonyMath.Core;
import PonyMath.Utility;

import PonyEngine.Render;

export namespace PonyEngine::Render
{
	struct RenderSystemParams
	{
		PonyMath::Core::Matrix4x4<float> viewMatrix = PonyMath::Core::Matrix4x4<float>::Predefined::Identity;
		PonyMath::Core::Matrix4x4<float> projectionMatrix = PonyMath::Core::PerspectiveMatrix(60.f * PonyMath::Core::DegToRad<float>, 16.f / 9.f, 0.2f, 1000.f);
		std::optional<PonyMath::Utility::Resolution<unsigned int>> resolution = {};
	};
}
