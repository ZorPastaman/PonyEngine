/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyShader.Core:ThreadGroupCounts;

import <algorithm>;
import <array>;
import <cstddef>;
import <cstdint>;
import <span>;
import <stdexcept>;

export namespace PonyShader::Core
{
	/// @brief Thread group counts wrapper. It corresponds to @p Pony_ThreadGroupCounts in PonyShader/Core/ThreadGroupCounts.hlsli on the HLSL side.
	class ThreadGroupCounts final
	{
	public:
		static constexpr std::size_t ThreadGroupCountCount = 3; ///< Thread group counts count.
		static constexpr std::uint32_t ThreadGroupCountMax = 65536u; ///< Every thread group count must be less than this number.
		static constexpr std::uint32_t ThreadGroupCountProductMax = 4194304u; ///< A product of thread group counts mustn't exceed this number.

		/// @brief Creates zero thread group counts.
		[[nodiscard("Pure constructor")]]
		constexpr ThreadGroupCounts() noexcept = default;
		/// @brief Creates thread group counts.
		/// @throw std::invalid_argument If any thread group count isn't less than @p ThreadGroupCountMax.
		/// @throw std::invalid_argument If the product of every thread group count is greater than @p ThreadGroupCountProductMax.
		/// @param x Thread group count X.
		/// @param y Thread group count Y.
		/// @param z Thread group count Z.
		[[nodiscard("Pure constructor")]]
		constexpr ThreadGroupCounts(std::uint32_t x, std::uint32_t y, std::uint32_t z);
		/// @brief Creates thread group counts.
		/// @param span Thread group counts. The order is x, y, z.
		[[nodiscard("Pure constructor")]]
		explicit constexpr ThreadGroupCounts(std::span<const std::uint32_t, 3> span);
		[[nodiscard("Pure constructor")]]
		constexpr ThreadGroupCounts(const ThreadGroupCounts& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr ThreadGroupCounts(ThreadGroupCounts&& other) noexcept = default;

		constexpr ~ThreadGroupCounts() noexcept = default;

		/// @brief Gets the thread group count X.
		/// @return Thread group count X.
		[[nodiscard("Pure function")]]
		constexpr std::uint32_t ThreadGroupCountX() const noexcept;
		/// @brief Sets the thread group count X.
		/// @throw std::invalid_argument If the @p count isn't less than @p ThreadGroupCountMax.
		/// @throw std::invalid_argument If the product of every thread group count is greater than @p ThreadGroupCountProductMax.
		/// @param count Thread group count X to set.
		constexpr void ThreadGroupCountX(std::uint32_t count);
		/// @brief Gets the thread group count Y.
		/// @return Thread group count Y.
		[[nodiscard("Pure function")]]
		constexpr std::uint32_t ThreadGroupCountY() const noexcept;
		/// @brief Sets the thread group count Y.
		/// @throw std::invalid_argument If the @p count isn't less than @p ThreadGroupCountMax.
		/// @throw std::invalid_argument If the product of every thread group count is greater than @p ThreadGroupCountProductMax.
		/// @param count Thread group count Y to set.
		constexpr void ThreadGroupCountY(std::uint32_t count);
		/// @brief Gets the thread group count Z.
		/// @return Thread group count Z.
		[[nodiscard("Pure function")]]
		constexpr std::uint32_t ThreadGroupCountZ() const noexcept;
		/// @brief Sets the thread group count Z.
		/// @throw std::invalid_argument If the @p count isn't less than @p ThreadGroupCountMax.
		/// @throw std::invalid_argument If the product of every thread group count is greater than @p ThreadGroupCountProductMax.
		/// @param count Thread group count Z to set.
		constexpr void ThreadGroupCountZ(std::uint32_t count);
		/// @brief Gets the thread group count by the @p index.
		/// @param index Thread group count index. 0 -> x, 1 -> y, 2 -> z.
		/// @return Thread group count.
		[[nodiscard("Pure function")]]
		constexpr std::uint32_t ThreadGroupCount(std::size_t index) const noexcept;
		/// @brief Sets the thread group count by the @p index.
		/// @throw std::invalid_argument If the @p count isn't less than @p ThreadGroupCountMax.
		/// @throw std::invalid_argument If the product of every thread group count is greater than @p ThreadGroupCountProductMax.
		/// @param index Thread group count index. 0 -> x, 1 -> y, 2 -> z.
		/// @param count Thread group count to set.
		constexpr void ThreadGroupCount(std::size_t index, std::uint32_t count);
		/// @brief Gets the thread group counts.
		/// @return Thread group counts.
		[[nodiscard("Pure function")]]
		constexpr std::span<const std::uint32_t, 3> Span() const noexcept;

		constexpr ThreadGroupCounts& operator =(const ThreadGroupCounts& other) noexcept = default;
		constexpr ThreadGroupCounts& operator =(ThreadGroupCounts&& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const ThreadGroupCounts& other) const noexcept;

	private:
		std::array<std::uint32_t, 3> counts; ///< Thread group counts.
	};
}

namespace PonyShader::Core
{
	constexpr ThreadGroupCounts::ThreadGroupCounts(const std::uint32_t x, const std::uint32_t y, const std::uint32_t z) :
		counts{ x, y, z }
	{
		if (x >= ThreadGroupCountMax || y >= ThreadGroupCountMax || z >= ThreadGroupCountMax) [[unlikely]]
		{
			throw std::invalid_argument("Thread group count must be less than 65536.");
		}
		if (x * y * z > ThreadGroupCountProductMax) [[unlikely]]
		{
			throw std::invalid_argument("Thread group count product exceeds 4194304.");
		}
	}

