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

export module PonyBase.COMUtility:GuidUtility;

import <cstdint>;
import <format>;
import <stdexcept>;
import <string>;
import <type_traits>;

import PonyBase.StringUtility;

export namespace PonyBase::Utility
{
	/// @brief Acquires GUID.
	/// @return GUID.
	[[nodiscard("Pure function")]]
	GUID AcquireGuid();

	/// @brief Creates a string representing the @p guid.
	/// @param guid GUID.
	/// @return String representing the @p guid.
	[[nodiscard("Pure function")]]
	std::string ToString(const GUID& guid) noexcept;
}

namespace PonyBase::Utility
{
	GUID AcquireGuid()
	{
		GUID acquiredGuid;
		if (const HRESULT result = CoCreateGuid(&acquiredGuid); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(SafeFormat("Failed to get guid with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		return acquiredGuid;
	}

	std::string ToString(const GUID& guid) noexcept
	{
		auto buffer = std::wstring(39, '\0');
		StringFromGUID2(guid, buffer.data(), static_cast<int>(buffer.size()));

		return ConvertToString(std::wstring_view(&buffer.front() + 1, &buffer.back() - 1));
	}
}
