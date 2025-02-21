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

import <cstdint>;

import PonyMath.Utility;

export namespace PonyEngine::Render::DXGI
{
	/// @brief Swap chain parameters.
	struct SwapChainParams final
	{
		Microsoft::WRL::ComPtr<IUnknown> device; ///< Render device.
		HWND hWnd; ///< Window handle. Must be an alive window.
		PonyMath::Utility::Resolution<std::uint32_t> resolution; ///< Swap chain resolution.
		std::uint32_t bufferCount; ///< Back buffer count.
	};
}
