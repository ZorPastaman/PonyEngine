/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/ObjectBody.h"

export module PonyMath.Shape:Rect;

import <cstddef>;
import <format>;
import <ostream>;
import <string>;
import <type_traits>;

import PonyMath.Core;

export namespace PonyMath::Shape
{
	template<Core::Arithmetic T>
	class Rect final // TODO: Add docs and tests
	{
	public:
		using ValueType = T;

		struct Predefined;

		[[nodiscard("Pure constructor")]]
		constexpr Rect() noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Rect(T x, T y, T width, T height) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Rect(const Core::Vector2<T>& position, const Core::Vector2<T>& size) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Rect(const Rect& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Rect(Rect&& other) noexcept = default;

		constexpr ~Rect() noexcept = default;

		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T>& Position() noexcept;
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector2<T>& Position() const noexcept;

		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T>& Size() noexcept;
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector2<T>& Size() const noexcept;

		[[nodiscard("Pure function")]]
		constexpr T MinX() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr T MinY() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T> Min() const noexcept;
		void MinX(T minX) noexcept;
		void MinY(T minY) noexcept;
		void Min(const Core::Vector2<T>& min) noexcept;

		[[nodiscard("Pure function")]]
		constexpr T MaxX() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr T MaxY() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T> Max() const noexcept;
		void MaxX(T maxX) noexcept;
		void MaxY(T maxY) noexcept;
		void Max(const Core::Vector2<T>& max) noexcept;

		[[nodiscard("Pure function")]]
		constexpr T Width() const noexcept;
		template<bool KeepCenter = false>
		constexpr void Width(T width) noexcept;
		[[nodiscard("Pure function")]]
		constexpr T Height() const noexcept;
		template<bool KeepCenter = false>
		constexpr void Height(T height) noexcept;

		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T> Center() const noexcept;
		constexpr void Center(const Core::Vector2<T>& center) noexcept;

		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept requires (std::is_floating_point_v<T>);

		[[nodiscard("Pure function")]]
		constexpr bool Contains(const Core::Vector2<T>& point) const noexcept; // TODO: Add AreOverlapping() functions

		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T> Normalize(const Core::Vector2<T>& point) const noexcept requires (std::is_floating_point_v<T>);
		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T> Unnormalize(const Core::Vector2<T>& point) const noexcept requires (std::is_floating_point_v<T>);
		[[nodiscard("Pure function")]]
		constexpr Rect Normalize(const Rect& rect) const noexcept requires (std::is_floating_point_v<T>);
		[[nodiscard("Pure function")]]
		constexpr Rect Unnormalize(const Rect& rect) const noexcept requires (std::is_floating_point_v<T>);

		constexpr void Set(T x, T y, T width, T height) noexcept;
		constexpr void Set(const Core::Vector2<T>& positionToSet, const Core::Vector2<T>& sizeToSet) noexcept;

		[[nodiscard("Pure function")]]
		std::string ToString() const;

		template<Core::Arithmetic U> [[nodiscard("Pure operator")]]
		explicit constexpr operator Rect<U>() const noexcept;

		constexpr Rect& operator =(const Rect& other) noexcept = default;
		constexpr Rect& operator =(Rect&& other) noexcept = default;

		[[nodiscard("Pure function")]]
		constexpr bool operator ==(const Rect& other) const noexcept = default;

	private:
		Core::Vector2<T> position;
		Core::Vector2<T> size;
	};

	template<Core::Arithmetic T>
	std::ostream& operator <<(std::ostream& stream, const Rect<T>& rect);

	template<Core::Arithmetic T>
	struct Rect<T>::Predefined final
	{
		NON_CONSTRUCTIBLE_BODY(Predefined)

		static constexpr auto Zero = Rect(T{0}, T{0}, T{0}, T{0});
	};
}

namespace PonyMath::Shape
{
	template<Core::Arithmetic T>
	constexpr Rect<T>::Rect(const T x, const T y, const T width, const T height) noexcept :
		position(x, y),
		size(width, height)
	{
	}

