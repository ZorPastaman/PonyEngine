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

export module PonyEngine.Render.Direct3D12:IRenderTarget;

import PonyEngine.Render;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 render target.
	class IRenderTarget : public Render::IRenderTarget
	{
		INTERFACE_BODY(IRenderTarget)
	};
}
