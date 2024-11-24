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

export module PonyEngine.Render.Direct3D12.Detail:Direct3D12SystemParams;

import PonyEngine.Render;

export namespace PonyEngine::Render
{
	struct Direct3D12SystemParams final
	{
		D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_12_2; ///< Feature level.
		INT commandQueuePriority = D3D12_COMMAND_QUEUE_PRIORITY_HIGH; ///< Command queue priority. It will be used for every command queue.
		DWORD renderTimeout = 20000; ///< Render timeout in milliseconds. The system throws an exception if the render time exceeds this value.

		RenderViewParams renderViewParams; // TODO: Don't use the same params. Divide parameters of different subsystems.
	};
}
