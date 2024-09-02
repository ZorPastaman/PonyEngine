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

export module PonyEngine.Log.Windows.Implementation;

export import PonyEngine.Log.Implementation;
export import PonyEngine.Log.Windows.Factory;

import :OutputDebugStringSubLogger;
import :OutputDebugStringSubLoggerDestroyer;

export namespace PonyEngine::Log
{
	/// @brief Creates an output debug string sub-logger.
	/// @param params Output debug string sub-logger parameters.
	/// @return Created output debug string sub-logger.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT OutputDebugStringSubLoggerData CreateOutputDebugStringSubLogger(const OutputDebugStringSubLoggerParams& params);
}

namespace PonyEngine::Log
{
	auto DefaultOutputDebugStringSubLoggerDestroyer = OutputDebugStringSubLoggerDestroyer(); ///< Default output debug string sub-logger destroyer.

	OutputDebugStringSubLoggerData CreateOutputDebugStringSubLogger(const OutputDebugStringSubLoggerParams&)
	{
		const auto outputDebugStringSubLogger = new OutputDebugStringSubLogger();
		const auto outputDebugStringSubLoggerDeleter = SubLoggerDeleter(DefaultOutputDebugStringSubLoggerDestroyer);

		return OutputDebugStringSubLoggerData{.subLogger = SubLoggerUniquePtr(outputDebugStringSubLogger, outputDebugStringSubLoggerDeleter)};
	}
}
