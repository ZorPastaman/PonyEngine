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

export module PonyDebug.Log.Windows.Impl;

export import PonyDebug.Log.Impl;
export import PonyDebug.Log.Windows;

import <utility>;

import PonyBase.Memory;

import PonyDebug.Log.Windows.Detail;

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
	OutputDebugStringSubLoggerData CreateOutputDebugStringSubLogger(const OutputDebugStringSubLoggerParams&)
	{
		auto outputDebugStringSubLogger = PonyBase::Memory::UniquePointer<OutputDebugStringSubLogger>::Create();

		return OutputDebugStringSubLoggerData{.subLogger = PonyBase::Memory::UniquePointer<IWindowsSubLogger>(std::move(outputDebugStringSubLogger))};
	}
}