	constexpr ThreadGroupCounts::ThreadGroupCounts(const std::span<const std::uint32_t, 3> span)
	{
		std::ranges::copy(span, counts.data());

		if (counts[0] >= ThreadGroupCountMax || counts[1] >= ThreadGroupCountMax || counts[2] >= ThreadGroupCountMax) [[unlikely]]
		{
			throw std::invalid_argument("Thread group count must be less than 65536.");
		}
		if (counts[0] * counts[1] * counts[2] > ThreadGroupCountProductMax) [[unlikely]]
		{
			throw std::invalid_argument("Thread group count product exceeds 4194304.");
		}
	}

	constexpr std::uint32_t ThreadGroupCounts::ThreadGroupCountX() const noexcept
	{
		return ThreadGroupCount(0);
	}

	constexpr void ThreadGroupCounts::ThreadGroupCountX(const std::uint32_t count)
	{
		ThreadGroupCount(0, count);
	}

	constexpr std::uint32_t ThreadGroupCounts::ThreadGroupCountY() const noexcept
	{
		return ThreadGroupCount(1);
	}

	constexpr void ThreadGroupCounts::ThreadGroupCountY(const std::uint32_t count)
	{
		ThreadGroupCount(1, count);
	}

	constexpr std::uint32_t ThreadGroupCounts::ThreadGroupCountZ() const noexcept
	{
		return ThreadGroupCount(2);
	}

	constexpr void ThreadGroupCounts::ThreadGroupCountZ(const std::uint32_t count)
	{
		ThreadGroupCount(2, count);
	}

	constexpr std::uint32_t ThreadGroupCounts::ThreadGroupCount(const std::size_t index) const noexcept
	{
		return counts[index];
	}

	constexpr void ThreadGroupCounts::ThreadGroupCount(const std::size_t index, const std::uint32_t count)
	{
		if (count >= ThreadGroupCountMax) [[unlikely]]
		{
			throw std::invalid_argument("Thread group count must be less than 65536.");
		}

		std::array<std::uint32_t, 3> newCounts = counts;
		newCounts[index] = count;
		if (newCounts[0] * newCounts[1] * newCounts[2] > ThreadGroupCountProductMax) [[unlikely]]
		{
			throw std::invalid_argument("Thread group count product exceeds 4194304.");
		}

		counts = newCounts;
	}

	constexpr std::span<const std::uint32_t, 3> ThreadGroupCounts::Span() const noexcept
	{
		return counts;
	}

	constexpr bool ThreadGroupCounts::operator ==(const ThreadGroupCounts& other) const noexcept
	{
		return counts == other.counts;
	}
}
