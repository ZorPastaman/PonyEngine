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

export module PonyEngine.Render.Direct3D12:IRenderObjectManager;

import PonyEngine.Render;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 render object manager.
	class IRenderObjectManager : public Render::IRenderObjectManager
	{
		INTERFACE_BODY(IRenderObjectManager)
	};
}
