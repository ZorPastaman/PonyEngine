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
	/// @brief Computes the FNV-1a 32-bit hash of the @p data.
	/// @param data Data.
	/// @return Hash.
	[[nodiscard("Pure function")]]
	constexpr std::uint32_t FNV1a32(std::span<const std::byte> data) noexcept;
	/// @brief Computes the FNV-1a 32-bit hash of the @p data.
	/// @param data Data.
	/// @return Hash.
	[[nodiscard("Pure function")]]
	std::uint32_t FNV1a32(std::string_view data) noexcept;

	/// @brief Computes the FNV-1a 64-bit hash of the @p data.
	/// @param data Data.
	/// @return Hash.
	[[nodiscard("Pure function")]]
	constexpr std::uint64_t FNV1a64(std::span<const std::byte> data) noexcept;
	/// @brief Computes the FNV-1a 64-bit hash of the @p data.
	/// @param data Data.
	/// @return Hash.
	[[nodiscard("Pure function")]]
	std::uint64_t FNV1a64(std::string_view data) noexcept;
}

namespace PonyEngine::Hash
{
	/// @brief Computes the FNV-1a hash of the @p data.
	/// @tparam T Hash type.
	/// @tparam Prime Prime number.
	/// @tparam Offset Offset basis.
	/// @param data Data.
	/// @return Hash.
	template<std::unsigned_integral T, T Prime, T Offset> [[nodiscard("Pure function")]]
	constexpr T FNV1a(std::span<const std::byte> data) noexcept;

	template<std::unsigned_integral T, T Prime, T Offset>
	constexpr T FNV1a(const std::span<const std::byte> data) noexcept
	{
		T hash = Offset;
		for (const std::byte byte : data)
		{
			hash ^= static_cast<T>(byte);
			hash *= Prime;
		}

		return hash;
	}

	constexpr std::uint32_t FNV1a32(const std::span<const std::byte> data) noexcept
	{
		return FNV1a<std::uint32_t, 16777619, 2166136261>(data);
	}

	std::uint32_t FNV1a32(const std::string_view data) noexcept
	{
		return FNV1a32(std::as_bytes(std::span(data)));
	}

	constexpr std::uint64_t FNV1a64(const std::span<const std::byte> data) noexcept
	{
		return FNV1a<std::uint64_t, 1099511628211, 14695981039346656037>(data);
	}

	std::uint64_t FNV1a64(const std::string_view data) noexcept
	{
		return FNV1a64(std::as_bytes(std::span(data)));
	}
}
