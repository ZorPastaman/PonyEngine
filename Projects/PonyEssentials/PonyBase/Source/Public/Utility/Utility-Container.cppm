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
import <type_traits>;
import <utility>;
import <vector>;

export namespace PonyBase::Utility
{
	/// @brief Moves an element from one index to another.
	/// @tparam T Value type.
	/// @param vector Vector.
	/// @param from From index.
	/// @param to To index. It's a target index after an erasure of an element at the index from.
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
		vector.erase(vector.begin() + from);
		vector.insert(vector.begin() + to, std::move(value));
	}
}
