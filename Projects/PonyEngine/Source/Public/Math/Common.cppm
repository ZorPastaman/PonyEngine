/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math.Common;

import <numbers>;

namespace PonyEngine::Math
{
	export constexpr inline const float DegToRad = std::numbers::pi_v<float> / 180.f;
	export constexpr inline const float RadToDeg = 180.f / std::numbers::pi_v<float>;
}
