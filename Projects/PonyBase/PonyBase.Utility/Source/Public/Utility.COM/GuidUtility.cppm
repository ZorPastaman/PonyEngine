/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/COM/Framework.h"

export module PonyBase.GuidUtility;

import <cstdint>;
import <format>;
import <string>;

export namespace PonyBase::Utility
{
	/// @brief Creates a string representing the @p guid.
	/// @param guid GUID.
	/// @return String representing the @p guid.
	[[nodiscard("Pure function")]]
	std::string ToString(const GUID& guid) noexcept; // TODO: Add test
}

namespace PonyBase::Utility
{
	std::string ToString(const GUID& guid) noexcept
	{
		return std::format("{:X}-{:X}-{:X}-{:X}", guid.Data1, guid.Data2, guid.Data3, *reinterpret_cast<const std::uint64_t*>(guid.Data4));
	}
}
