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

export module PonyEngine.Platform.Windows:Text;

import std;

export namespace PonyEngine::Platform
{
	/// @brief Gets a size of a converted string.
	/// @param source Wide string.
	/// @return String size.
	[[nodiscard("Pure function")]]
	std::size_t GetStringSize(std::wstring_view source);
	/// @brief Gets a size of a converted string.
	/// @param source String.
	/// @return Wide string size.
	[[nodiscard("Pure function")]]
	std::size_t GetWideStringSize(std::string_view source);

	/// @brief Converts std::wstring_view to char array with UTF-8 encoding.
	/// @param source Source.
	/// @param target Converted string. Must be enough size.
	/// @return Actual target string size.
	std::size_t ConvertToString(std::wstring_view source, std::span<char> target);
	/// @brief Converts std::string_view to std::wstring.
	/// @param source Source with UTF-8 encoding.
	/// @param target Converted string.
	/// @return Actual target string size.
	std::size_t ConvertToWideString(std::string_view source, std::span<wchar_t> target);
}

namespace PonyEngine::Platform
{
	std::size_t GetStringSize(const std::wstring_view source)
	{
		if (source.empty()) [[unlikely]]
		{
			return 0uz;
		}

		const int length = WideCharToMultiByte(CP_UTF8, 0, source.data(), static_cast<int>(source.size()), nullptr, 0, nullptr, nullptr);
		if (length <= 0) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to get utf8 string length: ErrorCode = '0x{:X}'", GetLastError()));
		}

		return static_cast<std::size_t>(length);
	}

	std::size_t GetWideStringSize(const std::string_view source)
	{
		if (source.empty()) [[unlikely]]
		{
			return 0uz;
		}

		const int length = MultiByteToWideChar(CP_UTF8, 0, source.data(), static_cast<int>(source.size()), nullptr, 0);
		if (length <= 0) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to get wide string length: ErrorCode = '0x{:X}'", GetLastError()));
		}

		return static_cast<std::size_t>(length);
	}

	std::size_t ConvertToString(const std::wstring_view source, const std::span<char> target)
	{
		if (source.empty()) [[unlikely]]
		{
			return 0uz;
		}

		const int length = WideCharToMultiByte(CP_UTF8, 0, source.data(), static_cast<int>(source.size()), target.data(), static_cast<int>(target.size()), nullptr, nullptr);
		if (length <= 0) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to convert to utf8 string: ErrorCode = '0x{:X}'", GetLastError()));
		}

		return static_cast<std::size_t>(length);
	}

	std::size_t ConvertToWideString(const std::string_view source, const std::span<wchar_t> target)
	{
		if (source.empty()) [[unlikely]]
		{
			return 0uz;
		}

		const int length = MultiByteToWideChar(CP_UTF8, 0, source.data(), static_cast<int>(source.size()), target.data(), static_cast<int>(target.size()));
		if (length <= 0) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to convert to wide string: ErrorCode = '0x{:X}'", GetLastError()));
		}

		return static_cast<std::size_t>(length);
	}
}
