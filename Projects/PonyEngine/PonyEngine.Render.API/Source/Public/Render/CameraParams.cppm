/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:CameraParams;

export namespace PonyEngine::Render
{
	struct CameraParams final
	{
		float fov;
		float nearPlane;
		float farPlane;
	};
}
