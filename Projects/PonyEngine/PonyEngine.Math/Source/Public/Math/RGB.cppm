/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math:RGB;

import <algorithm>;
import <array>;
import <concepts>;
import <cstddef>;
import <format>;
import <ostream>;
import <span>;
import <string>;

import :RGBInt;
import :Vector3;

export namespace PonyEngine::Math
{
	template<std::floating_point T>
	class RGB final
	{
	public:
		using ValueType = T; ///< Component type.

		static constexpr std::size_t ComponentCount = 3; ///< Component count. For any RGB, it's always 3.

		struct Predefined; ///< Predefined colors.

		[[nodiscard("Pure constructor")]]
		constexpr RGB() noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr RGB(T red, T green, T blue) noexcept;
		[[nodiscard("Pure constructor")]]
		explicit constexpr RGB(std::span<const T, ComponentCount> span) noexcept;
		template<std::unsigned_integral U> [[nodiscard("Pure constructor")]]
		explicit constexpr RGB(const RGBInt<U>& color) noexcept;
		[[nodiscard("Pure constructor")]]
		explicit constexpr RGB(const Vector3<T>& vector) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr RGB(const RGB& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr RGB(RGB&& other) noexcept = default;

		constexpr ~RGB() noexcept = default;

		[[nodiscard("Pure function")]]
		constexpr T& R() noexcept;
		[[nodiscard("Pure function")]]
		constexpr const T& R() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr T& G() noexcept;
		[[nodiscard("Pure function")]]
		constexpr const T& G() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr T& B() noexcept;
		[[nodiscard("Pure function")]]
		constexpr const T& B() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr std::span<T, 3> Span() noexcept;
		[[nodiscard("Pure function")]]
		constexpr std::span<const T, 3> Span() const noexcept;

		[[nodiscard("Pure function")]]
		constexpr T Grayscale() const noexcept;

		[[nodiscard("Pure function")]]
		constexpr T& Min() noexcept;
		[[nodiscard("Pure function")]]
		constexpr const T& Min() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr T& Max() noexcept;
		[[nodiscard("Pure function")]]
		constexpr const T& Max() const noexcept;

		[[nodiscard("Pure function")]]
		constexpr bool IsBlack() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr bool IsAlmostBlack(T tolerance = T{0.00001}) const noexcept;
		[[nodiscard("Pure function")]]
		constexpr bool IsWhite() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr bool IsAlmostWhite(T tolerance = T{0.00001}) const noexcept;

		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept;

		constexpr void Set(T red, T green, T blue) noexcept;
		constexpr void Set(std::span<const T, 3> span) noexcept;

		[[nodiscard("Pure function")]]
		std::string ToString() const;

		template<std::floating_point U> [[nodiscard("Pure operator")]]
		explicit constexpr operator RGB<U>() const noexcept;
		template<std::unsigned_integral U> [[nodiscard("Pure operator")]]
		explicit constexpr operator RGBInt<U>() const noexcept;

		[[nodiscard("Pure operator")]]
		explicit constexpr operator Vector3<T>() const noexcept;

		[[nodiscard("Pure operator")]]
		constexpr T& operator [](std::size_t index) noexcept;
		[[nodiscard("Pure operator")]]
		constexpr const T& operator [](std::size_t index) const noexcept;

		constexpr RGB& operator =(const RGB& other) noexcept = default;
		constexpr RGB& operator =(RGB&& other) noexcept = default;
		constexpr RGB& operator +=(const RGB& other) noexcept;
		constexpr RGB& operator -=(const RGB& other) noexcept;
		constexpr RGB& operator *=(const RGB& other) noexcept;
		constexpr RGB& operator *=(T multiplier) noexcept;
		constexpr RGB& operator /=(const RGB& other) noexcept;
		constexpr RGB& operator /=(T divisor) noexcept;

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const RGB& other) const noexcept;

	private:
		std::array<T, ComponentCount> components; ///< Component array in order red, green, blue, alpha.
	};

	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr T Distance(const RGB<T>& left, const RGB<T>& right) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr T DistanceSquared(const RGB<T>& left, const RGB<T>& right) noexcept;

	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr RGB<T> Lerp(const RGB<T>& from, const RGB<T>& to, T time) noexcept;

	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const RGB<T>& left, const RGB<T>& right, T tolerance = T{0.00001}) noexcept;

	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr RGB<T> operator +(const RGB<T>& left, const RGB<T>& right) noexcept;

	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr RGB<T> operator -(const RGB<T>& left, const RGB<T>& right) noexcept;

	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr RGB<T> operator *(const RGB<T>& left, const RGB<T>& right) noexcept;
	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr RGB<T> operator *(const RGB<T>& color, T multiplier) noexcept;
	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr RGB<T> operator *(T multiplier, const RGB<T>& color) noexcept;

	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr RGB<T> operator /(const RGB<T>& left, const RGB<T>& right) noexcept;
	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr RGB<T> operator /(const RGB<T>& color, T divisor) noexcept;

	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const RGB<T>& color);

	template<std::floating_point T>
	struct RGB<T>::Predefined final
	{
		Predefined() = delete;

		static constexpr RGB Red = RGB(T{1}, T{0}, T{0});
		static constexpr RGB Green = RGB(T{0}, T{1}, T{0});
		static constexpr RGB Blue = RGB(T{0}, T{0}, T{1});
		static constexpr RGB Black = RGB(T{0}, T{0}, T{0});
		static constexpr RGB White = RGB(T{1}, T{1}, T{1});
		static constexpr RGB Gray = RGB(T{0.5}, T{0.5}, T{0.5});
		static constexpr RGB Yellow = RGB(T{1}, T{1}, T{0});
		static constexpr RGB Magenta = RGB(T{1}, T{0}, T{1});
		static constexpr RGB Cyan = RGB(T{0}, T{1}, T{1});
	};
}

