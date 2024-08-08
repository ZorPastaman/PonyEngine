/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math:ColorRGB;

import <algorithm>;
import <array>;
import <concepts>;
import <cstddef>;
import <format>;
import <ostream>;
import <string>;

import :Color888;
import :Vector3;

export namespace PonyEngine::Math
{
	template<std::floating_point T>
	class ColorRGB final
	{
	public:
		using ValueType = T; ///< Component type.

		static constexpr std::size_t ComponentCount = 3; ///< Component count. For any ColorRGB, it's always 3.

		struct Predefined; ///< Predefined colors.

		[[nodiscard("Pure constructor")]]
		constexpr ColorRGB() noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr ColorRGB(T red, T green, T blue) noexcept;
		[[nodiscard("Pure constructor")]]
		explicit constexpr ColorRGB(const T* components) noexcept;
		[[nodiscard("Pure constructor")]]
		explicit constexpr ColorRGB(const Color888& color) noexcept;
		[[nodiscard("Pure constructor")]]
		explicit constexpr ColorRGB(const Vector3<T>& vector) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr ColorRGB(const ColorRGB& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr ColorRGB(ColorRGB&& other) noexcept = default;

		constexpr ~ColorRGB() noexcept = default;

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
		constexpr T* Data() noexcept;
		[[nodiscard("Pure function")]]
		constexpr const T* Data() const noexcept;

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
		constexpr void Set(const T* componentsToSet) noexcept;

		[[nodiscard("Pure function")]]
		constexpr std::array<T, 3> ToArray() const noexcept;
		constexpr void ToArray(T (&array)[ComponentCount]) const noexcept;

		[[nodiscard("Pure function")]]
		std::string ToString() const;

		template<Arithmetic U> [[nodiscard("Pure operator")]]
		explicit constexpr operator ColorRGB<U>() const noexcept;
		[[nodiscard("Pure operator")]]
		explicit constexpr operator Color888() const noexcept;

		[[nodiscard("Pure operator")]]
		explicit constexpr operator Vector3<T>() const noexcept;

		[[nodiscard("Pure operator")]]
		constexpr T& operator [](std::size_t index) noexcept;
		[[nodiscard("Pure operator")]]
		constexpr const T& operator [](std::size_t index) const noexcept;

		constexpr ColorRGB& operator =(const ColorRGB& other) noexcept = default;
		constexpr ColorRGB& operator =(ColorRGB&& other) noexcept = default;
		constexpr ColorRGB& operator +=(const ColorRGB& other) noexcept;
		constexpr ColorRGB& operator -=(const ColorRGB& other) noexcept;
		constexpr ColorRGB& operator *=(const ColorRGB& other) noexcept;
		constexpr ColorRGB& operator *=(T multiplier) noexcept;
		constexpr ColorRGB& operator /=(const ColorRGB& other) noexcept;
		constexpr ColorRGB& operator /=(T divisor) noexcept;

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const ColorRGB& other) const noexcept;

	private:
		static constexpr T InverseColor888Max = T{1} / Color888::MaxValue;

