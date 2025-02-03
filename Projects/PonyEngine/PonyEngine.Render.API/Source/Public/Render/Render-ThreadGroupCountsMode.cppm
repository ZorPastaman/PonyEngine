/***************************************************
* MIT License                                     *
*                                                 *
* Copyright (c) 2023-present Vladimir Popov       *
*                                                 *
* Email: zor1994@gmail.com                        *
* Repo: https://github.com/ZorPastaman/PonyEngine *
***************************************************/

export module PonyEngine.Render:ThreadGroupCountsMode;

import <cstdint>;

export namespace PonyEngine::Render
{
	enum class ThreadGroupCountsMode : std::uint8_t
	{
		SetMesh,
		SetMaterial,
		DivideMeshByMaterial
	};
}
