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

export module PonyEngine.Render.Windows:IRenderSystem;

import PonyEngine.Render;

export namespace PonyEngine::Render::Windows
{
	/// @brief Windows render system.
	class IRenderSystem : public Render::IRenderSystem
	{
		INTERFACE_BODY(IRenderSystem)
	};
}
