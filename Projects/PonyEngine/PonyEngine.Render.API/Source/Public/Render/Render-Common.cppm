/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:Common;

import <variant>;

import :OrthographicParams;
import :PerspectiveParams;

export namespace PonyEngine::Render
{
	constexpr float MinDepth = 0.f; ///< Minimal depth value.
	constexpr float MaxDepth = 1.f; ///< Maximal depth value.

	using CameraProjection = std::variant<PerspectiveParams, OrthographicParams>; ///< Camera projection parameters.
}
