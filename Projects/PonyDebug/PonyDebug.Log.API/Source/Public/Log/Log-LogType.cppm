/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/Enum.h"

export module PonyDebug.Log:LogType;

import <algorithm>;
import <array>;
import <bit>;
import <cstddef>;
import <cstdint>;
import <ostream>;
import <span>;
import <string>;
import <string_view>;
import <type_traits>;

namespace PonyDebug::Log
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

export namespace PonyDebug::Log
{
	/// @brief Severity of a log.
	enum class LogType : std::uint8_t
	{
		/// @brief Log everything.
		Verbose,
		/// @brief Log additional debug information.
		Debug,
		/// @brief Log a normal program execution.
		Info,
		/// @brief Log a non-critical error or suspicious program execution.
		Warning,
		/// @brief Log an error.
		Error,
		/// @brief Log an exception.
		Exception
	};

	/// @brief Severity of a log as a mask.
	enum class LogTypeMask : std::uint8_t
	{
		None = 0,
		/// @brief Log everything.
		Verbose = 1 << 0,
		/// @brief Log additional debug information.
		Debug = 1 << 1,
		/// @brief Log a normal program execution.
		Info = 1 << 2,
		/// @brief Log a non-critical error or suspicious program execution.
		Warning = 1 << 3,
		/// @brief Log an error.
		Error = 1 << 4,
		/// @brief Log an exception.
		Exception = 1 << 5,
		All = Verbose | Debug | Info | Warning | Error | Exception
	};

	ENUM_VALUE_MASK_FEATURES(LogType, LogTypeNames, LogTypeMask)
}
