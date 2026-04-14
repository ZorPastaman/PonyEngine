/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:DepthRange;

export namespace PonyEngine::RenderDevice
{
	/// @brief Depth range.
	struct DepthRange final
	{
		float min = 0.f; ///< Minimal depth.
		float max = 1.f; ///< Maximal depth.
	};
}
