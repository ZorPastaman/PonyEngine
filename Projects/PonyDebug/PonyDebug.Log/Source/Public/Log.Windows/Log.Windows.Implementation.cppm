/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/Linking.h"

export module PonyDebug.Log.Windows.Implementation;

export import PonyDebug.Log.Implementation;
export import PonyDebug.Log.Windows.Factory;

import :OutputDebugStringSubLogger;
import :OutputDebugStringSubLoggerDestroyer;

export namespace PonyDebug::Log
{
	/// @brief Creates an output debug string sub-logger.
	/// @param params Output debug string sub-logger parameters.
	/// @return Created output debug string sub-logger.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT OutputDebugStringSubLoggerData CreateOutputDebugStringSubLogger(const OutputDebugStringSubLoggerParams& params);
}

namespace PonyDebug::Log
{
	auto DefaultOutputDebugStringSubLoggerDestroyer = OutputDebugStringSubLoggerDestroyer(); ///< Default output debug string sub-logger destroyer.

	OutputDebugStringSubLoggerData CreateOutputDebugStringSubLogger(const OutputDebugStringSubLoggerParams&)
	{
		IWindowsSubLogger* const outputDebugStringSubLogger = new OutputDebugStringSubLogger();

		return OutputDebugStringSubLoggerData{.subLogger = SubLoggerUniquePtr(*outputDebugStringSubLogger, DefaultOutputDebugStringSubLoggerDestroyer)};
	}
}
