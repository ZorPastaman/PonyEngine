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
	/// @tparam Data Data type.
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
	/// @tparam Data Data type.
	/// @param data Data.
	/// @return Hash.
	template<FnvData Data> [[nodiscard("Pure function")]]
	constexpr std::uint64_t FNV1a64(std::span<const Data> data) noexcept;
	/// @brief Computes the FNV-1a 64-bit hash of the @p data.
	/// @param data Data.
	/// @return Hash.
	[[nodiscard("Pure function")]]
	constexpr std::uint64_t FNV1a64(std::string_view data) noexcept;

	/// @brief FNV-1a 32-bit hash helper.
	/// @details It lets easily combine hashes of independent spans as if they're one span.
	class FNV1a32Hash final
	{
	public:
		[[nodiscard("Pure constructor")]]
		constexpr FNV1a32Hash() noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr FNV1a32Hash(const FNV1a32Hash& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr FNV1a32Hash(FNV1a32Hash&& other) noexcept = default;

		constexpr ~FNV1a32Hash() noexcept = default;

		/// @brief Gets the current hash value.
		/// @return Hash value.
		[[nodiscard("Pure function")]]
		constexpr std::uint32_t Hash() const noexcept;
		/// @brief Updates the hash value with the data.
		/// @tparam Data Data type.
		/// @param data Data.
		/// @return New hash value.
		template<FnvData Data>
		constexpr std::uint32_t Hash(std::span<const Data> data) noexcept;
		/// @brief Updates the hash value with the data.
		/// @param data Data,
		/// @return New hash value.
		constexpr std::uint32_t Hash(std::string_view data) noexcept;

		FNV1a32Hash& operator =(const FNV1a32Hash& other) noexcept = default;
		FNV1a32Hash& operator =(FNV1a32Hash&& other) noexcept = default;

	private:
		std::uint32_t hash; ///< Hash value.
	};

	/// @brief FNV-1a 64-bit hash helper.
	/// @details It lets easily combine hashes of independent spans as if they're one span.
	class FNV1a64Hash final
	{
	public:
		[[nodiscard("Pure constructor")]]
		constexpr FNV1a64Hash() noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr FNV1a64Hash(const FNV1a64Hash& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr FNV1a64Hash(FNV1a64Hash&& other) noexcept = default;

		constexpr ~FNV1a64Hash() noexcept = default;

		/// @brief Gets the current hash value.
		/// @return Hash value.
		[[nodiscard("Pure function")]]
		constexpr std::uint64_t Hash() const noexcept;
		/// @brief Updates the hash value with the data.
		/// @tparam Data Data type.
		/// @param data Data.
		/// @return New hash value.
		template<FnvData Data>
		constexpr std::uint64_t Hash(std::span<const Data> data) noexcept;
		/// @brief Updates the hash value with the data.
		/// @param data Data,
		/// @return New hash value.
		constexpr std::uint64_t Hash(std::string_view data) noexcept;

		FNV1a64Hash& operator =(const FNV1a64Hash& other) noexcept = default;
		FNV1a64Hash& operator =(FNV1a64Hash&& other) noexcept = default;

	private:
		std::uint64_t hash; ///< Hash value.
	};
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
	template<std::unsigned_integral T, FnvData Data> [[nodiscard("Pure function")]]
	constexpr T FNV1a(std::span<const Data> data, T offset) noexcept;

	/// @brief Gets an FNV1a offset by the result type.
	/// @tparam T Hash result type.
	/// @return FNV1a offset.
	template<std::unsigned_integral T>
	constexpr T GetFNV1aOffset() noexcept
	{
		static_assert(sizeof(T) == 4 || sizeof(T) == 8, "Wrong size of return type. Must be either 32 or 64 bit.");
		return sizeof(T) == 4 ? 2166136261 : 14695981039346656037;
	}
	/// @brief Gets an FNV1a prime by the result type.
	/// @tparam T Hash result type.
	/// @return FNV1a prime.
	template<std::unsigned_integral T>
	constexpr T GetFNV1aPrime() noexcept
	{
		static_assert(sizeof(T) == 4 || sizeof(T) == 8, "Wrong size of return type. Must be either 32 or 64 bit.");
		return sizeof(T) == 4 ? 16777619 : 1099511628211;
	}
	template<std::unsigned_integral T>
	constexpr T FNV1aOffset = GetFNV1aOffset<T>();
	template<std::unsigned_integral T>
	constexpr T FNV1aPrime = GetFNV1aPrime<T>();

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

	constexpr FNV1a32Hash::FNV1a32Hash() noexcept :
		hash{FNV1aOffset<std::uint32_t>}
	{
	}

	constexpr std::uint32_t FNV1a32Hash::Hash() const noexcept
	{
		return hash;
	}

	template<FnvData Data>
	constexpr std::uint32_t FNV1a32Hash::Hash(const std::span<const Data> data) noexcept
	{
		return hash = FNV1a(data, hash);
	}

	constexpr std::uint32_t FNV1a32Hash::Hash(const std::string_view data) noexcept
	{
		return hash = FNV1a(std::span(data), hash);
	}

	constexpr FNV1a64Hash::FNV1a64Hash() noexcept :
		hash{FNV1aOffset<std::uint64_t>}
	{
	}

	constexpr std::uint64_t FNV1a64Hash::Hash() const noexcept
	{
		return hash;
	}

	template<FnvData Data>
	constexpr std::uint64_t FNV1a64Hash::Hash(std::span<const Data> data) noexcept
	{
		return hash = FNV1a(data, hash);
	}

	constexpr std::uint64_t FNV1a64Hash::Hash(const std::string_view data) noexcept
	{
		return hash = FNV1a(std::span(data), hash);
	}

	template<std::unsigned_integral T, FnvData Data>
	constexpr T FNV1a(const std::span<const Data> data) noexcept
	{
		return FNV1a(data, FNV1aOffset<T>);
	}

	template<std::unsigned_integral T, FnvData Data>
	constexpr T FNV1a(const std::span<const Data> data, const T offset) noexcept
	{
		T hash = offset;
		for (const Data value : data)
		{
			hash ^= static_cast<T>(static_cast<std::byte>(value));
			hash *= FNV1aPrime<T>;
		}

		return hash;
	}
}