		std::array<T, ComponentCount> components; ///< Component array in order red, green, blue, alpha.
	};

	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr T Distance(const ColorRGB<T>& left, const ColorRGB<T>& right) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr T DistanceSquared(const ColorRGB<T>& left, const ColorRGB<T>& right) noexcept;

	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr ColorRGB<T> Lerp(const ColorRGB<T>& from, const ColorRGB<T>& to, T time) noexcept;

	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const ColorRGB<T>& left, const ColorRGB<T>& right, T tolerance = T{0.00001}) noexcept;

	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr ColorRGB<T> operator +(const ColorRGB<T>& left, const ColorRGB<T>& right) noexcept;

	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr ColorRGB<T> operator -(const ColorRGB<T>& left, const ColorRGB<T>& right) noexcept;

	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr ColorRGB<T> operator *(const ColorRGB<T>& left, const ColorRGB<T>& right) noexcept;
	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr ColorRGB<T> operator *(const ColorRGB<T>& color, T multiplier) noexcept;
	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr ColorRGB<T> operator *(T multiplier, const ColorRGB<T>& color) noexcept;

	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr ColorRGB<T> operator /(const ColorRGB<T>& left, const ColorRGB<T>& right) noexcept;
	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr ColorRGB<T> operator /(const ColorRGB<T>& color, T divisor) noexcept;

	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const ColorRGB<T>& color);

	template<std::floating_point T>
	struct ColorRGB<T>::Predefined final
	{
		Predefined() = delete;

		static constexpr ColorRGB Red = ColorRGB(T{1}, T{0}, T{0});
		static constexpr ColorRGB Green = ColorRGB(T{0}, T{1}, T{0});
		static constexpr ColorRGB Blue = ColorRGB(T{0}, T{0}, T{1});
		static constexpr ColorRGB Black = ColorRGB(T{0}, T{0}, T{0});
		static constexpr ColorRGB White = ColorRGB(T{1}, T{1}, T{1});
		static constexpr ColorRGB Gray = ColorRGB(T{0.5}, T{0.5}, T{0.5});
		static constexpr ColorRGB Yellow = ColorRGB(T{1}, T{1}, T{0});
		static constexpr ColorRGB Magenta = ColorRGB(T{1}, T{0}, T{1});
		static constexpr ColorRGB Cyan = ColorRGB(T{0}, T{1}, T{1});
	};
}

namespace PonyEngine::Math
{
	template<std::floating_point T>
	constexpr ColorRGB<T>::ColorRGB(const T red, const T green, const T blue) noexcept :
		components{red, green, blue}
	{
	}

	template<std::floating_point T>
	constexpr ColorRGB<T>::ColorRGB(const T* const components) noexcept
	{
		Set(components);
	}

	template<std::floating_point T>
	constexpr ColorRGB<T>::ColorRGB(const Color888& color) noexcept :
		ColorRGB(color.R() * InverseColor888Max, color.G() * InverseColor888Max, color.B() * InverseColor888Max)
	{
	}

	template<std::floating_point T>
	constexpr ColorRGB<T>::ColorRGB(const Vector3<T>& vector) noexcept :
		ColorRGB(vector.Data())
	{
	}

	template<std::floating_point T>
	constexpr T& ColorRGB<T>::R() noexcept
	{
		return components[0];
	}

	template<std::floating_point T>
	constexpr const T& ColorRGB<T>::R() const noexcept
	{
		return components[0];
	}

	template<std::floating_point T>
	constexpr T& ColorRGB<T>::G() noexcept
	{
		return components[1];
	}

	template<std::floating_point T>
	constexpr const T& ColorRGB<T>::G() const noexcept
	{
		return components[1];
	}

	template<std::floating_point T>
	constexpr T& ColorRGB<T>::B() noexcept
	{
		return components[2];
	}

	template<std::floating_point T>
	constexpr const T& ColorRGB<T>::B() const noexcept
	{
		return components[2];
	}

	template<std::floating_point T>
	constexpr T* ColorRGB<T>::Data() noexcept
	{
		return components.data();
	}

	template<std::floating_point T>
	constexpr const T* ColorRGB<T>::Data() const noexcept
	{
		return components.data();
	}

	template<std::floating_point T>
	constexpr T ColorRGB<T>::Grayscale() const noexcept
	{
		return R() * T{0.299} + G() * T{0.587} + B() * T{0.114};
	}

	template<std::floating_point T>
	constexpr T& ColorRGB<T>::Min() noexcept
	{
		return *std::ranges::min_element(components);
	}

	template<std::floating_point T>
	constexpr const T& ColorRGB<T>::Min() const noexcept
	{
		return *std::ranges::min_element(components);
	}

	template<std::floating_point T>
	constexpr T& ColorRGB<T>::Max() noexcept
	{
		return *std::ranges::max_element(components);
	}

