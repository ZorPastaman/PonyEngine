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

export module PonyEngine.Render.Direct3D12.Detail:RenderTargetParams;

import PonyMath.Color;
import PonyMath.Utility;

import PonyEngine.Render;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 render target parameters.
	struct RenderTargetParams final
	{
		PonyMath::Utility::Resolution<UINT> resolution; ///< Render target resolution.
		PonyMath::Color::RGBA<FLOAT> clearColor; ///< Clear color.
		MSAAParams msaaParams; ///< MSAA parameters.
	};
}
