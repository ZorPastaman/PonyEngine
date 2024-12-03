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

export module PonyEngine.Time:FrameRateSystemFactory;

import PonyEngine.Core;

export namespace PonyEngine::Time
{
	/// @brief Frame rate system factory.
	class FrameRateSystemFactory : public Core::ISystemFactory
	{
		BASE_BODY(FrameRateSystemFactory)
	};
}
