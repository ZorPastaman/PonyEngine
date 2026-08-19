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

export module PonyEngine.File:FileRequestStatus;

import std;

export namespace PonyEngine::File
{
	/// @brief File request status.
	enum class FileRequestStatus : std::uint8_t
	{
		Pending, ///< A request is still in progress.
		Success, ///< A request finished with a success.
		Failure, ///< A request finished with a failure.
		Canceled ///< A request was canceled.
	};
}

namespace PonyEngine::File
{
	/// @brief File request status names.
	constexpr std::array<std::string_view, 4> FileRequestStatusNames
	{
		"Pending",
		"Success",
		"Failure",
		"Canceled"
	};
}

export 
{
	PONY_ENUM_VALUE_FORMATTER(PonyEngine::File::FileRequestStatus, PonyEngine::File::FileRequestStatusNames)
}
