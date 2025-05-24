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

export module PonyEngine.Render.DXGI.Detail:IRenderSystemContext;

import PonyEngine.Render.Detail.Old;

export namespace PonyEngine::Render::DXGI
{
	/// @brief DXGI render system context.
	class IRenderSystemContext : public Render::IRenderSystemContext
	{
		INTERFACE_BODY(IRenderSystemContext)
	};
}
