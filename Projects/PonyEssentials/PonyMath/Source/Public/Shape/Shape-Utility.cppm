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

import :AABB;
import :AABR;

export namespace PonyMath::Shape
{
	template<Core::Arithmetic T> [[nodiscard("Pure function")]]
	constexpr AABR<T> CreateBoundingRect(std::span<const Core::Vector2<T>> positions) noexcept;

	template<Core::Arithmetic T> [[nodiscard("Pure function")]]
	constexpr AABB<T> CreateBoundingBox(std::span<const Core::Vector3<T>> positions) noexcept;
}

namespace PonyMath::Shape
{
	template<Core::Arithmetic T>
	constexpr AABR<T> CreateBoundingRect(std::span<const Core::Vector2<T>> positions) noexcept
	{
		if (positions.size() == 0)
		{
			return AABR<T>::Predefined::Zero;
		}

		auto min = positions[0];
		auto max = positions[0];

		for (std::size_t i = 1; i < positions.size(); ++i)
		{
			min = Core::Min(min, positions[i]);
			max = Core::Max(max, positions[i]);
		}

		AABR<T> answer;
		answer.Center() = (min + max) / T{2};
		answer.Extents(Core::Vector2<T>(max.X() - answer.Center().X(), max.Y() - answer.Center().Y()));

		return answer;
	}

	template<Core::Arithmetic T>
	constexpr AABB<T> CreateBoundingBox(const std::span<const Core::Vector3<T>> positions) noexcept
	{
		if (positions.size() == 0)
		{
			return AABB<T>::Predefined::Zero;
		}

		auto min = positions[0];
		auto max = positions[0];

		for (std::size_t i = 1; i < positions.size(); ++i)
		{
			min = Core::Min(min, positions[i]);
			max = Core::Max(max, positions[i]);
		}

		AABB<T> answer;
		answer.Center() = (min + max) / T{2};
		answer.Extents(Core::Vector3<T>(max.X() - answer.Center().X(), max.Y() - answer.Center().Y(), max.Z() - answer.Center().Z()));

		return answer;
	}
}
