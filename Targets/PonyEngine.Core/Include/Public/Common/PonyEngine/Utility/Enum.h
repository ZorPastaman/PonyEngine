/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: cybercode.smith@pm.me                    *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#pragma once

/// @brief Creates a function to convert an enum value to a predefined string value.
/// @note Import <algorithm>, <cstddef>, <ostream> and <string_view>.
/// @param Value Value enum type.
/// @param Value param name.
/// @param ValueNames Array of value enum names.
#define ENUM_VALUE_TO_STRING(Value, ValueNames) \
	[[nodiscard("Pure function")]] \
	constexpr std::string_view ToString(const Value value) noexcept \
	{ \
		return ValueNames[std::min(static_cast<std::size_t>(value), ValueNames.size() - 1)]; \
	} \
	std::ostream& operator <<(std::ostream& stream, const Value value) \
	{ \
		return stream << ToString(value); \
	} \

/// @brief Creates a function that makes a string representing the enum mask.
/// @note Enum must have Enum::All value defined.
/// @note Import <bit>, <ostream>, <string> and <type_traits>.
/// @param Mask Mask enum type.
/// @param MaskNames Array of mask enum names.
#define ENUM_MASK_TO_STRING(Mask, MaskNames) \
	[[nodiscard("Pure function")]] \
	constexpr std::string ToString(const Mask mask) \
	{ \
		if (static_cast<std::underlying_type_t<Mask>>(mask) == std::underlying_type_t<Mask>{0}) \
		{ \
			return "None"; \
		} \
		if (static_cast<std::underlying_type_t<Mask>>(mask) == static_cast<std::underlying_type_t<Mask>>(Mask::All)) \
		{ \
			return "All"; \
		} \
		std::string answer = ""; \
		for (std::underlying_type_t<Mask> i = 0; i < std::countr_one(static_cast<std::underlying_type_t<Mask>>(Mask::All)); ++i) \
		{ \
			if (((std::underlying_type_t<Mask>{1} << i) & static_cast<std::underlying_type_t<Mask>>(mask)) != std::underlying_type_t<Mask>{0}) \
			{ \
				if (!answer.empty()) \
				{ \
					answer += " | "; \
				} \
				answer += MaskNames[i]; \
			} \
		} \
		return answer; \
	} \
	std::ostream& operator <<(std::ostream& stream, const Mask mask) \
	{ \
		return stream << ToString(mask); \
	} \

/// @brief Creates mask enum operators.
/// @note Mask must include All value. Import <type_traits>.
/// @param Mask Mask enum type.
#define ENUM_MASK_OPERATORS(Mask) \
	[[nodiscard("Pure function")]] \
	constexpr Mask operator &(const Mask left, const Mask right) noexcept \
	{ \
		return static_cast<Mask>(static_cast<std::underlying_type_t<Mask>>(left) & static_cast<std::underlying_type_t<Mask>>(right)); \
	} \
	 \
	[[nodiscard("Pure function")]] \
	constexpr Mask operator |(const Mask left, const Mask right) noexcept \
	{ \
		return static_cast<Mask>(static_cast<std::underlying_type_t<Mask>>(left) | static_cast<std::underlying_type_t<Mask>>(right)); \
	} \
	[[nodiscard("Pure function")]] \
	constexpr Mask operator ^(const Mask left, const Mask right) noexcept \
	{ \
		return static_cast<Mask>(static_cast<std::underlying_type_t<Mask>>(left) ^ static_cast<std::underlying_type_t<Mask>>(right)); \
	} \
	[[nodiscard("Pure function")]] \
	constexpr Mask operator ~(const Mask mask) noexcept \
	{ \
		return mask ^ Mask::All; \
	} \
	constexpr Mask& operator &=(Mask& left, const Mask right) noexcept \
	{ \
		return left = left & right; \
	} \
	 \
	constexpr Mask& operator |=(Mask& left, const Mask right) noexcept \
	{ \
		return left = left | right; \
	} \
	constexpr Mask& operator ^=(Mask& left, const Mask right) noexcept \
	{ \
		return left = left ^ right; \
	} \

