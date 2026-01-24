/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#pragma once

#ifndef NDEBUG
#define PONY_ENUM_FORMATTER_ERROR_CHECK \
	if (context.begin() == context.end()) [[unlikely]] \
	{ \
		throw std::format_error("Unexpected context end.");\
	} \
	if (*context.begin() != '}') [[unlikely]] \
	{ \
		throw std::format_error("Unexpected format specifier."); \
	}
#else
#define PONY_ENUM_FORMATTER_ERROR_CHECK
#endif

/// @brief Creates a formatter for an enum value.
/// @note This define must be used in a global namespace.
/// @param Value Value enum type.
/// @param ValueNames Value names. They're synced by index.
#define PONY_ENUM_VALUE_FORMATTER(Value, ValueNames) \
	template<> \
	struct std::formatter<Value, char> \
	{ \
		static constexpr auto parse(std::format_parse_context& context) \
		{ \
			PONY_ENUM_FORMATTER_ERROR_CHECK \
			return context.begin(); \
		} \
		static auto format(const Value value, std::format_context& context) \
		{ \
			const std::size_t index = static_cast<std::size_t>(value); \
			return std::ranges::copy(index < ValueNames.size() ? ValueNames[index] : "Unknown"sv, context.out()).out; \
		} \
	}; \

/// @brief Creates a formatter for an enum mask.
/// @note This define must be used in a global namespace.
/// @note The enum must have All value defined.
/// @param Mask Mask enum type.
/// @param MaskNames Mask names. They're synced by index.
#define PONY_ENUM_MASK_FORMATTER(Mask, MaskNames) \
	template<> \
	struct std::formatter<Mask, char> \
	{ \
		static constexpr auto parse(std::format_parse_context& context) \
		{ \
			PONY_ENUM_FORMATTER_ERROR_CHECK \
			return context.begin(); \
		} \
		static auto format(const Mask mask, std::format_context& context) \
		{ \
			if (std::to_underlying(mask) == std::underlying_type_t<Mask>{0}) \
			{ \
				return std::ranges::copy("None"sv, context.out()).out; \
			} \
			if (mask == Mask::All) \
			{ \
				return std::ranges::copy("All"sv, context.out()).out; \
			} \
			if (std::to_underlying(mask) > std::to_underlying(Mask::All)) \
			{ \
				return std::ranges::copy("Unknown"sv, context.out()).out; \
			} \
			\
			bool hasText = false; \
			auto it = context.out(); \
			for (std::underlying_type_t<Mask> i = 0; i < static_cast<std::underlying_type_t<Mask>>(std::countr_one(std::to_underlying(Mask::All))); ++i) \
			{ \
				if (((std::underlying_type_t<Mask>{1} << i) & std::to_underlying(mask)) != std::underlying_type_t<Mask>{0}) \
				{ \
					if (hasText) \
					{ \
						it = std::ranges::copy(" | "sv, it).out; \
					} \
					it = std::ranges::copy(MaskNames[i], it).out; \
					hasText = true; \
				} \
			} \
			return it; \
		} \
	}; \

/// @brief Creates mask enum operators.
/// @note Mask must include All value.
/// @param Mask Mask enum type.
#define PONY_ENUM_MASK_OPERATORS(Mask) \
	[[nodiscard("Pure function")]] \
	constexpr Mask operator &(const Mask left, const Mask right) noexcept \
	{ \
		return static_cast<Mask>(std::to_underlying(left) & std::to_underlying(right)); \
	} \
	 \
	[[nodiscard("Pure function")]] \
	constexpr Mask operator |(const Mask left, const Mask right) noexcept \
	{ \
		return static_cast<Mask>(std::to_underlying(left) | std::to_underlying(right)); \
	} \
	[[nodiscard("Pure function")]] \
	constexpr Mask operator ^(const Mask left, const Mask right) noexcept \
	{ \
		return static_cast<Mask>(std::to_underlying(left) ^ std::to_underlying(right)); \
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

/// @brief Creates mask enum check functions.
/// @param Mask Mask enum type.
#define PONY_ENUM_MASK_CHECKS(Mask) \
	[[nodiscard("Pure function")]] \
	constexpr bool All(const Mask value, const Mask mask) noexcept \
	{ \
		return (value & mask) == value; \
	} \
	[[nodiscard("Pure function")]] \
	constexpr bool Any(const Mask value, const Mask mask) noexcept \
	{ \
		return std::to_underlying(value & mask); \
	} \
	[[nodiscard("Pure function")]] \
	constexpr bool None(const Mask value, const Mask mask) noexcept \
	{ \
		return !Any(value, mask); \
	} \

/// @brief Creates functions for the value enum and mask enum pair.
/// @param Value Value enum type.
/// @param Mask Mask enum type.
#define PONY_ENUM_VALUE_MASK(Value, Mask) \
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
			mask |= std::to_underlying(ToMask(value)); \
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
		return std::to_underlying(ToMask(value)) & std::to_underlying(mask); \
	} \
	 \
	/* @brief Converts the mask to a value. */ \
	/* @param mask Mask. Must have only one true bit; otherwise the behaviour is undefined. */ \
	/* @return Value. */ \
	[[nodiscard("Pure function")]] \
	constexpr Value ToValue(const Mask mask) noexcept \
	{ \
		return static_cast<Value>(std::countr_zero(std::to_underlying(mask))); \
	} \
	 \
	/* @brief Converts the mask to values. */ \
	/* @param mask Mask. */ \
	/* @param values Values output. It must have enough size to contain all the possible values. */ \
	/* @return Value output count. */ \
	constexpr std::size_t ToValues(const Mask mask, const std::span<Value> values) noexcept \
	{ \
		std::size_t valueCount = 0; \
		for (std::underlying_type_t<Mask> i = 0; i < std::countr_one(std::to_underlying(Mask::All)) && valueCount < values.size(); ++i) \
		{ \
			if (IsInMask(static_cast<Value>(i), mask)) \
			{ \
				values[valueCount] = static_cast<Value>(i); \
				++valueCount; \
			} \
		} \
		return valueCount; \
	} \

/// @brief Creates all the mask enum features except a formatter.
/// @note All the restrictions of the features are applied to this.
/// @param Mask Mask enum type.
#define PONY_ENUM_MASK_FEATURES(Mask) PONY_ENUM_MASK_OPERATORS(Mask) PONY_ENUM_MASK_CHECKS(Mask)
/// @brief Creates all the value enum and mask enum features except formatters.
/// @note All the restrictions of the features are applied to this.
/// @param Value Value enum type.
/// @param Mask Mask enum type.
#define PONY_ENUM_VALUE_MASK_FEATURES(Value, Mask) PONY_ENUM_MASK_FEATURES(Mask) PONY_ENUM_VALUE_MASK(Value, Mask)
