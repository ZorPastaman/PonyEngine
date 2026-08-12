/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Object/Body.h"

export module PonyEngine.Resource.Ext:EngineResourceType;

import std;

export namespace PonyEngine::Resource
{
	/// @brief Engine resource types.
	struct EngineResourceType final
	{
		PONY_NON_CONSTRUCTIBLE_BODY(EngineResourceType)

		static constexpr std::string_view Text = "PonyText";

		static constexpr std::string_view Material = "PonyMaterial";
		static constexpr std::string_view Mesh = "PonyMesh";
		static constexpr std::string_view Shader = "PonyShader";
		static constexpr std::string_view Texture = "PonyTexture";

		static constexpr std::string_view Map = "PonyMap";
	};
}
