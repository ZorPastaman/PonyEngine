/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.Impl:Utility;

import std;

export namespace PonyEngine::Resource
{
	bool CheckTypes(std::span<const std::type_index> required, std::span<const std::type_index> provided) noexcept;
}

namespace PonyEngine::Resource
{
	bool CheckTypes(const std::span<const std::type_index> required, const std::span<const std::type_index> provided) noexcept
	{
		for (const std::type_index type : required)
		{
			if (!std::ranges::contains(provided, type))
			{
				return false;
			}
		}

		return true;
	}
}
