/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/ObjectBody.h"

export module PonyEngine.Render.Direct3D12.Detail:IDirect3D12RenderSystemContext;

import PonyEngine.Render.Detail;

export namespace PonyEngine::Render
{
	/// @brief Direct3D12 render system context.
	class IDirect3D12RenderSystemContext : public IRenderSystemContext
	{
		INTERFACE_BODY(IDirect3D12RenderSystemContext)
	};
}
