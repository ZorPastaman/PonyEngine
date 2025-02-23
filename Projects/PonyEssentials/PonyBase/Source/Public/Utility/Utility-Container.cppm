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
import <vector>;

export namespace PonyBase::Utility
{
	template<typename T>
	void Move(std::vector<T>& vector, std::size_t from, std::size_t to);
}

namespace PonyBase::Utility
{
	template<typename T>
	void Move(std::vector<T>& vector, const std::size_t from, const std::size_t to)
	{
		if (from == to)
		{
			return;
		}

		const T value = vector[from];
		vector.erase(vector.begin() + from);
		vector.insert(vector.begin() + to - (to > from), value);
	}
}
