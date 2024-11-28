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

export module PonyEngine.Render.Direct3D12.Detail:Direct3D12RenderTargetParams;

import <span>;

import PonyMath.Color;
import PonyMath.Utility;

export namespace PonyEngine::Render
{
	/// @brief Direct3D12 render target parameters.
	struct Direct3D12RenderTargetParams final
	{
		std::span<ID3D12Resource2*> backBuffers; ///< Back buffers.
		PonyMath::Utility::Resolution<UINT> resolution; ///< Back buffer resolution.
		PonyMath::Color::RGBA<FLOAT> clearColor; ///< Clear color.
		DXGI_FORMAT rtvFormat; ///< Rtv format.
		DXGI_SAMPLE_DESC sampleDesc; ///< Sample description.
	};
}
