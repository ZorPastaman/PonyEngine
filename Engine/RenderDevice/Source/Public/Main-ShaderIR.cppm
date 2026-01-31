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

export module PonyEngine.RenderDevice:ShaderIR;

import std;

export namespace PonyEngine::RenderDevice
{
	struct ShaderIR final
	{
		PONY_NON_CONSTRUCTIBLE_BODY(ShaderIR)

		static constexpr std::string_view DXIL = "DXIL";
		static constexpr std::string_view SPIRV = "SPIR-V";
		static constexpr std::string_view AIR = "AIR";
	};
}
