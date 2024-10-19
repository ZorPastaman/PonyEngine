/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/Direct3D12/Framework.h"

export module PonyEngine.Render.Direct3D12.Implementation:Direct3D12CameraParams;

export namespace PonyEngine::Render
{
	struct Direct3D12CameraParams final
	{
		FLOAT fov;
		FLOAT nearPlane;
		FLOAT farPlane;
	};
}
