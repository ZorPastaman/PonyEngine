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

export module PonyEngine.RenderDevice:RenderAPI;

import std;

export namespace PonyEngine::Render
{
	struct RenderAPI final
	{
		PONY_NON_CONSTRUCTIBLE_BODY(RenderAPI)

		static constexpr std::string_view Direct3D = "Direct3D";
		static constexpr std::string_view Vulkan = "Vulkan";
		static constexpr std::string_view Metal = "Metal";

		static constexpr std::string_view Empty = "Empty";
	};
}
