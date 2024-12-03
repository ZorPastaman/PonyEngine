/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/Base.h"

export module PonyEngine.Render:RenderSystemFactory;

import PonyEngine.Core;

export namespace PonyEngine::Render
{
	/// @brief Render system factory.
	class RenderSystemFactory : public Core::ISystemFactory
	{
		BASE_BODY(RenderSystemFactory)
	};
}
