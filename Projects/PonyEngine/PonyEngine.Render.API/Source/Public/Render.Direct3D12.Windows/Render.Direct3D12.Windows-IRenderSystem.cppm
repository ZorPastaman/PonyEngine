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

export module PonyEngine.Render.Direct3D12.Windows:IRenderSystem;

import PonyEngine.Render.Direct3D12;

export namespace PonyEngine::Render::Direct3D12::Windows
{
	/// @brief Windows Direct3D12 render system.
	class IRenderSystem : public Direct3D12::IRenderSystem
	{
		INTERFACE_BODY(IRenderSystem)
	};
}