	template<std::floating_point T>
	constexpr const T& ColorRGB<T>::Max() const noexcept
	{
		return *std::ranges::max_element(components);
	}

	template<std::floating_point T>
	constexpr bool ColorRGB<T>::IsBlack() const noexcept
	{
		return *this == Predefined::Black;
	}

	template<std::floating_point T>
	constexpr bool ColorRGB<T>::IsAlmostBlack(const T tolerance) const noexcept
	{
		return AreAlmostEqual(*this, Predefined::Black, tolerance);
	}

	template<std::floating_point T>
	constexpr bool ColorRGB<T>::IsWhite() const noexcept
	{
		return *this == Predefined::White;
	}

	template<std::floating_point T>
	constexpr bool ColorRGB<T>::IsAlmostWhite(const T tolerance) const noexcept
	{
		return AreAlmostEqual(*this, Predefined::White, tolerance);
	}

	template<std::floating_point T>
	bool ColorRGB<T>::IsFinite() const noexcept
	{
		return std::isfinite(R()) && std::isfinite(G()) && std::isfinite(B());
	}

	template<std::floating_point T>
	constexpr void ColorRGB<T>::Set(const T red, const T green, const T blue) noexcept
	{
		R() = red;
		G() = green;
		B() = blue;
	}

	template<std::floating_point T>
	constexpr void ColorRGB<T>::Set(const T* const componentsToSet) noexcept
	{
		std::copy(componentsToSet, componentsToSet + ComponentCount, Data());
	}

	template<std::floating_point T>
	constexpr std::array<T, 3> ColorRGB<T>::ToArray() const noexcept
	{
		return components;
	}

	template<std::floating_point T>
	constexpr void ColorRGB<T>::ToArray(T (&array)[ComponentCount]) const noexcept
	{
		std::ranges::copy(components, array);
	}

	template<std::floating_point T>
	std::string ColorRGB<T>::ToString() const
	{
		return std::format("(R: {}, G: {}, B: {})", R(), G(), B());
	}

	template<std::floating_point T>
	constexpr T Distance(const ColorRGB<T>& left, const ColorRGB<T>& right) noexcept
	{
		return std::sqrt(DistanceSquared(left, right));
	}

	template<std::floating_point T>
	constexpr T DistanceSquared(const ColorRGB<T>& left, const ColorRGB<T>& right) noexcept
	{
		ColorRGB<T> difference = left - right;
		difference *= difference;

		return difference.R() + difference.G() + difference.B();
	}

	template<std::floating_point T>
	constexpr ColorRGB<T> Lerp(const ColorRGB<T>& from, const ColorRGB<T>& to, const T time) noexcept
	{
		return from + (to - from) * time;
	}

	template<std::floating_point T>
	constexpr bool AreAlmostEqual(const ColorRGB<T>& left, const ColorRGB<T>& right, const T tolerance) noexcept
	{
		return DistanceSquared(left, right) < tolerance * tolerance;
	}

	template<std::floating_point T>
	template<Arithmetic U>
	constexpr ColorRGB<T>::operator ColorRGB<U>() const noexcept
	{
		ColorRGB<U> cast;
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			cast[i] = static_cast<U>((*this)[i]);
		}

