/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Hash:FNV1a;

import std;

export namespace PonyEngine::Hash
{
	/// @brief Fnv data concept that is satisfied only with 1-byte arithmetic type.
	template<typename T>
	concept FnvData = sizeof(T) == 1 && (std::is_arithmetic_v<T> || std::is_enum_v<T>);

	/// @brief Computes the FNV-1a 32-bit hash of the @p data.
	/// @param data Data.
	/// @return Hash.
	template<FnvData Data> [[nodiscard("Pure function")]]
	constexpr std::uint32_t FNV1a32(std::span<const Data> data) noexcept;
	/// @brief Computes the FNV-1a 32-bit hash of the @p data.
	/// @param data Data.
	/// @return Hash.
	[[nodiscard("Pure function")]]
	constexpr std::uint32_t FNV1a32(std::string_view data) noexcept;

	/// @brief Computes the FNV-1a 64-bit hash of the @p data.
	/// @param data Data.
	/// @return Hash.
	template<FnvData Data> [[nodiscard("Pure function")]]
	constexpr std::uint64_t FNV1a64(std::span<const Data> data) noexcept;
	/// @brief Computes the FNV-1a 64-bit hash of the @p data.
	/// @param data Data.
	/// @return Hash.
	[[nodiscard("Pure function")]]
	constexpr std::uint64_t FNV1a64(std::string_view data) noexcept;
}

namespace PonyEngine::Hash
{
	/// @brief Computes the FNV-1a hash of the @p data.
	/// @tparam T Hash type.
	/// @tparam Data Data type.
	/// @param data Data.
	/// @return Hash.
	template<std::unsigned_integral T, FnvData Data> [[nodiscard("Pure function")]]
	constexpr T FNV1a(std::span<const Data> data) noexcept;

	template<FnvData Data>
	constexpr std::uint32_t FNV1a32(const std::span<const Data> data) noexcept
	{
		return FNV1a<std::uint32_t>(data);
	}

	constexpr std::uint32_t FNV1a32(const std::string_view data) noexcept
	{
		return FNV1a<std::uint32_t>(std::span(data));
	}

	template<FnvData Data>
	constexpr std::uint64_t FNV1a64(const std::span<const Data> data) noexcept
	{
		return FNV1a<std::uint64_t>(data);
	}

	constexpr std::uint64_t FNV1a64(const std::string_view data) noexcept
	{
		return FNV1a<std::uint64_t>(std::span(data));
	}

	template<std::unsigned_integral T, FnvData Data>
	constexpr T FNV1a(const std::span<const Data> data) noexcept
	{
		static_assert(sizeof(T) == 4 || sizeof(T) == 8, "Wrong size of return type. Must be either 32 or 64 bit.");
		constexpr T offset = sizeof(T) == 4 ? 2166136261 : 14695981039346656037;
		constexpr T prime = sizeof(T) == 4 ? 16777619 : 1099511628211;

		T hash = offset;
		for (const Data value : data)
		{
			hash ^= static_cast<T>(static_cast<std::byte>(value));
			hash *= prime;
		}

		return hash;
	}
}
