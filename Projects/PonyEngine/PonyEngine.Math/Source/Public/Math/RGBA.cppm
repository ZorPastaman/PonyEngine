/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math:RGBA;

import <algorithm>;
import <array>;
import <concepts>;
import <cstddef>;
import <format>;
import <ostream>;
import <string>;

import :RGB;
import :RGBAInt;
import :Common;
import :Vector4;

export namespace PonyEngine::Math
{
	template<std::floating_point T>
	class RGBA final
	{
	public:
		using ValueType = T; ///< Component type.

		static constexpr std::size_t ComponentCount = 4; ///< Component count. For any RGBA, it's always 4.

		struct Predefined; ///< Predefined colors.

		[[nodiscard("Pure constructor")]]
		constexpr RGBA() noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr RGBA(T red, T green, T blue, T alpha) noexcept;
		[[nodiscard("Pure constructor")]]
		explicit constexpr RGBA(const T* components) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr RGBA(const RGB<T>& rgb, T alpha) noexcept;
		template<std::unsigned_integral U> [[nodiscard("Pure constructor")]]
		explicit constexpr RGBA(const RGBAInt<U>& color) noexcept;
		[[nodiscard("Pure constructor")]]
		explicit constexpr RGBA(const Vector4<T>& vector) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr RGBA(const RGBA& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr RGBA(RGBA&& other) noexcept = default;

		constexpr ~RGBA() noexcept = default;

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

		template<std::floating_point U> [[nodiscard("Pure operator")]]
		explicit constexpr operator RGBA<U>() const noexcept;
		[[nodiscard("Pure operator")]]
		explicit constexpr operator RGB<T>() const noexcept;
		template<std::unsigned_integral U> [[nodiscard("Pure operator")]]
		explicit constexpr operator RGBAInt<U>() const noexcept;

		[[nodiscard("Pure operator")]]
		explicit constexpr operator Vector4<T>() const noexcept;

		[[nodiscard("Pure operator")]]
		constexpr T& operator [](std::size_t index) noexcept;
		[[nodiscard("Pure operator")]]
		constexpr const T& operator [](std::size_t index) const noexcept;

		constexpr RGBA& operator =(const RGBA& other) noexcept = default;
		constexpr RGBA& operator =(RGBA&& other) noexcept = default;
		constexpr RGBA& operator +=(const RGBA& other) noexcept;
		constexpr RGBA& operator -=(const RGBA& other) noexcept;
		constexpr RGBA& operator *=(const RGBA& other) noexcept;
		constexpr RGBA& operator *=(T multiplier) noexcept;
		constexpr RGBA& operator /=(const RGBA& other) noexcept;
		constexpr RGBA& operator /=(T divisor) noexcept;

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const RGBA& other) const noexcept;

	private:
		std::array<T, ComponentCount> components; ///< Component array in order red, green, blue, alpha.
	};

	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr T Distance(const RGBA<T>& left, const RGBA<T>& right) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr T DistanceSquared(const RGBA<T>& left, const RGBA<T>& right) noexcept;

	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr RGBA<T> Lerp(const RGBA<T>& from, const RGBA<T>& to, T time) noexcept;

	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const RGBA<T>& left, const RGBA<T>& right, T tolerance = T{0.00001}) noexcept;

	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr RGBA<T> operator +(const RGBA<T>& left, const RGBA<T>& right) noexcept;

	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr RGBA<T> operator -(const RGBA<T>& left, const RGBA<T>& right) noexcept;

	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr RGBA<T> operator *(const RGBA<T>& left, const RGBA<T>& right) noexcept;
	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr RGBA<T> operator *(const RGBA<T>& color, T multiplier) noexcept;
	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr RGBA<T> operator *(T multiplier, const RGBA<T>& color) noexcept;

	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr RGBA<T> operator /(const RGBA<T>& left, const RGBA<T>& right) noexcept;
	template<std::floating_point T> [[nodiscard("Pure operator")]]
	constexpr RGBA<T> operator /(const RGBA<T>& color, T divisor) noexcept;

	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const RGBA<T>& color);

	template<std::floating_point T>
	struct RGBA<T>::Predefined final
	{
		Predefined() = delete;

		static constexpr RGBA Red = RGBA(T{1}, T{0}, T{0}, T{1});
		static constexpr RGBA Green = RGBA(T{0}, T{1}, T{0}, T{1});
		static constexpr RGBA Blue = RGBA(T{0}, T{0}, T{1}, T{1});
		static constexpr RGBA Black = RGBA(T{0}, T{0}, T{0}, T{1});
		static constexpr RGBA White = RGBA(T{1}, T{1}, T{1}, T{1});
		static constexpr RGBA Clear = RGBA(T{0}, T{0}, T{0}, T{0});
		static constexpr RGBA Gray = RGBA(T{0.5}, T{0.5}, T{0.5}, T{1});
		static constexpr RGBA Yellow = RGBA(T{1}, T{1}, T{0}, T{1});
		static constexpr RGBA Magenta = RGBA(T{1}, T{0}, T{1}, T{1});
		static constexpr RGBA Cyan = RGBA(T{0}, T{1}, T{1}, T{1});
	};
}

