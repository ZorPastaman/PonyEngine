/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Platform/Windows/COM.h"

export module PonyEngine.Platform:Windows.GUID;

import std;

import :Windows.Text;

export namespace PonyEngine::Platform::Windows
{
	/// @brief Acquires GUID.
	/// @return GUID.
	[[nodiscard("Pure function")]]
	GUID AcquireGuid();

	/// @brief Creates a string representing the @p guid.
	/// @param guid GUID.
	/// @return String representing the @p guid.
	[[nodiscard("Pure function")]]
	std::string ToString(const GUID& guid);
}

/// @brief Stream insertion operator for GUID.
/// @param stream The output stream to write to.
/// @param guid The GUID to output.
/// @return Reference to the output stream.
export std::ostream& operator <<(std::ostream& stream, const GUID& guid)
{
	return stream << PonyEngine::Platform::Windows::ToString(guid);
}

/// @brief Windows GUID formatter.
export template<>
struct std::formatter<GUID, char>
{
	static constexpr auto parse(std::format_parse_context& context)
	{
		if (context.begin() == context.end()) [[unlikely]]
		{
			throw std::format_error("Unexpected context end.");
		}
		if (*context.begin() != '}') [[unlikely]]
		{
			throw std::format_error("Unexpected format specifier.");
		}

		return context.begin();
	}

	static auto format(const GUID& guid, std::format_context& context)
	{
		return std::ranges::copy(PonyEngine::Platform::Windows::ToString(guid), context.out()).out;
	}
};

namespace PonyEngine::Platform::Windows
{
	GUID AcquireGuid()
	{
		GUID acquiredGuid;
		if (const HRESULT result = CoCreateGuid(&acquiredGuid); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(Text::FormatSafe("Failed to get guid. Result: '0x{:X}'.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		return acquiredGuid;
	}

	std::string ToString(const GUID& guid)
	{
		auto buffer = std::wstring(39, L'\0');
		StringFromGUID2(guid, buffer.data(), static_cast<int>(buffer.size()));

		return ConvertToString(std::wstring_view(&buffer.front() + 1, &buffer.back() - 1));
	}
}
