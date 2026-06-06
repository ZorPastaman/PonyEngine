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
	enum class RequestStatus : std::uint8_t
	{
		Pending,
		Completed,
		Failed
	};
}

namespace PonyEngine::File
{
	constexpr std::array<std::string_view, 3> RequestStatusNames
	{
		"Pending",
		"Completed",
		"Failed"
	};
}

export 
{
	PONY_ENUM_VALUE_FORMATTER(PonyEngine::File::RequestStatus, PonyEngine::File::RequestStatusNames)
}
