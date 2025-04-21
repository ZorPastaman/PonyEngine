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

import PonyMath.Utility;

export namespace PonyEngine::Render
{
	/// @brief Swap chain parameters.
	struct SwapChainParams final
	{
		PonyMath::Utility::Resolution<std::uint32_t> resolution = PonyMath::Utility::Resolution<std::uint32_t>(1280u, 720u);; ///< Swap chain resolution.
		std::uint8_t bufferCount = 3u; ///< Back buffer count.
	};
}
