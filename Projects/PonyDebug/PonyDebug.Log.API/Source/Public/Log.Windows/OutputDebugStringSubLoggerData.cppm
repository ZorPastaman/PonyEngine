/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyDebug.Log.Windows:OutputDebugStringSubLoggerData;

import PonyBase.Memory;

import :IWindowsSubLogger;

export namespace PonyDebug::Log
{
	/// @brief Output debug string sub-logger data.
	struct OutputDebugStringSubLoggerData final
	{
		PonyBase::Memory::UniquePointer<IWindowsSubLogger> subLogger; ///< Sub-logger.
	};
}
