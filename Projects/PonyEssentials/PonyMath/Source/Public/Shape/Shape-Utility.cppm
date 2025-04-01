/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyMath.Shape:Utility;

import <algorithm>;
import <cstddef>;
import <optional>;
import <span>;

import PonyMath.Core;

import :AABB;
import :AABR;

export namespace PonyMath::Shape
{
	/// @brief Creates an axis-aligned bounding rect that overlaps all the @p positions.
	/// @tparam T Component type.
	/// @param positions Position.
	/// @return Axis-aligned bounding rect. @a Nullopt if the @p positions count is zero.
	template<Core::Arithmetic T> [[nodiscard("Pure function")]]
	std::optional<AABR<T>> CreateBoundingRect(std::span<const Core::Vector2<T>> positions) noexcept;
	/// @brief Creates an axis-aligned bounding box that overlaps all the @p positions.
	/// @tparam T Component type.
	/// @param positions Position.
	/// @return Axis-aligned bounding box. @a Nullopt if the @p positions count is zero.
	template<Core::Arithmetic T> [[nodiscard("Pure function")]]
	std::optional<AABB<T>> CreateBoundingBox(std::span<const Core::Vector3<T>> positions) noexcept;
}

namespace PonyMath::Shape
{
	template<Core::Arithmetic T>
	std::optional<AABR<T>> CreateBoundingRect(const std::span<const Core::Vector2<T>> positions) noexcept
	{
		if (positions.size() == 0) [[unlikely]]
		{
			return std::nullopt;
		}

		auto min = positions[0];
		auto max = positions[0];
		for (std::size_t i = 1; i < positions.size(); ++i)
		{
			min = Core::Min(min, positions[i]);
			max = Core::Max(max, positions[i]);
		}

		const Core::Vector2<T> center = (min + max) / T{2};
		Core::Vector2<T> extents;
		for (std::size_t i = 0; i < Core::Vector2<T>::ComponentCount; ++i)
		{
			const T extent = std::max(max[i] - center[i], center[i] - min[i]);
			extents[i] = std::max(extent, T{0});
		}

		return AABR<T>(center, extents);
	}

	template<Core::Arithmetic T>
	std::optional<AABB<T>> CreateBoundingBox(const std::span<const Core::Vector3<T>> positions) noexcept
	{
		if (positions.size() == 0) [[unlikely]]
		{
			return std::nullopt;
		}

		auto min = positions[0];
		auto max = positions[0];
		for (std::size_t i = 1; i < positions.size(); ++i)
		{
			min = Core::Min(min, positions[i]);
			max = Core::Max(max, positions[i]);
		}

		const Core::Vector3<T> center = (min + max) / T{2};
		Core::Vector3<T> extents;
		for (std::size_t i = 0; i < Core::Vector3<T>::ComponentCount; ++i)
		{
			const T extent = std::max(max[i] - center[i], center[i] - min[i]);
			extents[i] = std::max(extent, T{0});
		}

		return AABB<T>(center, extents);
	}
}
