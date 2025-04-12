/***************************************************
* MIT License                                     *
*                                                 *
* Copyright (c) 2023-present Vladimir Popov       *
*                                                 *
* Email: zor1994@gmail.com                        *
* Repo: https://github.com/ZorPastaman/PonyEngine *
***************************************************/

export module PonyEngine.Render:ThreadGroupCountsMode;

import <cstdint>;

export namespace PonyEngine::Render
{
	/// @brief Thread group counts calculation mode.
	enum class ThreadGroupCountsMode : std::uint8_t
	{
		/// @brief Take mesh thread group counts. Ignore material thread group counts.
		SetMesh,
		/// @brief Take material thread group counts. Ignore mesh thread group counts.
		SetMaterial,
		/// @brief Multiplies mesh thread group counts by material thread group counts.
		/// Each axis is multiplied independently.
		Multiply,
		/// @brief Divide mesh thread group counts by material thread group counts.
		/// Each axis is divided independently. If a material thread group count is zero, the result is zero.
		/// The result is ceiled.
		DivideMeshByMaterial,
		/// @brief Divide material thread group counts by mesh thread group counts.
		/// Each axis is divided independently. If a mesh thread group count is zero, the result is zero.
		/// The result is ceiled.
		DivideMaterialByMesh
	};
}
