/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math:ColorRGBA;

import <algorithm>;
import <array>;
import <concepts>;
import <cstddef>;
import <format>;
import <ostream>;
import <string>;

import :Color8888;
import :ColorRGB;
import :Common;
import :Vector4;

export namespace PonyEngine::Math
{
	template<std::floating_point T>
	class ColorRGBA final
	{
	public:
		using ValueType = T; ///< Component type.

		static constexpr std::size_t ComponentCount = 4; ///< Component count. For any ColorRGBA, it's always 4.

		struct Predefined; ///< Predefined colors.

		[[nodiscard("Pure constructor")]]
		constexpr ColorRGBA() noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr ColorRGBA(T red, T green, T blue, T alpha) noexcept;
		[[nodiscard("Pure constructor")]]
		explicit constexpr ColorRGBA(const T* components) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr ColorRGBA(const ColorRGB<T>& rgb, T alpha) noexcept;
		[[nodiscard("Pure constructor")]]
		explicit constexpr ColorRGBA(const Color8888& color) noexcept;
		[[nodiscard("Pure constructor")]]
		explicit constexpr ColorRGBA(const Vector4<T>& vector) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr ColorRGBA(const ColorRGBA& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr ColorRGBA(ColorRGBA&& other) noexcept = default;

		constexpr ~ColorRGBA() noexcept = default;

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
		constexpr T& A() noexcept;
		[[nodiscard("Pure function")]]
		constexpr const T& A() const noexcept;
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
		constexpr bool IsTransparent() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr bool IsAlmostTransparent(T tolerance = T{0.00001}) const noexcept;

		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept;

		constexpr void Set(T red, T green, T blue, T alpha) noexcept;
		constexpr void Set(const T* componentsToSet) noexcept;

		[[nodiscard("Pure function")]]
		constexpr std::array<T, 4> ToArray() const noexcept;
		constexpr void ToArray(T (&array)[ComponentCount]) const noexcept;

		[[nodiscard("Pure function")]]
		std::string ToString() const;

		template<Arithmetic U> [[nodiscard("Pure operator")]]
		explicit constexpr operator ColorRGBA<U>() const noexcept;
		[[nodiscard("Pure operator")]]
		explicit constexpr operator ColorRGB<T>() const noexcept;
		[[nodiscard("Pure operator")]]
		explicit constexpr operator Color8888() const noexcept;

		[[nodiscard("Pure operator")]]
		explicit constexpr operator Vector4<T>() const noexcept;

		[[nodiscard("Pure operator")]]
		constexpr T& operator [](std::size_t index) noexcept;
		[[nodiscard("Pure operator")]]
		constexpr const T& operator [](std::size_t index) const noexcept;

		constexpr ColorRGBA& operator =(const ColorRGBA& other) noexcept = default;
		constexpr ColorRGBA& operator =(ColorRGBA&& other) noexcept = default;
		constexpr ColorRGBA& operator +=(const ColorRGBA& other) noexcept;
		constexpr ColorRGBA& operator -=(const ColorRGBA& other) noexcept;
		constexpr ColorRGBA& operator *=(const ColorRGBA& other) noexcept;
		constexpr ColorRGBA& operator *=(T multiplier) noexcept;
		constexpr ColorRGBA& operator /=(const ColorRGBA& other) noexcept;
		constexpr ColorRGBA& operator /=(T divisor) noexcept;

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const ColorRGBA& other) const noexcept;

	private:
		static constexpr T InverseColor8888Max = T{1} / Color8888::MaxValue;

