/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:RenderSystemParams;

import :FrameParams;
import :SwapChainParams;

export namespace PonyEngine::Render
{
	/// @brief Render system parameters.
	struct RenderSystemParams
	{
		/// @brief Main frame parameters.
		/// @note Must have a correct rtv format that is compatible with sRGB but not sRGB.
		FrameParams mainFrameParams;
		SwapChainParams swapChainParams; ///< Swap chain parameters.
	};
}
