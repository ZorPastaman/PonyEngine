/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyBase.StringUtility:StringConvert;

import <algorithm>;
import <string>;

export namespace PonyBase::Utility
{
	/// @brief Converts std::wstring to std::string. It just casts every wchar to char.
	/// @param source Source.
	/// @return Converted string.
	[[nodiscard("Pure function")]]
	std::string ConvertToString(std::wstring_view source);
}

namespace PonyBase::Utility
{
	std::string ConvertToString(const std::wstring_view source)
	{
		std::string answer(source.size(), '\0');
		std::ranges::transform(source, answer.begin(), [](const std::wstring_view::value_type c) { return static_cast<std::string::value_type>(c); });

		return answer;
	}
}
