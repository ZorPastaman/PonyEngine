/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:CameraProjection;

import <variant>;

import PonyMath.Core;

import :OrthographicParams;
import :PerspectiveParams;

export namespace PonyEngine::Render
{
	struct CameraProjection final
	{
		std::variant<PerspectiveParams, OrthographicParams> projection = PerspectiveParams{.fov = 60.f * PonyMath::Core::DegToRad<float>, .aspect = 16.f / 9.f, .nearPlane = 0.2f, .farPlane = 1000.f}; ///< Projection.
	};
}