		std::array<T, ComponentCount> components; ///< Component array in order red, green, blue, alpha.
	};

	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr T Distance(const ColorRGBA<T>& left, const ColorRGBA<T>& right) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr T DistanceSquared(const ColorRGBA<T>& left, const ColorRGBA<T>& right) noexcept;

	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr ColorRGBA<T> Lerp(const ColorRGBA<T>& from, const ColorRGBA<T>& to, T time) noexcept;

	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const ColorRGBA<T>& left, const ColorRGBA<T>& right, T tolerance = T{0.00001}) noexcept;

	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr ColorRGBA<T> operator +(const ColorRGBA<T>& left, const ColorRGBA<T>& right) noexcept;

	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr ColorRGBA<T> operator -(const ColorRGBA<T>& left, const ColorRGBA<T>& right) noexcept;

	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr ColorRGBA<T> operator *(const ColorRGBA<T>& left, const ColorRGBA<T>& right) noexcept;
	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr ColorRGBA<T> operator *(const ColorRGBA<T>& color, T multiplier) noexcept;
	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr ColorRGBA<T> operator *(T multiplier, const ColorRGBA<T>& color) noexcept;

	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr ColorRGBA<T> operator /(const ColorRGBA<T>& left, const ColorRGBA<T>& right) noexcept;
	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr ColorRGBA<T> operator /(const ColorRGBA<T>& color, T divisor) noexcept;

	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const ColorRGBA<T>& color);

	template<std::floating_point T>
	struct ColorRGBA<T>::Predefined final
	{
		Predefined() = delete;

		static constexpr ColorRGBA Red = ColorRGBA(T{1}, T{0}, T{0}, T{1});
		static constexpr ColorRGBA Green = ColorRGBA(T{0}, T{1}, T{0}, T{1});
		static constexpr ColorRGBA Blue = ColorRGBA(T{0}, T{0}, T{1}, T{1});
		static constexpr ColorRGBA Black = ColorRGBA(T{0}, T{0}, T{0}, T{1});
		static constexpr ColorRGBA White = ColorRGBA(T{1}, T{1}, T{1}, T{1});
		static constexpr ColorRGBA Clear = ColorRGBA(T{0}, T{0}, T{0}, T{0});
		static constexpr ColorRGBA Gray = ColorRGBA(T{0.5}, T{0.5}, T{0.5}, T{1});
		static constexpr ColorRGBA Yellow = ColorRGBA(T{1}, T{1}, T{0}, T{1});
		static constexpr ColorRGBA Magenta = ColorRGBA(T{1}, T{0}, T{1}, T{1});
		static constexpr ColorRGBA Cyan = ColorRGBA(T{0}, T{1}, T{1}, T{1});
	};
}

namespace PonyEngine::Math
{
	template<std::floating_point T>
	constexpr ColorRGBA<T>::ColorRGBA(const T red, const T green, const T blue, const T alpha) noexcept :
		components{red, green, blue, alpha}
	{
	}

	template<std::floating_point T>
	constexpr ColorRGBA<T>::ColorRGBA(const T* const components) noexcept
	{
		Set(components);
	}

	template<std::floating_point T>
	constexpr ColorRGBA<T>::ColorRGBA(const ColorRGB<T>& rgb, const T alpha) noexcept :
		ColorRGBA(rgb.R(), rgb.G(), rgb.B(), alpha)
	{
	}

	template<std::floating_point T>
	constexpr ColorRGBA<T>::ColorRGBA(const Color8888& color) noexcept :
		ColorRGBA(color.R() * InverseColor8888Max, color.G() * InverseColor8888Max, color.B() * InverseColor8888Max, color.A() * InverseColor8888Max)
	{
	}

	template<std::floating_point T>
	constexpr ColorRGBA<T>::ColorRGBA(const Vector4<T>& vector) noexcept :
		ColorRGBA(vector.Data())
	{
	}

	template<std::floating_point T>
	constexpr T& ColorRGBA<T>::R() noexcept
	{
		return components[0];
	}

	template<std::floating_point T>
	constexpr const T& ColorRGBA<T>::R() const noexcept
	{
		return components[0];
	}

	template<std::floating_point T>
	constexpr T& ColorRGBA<T>::G() noexcept
	{
		return components[1];
	}

	template<std::floating_point T>
	constexpr const T& ColorRGBA<T>::G() const noexcept
	{
		return components[1];
	}

	template<std::floating_point T>
	constexpr T& ColorRGBA<T>::B() noexcept
	{
		return components[2];
	}

	template<std::floating_point T>
	constexpr const T& ColorRGBA<T>::B() const noexcept
	{
		return components[2];
	}

	template<std::floating_point T>
	constexpr T& ColorRGBA<T>::A() noexcept
	{
		return components[3];
	}

	template<std::floating_point T>
	constexpr const T& ColorRGBA<T>::A() const noexcept
	{
		return components[3];
	}

	template<std::floating_point T>
	constexpr T* ColorRGBA<T>::Data() noexcept
	{
		return components.data();
	}

	template<std::floating_point T>
	constexpr const T* ColorRGBA<T>::Data() const noexcept
	{
		return components.data();
	}

	template<std::floating_point T>
	constexpr T ColorRGBA<T>::Grayscale() const noexcept
	{
		return static_cast<ColorRGB<T>>(*this).Grayscale();
	}

	template<std::floating_point T>
	constexpr T& ColorRGBA<T>::Min() noexcept
	{
		return *std::ranges::min_element(components);
	}

