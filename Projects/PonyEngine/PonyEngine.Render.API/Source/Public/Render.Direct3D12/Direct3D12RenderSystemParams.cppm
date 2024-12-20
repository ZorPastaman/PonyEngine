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

export module PonyEngine.Render.Direct3D12:Direct3D12RenderSystemParams;

import PonyEngine.Render;

import :Direct3D12SwapChainParams;

export namespace PonyEngine::Render
{
	/// @brief Direct3D12 render system parameters.
	struct Direct3D12RenderSystemParams : RenderSystemParams
	{
		INT commandQueuePriority = D3D12_COMMAND_QUEUE_PRIORITY_HIGH; ///< Command queue priority. It will be used for every command queue.
		DWORD renderTimeout = 5000; ///< Render timeout in milliseconds. The system throws an exception if the render time exceeds this value.

		Direct3D12SwapChainParams swapChainParams; ///< Swap chain parameters.
	};
}
