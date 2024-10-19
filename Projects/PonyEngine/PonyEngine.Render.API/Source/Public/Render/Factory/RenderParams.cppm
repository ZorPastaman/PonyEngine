/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Factory:RenderParams;

import <optional>;

import PonyEngine.Render;
import PonyEngine.Screen;

export namespace PonyEngine::Render
{
	struct RenderParams
	{
		CameraParams cameraParams = CameraParams{.fov = 60.f * PonyMath::Core::DegToRad<float>, .nearPlane = 0.2f, .farPlane = 1000.f};
		std::optional<Screen::Resolution<unsigned int>> resolution = {};
	};
}
