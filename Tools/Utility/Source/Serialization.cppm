/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyTools.Serialization;

import std;

export namespace PonyTools::Serialization
{
	/// @brief Parses the line.
	/// @param input Line.
	/// @return Parsed line.
	[[nodiscard("Pure function")]]
	std::vector<std::string> ParseLine(std::string_view input);
}

namespace PonyTools::Serialization
{
	std::vector<std::string> ParseLine(const std::string_view input)
	{
		std::vector<std::string> paths;

		std::string current;
		bool insideQuotes = false;

		for (const char c : input)
		{
			if (c == '"') [[unlikely]]
			{
				insideQuotes = !insideQuotes;
				continue;
			}

			if (!insideQuotes && std::isspace(static_cast<unsigned char>(c))) [[unlikely]]
			{
				if (!current.empty()) [[likely]]
				{
					paths.push_back(current);
					current.clear();
				}
			}
			else [[likely]]
			{
				current += c;
			}
		}

		if (insideQuotes) [[unlikely]]
		{
			throw std::invalid_argument("Unterminated quoted path");
		}

		if (!current.empty()) [[likely]]
		{
			paths.push_back(current);
		}

		return paths;
	}
}
