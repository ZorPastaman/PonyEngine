/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:SwapChainParams;

import <cstdint>;

export namespace PonyEngine::Render
{
	/// @brief Swap chain parameters.
	struct SwapChainParams final
	{
		std::uint8_t bufferCount = 3u; ///< Back buffer count.
		bool useWindowResolution = true; ///< If it's true, the resolution from the frame parameters will be ignored and the resolution from the window will be used.
	};
}
