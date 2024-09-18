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

export module PonyEngine.Render.Direct3D12.Windows.Factory:WindowsDirect3D12RenderParams;

import <optional>;

import PonyBase.Math;

export namespace PonyEngine::Render
{
	/// @brief Windows Direct3D 12 render parameters.
	struct WindowsDirect3D12RenderParams final
	{
		D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_12_2;
		std::optional<PonyBase::Math::Vector2<UINT>> resolution = {};
		INT commandQueuePriority = D3D12_COMMAND_QUEUE_PRIORITY_HIGH;

		DWORD fenceTimeout = 20000;
	};
}
