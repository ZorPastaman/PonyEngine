/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Format:Optional;

import std;

/// @brief Formatter of std::optional.
/// @tparam T Underlying type.
export template<typename T>
struct std::formatter<std::optional<T>, char>
{
private:
	std::formatter<T, char> subFormatter;

public:
	[[nodiscard("Pure function")]]
	constexpr formatter<T, char>& underlying() noexcept
	{
		return subFormatter.underlying();
	}

	[[nodiscard("Pure function")]]
	constexpr const formatter<T, char>& underlying() const noexcept
	{
		return subFormatter.underlying();
	}

	constexpr std::format_parse_context::iterator parse(std::format_parse_context& context)
	{
		return subFormatter.parse(context);
	}

	std::format_context::iterator format(const std::optional<T>& optional, std::format_context& context) const
	{
		if (optional)
		{
			return subFormatter.format(*optional, context);
		}

		return std::ranges::copy("std::nullopt", context.out()).out;
	}
};
