/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Compiler/Linking.h"

export module PonyEngine.Log.Windows.Implementation;

export import PonyEngine.Log.Implementation;
export import PonyEngine.Log.Windows.Factory;

import :OutputDebugStringSubLogger;
import :OutputDebugStringSubLoggerDestroyer;

export namespace PonyEngine::Log
{
	/// @brief Creates an output debug string sub-logger.
	/// @return Created output debug string sub-logger.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT OutputDebugStringSubLoggerData CreateOutputDebugStringSubLogger();
}

namespace PonyEngine::Log
{
	auto DefaultOutputDebugStringSubLoggerDestroyer = OutputDebugStringSubLoggerDestroyer(); ///< Default output debug string sub-logger destroyer.

	OutputDebugStringSubLoggerData CreateOutputDebugStringSubLogger()
	{
		const auto outputDebugStringSubLogger = new OutputDebugStringSubLogger();
		const auto outputDebugStringSubLoggerDeleter = SubLoggerDeleter(DefaultOutputDebugStringSubLoggerDestroyer);

		return OutputDebugStringSubLoggerData{.subLogger = SubLoggerUniquePtr(outputDebugStringSubLogger, outputDebugStringSubLoggerDeleter)};
	}
}
