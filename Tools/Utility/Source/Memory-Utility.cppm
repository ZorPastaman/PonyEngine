/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyTools.Memory:Utility;

import std;

export namespace PonyTools::Memory
{
	constexpr bool IsHostBigEndian = std::endian::native == std::endian::big;

	template<std::integral T>
	T ConvertToTargetEndianess(T value, bool isTargetBigEndian) noexcept;
}

namespace PonyTools::Memory
{
	template<std::integral T>
	T ConvertToTargetEndianess(const T value, const bool isTargetBigEndian) noexcept
	{
		return isTargetBigEndian == IsHostBigEndian ? value : std::byteswap(value);
	}
}