		return cast;
	}

	template<std::floating_point T>
	constexpr ColorRGB<T>::operator Color888() const noexcept
	{
		return Color888(R() * Color888::MaxValue, G() * Color888::MaxValue, B() * Color888::MaxValue);
	}

	template<std::floating_point T>
	constexpr ColorRGB<T>::operator Vector3<T>() const noexcept
	{
		return Vector3<T>(Data());
	}

	template<std::floating_point T>
	constexpr T& ColorRGB<T>::operator [](const std::size_t index) noexcept
	{
		return components[index];
	}

	template<std::floating_point T>
	constexpr const T& ColorRGB<T>::operator [](const std::size_t index) const noexcept
	{
		return components[index];
	}

	template<std::floating_point T>
	constexpr ColorRGB<T>& ColorRGB<T>::operator +=(const ColorRGB& other) noexcept
	{
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			(*this)[i] += other[i];
		}

		return *this;
	}

	template<std::floating_point T>
	constexpr ColorRGB<T>& ColorRGB<T>::operator -=(const ColorRGB& other) noexcept
	{
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			(*this)[i] -= other[i];
		}

		return *this;
	}

	template<std::floating_point T>
	constexpr ColorRGB<T>& ColorRGB<T>::operator *=(const ColorRGB& other) noexcept
	{
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			(*this)[i] *= other[i];
		}

		return *this;
	}

	template<std::floating_point T>
	constexpr ColorRGB<T>& ColorRGB<T>::operator *=(const T multiplier) noexcept
	{
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			(*this)[i] *= multiplier;
		}

		return *this;
	}

	template<std::floating_point T>
	constexpr ColorRGB<T>& ColorRGB<T>::operator /=(const ColorRGB& other) noexcept
	{
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			(*this)[i] /= other[i];
		}

		return *this;
	}

	template<std::floating_point T>
	constexpr ColorRGB<T>& ColorRGB<T>::operator /=(const T divisor) noexcept
	{
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			(*this)[i] /= divisor;
		}

		return *this;
	}

	template<std::floating_point T>
	constexpr bool ColorRGB<T>::operator ==(const ColorRGB& other) const noexcept
	{
		return components == other.components;
	}

	template<std::floating_point T>
	constexpr ColorRGB<T> operator +(const ColorRGB<T>& left, const ColorRGB<T>& right) noexcept
	{
		ColorRGB<T> sum;
		for (std::size_t i = 0; i < ColorRGB<T>::ComponentCount; ++i)
		{
			sum[i] = left[i] + right[i];
		}

		return sum;
	}

	template<std::floating_point T>
	constexpr ColorRGB<T> operator -(const ColorRGB<T>& left, const ColorRGB<T>& right) noexcept
	{
		ColorRGB<T> difference;
		for (std::size_t i = 0; i < ColorRGB<T>::ComponentCount; ++i)
		{
			difference[i] = left[i] - right[i];
		}

		return difference;
	}

	template<std::floating_point T>
	constexpr ColorRGB<T> operator *(const ColorRGB<T>& left, const ColorRGB<T>& right) noexcept
	{
		ColorRGB<T> product;
		for (std::size_t i = 0; i < ColorRGB<T>::ComponentCount; ++i)
		{
			product[i] = left[i] * right[i];
		}

		return product;
	}

	template<std::floating_point T>
	constexpr ColorRGB<T> operator *(const ColorRGB<T>& color, const T multiplier) noexcept
	{
		ColorRGB<T> product;
		for (std::size_t i = 0; i < ColorRGB<T>::ComponentCount; ++i)
		{
			product[i] = color[i] * multiplier;
		}

		return product;
	}

	template<std::floating_point T>
	constexpr ColorRGB<T> operator *(const T multiplier, const ColorRGB<T>& color) noexcept
	{
		return color * multiplier;
	}

	template<std::floating_point T>
	constexpr ColorRGB<T> operator /(const ColorRGB<T>& left, const ColorRGB<T>& right) noexcept
	{
		ColorRGB<T> quotient;
		for (std::size_t i = 0; i < ColorRGB<T>::ComponentCount; ++i)
		{
			quotient[i] = left[i] / right[i];
		}

		return quotient;
	}

	template<std::floating_point T>
	constexpr ColorRGB<T> operator /(const ColorRGB<T>& color, const T divisor) noexcept
	{
		ColorRGB<T> quotient;
		for (std::size_t i = 0; i < ColorRGB<T>::ComponentCount; ++i)
		{
			quotient[i] = color[i] / divisor;
		}

		return quotient;
	}

	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const ColorRGB<T>& color)
	{
		return stream << color.ToString();
	}
}
