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
import <optional>;

import PonyMath.Utility;

export namespace PonyEngine::Render
{
	/// @brief Swap chain parameters.
	struct SwapChainParams final
	{
		std::optional<PonyMath::Utility::Resolution<std::uint32_t>> resolution = std::nullopt; ///< Swap chain resolution. If it's std::nullopt, uses a window resolution.
		std::uint8_t bufferCount = 3u; ///< Back buffer count.
		bool srgbOutput = true; ///< Should the output be converted to srgb? The main frame render target texture format must be srgb compatible.
	};
}
