/***************************************************
* MIT License                                     *
*                                                 *
* Copyright (c) 2023-present Vladimir Popov       *
*                                                 *
* Email: zor1994@gmail.com                        *
* Repo: https://github.com/ZorPastaman/PonyEngine *
***************************************************/

export module PonyEngine.Render:PerspectiveParams;

export namespace PonyEngine::Render
{
	struct PerspectiveParams final
	{
		float fov;
		float aspect;
		float nearPlane;
		float farPlane;
	};
}
