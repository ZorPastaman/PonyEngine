/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#if PONY_WINCORE
#include "PonyEngine/Platform/WinCore/Framework.h"
#endif

export module PonyEngine.Text:Convert;

import std;

import :Format;

#if PONY_WINCORE
export namespace PonyEngine::Text::WinCore
{
	/// @brief Converts std::wstring_view to std::string with UTF-8 encoding.
	/// @param source Source.
	/// @return Converted string.
	[[nodiscard("Pure function")]]
	std::string ConvertToString(std::wstring_view source);

	/// @brief Converts std::string_view to std::wstring.
	/// @param source Source with UTF-8 encoding.
	/// @return Converted string.
	[[nodiscard("Pure function")]]
	std::wstring ConvertToWideString(std::string_view source);
}
#endif

#if PONY_WINCORE
namespace PonyEngine::Text::WinCore
{
	std::string ConvertToString(const std::wstring_view source)
	{
		if (source.empty())
		{
			return std::string();
		}

		const int length = WideCharToMultiByte(CP_UTF8, DWORD{0}, source.data(), static_cast<int>(source.length()), nullptr, 0, nullptr, nullptr);
		if (length <= 0) [[unlikely]]
		{
			throw std::runtime_error(FormatSafe("Failed to get utf8 string length. Error code: '0x{:X}'.", GetLastError()));
		}

		auto answer = std::string(length, '\0');
		if (WideCharToMultiByte(CP_UTF8, DWORD{0}, source.data(), static_cast<int>(source.length()), answer.data(), static_cast<int>(answer.length()), nullptr, nullptr) <= 0) [[unlikely]]
		{
			throw std::runtime_error(FormatSafe("Failed to convert to utf8 string. Error code: '0x{:X}'.", GetLastError()));
		}

		return answer;
	}

	std::wstring ConvertToWideString(const std::string_view source)
	{
		if (source.empty())
		{
			return std::wstring();
		}

		const int length = MultiByteToWideChar(CP_UTF8, DWORD{0}, source.data(), static_cast<int>(source.length()), nullptr, 0);
		if (length <= 0) [[unlikely]]
		{
			throw std::runtime_error(FormatSafe("Failed to get wide string length. Error code: '0x{:X}'.", GetLastError()));
		}

		auto answer = std::wstring(length, L'\0');
		if (MultiByteToWideChar(CP_UTF8, DWORD{0}, source.data(), static_cast<int>(source.length()), answer.data(), static_cast<int>(answer.length())) <= 0) [[unlikely]]
		{
			throw std::runtime_error(FormatSafe("Failed to convert to wide string. Error code: '0x{:X}'.", GetLastError()));
		}

		return answer;
	}
}
#endif
