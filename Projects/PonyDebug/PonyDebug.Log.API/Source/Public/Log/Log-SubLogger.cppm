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

export module PonyDebug.Log:SubLogger;

import :ISubLogger;

export namespace PonyDebug::Log
{
	/// @brief Sub-logger.
	class SubLogger : public ISubLogger
	{
		BASE_BODY(SubLogger)
	};
}
