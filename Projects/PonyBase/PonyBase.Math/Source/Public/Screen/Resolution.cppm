/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyBase.Screen:Resolution;

import <concepts>;
import <format>;
import <string>;

import PonyBase.Math;

export namespace PonyBase::Screen
{
	template<std::unsigned_integral T>
	class Resolution final
	{
	public:
		[[nodiscard("Pure constructor")]]
		constexpr Resolution() noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Resolution(T width, T height) noexcept;
		[[nodiscard("Pure constructor")]]
		explicit constexpr Resolution(const Math::Vector2<T>& vector) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Resolution(const Resolution& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Resolution(Resolution&& other) noexcept = default;

		constexpr ~Resolution() noexcept = default;

		[[nodiscard("Pure function")]]
		constexpr T& Width() noexcept;
		[[nodiscard("Pure function")]]
		constexpr const T& Width() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr T& Height() noexcept;
		[[nodiscard("Pure function")]]
		constexpr const T& Height() const noexcept;

		template<std::floating_point U> [[nodiscard("Pure function")]]
		constexpr U Aspect() const noexcept;

		[[nodiscard("Pure function")]]
		std::string ToString() const;

		template<std::unsigned_integral U> [[nodiscard("Pure operator")]]
		explicit constexpr operator Resolution<U>() const noexcept;

		[[nodiscard("Pure operator")]]
		explicit constexpr operator Math::Vector2<T>() const noexcept;

		constexpr Resolution& operator =(const Resolution& other) noexcept = default;
		constexpr Resolution& operator =(Resolution&& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Resolution&) const noexcept = default;

	private:
		Math::Vector2<T> resolution;
	};
}

namespace PonyBase::Screen
{
	template<std::unsigned_integral T>
	constexpr Resolution<T>::Resolution(const T width, const T height) noexcept :
		resolution(width, height)
	{
	}

	template<std::unsigned_integral T>
	constexpr Resolution<T>::Resolution(const Math::Vector2<T>& vector) noexcept :
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
	constexpr Resolution<T>::operator Math::Vector2<T>() const noexcept
	{
		return resolution;
	}
}
