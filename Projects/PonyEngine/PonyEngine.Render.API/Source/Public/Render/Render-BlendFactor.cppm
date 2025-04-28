/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:BlendFactor;

import <cstdint>;

export namespace PonyEngine::Render
{
	/// @brief Blend factor.
	enum class BlendFactor : std::uint8_t
	{
		Zero,
		One,
		ColorSource,
		ColorSourceInverse,
		AlphaSource,
		AlphaSourceInverse,
		AlphaSourceSaturate,
		ColorDestination,
		ColorDestinationInverse,
		AlphaDestination,
		AlphaDestinationInverse,
	};
}