namespace PonyEngine::Math
{
	template<std::floating_point T>
	constexpr RGBA<T>::RGBA(const T red, const T green, const T blue, const T alpha) noexcept :
		components{red, green, blue, alpha}
	{
	}

	template<std::floating_point T>
	constexpr RGBA<T>::RGBA(const T* const components) noexcept
	{
		Set(components);
	}

	template<std::floating_point T>
	constexpr RGBA<T>::RGBA(const RGB<T>& rgb, const T alpha) noexcept :
		RGBA(rgb.R(), rgb.G(), rgb.B(), alpha)
	{
	}

	template<std::floating_point T>
	template<std::unsigned_integral U>
	constexpr RGBA<T>::RGBA(const RGBAInt<U>& color) noexcept
	{
		constexpr T inverseMaxValue = T{1} / RGBAInt<U>::MaxValue;
		Set(color.R() * inverseMaxValue, color.G() * inverseMaxValue, color.B() * inverseMaxValue, color.A() * inverseMaxValue);
	}

	template<std::floating_point T>
	constexpr RGBA<T>::RGBA(const Vector4<T>& vector) noexcept :
		RGBA(vector.Data())
	{
	}

	template<std::floating_point T>
	constexpr T& RGBA<T>::R() noexcept
	{
		return components[0];
	}

	template<std::floating_point T>
	constexpr const T& RGBA<T>::R() const noexcept
	{
		return components[0];
	}

	template<std::floating_point T>
	constexpr T& RGBA<T>::G() noexcept
	{
		return components[1];
	}

	template<std::floating_point T>
	constexpr const T& RGBA<T>::G() const noexcept
	{
		return components[1];
	}

	template<std::floating_point T>
	constexpr T& RGBA<T>::B() noexcept
	{
		return components[2];
	}

	template<std::floating_point T>
	constexpr const T& RGBA<T>::B() const noexcept
	{
		return components[2];
	}

	template<std::floating_point T>
	constexpr T& RGBA<T>::A() noexcept
	{
		return components[3];
	}

	template<std::floating_point T>
	constexpr const T& RGBA<T>::A() const noexcept
	{
		return components[3];
	}

	template<std::floating_point T>
	constexpr T* RGBA<T>::Data() noexcept
	{
		return components.data();
	}

	template<std::floating_point T>
	constexpr const T* RGBA<T>::Data() const noexcept
	{
		return components.data();
	}

	template<std::floating_point T>
	constexpr T RGBA<T>::Grayscale() const noexcept
	{
		return static_cast<RGB<T>>(*this).Grayscale();
	}

	template<std::floating_point T>
	constexpr T& RGBA<T>::Min() noexcept
	{
		return *std::ranges::min_element(components);
	}

	template<std::floating_point T>
	constexpr const T& RGBA<T>::Min() const noexcept
	{
		return *std::ranges::min_element(components);
	}

	template<std::floating_point T>
	constexpr T& RGBA<T>::Max() noexcept
	{
		return *std::ranges::max_element(components);
	}

