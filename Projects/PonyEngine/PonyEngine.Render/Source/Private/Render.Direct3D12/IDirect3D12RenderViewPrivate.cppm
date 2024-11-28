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

export module PonyEngine.Render.Direct3D12.Detail:IDirect3D12RenderViewPrivate;

import PonyEngine.Render.Direct3D12;

export namespace PonyEngine::Render
{
	/// @brief Render target view.
	class IDirect3D12RenderViewPrivate : public IDirect3D12RenderView
	{
		INTERFACE_BODY(IDirect3D12RenderViewPrivate)
	};
}
