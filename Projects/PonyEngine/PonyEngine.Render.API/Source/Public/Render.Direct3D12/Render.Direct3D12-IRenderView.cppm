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

export module PonyEngine.Render.Direct3D12:IRenderView;

import PonyEngine.Render;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 render view.
	class IRenderView : public Render::IRenderView
	{
		INTERFACE_BODY(IRenderView)
	};
}
