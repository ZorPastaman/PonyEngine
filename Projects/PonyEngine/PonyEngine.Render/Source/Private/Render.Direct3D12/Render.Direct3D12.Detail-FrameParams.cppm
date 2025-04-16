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

export module PonyEngine.Render.Direct3D12.Detail:FrameParams;

import <cstdint>;

import PonyMath.Color;
import PonyMath.Utility;

import PonyEngine.Render;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Frame parameters.
	struct FrameParams final
	{
		PonyMath::Utility::Resolution<std::uint32_t> resolution; ///< Render target resolution.
		DXGI_SAMPLE_DESC sampleDesc; ///< Sample description.
		PonyMath::Color::RGBA<float> clearColor; ///< Clear color.
		float clearDepth; ///< Clear depth.
		std::uint8_t clearStencil; ///< Clear stencil.
		DXGI_FORMAT rtvFormat; ///< Render target view format. If it's Unknown, it means no render target is required.
		DXGI_FORMAT dsvFormat; ///< Depth stencil view format. If it's Unknown, it means no depth stencil is required.
	};
}
