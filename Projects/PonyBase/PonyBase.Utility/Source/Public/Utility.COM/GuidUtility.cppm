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

import PonyBase.StringUtility;

export namespace PonyBase::Utility
{
	[[nodiscard("Pure function")]]
	GUID AcquireGuid();

	/// @brief Creates a string representing the @p guid.
	/// @param guid GUID.
	/// @return String representing the @p guid.
	[[nodiscard("Pure function")]]
	std::string ToString(const GUID& guid) noexcept; // TODO: Add test
}

namespace PonyBase::Utility
{
	GUID AcquireGuid()
	{
		GUID acquiredGuid;
		if (const HRESULT result = CoCreateGuid(&acquiredGuid); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(SafeFormat("Failed to get guid for Direct3D 12 render system with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		return acquiredGuid;
	}

	std::string ToString(const GUID& guid) noexcept
	{
		return std::format("{:X}-{:X}-{:X}-{:X}", guid.Data1, guid.Data2, guid.Data3, *reinterpret_cast<const std::uint64_t*>(guid.Data4));
	}
}
