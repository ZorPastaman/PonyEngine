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

export module PonyEngine.Render.Direct3D12:IDirect3D12RenderTarget;

import PonyEngine.Render;

export namespace PonyEngine::Render
{
	/// @brief Direct3D12 render target.
	class IDirect3D12RenderTarget : public IRenderTarget
	{
		INTERFACE_BODY(IDirect3D12RenderTarget)
	};
}
