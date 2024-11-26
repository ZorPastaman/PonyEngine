/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/Direct3D12/Framework.h"

export module PonyEngine.Render.Direct3D12.Detail:Direct3D12MaterialParams;

import <optional>;

export namespace PonyEngine::Render
{
	/// @brief Direct3D12 material parameters.
	struct Direct3D12MaterialParams final
	{
		D3D_PRIMITIVE_TOPOLOGY primitiveTopology; ///< Primitive topology.

		UINT vertexSlot; ///< Vertex slot.
		std::optional<UINT> vertexColorSlot; ///< Vertex color slot. It's @a nullopt if the material doesn't support it.
	};
}
