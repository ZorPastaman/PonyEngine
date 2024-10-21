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

export module PonyEngine.Render.Direct3D12.Factory:Direct3D12RenderSystemParams;

import PonyEngine.Render.Factory;

export namespace PonyEngine::Render
{
	struct Direct3D12RenderSystemParams : RenderSystemParams
	{
		D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_12_2;
		INT commandQueuePriority = D3D12_COMMAND_QUEUE_PRIORITY_HIGH;

		DWORD fenceTimeout = 20000;
	};
}
