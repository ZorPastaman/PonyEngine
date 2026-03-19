/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:DepthStencil;

import std;

export namespace PonyEngine::RenderDevice
{
	/// @brief Depth stencil value.
	struct DepthStencil final
	{
		float depth = 1.f; ///< Depth.
		std::uint8_t stencil = 0u; ///< Stencil.
	};
}
