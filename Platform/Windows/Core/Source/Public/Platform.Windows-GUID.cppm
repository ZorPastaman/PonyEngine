/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <objbase.h>

export module PonyEngine.Platform.Windows:GUID;

import std;

export namespace PonyEngine::Platform::Windows
{
	constexpr std::size_t GuidTextSize = 36uz; ///< GUID text representation length. It doesn't include brackets.

	/// @brief Acquires GUID.
	/// @return GUID.
	[[nodiscard("Pure function")]]
	GUID AcquireGuid();
}

/// @brief COM GUID formatter.
/// @details The format is ":<guid_args>". The default brackets are {}.
///          Guid args: n - no brackets.
export template<>
struct std::formatter<GUID, char>
{
private:
	std::string_view opening = "{";
	std::string_view closing = "}";
	bool noBrackets = false;

public:
	constexpr void set_brackets(const std::string_view opening, const std::string_view closing) noexcept
	{
		this->opening = opening;
		this->closing = closing;
	}

	constexpr std::format_parse_context::iterator parse(std::format_parse_context& context)
	{
		auto it = context.begin();

#ifndef NDEBUG
		if (it == context.end()) [[unlikely]]
		{
			throw std::format_error("Unexpected context end");
		}
#endif

		for (; *it != '}'; ++it)
		{
			switch (*it)
			{
			case 'n':
				noBrackets = true;
				break;
			default: [[unlikely]]
#ifndef NDEBUG
				throw std::format_error("Unexpected format specifier");
#else
				break;
#endif
			}
		}

		return it;
	}

	std::format_context::iterator format(const GUID& guid, std::format_context& context) const
	{
		auto it = context.out();

		if (!noBrackets)
		{
			it = std::ranges::copy(opening, it).out;
		}

		it = std::format_to(it, "{:08X}-{:04X}-{:04X}-{:02X}{:02X}-{:02X}{:02X}{:02X}{:02X}{:02X}{:02X}",
			guid.Data1, guid.Data2, guid.Data3,
			guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);

		if (!noBrackets)
		{
			it = std::ranges::copy(closing, it).out;
		}

		return it;
	}
};

namespace PonyEngine::Platform::Windows
{
	GUID AcquireGuid()
	{
		GUID acquiredGuid;
		if (const HRESULT result = CoCreateGuid(&acquiredGuid); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to get guid: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		return acquiredGuid;
	}
}
