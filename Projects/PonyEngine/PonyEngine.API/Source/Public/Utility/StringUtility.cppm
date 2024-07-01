/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Utility:StringUtility;

import <algorithm>;
import <ranges>;
import <string>;

export namespace PonyEngine::Utility
{
	/// @brief Converts std::wstring to std::string. It just casts every wchar to char.
	/// @param source Source.
	/// @return Converted string.
	[[nodiscard("Pure function")]]
	std::string ConvertToString(const std::wstring& source);
}

namespace PonyEngine::Utility
{
	std::string ConvertToString(const std::wstring& source)
	{
		std::string answer(source.length(), 0);
		std::ranges::transform(source, answer.begin(), [](const wchar_t c) { return static_cast<std::string::value_type>(c); });

		return answer;
	}
}
