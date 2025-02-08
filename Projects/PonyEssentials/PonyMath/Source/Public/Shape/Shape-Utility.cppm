/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyMath.Shape:Utility;

import <span>;

import PonyMath.Core;

import :Box;

export namespace PonyMath::Shape
{
	template<Core::Arithmetic T> [[nodiscard("Pure function")]]
	constexpr Box<T> CreateBoundingBox(std::span<const Core::Vector3<T>> positions) noexcept;
}

namespace PonyMath::Shape
{
	template<Core::Arithmetic T>
	constexpr Box<T> CreateBoundingBox(const std::span<const Core::Vector3<T>> positions) noexcept
	{
		if (positions.size() == 0)
		{
			return Box<T>::Predefined::Zero;
		}

		auto min = positions[0];
		auto max = positions[0];

		for (std::size_t i = 1; i < positions.size(); ++i)
		{
			min = Core::Min(min, positions[i]);
			max = Core::Max(max, positions[i]);
		}

		return Box<T>(min, max - min);
	}
}