namespace PonyEngine::Math
{
	template<std::floating_point T>
	constexpr RGB<T>::RGB(const T red, const T green, const T blue) noexcept :
		components{red, green, blue}
	{
	}

	template<std::floating_point T>
	constexpr RGB<T>::RGB(const std::span<const T, ComponentCount> span) noexcept
	{
		Set(span);
	}

	template<std::floating_point T>
	template<std::unsigned_integral U>
	constexpr RGB<T>::RGB(const RGBInt<U>& color) noexcept
	{
		constexpr T inverseMaxValue = T{1} / RGBInt<U>::MaxValue;
		Set(color.R() * inverseMaxValue, color.G() * inverseMaxValue, color.B() * inverseMaxValue);
	}

	template<std::floating_point T>
	constexpr RGB<T>::RGB(const Vector3<T>& vector) noexcept :
		RGB(vector.Data())
	{
	}

	template<std::floating_point T>
	constexpr T& RGB<T>::R() noexcept
	{
		return components[0];
	}

	template<std::floating_point T>
	constexpr const T& RGB<T>::R() const noexcept
	{
		return components[0];
	}

	template<std::floating_point T>
	constexpr T& RGB<T>::G() noexcept
	{
		return components[1];
	}

	template<std::floating_point T>
	constexpr const T& RGB<T>::G() const noexcept
	{
		return components[1];
	}

	template<std::floating_point T>
	constexpr T& RGB<T>::B() noexcept
	{
		return components[2];
	}

	template<std::floating_point T>
	constexpr const T& RGB<T>::B() const noexcept
	{
		return components[2];
	}

	template<std::floating_point T>
	constexpr std::span<T, 3> RGB<T>::Span() noexcept
	{
		return components;
	}

	template<std::floating_point T>
	constexpr std::span<const T, 3> RGB<T>::Span() const noexcept
	{
		return components;
	}

	template<std::floating_point T>
	constexpr T RGB<T>::Grayscale() const noexcept
	{
		return R() * T{0.299} + G() * T{0.587} + B() * T{0.114};
	}

	template<std::floating_point T>
	constexpr T& RGB<T>::Min() noexcept
	{
		return *std::ranges::min_element(components);
	}

	template<std::floating_point T>
	constexpr const T& RGB<T>::Min() const noexcept
	{
		return *std::ranges::min_element(components);
	}

	template<std::floating_point T>
	constexpr T& RGB<T>::Max() noexcept
	{
		return *std::ranges::max_element(components);
	}

	template<std::floating_point T>
	constexpr const T& RGB<T>::Max() const noexcept
	{
		return *std::ranges::max_element(components);
	}

	template<std::floating_point T>
	constexpr bool RGB<T>::IsBlack() const noexcept
	{
		return *this == Predefined::Black;
	}

	template<std::floating_point T>
	constexpr bool RGB<T>::IsAlmostBlack(const T tolerance) const noexcept
	{
		return AreAlmostEqual(*this, Predefined::Black, tolerance);
	}

	template<std::floating_point T>
	constexpr bool RGB<T>::IsWhite() const noexcept
	{
		return *this == Predefined::White;
	}

	template<std::floating_point T>
	constexpr bool RGB<T>::IsAlmostWhite(const T tolerance) const noexcept
	{
		return AreAlmostEqual(*this, Predefined::White, tolerance);
	}

	template<std::floating_point T>
	bool RGB<T>::IsFinite() const noexcept
	{
		return std::isfinite(R()) && std::isfinite(G()) && std::isfinite(B());
	}

	template<std::floating_point T>
	constexpr void RGB<T>::Set(const T red, const T green, const T blue) noexcept
	{
		R() = red;
		G() = green;
		B() = blue;
	}

	template<std::floating_point T>
	constexpr void RGB<T>::Set(const std::span<const T, 3> span) noexcept
	{
		std::ranges::copy(span, components.data());
	}

	template<std::floating_point T>
	std::string RGB<T>::ToString() const
	{
		return std::format("(R: {}, G: {}, B: {})", R(), G(), B());
	}

	template<std::floating_point T>
	constexpr T Distance(const RGB<T>& left, const RGB<T>& right) noexcept
	{
		return std::sqrt(DistanceSquared(left, right));
	}

	template<std::floating_point T>
	constexpr T DistanceSquared(const RGB<T>& left, const RGB<T>& right) noexcept
	{
		RGB<T> difference = left - right;
		difference *= difference;

		return difference.R() + difference.G() + difference.B();
	}

