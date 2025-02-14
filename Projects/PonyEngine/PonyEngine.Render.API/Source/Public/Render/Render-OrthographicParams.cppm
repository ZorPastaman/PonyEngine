/***************************************************
* MIT License                                     *
*                                                 *
* Copyright (c) 2023-present Vladimir Popov       *
*                                                 *
* Email: zor1994@gmail.com                        *
* Repo: https://github.com/ZorPastaman/PonyEngine *
***************************************************/

export module PonyEngine.Render:OrthographicParams;

export namespace PonyEngine::Render
{
	struct OrthographicParams final
	{
		float width;
		float height;
		float nearPlane;
		float farPlane;
	};
}
