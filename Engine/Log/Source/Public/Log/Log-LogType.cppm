/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Type/Enum.h"

export module PonyEngine.Log:LogType;

import std;

namespace PonyEngine::Log
{
	/// @brief Log type names by index.
	constexpr std::array<std::string_view, 7> LogTypeNames
	{
		"Verbose",
		"Debug",
		"Info",
		"Warning",
		"Error",
		"Exception",
		"Unknown"
	};
}

export namespace PonyEngine::Log
{
	/// @brief Severity of a log.
	enum class LogType : std::uint8_t
	{
		Verbose, ///< Log everything.
		Debug, ///< Log additional debug information.
		Info, ///< Log a normal program execution.
		Warning, ///< Log a non-critical error or suspicious program execution.
		Error, ///< Log an error.
		Exception ///< Log an exception.
	};

	/// @brief Severity of a log as a mask.
	enum class LogTypeMask : std::uint8_t
	{
		None = 0,
		Verbose = 1 << 0, ///< Log everything.
		Debug = 1 << 1, ///< Log additional debug information.
		Info = 1 << 2, ///< Log a normal program execution.
		Warning = 1 << 3, ///< Log a non-critical error or suspicious program execution.
		Error = 1 << 4, ///< Log an error.
		Exception = 1 << 5, ///< Log an exception.
		All = Verbose | Debug | Info | Warning | Error | Exception
	};

	ENUM_VALUE_MASK_FEATURES(LogType, LogTypeNames, LogTypeMask, LogTypeNames)
}

export
{
	ENUM_VALUE_MASK_FORMATTER(PonyEngine::Log, LogType, LogTypeMask)
}