	template<Core::Arithmetic T>
	constexpr Rect<T>::Rect(const Core::Vector2<T>& position, const Core::Vector2<T>& size) noexcept :
		position(position),
		size(size)
	{
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector2<T>& Rect<T>::Position() noexcept
	{
		return position;
	}

	template<Core::Arithmetic T>
	constexpr const Core::Vector2<T>& Rect<T>::Position() const noexcept
	{
		return position;
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector2<T>& Rect<T>::Size() noexcept
	{
		return size;
	}

	template<Core::Arithmetic T>
	constexpr const Core::Vector2<T>& Rect<T>::Size() const noexcept
	{
		return size;
	}

	template<Core::Arithmetic T>
	constexpr T Rect<T>::MinX() const noexcept
	{
		return position.X();
	}

	template<Core::Arithmetic T>
	constexpr T Rect<T>::MinY() const noexcept
	{
		return position.Y();
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector2<T> Rect<T>::Min() const noexcept
	{
		return position;
	}

	template<Core::Arithmetic T>
	void Rect<T>::MinX(const T minX) noexcept
	{
		position.X() = minX;
	}

	template<Core::Arithmetic T>
	void Rect<T>::MinY(const T minY) noexcept
	{
		position.Y() = minY;
	}

	template<Core::Arithmetic T>
	void Rect<T>::Min(const Core::Vector2<T>& min) noexcept
	{
		position = min;
	}

	template<Core::Arithmetic T>
	constexpr T Rect<T>::MaxX() const noexcept
	{
		return position.X() + size.X();
	}

	template<Core::Arithmetic T>
	constexpr T Rect<T>::MaxY() const noexcept
	{
		return position.Y() + size.Y();
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector2<T> Rect<T>::Max() const noexcept
	{
		return Core::Vector2<T>(MaxX(), MaxY());
	}

	template<Core::Arithmetic T>
	void Rect<T>::MaxX(const T maxX) noexcept
	{
		size.X() = maxX - position.X();
	}

	template<Core::Arithmetic T>
	void Rect<T>::MaxY(const T maxY) noexcept
	{
		size.Y() = maxY - position.Y();
	}

	template<Core::Arithmetic T>
	void Rect<T>::Max(const Core::Vector2<T>& max) noexcept
	{
		size = max - position;
	}

	template<Core::Arithmetic T>
	bool Rect<T>::IsFinite() const noexcept requires (std::is_floating_point_v<T>)
	{
		return position.IsFinite() && size.IsFinite();
	}

	template<Core::Arithmetic T>
	constexpr T Rect<T>::Width() const noexcept
	{
		return size.X();
	}

	template<Core::Arithmetic T>
	template<bool KeepCenter>
	constexpr void Rect<T>::Width(const T width) noexcept
	{
		if constexpr (KeepCenter)
		{
			const T halfDelta = (width - size.X()) / T{2};
			position.X() -= halfDelta;
			size.X() += halfDelta;
		}
		else
		{
			size.X() = width;
		}
	}

	template<Core::Arithmetic T>
	constexpr T Rect<T>::Height() const noexcept
	{
		return size.Y();
	}

	template<Core::Arithmetic T>
	template<bool KeepCenter>
	constexpr void Rect<T>::Height(const T height) noexcept
	{
		if constexpr (KeepCenter)
		{
			const T halfDelta = (height - size.X()) / T{2};
			position.Y() -= halfDelta;
			size.Y() += halfDelta;
		}
		else
		{
			size.Y() = height;
		}
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector2<T> Rect<T>::Center() const noexcept
	{
		return position + size / T{2};
	}

	template<Core::Arithmetic T>
	constexpr void Rect<T>::Center(const Core::Vector2<T>& center) noexcept
	{
		position = center - (Center() - position);
	}

	template<Core::Arithmetic T>
	constexpr bool Rect<T>::Contains(const Core::Vector2<T>& point) const noexcept
	{
		const Core::Vector2<T> max = Max();

		return point.X() >= position.X() && point.Y() >= position.Y() && point.X() <= max.X() && point.Y() <= max.Y();
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector2<T> Rect<T>::Normalize(const Core::Vector2<T>& point) const noexcept requires (std::is_floating_point_v<T>)
	{
		Core::Vector2<T> normalized;
		for (std::size_t i = 0; i < Core::Vector2<T>::ComponentCount; ++i)
		{
			normalized[i] = (point[i] - position[i]) / size[i];
		}

		return normalized;
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector2<T> Rect<T>::Unnormalize(const Core::Vector2<T>& point) const noexcept requires (std::is_floating_point_v<T>)
	{
		Core::Vector2<T> unnormalized;
		for (std::size_t i = 0; i < Core::Vector2<T>::ComponentCount; ++i)
		{
			unnormalized[i] = point[i] * size[i] + position[i];
		}

		return unnormalized;
	}

	template<Core::Arithmetic T>
	constexpr Rect<T> Rect<T>::Normalize(const Rect& rect) const noexcept requires (std::is_floating_point_v<T>)
	{
		Rect normalized;
		normalized.position = Normalize(rect.position);
		for (std::size_t i = 0; i < Core::Vector2<T>::ComponentCount; ++i)
		{
			normalized.size[i] = rect.size[i] / size[i];
		}

		return normalized;
	}

	template<Core::Arithmetic T>
	constexpr Rect<T> Rect<T>::Unnormalize(const Rect& rect) const noexcept requires (std::is_floating_point_v<T>)
	{
		Rect unnormalized;
		unnormalized.position = Unnormalize(rect.position);
		for (std::size_t i = 0; i < Core::Vector2<T>::ComponentCount; ++i)
		{
			unnormalized.size[i] = rect.size[i] * size[i];
		}

		return unnormalized;
	}

	template<Core::Arithmetic T>
	constexpr void Rect<T>::Set(const T x, const T y, const T width, const T height) noexcept
	{
		position.Set(x, y);
		size.Set(width, height);
	}

	template<Core::Arithmetic T>
	constexpr void Rect<T>::Set(const Core::Vector2<T>& positionToSet, const Core::Vector2<T>& sizeToSet) noexcept
	{
		position.Set(positionToSet);
		size.Set(sizeToSet);
	}

	template<Core::Arithmetic T>
	template<Core::Arithmetic U>
	constexpr Rect<T>::operator Rect<U>() const noexcept
	{
		Rect<U> rect;
		for (std::size_t i = 0; i < Core::Vector2<U>::ComponentCount; ++i)
		{
			rect.Position()[i] = static_cast<U>(position[i]);
			rect.Size()[i] = static_cast<U>(size[i]);
		}

		return rect;
	}

	template<Core::Arithmetic T>
	std::string Rect<T>::ToString() const
	{
		return std::format("Position: {}, Size: {}", position.ToString(), size.ToString());
	}

	template<Core::Arithmetic T>
	std::ostream& operator <<(std::ostream& stream, const Rect<T>& rect)
	{
		return stream << rect.ToString();
	}
}
