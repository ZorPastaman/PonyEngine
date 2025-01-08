/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#ifdef _WIN32
#include "PonyBase/Core/Windows/Framework.h"
#else
#error "Unsupported platform!"
#endif

export module PonyBase.Utility:StringConvert;

import <stdexcept>;
import <string>;

import :SafeFormat;

export namespace PonyBase::Utility
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

namespace PonyBase::Utility
{
#ifdef _WIN32
	std::string ConvertToString(const std::wstring_view source)
	{
		if (source.empty())
		{
			return std::string();
		}

		const int length = WideCharToMultiByte(CP_UTF8, DWORD{0}, source.data(), static_cast<int>(source.length()), nullptr, 0, nullptr, nullptr);
		if (length <= 0) [[unlikely]]
		{
			throw std::runtime_error(SafeFormat("Failed to get utf8 string length. Error code: '{}'.", GetLastError()));
		}

		auto answer = std::string(length, '\0');
		if (WideCharToMultiByte(CP_UTF8, DWORD{0}, source.data(), static_cast<int>(source.length()), answer.data(), static_cast<int>(answer.length()), nullptr, nullptr) <= 0) [[unlikely]]
		{
			throw std::runtime_error(SafeFormat("Failed to convert to utf8 string. Error code: '{}'.", GetLastError()));
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
			throw std::runtime_error(SafeFormat("Failed to get wide string length. Error code: '{}'.", GetLastError()));
		}

		auto answer = std::wstring(length, L'\0');
		if (MultiByteToWideChar(CP_UTF8, DWORD{0}, source.data(), static_cast<int>(source.length()), answer.data(), static_cast<int>(answer.length())) <= 0) [[unlikely]]
		{
			throw std::runtime_error(SafeFormat("Failed to convert to wide string. Error code: '{}'.", GetLastError()));
		}

		return answer;
	}
#endif
}
