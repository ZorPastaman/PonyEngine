/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Platform/Windows/Framework.h"

export module PonyEngine.Platform:Windows.Text;

import std;

import PonyEngine.Text;

export namespace PonyEngine::Platform::Windows
{
	/// @brief Converts std::wstring_view to std::string with UTF-8 encoding.
	/// @param source Source.
	/// @return Converted string.
	[[nodiscard("Pure function")]]
	std::string ConvertToString(std::wstring_view source);
	/// @brief Converts std::wstring_view to std::string with UTF-8 encoding.
	/// @param source Source.
	/// @param target Converted string.
	/// @note In case of an exception, the @p target may be corrupted.
	void ConvertToString(std::wstring_view source, std::string& target);

	/// @brief Converts std::string_view to std::wstring.
	/// @param source Source with UTF-8 encoding.
	/// @return Converted string.
	[[nodiscard("Pure function")]]
	std::wstring ConvertToWideString(std::string_view source);
	/// @brief Converts std::string_view to std::wstring.
	/// @param source Source with UTF-8 encoding.
	/// @param target Converted string.
	/// @note In case of an exception, the @p target may be corrupted.
	void ConvertToWideString(std::string_view source, std::wstring& target);
}

namespace PonyEngine::Platform::Windows
{
	std::string ConvertToString(const std::wstring_view source)
	{
		std::string target;
		ConvertToString(source, target);
		return target;
	}

	void ConvertToString(const std::wstring_view source, std::string& target)
	{
		if (source.empty()) [[unlikely]]
		{
			target.resize(0uz);
			return;
		}

		const int length = WideCharToMultiByte(CP_UTF8, DWORD{0}, source.data(), static_cast<int>(source.length()), nullptr, 0, nullptr, nullptr);
		if (length <= 0) [[unlikely]]
		{
			throw std::runtime_error(Text::FormatSafe("Failed to get utf8 string length. Error code: '0x{:X}'.", GetLastError()));
		}

		target.resize(length);
		if (WideCharToMultiByte(CP_UTF8, DWORD{0}, source.data(), static_cast<int>(source.length()), target.data(), static_cast<int>(target.length()), nullptr, nullptr) <= 0) [[unlikely]]
		{
			throw std::runtime_error(Text::FormatSafe("Failed to convert to utf8 string. Error code: '0x{:X}'.", GetLastError()));
		}
	}

	std::wstring ConvertToWideString(const std::string_view source)
	{
		std::wstring target;
		ConvertToWideString(source, target);
		return target;
	}

	void ConvertToWideString(const std::string_view source, std::wstring& target)
	{
		if (source.empty()) [[unlikely]]
		{
			target.resize(0uz);
			return;
		}

		const int length = MultiByteToWideChar(CP_UTF8, DWORD{0}, source.data(), static_cast<int>(source.length()), nullptr, 0);
		if (length <= 0) [[unlikely]]
		{
			throw std::runtime_error(Text::FormatSafe("Failed to get wide string length. Error code: '0x{:X}'.", GetLastError()));
		}

		target.resize(length);
		if (MultiByteToWideChar(CP_UTF8, DWORD{0}, source.data(), static_cast<int>(source.length()), target.data(), static_cast<int>(target.length())) <= 0) [[unlikely]]
		{
			throw std::runtime_error(Text::FormatSafe("Failed to convert to wide string. Error code: '0x{:X}'.", GetLastError()));
		}
	}
}
