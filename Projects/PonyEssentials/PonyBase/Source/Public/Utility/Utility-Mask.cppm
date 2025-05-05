/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyBase.Utility:Mask;

import <type_traits>;

export namespace PonyBase::Utility
{
	/// @brief The concept is satisfied if @p T is an enum type with an unsigned underlying type.
	template<typename T>
	concept UnsignedEnum = std::is_enum_v<T> && std::is_unsigned_v<std::underlying_type_t<T>>;

	/// @brief Checks if the enum value is in the enum mask.
	/// @tparam T Enum type.
	/// @param value Value.
	/// @param mask Mask.
	/// @return @a True if it's in the mask; @a false otherwise.
	template<UnsignedEnum T> [[nodiscard("Pure function")]] // TODO: Add tests
	constexpr bool IsInMask(T value, std::underlying_type_t<T> mask) noexcept;
}

namespace PonyBase::Utility
{
	template <UnsignedEnum T>
	constexpr bool IsInMask(const T value, const std::underlying_type_t<T> mask) noexcept
	{
		return std::underlying_type_t<T>{1} << static_cast<std::underlying_type_t<T>>(value) & mask;
	}
}
