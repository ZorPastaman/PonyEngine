/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:DepthStencilContainerParams;

import std;

export namespace PonyEngine::RenderDevice
{
	/// @brief Depth stencil container parameters.
	struct DepthStencilContainerParams final
	{
		std::uint32_t size = 1u; ///< Container size.
	};
}
