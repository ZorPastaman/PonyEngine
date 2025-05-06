/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyBase.Utility:Mask;

import <concepts>;
import <cstdint>;
import <span>;
import <type_traits>;

export namespace PonyBase::Utility
{
	/// @brief The concept is satisfied if @p T is an enum type with an unsigned underlying type.
	template<typename T>
	concept UnsignedEnum = std::is_enum_v<T> && std::is_unsigned_v<std::underlying_type_t<T>>;

	/// @brief Checks if the enum value is in the enum mask.
	/// @tparam T Enum type.
	/// @tparam U Mask type.
	/// @param value Value.
	/// @param mask Mask.
	/// @return @a True if it's in the mask; @a false otherwise.
	template<UnsignedEnum T, std::unsigned_integral U> [[nodiscard("Pure function")]]// TODO: Add tests
	constexpr bool IsInMask(T value, U mask) noexcept;

	/// @brief Converts an enum value to an enum mask.
	/// @tparam T Enum type.
	/// @tparam U Mask type.
	/// @param value Value.
	/// @return Mask.
	template<UnsignedEnum T, std::unsigned_integral U = std::uint32_t> [[nodiscard("Pure function")]]
	constexpr U ToMask(T value) noexcept;
	/// @brief Converts enum values to an enum mask.
	/// @tparam T Enum type.
	/// @tparam U Mask type.
	/// @param values Values.
	/// @return Mask.
	template<UnsignedEnum T, std::unsigned_integral U = std::uint32_t> [[nodiscard("Pure function")]]
	constexpr U ToMask(std::span<const T> values) noexcept;
}

namespace PonyBase::Utility
{
	template <UnsignedEnum T, std::unsigned_integral U>
	constexpr bool IsInMask(const T value, const U mask) noexcept
	{
		return ToMask<T, U>(value) & mask;
	}

	template <UnsignedEnum T, std::unsigned_integral U>
	constexpr U ToMask(const T value) noexcept
	{
		return U{1} << static_cast<U>(value);
	}

	template <UnsignedEnum T, std::unsigned_integral U>
	constexpr U ToMask(const std::span<const T> values) noexcept
	{
		U mask = U{0};
		for (const T value : values)
		{
			mask |= ToMask<T, U>(value);
		}

		return mask;
	}
}
