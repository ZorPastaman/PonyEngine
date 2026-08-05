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

export module PonyEngine.File:RequestStatus;

import std;

export namespace PonyEngine::File
{
	/// @brief Request status.
	enum class RequestStatus : std::uint8_t
	{
		Pending, ///< A request is still in progress.
		Success, ///< A request finished with a success.
		Failure, ///< A request finished with a failure.
		Canceled ///< A request was canceled.
	};
}

namespace PonyEngine::File
{
	/// @brief Request status names.
	constexpr std::array<std::string_view, 4> RequestStatusNames
	{
		"Pending",
		"Success",
		"Failure",
		"Canceled"
	};
}

export 
{
	PONY_ENUM_VALUE_FORMATTER(PonyEngine::File::RequestStatus, PonyEngine::File::RequestStatusNames)
}
