/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Render/Direct3D12/Framework.h"

export module PonyEngine.Render.Direct3D12.Windows.Factory:WindowsDirect3D12RenderSystemParams;

import PonyBase.Math;

export namespace PonyEngine::Render
{
	/// @brief Direct3D 12 render system for Windows parameters.
	struct WindowsDirect3D12RenderSystemParams final
	{
		PonyBase::Math::Vector2<UINT> resolution = PonyBase::Math::Vector2<UINT>(800, 600);
		INT commandQueuePriority = D3D12_COMMAND_QUEUE_PRIORITY_HIGH;
		DWORD fenceTimeout = 20000;
	};
}