	template<std::floating_point T>
	constexpr const T& ColorRGBA<T>::Min() const noexcept
	{
		return *std::ranges::min_element(components);
	}

	template<std::floating_point T>
	constexpr T& ColorRGBA<T>::Max() noexcept
	{
		return *std::ranges::max_element(components);
	}

	template<std::floating_point T>
	constexpr const T& ColorRGBA<T>::Max() const noexcept
	{
		return *std::ranges::max_element(components);
	}

	template<std::floating_point T>
	constexpr bool ColorRGBA<T>::IsBlack() const noexcept
	{
		return *this == Predefined::Black;
	}

	template<std::floating_point T>
	constexpr bool ColorRGBA<T>::IsAlmostBlack(const T tolerance) const noexcept
	{
		return AreAlmostEqual(*this, Predefined::Black, tolerance);
	}

	template<std::floating_point T>
	constexpr bool ColorRGBA<T>::IsWhite() const noexcept
	{
		return *this == Predefined::White;
	}

	template<std::floating_point T>
	constexpr bool ColorRGBA<T>::IsAlmostWhite(const T tolerance) const noexcept
	{
		return AreAlmostEqual(*this, Predefined::White, tolerance);
	}

	template<std::floating_point T>
	constexpr bool ColorRGBA<T>::IsTransparent() const noexcept
	{
		return A() == T{0};
	}

	template<std::floating_point T>
	constexpr bool ColorRGBA<T>::IsAlmostTransparent(const T tolerance) const noexcept
	{
		return AreAlmostEqual(A(), T{0}, tolerance);
	}

	template<std::floating_point T>
	bool ColorRGBA<T>::IsFinite() const noexcept
	{
		return std::isfinite(R()) && std::isfinite(G()) && std::isfinite(B()) && std::isfinite(A());
	}

	template<std::floating_point T>
	constexpr void ColorRGBA<T>::Set(const T red, const T green, const T blue, const T alpha) noexcept
	{
		R() = red;
		G() = green;
		B() = blue;
		A() = alpha;
	}

	template<std::floating_point T>
	constexpr void ColorRGBA<T>::Set(const T* const componentsToSet) noexcept
	{
		std::copy(componentsToSet, componentsToSet + ComponentCount, Data());
	}

	template<std::floating_point T>
	constexpr std::array<T, 4> ColorRGBA<T>::ToArray() const noexcept
	{
		return components;
	}

	template<std::floating_point T>
	constexpr void ColorRGBA<T>::ToArray(T (&array)[ComponentCount]) const noexcept
	{
		std::ranges::copy(components, array);
	}

	template<std::floating_point T>
	std::string ColorRGBA<T>::ToString() const
	{
		return std::format("(R: {}, G: {}, B: {}, A: {})", R(), G(), B(), A());
	}

	template<std::floating_point T>
	constexpr T Distance(const ColorRGBA<T>& left, const ColorRGBA<T>& right) noexcept
	{
		return std::sqrt(DistanceSquared(left, right));
	}

	template<std::floating_point T>
	constexpr T DistanceSquared(const ColorRGBA<T>& left, const ColorRGBA<T>& right) noexcept
	{
		ColorRGBA<T> difference = left - right;
		difference *= difference;

		return difference.R() + difference.G() + difference.B() + difference.A();
	}

	template<std::floating_point T>
	constexpr ColorRGBA<T> Lerp(const ColorRGBA<T>& from, const ColorRGBA<T>& to, const T time) noexcept
	{
		return from + (to - from) * time;
	}

	template<std::floating_point T>
	constexpr bool AreAlmostEqual(const ColorRGBA<T>& left, const ColorRGBA<T>& right, const T tolerance) noexcept
	{
		return DistanceSquared(left, right) < tolerance * tolerance;
	}

	template<std::floating_point T>
	template<Arithmetic U>
	constexpr ColorRGBA<T>::operator ColorRGBA<U>() const noexcept
	{
		ColorRGBA<U> cast;
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			cast[i] = static_cast<U>((*this)[i]);
		}

