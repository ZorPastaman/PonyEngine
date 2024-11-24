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
	struct Direct3D12RenderTargetParams final
	{
		std::span<ID3D12Resource2*> backBuffers;
		PonyMath::Utility::Resolution<UINT> resolution;
		PonyMath::Color::RGBA<FLOAT> clearColor;
		DXGI_FORMAT rtvFormat;
		DXGI_SAMPLE_DESC sampleDesc;
	};
}
