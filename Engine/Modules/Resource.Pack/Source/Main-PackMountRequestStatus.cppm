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

export module PonyEngine.Resource.Pack:PackMountRequestStatus;

import std;

export namespace PonyEngine::Resource::Pack
{
	/// @brief Pack mount request status.
	enum class PackMountRequestStatus : std::uint8_t
	{
		Pending, ///< A request is still in progress.
		Success, ///< A request finished with a success.
		Failure, ///< A request finished with a failure.
		Canceled ///< A request is canceled.
	};
}

namespace PonyEngine::Resource::Pack
{
	/// @brief Pack mount request status names.
	constexpr std::array<std::string_view, 4> PackMountRequestStatusNames
	{
		"Pending",
		"Success",
		"Failure",
		"Canceled"
	};
}

export
{
	PONY_ENUM_VALUE_FORMATTER(PonyEngine::Resource::Pack::PackMountRequestStatus, PonyEngine::Resource::Pack::PackMountRequestStatusNames)
}
