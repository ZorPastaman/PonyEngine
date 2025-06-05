/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyBase.Utility:Container;

import <cstddef>;
import <cstring>;
import <type_traits>;
import <utility>;
import <vector>;

export namespace PonyBase::Utility
{
	/// @brief Moves an element from one index to another.
	/// @note The @p vector may change on an exception.
	/// @tparam T Value type.
	/// @param vector Vector.
	/// @param from From index.
	/// @param to To index.
	template<typename T>
	void Move(std::vector<T>& vector, std::size_t from, std::size_t to) noexcept (std::is_nothrow_move_constructible_v<T>);
}

namespace PonyBase::Utility
{
	template<typename T>
	void Move(std::vector<T>& vector, const std::size_t from, const std::size_t to) noexcept (std::is_nothrow_move_constructible_v<T>)
	{
		if (from == to)
		{
			return;
		}

		T value = std::move(vector[from]);

		if constexpr (std::is_trivially_move_assignable_v<T>)
		{
			if (from < to)
			{
				std::memmove(&vector[from], &vector[from + 1], (to - from) * sizeof(T));
			}
			else
			{
				std::memmove(&vector[to + 1], &vector[to], (from - to) * sizeof(T));
			}
		}
		else
		{
			if (from < to)
			{
				for (std::size_t i = from; i < to; ++i)
				{
					vector[i] = std::move(vector[i + 1]);
				}
			}
			else
			{
				for (std::size_t i = from; i > to; --i)
				{
					vector[i] = std::move(vector[i - 1]);
				}
			}
		}

		vector[to] = std::move(value);
	}
}