/// @brief Creates functions for the value enum and mask enum pair.
/// @note Import <bit>, <cstddef>, <span> and <type_traits>.
/// @param Value Value enum type.
/// @param Mask Mask enum type.
#define ENUM_VALUE_MASK(Value, Mask) \
	/* @brief Converts the value to a mask. */ \
	/* @param value Value. */ \
	/* @return Mask. */ \
	[[nodiscard("Pure function")]] \
	constexpr Mask ToMask(const Value value) noexcept \
	{ \
		return static_cast<Mask>(1u << static_cast<std::underlying_type_t<Mask>>(value)); \
	} \
	 \
	/* @brief Converts the values to a mask. */ \
	/* @param value Values. */ \
	/* @return Mask. */ \
	[[nodiscard("Pure function")]] \
	constexpr Mask ToMask(const std::span<const Value> values) noexcept \
	{ \
		std::underlying_type_t<Mask> mask = std::underlying_type_t<Mask>{0u}; \
		for (const Value value : values) \
		{ \
			mask |= static_cast<std::underlying_type_t<Mask>>(ToMask(value)); \
		} \
		 \
		return static_cast<Mask>(mask); \
	} \
	 \
	/* @brief Checks if the mask contains the value. */ \
	/* @param value Value. */ \
	/* @param mask Mask. */ \
	/* @return @a True if the mask contains the value; @a false otherwise. */ \
	[[nodiscard("Pure function")]] \
	constexpr bool IsInMask(const Value value, const Mask mask) noexcept \
	{ \
		return static_cast<std::underlying_type_t<Mask>>(ToMask(value)) & static_cast<std::underlying_type_t<Mask>>(mask); \
	} \
	 \
	/* @brief Converts the mask to a value. */ \
	/* @param mask Mask. Must have only one true bit; otherwise the behaviour is undefined. */ \
	/* @return Value. */ \
	[[nodiscard("Pure function")]] \
	constexpr Value ToValue(const Mask mask) noexcept \
	{ \
		return static_cast<Value>(std::countr_zero(static_cast<std::underlying_type_t<Mask>>(mask))); \
	} \
	 \
	/* @brief Converts the mask to values. */ \
	/* @param mask Mask. */ \
	/* @param values Values output. It must have enough size to contain all the possible values. */ \
	/* @return Value output count. */ \
	constexpr std::size_t ToValues(const Mask mask, const std::span<Value> values) noexcept \
	{ \
		std::size_t valueCount = 0; \
		for (std::underlying_type_t<Mask> i = 0; i < std::countr_one(static_cast<std::underlying_type_t<Mask>>(Mask::All)) && valueCount < values.size(); ++i) \
		{ \
			if (IsInMask(static_cast<Value>(i), mask)) \
			{ \
				values[valueCount] = static_cast<Value>(i); \
				++valueCount; \
			} \
		} \
		return valueCount; \
	} \

/// @brief Creates all the value enum features.
/// @note All the restrictions of the features are applied to this.
/// @param Value Value enum type.
#define ENUM_VALUE_FEATURES(Value, ValueNames) ENUM_VALUE_TO_STRING(Value, ValueNames)
/// @brief Creates all the mask enum features.
/// @note All the restrictions of the features are applied to this.
/// @param Mask Mask enum type.
#define ENUM_MASK_FEATURES(Mask, MaskNames) ENUM_MASK_TO_STRING(Mask, MaskNames) ENUM_MASK_OPERATORS(Mask)
/// @brief Creates all the value enum and mask enum features.
/// @note All the restrictions of the features are applied to this.
/// @param Value Value enum type.
/// @param Mask Mask enum type.
#define ENUM_VALUE_MASK_FEATURES(Value, ValueNames, Mask, MaskNames) ENUM_VALUE_FEATURES(Value, ValueNames) ENUM_MASK_FEATURES(Mask, MaskNames) \
	ENUM_VALUE_MASK(Value, Mask)
