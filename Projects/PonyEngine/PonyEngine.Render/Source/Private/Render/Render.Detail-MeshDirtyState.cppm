/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Detail:MeshDirtyState;

import <cstdint>;
import <unordered_set>;
import <utility>;

import :MeshDirtyFlag;

export namespace PonyEngine::Render
{
	/// @brief Mesh dirty state.
	struct MeshDirtyState final
	{
		std::unordered_set<std::pair<std::uint32_t, std::uint32_t>> dirtyData; ///< Dirty data buffer indices. Data type index, data index.
		MeshDirtyFlag dirtyFlags; ///< Mesh dirty flags.
	};
}
