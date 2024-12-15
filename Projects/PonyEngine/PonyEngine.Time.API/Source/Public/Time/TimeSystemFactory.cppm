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

export module PonyEngine.Time:TimeSystemFactory;

import PonyEngine.Core;

export namespace PonyEngine::Time
{
	/// @brief Time system factory.
	class TimeSystemFactory : public Core::ISystemFactory
	{
		BASE_BODY(TimeSystemFactory)
	};
}
