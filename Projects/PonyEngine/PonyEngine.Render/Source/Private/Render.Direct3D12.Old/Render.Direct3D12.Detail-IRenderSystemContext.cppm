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

export module PonyEngine.Render.Direct3D12.Detail:IRenderSystemContext;

import PonyEngine.Render.Detail.Old;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 render system context.
	class IRenderSystemContext : public Render::IRenderSystemContext
	{
		INTERFACE_BODY(IRenderSystemContext)
	};
}
