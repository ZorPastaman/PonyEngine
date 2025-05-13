/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:RenderSystemParams;

import <cstdint>;

import :API;
import :CommandQueuePriority;
import :FrameParams;
import :SwapChainParams;

export namespace PonyEngine::Render
{
	/// @brief Render system parameters.
	struct RenderSystemParams
	{
		/// @brief Main frame parameters.
		FrameParams mainFrameParams;
		SwapChainParams swapChainParams; ///< Swap chain parameters.
		std::int32_t commandQueuePriority = static_cast<std::int32_t>(CommandQueuePriority::High); ///< Command queue priority.
		std::uint32_t timeout = 5000; ///< Timeout in milliseconds. The system throws an exception if the render time exceeds this value.
		API api = API::None; ///< Render API.
	};
}
