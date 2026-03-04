/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:DepthBias;

export namespace PonyEngine::RenderDevice
{
	/// @brief Depth bias.
	struct DepthBias final
	{
		float depthBias = 0.f; ///< Main depth bias.
		float depthBiasClamp = 0.f; ///< Depth bias clamp.
		float slopeScaledDepthBias = 0.f; ///< Slope scaled depth bias.
	};
}
