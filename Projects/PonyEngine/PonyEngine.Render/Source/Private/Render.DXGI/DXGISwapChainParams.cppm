/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/DXGI/Framework.h"

export module PonyEngine.Render.DXGI.Detail:DXGISwapChainParams;

import PonyMath.Utility;

export namespace PonyEngine::Render
{
	struct DXGISwapChainParams final
	{
		HWND hWnd;
		PonyMath::Utility::Resolution<UINT> resolution;
		DXGI_FORMAT rtvFormat;
		UINT bufferCount;
	};
}
