/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/Interface.h"

export module PonyEngine.Render.Direct3D12.Windows:IWindowsDirect3D12RenderSystem;

import PonyEngine.Render.Direct3D12;

export namespace PonyEngine::Render
{
	class IWindowsDirect3D12RenderSystem : public IDirect3D12RenderSystem
	{
		INTERFACE_BODY(IWindowsDirect3D12RenderSystem)
	};
}
