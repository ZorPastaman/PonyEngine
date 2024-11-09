/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyMath.Utility:Resolution;

import <concepts>;
import <format>;
import <ostream>;
import <span>;
import <string>;

import PonyMath.Core;

export namespace PonyMath::Utility
{
	/// @brief Resolution.
	/// @tparam T Value type.
	template<std::unsigned_integral T>
	class Resolution final
	{
	public:
		using ValueType = T; ///< Value type.

		/// @brief Creates a resolution 0x0.
		[[nodiscard("Pure constructor")]]
		constexpr Resolution() noexcept = default;
		/// @brief Creates a resolution @p width x @p height.
		/// @param width Width.
		/// @param height Height.
		[[nodiscard("Pure constructor")]]
		constexpr Resolution(T width, T height) noexcept;
		/// @brief Creates a resolution vector.X() x vector.Y().
		/// @param vector Vector.
		[[nodiscard("Pure constructor")]]
		explicit constexpr Resolution(const Core::Vector2<T>& vector) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Resolution(const Resolution& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Resolution(Resolution&& other) noexcept = default;

		constexpr ~Resolution() noexcept = default;

		/// @brief Gets the width.
		/// @return Width.
		[[nodiscard("Pure function")]]
		constexpr T& Width() noexcept;
		/// @brief Gets the width.
		/// @return Width.
		[[nodiscard("Pure function")]]
		constexpr const T& Width() const noexcept;
		/// @brief Gets the height.
		/// @return Height.
		[[nodiscard("Pure function")]]
		constexpr T& Height() noexcept;
		/// @brief Gets the height.
		/// @return Height.
		[[nodiscard("Pure function")]]
		constexpr const T& Height() const noexcept;
		/// @brief Gets the resolution span.
		/// @return Resolution span. The order is width, height.
		[[nodiscard("Pure function")]]
		constexpr std::span<T, 2> Span() noexcept;
		/// @brief Gets the resolution span.
		/// @return Resolution span. The order is width, height.
		[[nodiscard("Pure function")]]
		constexpr std::span<const T, 2> Span() const noexcept;
		/// @brief Gets the resolution vector.
		/// @return Resolution vector. Width -> x, Height -> y.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T>& Vector() noexcept;
		/// @brief Gets the resolution vector.
		/// @return Resolution vector. Width -> x, Height -> y.
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector2<T>& Vector() const noexcept;

		/// @brief Computes an aspect ratio (width / height).
		/// @tparam U Aspect ratio type.
		/// @return Aspect ratio.
		template<std::floating_point U> [[nodiscard("Pure function")]]
		constexpr U Aspect() const noexcept;

		/// @brief Creates a string representing a state of the resolution.
		/// @return String representing a state of the resolution.
		[[nodiscard("Pure function")]]
		std::string ToString() const;

		/// @brief Converts to the other resolution type.
		/// @tparam U Target type.
		template<std::unsigned_integral U> [[nodiscard("Pure operator")]]
		explicit constexpr operator Resolution<U>() const noexcept;

		/// @brief Converts to a vector. Width -> X, height -> Y.
		[[nodiscard("Pure operator")]]
		explicit constexpr operator PonyMath::Core::Vector2<T>() const noexcept;

		constexpr Resolution& operator =(const Resolution& other) noexcept = default;
		constexpr Resolution& operator =(Resolution&& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Resolution& other) const noexcept = default;

	private:
		Core::Vector2<T> resolution; ///< Resolution. X - width, Y - height.
	};

	/// @brief Puts @p resolution.ToString() into the @p stream.
	/// @tparam T Value type.
	/// @param stream Stream.
	/// @param resolution Resolution.
	/// @return @p stream.
	template<std::unsigned_integral T>
	std::ostream& operator <<(std::ostream& stream, const Resolution<T>& resolution);

}

namespace PonyMath::Utility
{
	template<std::unsigned_integral T>
	constexpr Resolution<T>::Resolution(const T width, const T height) noexcept :
		resolution(width, height)
	{
	}

	template<std::unsigned_integral T>
	constexpr Resolution<T>::Resolution(const Core::Vector2<T>& vector) noexcept :
		Resolution(vector.X(), vector.Y())
	{
	}

	template<std::unsigned_integral T>
	constexpr T& Resolution<T>::Width() noexcept
	{
		return resolution.X();
	}

	template<std::unsigned_integral T>
	constexpr const T& Resolution<T>::Width() const noexcept
	{
		return resolution.X();
	}

	template<std::unsigned_integral T>
	constexpr T& Resolution<T>::Height() noexcept
	{
		return resolution.Y();
	}

	template<std::unsigned_integral T>
	constexpr const T& Resolution<T>::Height() const noexcept
	{
		return resolution.Y();
	}

	template<std::unsigned_integral T>
	constexpr std::span<T, 2> Resolution<T>::Span() noexcept
	{
		return resolution.Span();
	}

	template<std::unsigned_integral T>
	constexpr std::span<const T, 2> Resolution<T>::Span() const noexcept
	{
		return resolution.Span();
	}

	template<std::unsigned_integral T>
	constexpr Core::Vector2<T>& Resolution<T>::Vector() noexcept
	{
		return resolution;
	}

	template<std::unsigned_integral T>
	constexpr const Core::Vector2<T>& Resolution<T>::Vector() const noexcept
	{
		return resolution;
	}

	template<std::unsigned_integral T>
	template<std::floating_point U>
	constexpr U Resolution<T>::Aspect() const noexcept
	{
		return static_cast<U>(Width()) / static_cast<U>(Height());
	}

	template<std::unsigned_integral T>
	std::string Resolution<T>::ToString() const
	{
		return std::format("{}x{}", Width(), Height());
	}

	template<std::unsigned_integral T>
	template<std::unsigned_integral U>
	constexpr Resolution<T>::operator Resolution<U>() const noexcept
	{
		return Resolution<U>(static_cast<U>(Width()), static_cast<U>(Height()));
	}

	template<std::unsigned_integral T>
	constexpr Resolution<T>::operator PonyMath::Core::Vector2<T>() const noexcept
	{
		return resolution;
	}

	template<std::unsigned_integral T>
	std::ostream& operator <<(std::ostream& stream, const Resolution<T>& resolution)
	{
		return stream << resolution.ToString();
	}
}
