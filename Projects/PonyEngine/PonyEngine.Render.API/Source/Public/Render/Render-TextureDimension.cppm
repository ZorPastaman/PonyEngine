/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:TextureDimension;

import <cstdint>;
import <type_traits>;

export namespace PonyEngine::Render
{
	/// @brief Texture dimensions.
	enum class TextureDimension : std::uint8_t
	{
		Texture1D,
		Texture2D,
		Texture3D
	};
}