		return cast;
	}

	template<std::floating_point T>
	constexpr ColorRGBA<T>::operator ColorRGB<T>() const noexcept
	{
		return ColorRGB<T>(Data());
	}

	template<std::floating_point T>
	constexpr ColorRGBA<T>::operator Color8888() const noexcept
	{
		return Color8888(R() * Color8888::MaxValue, G() * Color8888::MaxValue, B() * Color8888::MaxValue, A() * Color8888::MaxValue);
	}

	template<std::floating_point T>
	constexpr ColorRGBA<T>::operator Vector4<T>() const noexcept
	{
		return Vector4<T>(Data());
	}

	template<std::floating_point T>
	constexpr T& ColorRGBA<T>::operator [](const std::size_t index) noexcept
	{
		return components[index];
	}

	template<std::floating_point T>
	constexpr const T& ColorRGBA<T>::operator [](const std::size_t index) const noexcept
	{
		return components[index];
	}

	template<std::floating_point T>
	constexpr ColorRGBA<T>& ColorRGBA<T>::operator +=(const ColorRGBA& other) noexcept
	{
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			(*this)[i] += other[i];
		}

		return *this;
	}

	template<std::floating_point T>
	constexpr ColorRGBA<T>& ColorRGBA<T>::operator -=(const ColorRGBA& other) noexcept
	{
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			(*this)[i] -= other[i];
		}

		return *this;
	}

	template<std::floating_point T>
	constexpr ColorRGBA<T>& ColorRGBA<T>::operator *=(const ColorRGBA& other) noexcept
	{
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			(*this)[i] *= other[i];
		}

		return *this;
	}

	template<std::floating_point T>
	constexpr ColorRGBA<T>& ColorRGBA<T>::operator *=(const T multiplier) noexcept
	{
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			(*this)[i] *= multiplier;
		}

		return *this;
	}

	template<std::floating_point T>
	constexpr ColorRGBA<T>& ColorRGBA<T>::operator /=(const ColorRGBA& other) noexcept
	{
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			(*this)[i] /= other[i];
		}

		return *this;
	}

	template<std::floating_point T>
	constexpr ColorRGBA<T>& ColorRGBA<T>::operator /=(const T divisor) noexcept
	{
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			(*this)[i] /= divisor;
		}

		return *this;
	}

	template<std::floating_point T>
	constexpr bool ColorRGBA<T>::operator ==(const ColorRGBA& other) const noexcept
	{
		return components == other.components;
	}

	template<std::floating_point T>
	constexpr ColorRGBA<T> operator +(const ColorRGBA<T>& left, const ColorRGBA<T>& right) noexcept
	{
		ColorRGBA<T> sum;
		for (std::size_t i = 0; i < ColorRGBA<T>::ComponentCount; ++i)
		{
			sum[i] = left[i] + right[i];
		}

		return sum;
	}

	template<std::floating_point T>
	constexpr ColorRGBA<T> operator -(const ColorRGBA<T>& left, const ColorRGBA<T>& right) noexcept
	{
		ColorRGBA<T> difference;
		for (std::size_t i = 0; i < ColorRGBA<T>::ComponentCount; ++i)
		{
			difference[i] = left[i] - right[i];
		}

		return difference;
	}

	template<std::floating_point T>
	constexpr ColorRGBA<T> operator *(const ColorRGBA<T>& left, const ColorRGBA<T>& right) noexcept
	{
		ColorRGBA<T> product;
		for (std::size_t i = 0; i < ColorRGBA<T>::ComponentCount; ++i)
		{
			product[i] = left[i] * right[i];
		}

		return product;
	}

	template<std::floating_point T>
	constexpr ColorRGBA<T> operator *(const ColorRGBA<T>& color, const T multiplier) noexcept
	{
		ColorRGBA<T> product;
		for (std::size_t i = 0; i < ColorRGBA<T>::ComponentCount; ++i)
		{
			product[i] = color[i] * multiplier;
		}

		return product;
	}

	template<std::floating_point T>
	constexpr ColorRGBA<T> operator *(const T multiplier, const ColorRGBA<T>& color) noexcept
	{
		return color * multiplier;
	}

	template<std::floating_point T>
	constexpr ColorRGBA<T> operator /(const ColorRGBA<T>& left, const ColorRGBA<T>& right) noexcept
	{
		ColorRGBA<T> quotient;
		for (std::size_t i = 0; i < ColorRGBA<T>::ComponentCount; ++i)
		{
			quotient[i] = left[i] / right[i];
		}

		return quotient;
	}

	template<std::floating_point T>
	constexpr ColorRGBA<T> operator /(const ColorRGBA<T>& color, const T divisor) noexcept
	{
		ColorRGBA<T> quotient;
		for (std::size_t i = 0; i < ColorRGBA<T>::ComponentCount; ++i)
		{
			quotient[i] = color[i] / divisor;
		}

		return quotient;
	}

	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const ColorRGBA<T>& color)
	{
		return stream << color.ToString();
	}
}