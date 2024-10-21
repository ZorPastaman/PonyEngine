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

import PonyEngine.Render;
import PonyEngine.Screen;

export namespace PonyEngine::Render
{
	struct RenderSystemParams
	{
		CameraParams cameraParams = CameraParams{.fov = 60.f * PonyMath::Core::DegToRad<float>, .nearPlane = 0.2f, .farPlane = 1000.f}; // TODO: Use projection matrix
		std::optional<Screen::Resolution<unsigned int>> resolution = {};
	};
}
