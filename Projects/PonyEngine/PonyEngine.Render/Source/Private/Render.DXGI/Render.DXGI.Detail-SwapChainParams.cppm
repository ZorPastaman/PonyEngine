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

export module PonyEngine.Render.DXGI.Detail:SwapChainParams;

import PonyMath.Utility;

export namespace PonyEngine::Render::DXGI
{
	/// @brief Swap chain parameters.
	struct SwapChainParams final
	{
		HWND hWnd; ///< Window handle. Must be an alive window.
		PonyMath::Utility::Resolution<UINT> resolution; ///< Swap chain resolution.
		UINT bufferCount; ///< Back buffer count.
	};
}
