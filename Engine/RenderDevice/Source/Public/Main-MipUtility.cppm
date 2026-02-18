/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:MipUtility;

import std;

import PonyEngine.Math;

export namespace PonyEngine::RenderDevice
{
	template<std::unsigned_integral T> [[nodiscard("Pure function")]]
	constexpr T MipSize(T size, std::uint8_t mipIndex) noexcept;
	template<std::unsigned_integral T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr Math::Vector<T, Size> MipSize(const Math::Vector<T, Size>& size, std::uint8_t mipIndex) noexcept;
}

namespace PonyEngine::RenderDevice
{
	template<std::unsigned_integral T>
	constexpr T MipSize(const T size, const std::uint8_t mipIndex) noexcept
	{
		return std::max(size >> mipIndex, 1u);
	}

	template<std::unsigned_integral T, std::size_t Size>
	constexpr Math::Vector<T, Size> MipSize(const Math::Vector<T, Size>& size, const std::uint8_t mipIndex) noexcept
	{
		Math::Vector<T, Size> answer;
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			answer[i] = MipSize(size[i], mipIndex);
		}

		return answer;
	}
}