	template<std::floating_point T>
	constexpr RGB<T> Lerp(const RGB<T>& from, const RGB<T>& to, const T time) noexcept
	{
		return from + (to - from) * time;
	}

	template<std::floating_point T>
	constexpr bool AreAlmostEqual(const RGB<T>& left, const RGB<T>& right, const T tolerance) noexcept
	{
		return DistanceSquared(left, right) < tolerance * tolerance;
	}

	template<std::floating_point T>
	template<std::floating_point U>
	constexpr RGB<T>::operator RGB<U>() const noexcept
	{
		RGB<U> cast;
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			cast[i] = static_cast<U>((*this)[i]);
		}

		return cast;
	}

	template<std::floating_point T>
	template<std::unsigned_integral U>
	constexpr RGB<T>::operator RGBInt<U>() const noexcept
	{
		return RGBInt<U>(R() * RGBInt<U>::MaxValue, G() * RGBInt<U>::MaxValue, B() * RGBInt<U>::MaxValue);
	}

	template<std::floating_point T>
	constexpr RGB<T>::operator Vector3<T>() const noexcept
	{
		return Vector3<T>(Span().data());
	}

	template<std::floating_point T>
	constexpr T& RGB<T>::operator [](const std::size_t index) noexcept
	{
		return components[index];
	}

	template<std::floating_point T>
	constexpr const T& RGB<T>::operator [](const std::size_t index) const noexcept
	{
		return components[index];
	}

	template<std::floating_point T>
	constexpr RGB<T>& RGB<T>::operator +=(const RGB& other) noexcept
	{
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			(*this)[i] += other[i];
		}

		return *this;
	}

	template<std::floating_point T>
	constexpr RGB<T>& RGB<T>::operator -=(const RGB& other) noexcept
	{
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			(*this)[i] -= other[i];
		}

		return *this;
	}

	template<std::floating_point T>
	constexpr RGB<T>& RGB<T>::operator *=(const RGB& other) noexcept
	{
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			(*this)[i] *= other[i];
		}

		return *this;
	}

	template<std::floating_point T>
	constexpr RGB<T>& RGB<T>::operator *=(const T multiplier) noexcept
	{
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			(*this)[i] *= multiplier;
		}

		return *this;
	}

	template<std::floating_point T>
	constexpr RGB<T>& RGB<T>::operator /=(const RGB& other) noexcept
	{
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			(*this)[i] /= other[i];
		}

		return *this;
	}

	template<std::floating_point T>
	constexpr RGB<T>& RGB<T>::operator /=(const T divisor) noexcept
	{
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			(*this)[i] /= divisor;
		}

		return *this;
	}

	template<std::floating_point T>
	constexpr bool RGB<T>::operator ==(const RGB& other) const noexcept
	{
		return components == other.components;
	}

	template<std::floating_point T>
	constexpr RGB<T> operator +(const RGB<T>& left, const RGB<T>& right) noexcept
	{
		RGB<T> sum;
		for (std::size_t i = 0; i < RGB<T>::ComponentCount; ++i)
		{
			sum[i] = left[i] + right[i];
		}

		return sum;
	}

	template<std::floating_point T>
	constexpr RGB<T> operator -(const RGB<T>& left, const RGB<T>& right) noexcept
	{
		RGB<T> difference;
		for (std::size_t i = 0; i < RGB<T>::ComponentCount; ++i)
		{
			difference[i] = left[i] - right[i];
		}

		return difference;
	}

	template<std::floating_point T>
	constexpr RGB<T> operator *(const RGB<T>& left, const RGB<T>& right) noexcept
	{
		RGB<T> product;
		for (std::size_t i = 0; i < RGB<T>::ComponentCount; ++i)
		{
			product[i] = left[i] * right[i];
		}

		return product;
	}

	template<std::floating_point T>
	constexpr RGB<T> operator *(const RGB<T>& color, const T multiplier) noexcept
	{
		RGB<T> product;
		for (std::size_t i = 0; i < RGB<T>::ComponentCount; ++i)
		{
			product[i] = color[i] * multiplier;
		}

		return product;
	}

	template<std::floating_point T>
	constexpr RGB<T> operator *(const T multiplier, const RGB<T>& color) noexcept
	{
		return color * multiplier;
	}

	template<std::floating_point T>
	constexpr RGB<T> operator /(const RGB<T>& left, const RGB<T>& right) noexcept
	{
		RGB<T> quotient;
		for (std::size_t i = 0; i < RGB<T>::ComponentCount; ++i)
		{
			quotient[i] = left[i] / right[i];
		}

		return quotient;
	}

	template<std::floating_point T>
	constexpr RGB<T> operator /(const RGB<T>& color, const T divisor) noexcept
	{
		RGB<T> quotient;
		for (std::size_t i = 0; i < RGB<T>::ComponentCount; ++i)
		{
			quotient[i] = color[i] / divisor;
		}

		return quotient;
	}

	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const RGB<T>& color)
	{
		return stream << color.ToString();
	}
}