	template<std::floating_point T>
	constexpr const T& RGBA<T>::Max() const noexcept
	{
		return *std::ranges::max_element(components);
	}

	template<std::floating_point T>
	constexpr bool RGBA<T>::IsBlack() const noexcept
	{
		return *this == Predefined::Black;
	}

	template<std::floating_point T>
	constexpr bool RGBA<T>::IsAlmostBlack(const T tolerance) const noexcept
	{
		return AreAlmostEqual(*this, Predefined::Black, tolerance);
	}

	template<std::floating_point T>
	constexpr bool RGBA<T>::IsWhite() const noexcept
	{
		return *this == Predefined::White;
	}

	template<std::floating_point T>
	constexpr bool RGBA<T>::IsAlmostWhite(const T tolerance) const noexcept
	{
		return AreAlmostEqual(*this, Predefined::White, tolerance);
	}

	template<std::floating_point T>
	constexpr bool RGBA<T>::IsTransparent() const noexcept
	{
		return A() == T{0};
	}

	template<std::floating_point T>
	constexpr bool RGBA<T>::IsAlmostTransparent(const T tolerance) const noexcept
	{
		return AreAlmostEqual(A(), T{0}, tolerance);
	}

	template<std::floating_point T>
	bool RGBA<T>::IsFinite() const noexcept
	{
		return std::isfinite(R()) && std::isfinite(G()) && std::isfinite(B()) && std::isfinite(A());
	}

	template<std::floating_point T>
	constexpr void RGBA<T>::Set(const T red, const T green, const T blue, const T alpha) noexcept
	{
		R() = red;
		G() = green;
		B() = blue;
		A() = alpha;
	}

	template<std::floating_point T>
	constexpr void RGBA<T>::Set(const T* const componentsToSet) noexcept
	{
		std::copy(componentsToSet, componentsToSet + ComponentCount, Data());
	}

	template<std::floating_point T>
	constexpr std::array<T, 4> RGBA<T>::ToArray() const noexcept
	{
		return components;
	}

	template<std::floating_point T>
	constexpr void RGBA<T>::ToArray(T (&array)[ComponentCount]) const noexcept
	{
		std::ranges::copy(components, array);
	}

	template<std::floating_point T>
	std::string RGBA<T>::ToString() const
	{
		return std::format("(R: {}, G: {}, B: {}, A: {})", R(), G(), B(), A());
	}

	template<std::floating_point T>
	constexpr T Distance(const RGBA<T>& left, const RGBA<T>& right) noexcept
	{
		return std::sqrt(DistanceSquared(left, right));
	}

	template<std::floating_point T>
	constexpr T DistanceSquared(const RGBA<T>& left, const RGBA<T>& right) noexcept
	{
		RGBA<T> difference = left - right;
		difference *= difference;

		return difference.R() + difference.G() + difference.B() + difference.A();
	}

	template<std::floating_point T>
	constexpr RGBA<T> Lerp(const RGBA<T>& from, const RGBA<T>& to, const T time) noexcept
	{
		return from + (to - from) * time;
	}

	template<std::floating_point T>
	constexpr bool AreAlmostEqual(const RGBA<T>& left, const RGBA<T>& right, const T tolerance) noexcept
	{
		return DistanceSquared(left, right) < tolerance * tolerance;
	}

	template<std::floating_point T>
	template<std::floating_point U>
	constexpr RGBA<T>::operator RGBA<U>() const noexcept
	{
		RGBA<U> cast;
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			cast[i] = static_cast<U>((*this)[i]);
		}

