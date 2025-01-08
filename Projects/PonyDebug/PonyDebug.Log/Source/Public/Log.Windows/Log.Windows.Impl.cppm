/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <memory>

#include "PonyBase/Core/Linking.h"

export module PonyDebug.Log.Windows.Impl;

export import PonyDebug.Log.Impl;
export import PonyDebug.Log.Windows;

import <memory>; 

import PonyDebug.Log.Windows.Detail;

export namespace PonyDebug::Log::Windows
{
	/// @brief Creates an output debug string sub-logger.
	/// @param params Output debug string sub-logger parameters.
	/// @return Created output debug string sub-logger.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT OutputDebugStringSubLoggerData CreateOutputDebugStringSubLogger(const OutputDebugStringSubLoggerParams& params);
}

namespace PonyDebug::Log::Windows
{
	OutputDebugStringSubLoggerData CreateOutputDebugStringSubLogger(const OutputDebugStringSubLoggerParams& params)
	{
		return OutputDebugStringSubLoggerData{.subLogger = std::make_unique<OutputDebugStringSubLogger>(params)};
	}
}
