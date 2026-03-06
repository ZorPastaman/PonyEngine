/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:SubTextureIndex;

import std;

import :Aspect;

export namespace PonyEngine::RenderDevice
{
	/// @brief Sub-texture index.
	struct SubTextureIndex final
	{
		std::uint16_t arrayIndex = 0u; ///< Array element index.
		std::uint8_t mipIndex = 0u; ///< Mip index.
		Aspect aspect = Aspect::Color; ///< Aspect.
	};
}