		return cast;
	}

	template<std::floating_point T>
	constexpr RGBA<T>::operator RGB<T>() const noexcept
	{
		return RGB<T>(Data());
	}

	template<std::floating_point T>
	template<std::unsigned_integral U>
	constexpr RGBA<T>::operator RGBAInt<U>() const noexcept
	{
		return RGBAInt<U>(R() * RGBAInt<U>::MaxValue, G() * RGBAInt<U>::MaxValue, B() * RGBAInt<U>::MaxValue, A() * RGBAInt<U>::MaxValue);
	}

	template<std::floating_point T>
	constexpr RGBA<T>::operator Vector4<T>() const noexcept
	{
		return Vector4<T>(Data());
	}

	template<std::floating_point T>
	constexpr T& RGBA<T>::operator [](const std::size_t index) noexcept
	{
		return components[index];
	}

	template<std::floating_point T>
	constexpr const T& RGBA<T>::operator [](const std::size_t index) const noexcept
	{
		return components[index];
	}

	template<std::floating_point T>
	constexpr RGBA<T>& RGBA<T>::operator +=(const RGBA& other) noexcept
	{
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			(*this)[i] += other[i];
		}

		return *this;
	}

	template<std::floating_point T>
	constexpr RGBA<T>& RGBA<T>::operator -=(const RGBA& other) noexcept
	{
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			(*this)[i] -= other[i];
		}

		return *this;
	}

	template<std::floating_point T>
	constexpr RGBA<T>& RGBA<T>::operator *=(const RGBA& other) noexcept
	{
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			(*this)[i] *= other[i];
		}

		return *this;
	}

	template<std::floating_point T>
	constexpr RGBA<T>& RGBA<T>::operator *=(const T multiplier) noexcept
	{
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			(*this)[i] *= multiplier;
		}

		return *this;
	}

	template<std::floating_point T>
	constexpr RGBA<T>& RGBA<T>::operator /=(const RGBA& other) noexcept
	{
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			(*this)[i] /= other[i];
		}

		return *this;
	}

	template<std::floating_point T>
	constexpr RGBA<T>& RGBA<T>::operator /=(const T divisor) noexcept
	{
		for (std::size_t i = 0; i < ComponentCount; ++i)
		{
			(*this)[i] /= divisor;
		}

		return *this;
	}

	template<std::floating_point T>
	constexpr bool RGBA<T>::operator ==(const RGBA& other) const noexcept
	{
		return components == other.components;
	}

	template<std::floating_point T>
	constexpr RGBA<T> operator +(const RGBA<T>& left, const RGBA<T>& right) noexcept
	{
		RGBA<T> sum;
		for (std::size_t i = 0; i < RGBA<T>::ComponentCount; ++i)
		{
			sum[i] = left[i] + right[i];
		}

		return sum;
	}

	template<std::floating_point T>
	constexpr RGBA<T> operator -(const RGBA<T>& left, const RGBA<T>& right) noexcept
	{
		RGBA<T> difference;
		for (std::size_t i = 0; i < RGBA<T>::ComponentCount; ++i)
		{
			difference[i] = left[i] - right[i];
		}

		return difference;
	}

	template<std::floating_point T>
	constexpr RGBA<T> operator *(const RGBA<T>& left, const RGBA<T>& right) noexcept
	{
		RGBA<T> product;
		for (std::size_t i = 0; i < RGBA<T>::ComponentCount; ++i)
		{
			product[i] = left[i] * right[i];
		}

		return product;
	}

	template<std::floating_point T>
	constexpr RGBA<T> operator *(const RGBA<T>& color, const T multiplier) noexcept
	{
		RGBA<T> product;
		for (std::size_t i = 0; i < RGBA<T>::ComponentCount; ++i)
		{
			product[i] = color[i] * multiplier;
		}

		return product;
	}

	template<std::floating_point T>
	constexpr RGBA<T> operator *(const T multiplier, const RGBA<T>& color) noexcept
	{
		return color * multiplier;
	}

	template<std::floating_point T>
	constexpr RGBA<T> operator /(const RGBA<T>& left, const RGBA<T>& right) noexcept
	{
		RGBA<T> quotient;
		for (std::size_t i = 0; i < RGBA<T>::ComponentCount; ++i)
		{
			quotient[i] = left[i] / right[i];
		}

		return quotient;
	}

	template<std::floating_point T>
	constexpr RGBA<T> operator /(const RGBA<T>& color, const T divisor) noexcept
	{
		RGBA<T> quotient;
		for (std::size_t i = 0; i < RGBA<T>::ComponentCount; ++i)
		{
			quotient[i] = color[i] / divisor;
		}

		return quotient;
	}

	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const RGBA<T>& color)
	{
		return stream << color.ToString();
	}
}
