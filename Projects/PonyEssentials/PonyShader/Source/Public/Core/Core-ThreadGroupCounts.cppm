/***************************************************
* MIT License                                     *
*                                                 *
* Copyright (c) 2023-present Vladimir Popov       *
*                                                 *
* Email: zor1994@gmail.com                        *
* Repo: https://github.com/ZorPastaman/PonyEngine *
***************************************************/

export module PonyShader.Core:ThreadGroupCounts;

import <array>;
import <cstdint>;
import <span>;
import <stdexcept>;

export namespace PonyShader::Core
{
	class ThreadGroupCounts final
	{
	public:
		static constexpr std::uint32_t ThreadGroupCountMax = 65536u;
		static constexpr std::uint32_t ThreadGroupCountProductMax = 4194304u;

		[[nodiscard("Pure constructor")]]
		ThreadGroupCounts() noexcept;
		[[nodiscard("Pure constructor")]]
		ThreadGroupCounts(std::uint32_t x, std::uint32_t y, std::uint32_t z);
		[[nodiscard("Pure constructor")]]
		explicit ThreadGroupCounts(std::span<const std::uint32_t, 3> span);
		[[nodiscard("Pure constructor")]]
		ThreadGroupCounts(const ThreadGroupCounts& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		ThreadGroupCounts(ThreadGroupCounts&& other) noexcept = default;

		~ThreadGroupCounts() noexcept = default;

		[[nodiscard("Pure function")]]
		std::uint32_t ThreadGroupCountX() const noexcept;
		void ThreadGroupCountX(std::uint32_t count);
		[[nodiscard("Pure function")]]
		std::uint32_t ThreadGroupCountY() const noexcept;
		void ThreadGroupCountY(std::uint32_t count);
		[[nodiscard("Pure function")]]
		std::uint32_t ThreadGroupCountZ() const noexcept;
		void ThreadGroupCountZ(std::uint32_t count);
		[[nodiscard("Pure function")]]
		std::span<const std::uint32_t, 3> Span() const noexcept;

		void Set(std::uint32_t x, std::uint32_t y, std::uint32_t z);
		void Set(std::span<const std::uint32_t, 3> span);

		ThreadGroupCounts& operator =(const ThreadGroupCounts& other) noexcept = default;
		ThreadGroupCounts& operator =(ThreadGroupCounts&& other) noexcept = default;

	private:
		std::array<std::uint32_t, 3> counts;
		std::uint32_t padding = 0u;
	};
}

namespace PonyShader::Core
{
	ThreadGroupCounts::ThreadGroupCounts() noexcept :
		counts{ 1u, 1u, 1u }
	{
	}

	ThreadGroupCounts::ThreadGroupCounts(const std::uint32_t x, const std::uint32_t y, const std::uint32_t z)
	{
		Set(x, y, z);
	}

	ThreadGroupCounts::ThreadGroupCounts(const std::span<const std::uint32_t, 3> span)
	{
		Set(span);
	}

	std::uint32_t ThreadGroupCounts::ThreadGroupCountX() const noexcept
	{
		return counts[0];
	}

	void ThreadGroupCounts::ThreadGroupCountX(const std::uint32_t count)
	{
		if (count >= ThreadGroupCountMax) [[unlikely]]
		{
			throw std::invalid_argument("Thread group count must be less than 65536.");
		}
		if (count * counts[1] * counts[2] > ThreadGroupCountProductMax) [[unlikely]]
		{
			throw std::invalid_argument("Thread group count product exceeds 4194304.");
		}

		counts[0] = count;
	}

	std::uint32_t ThreadGroupCounts::ThreadGroupCountY() const noexcept
	{
		return counts[1];
	}

	void ThreadGroupCounts::ThreadGroupCountY(const std::uint32_t count)
	{
		if (count >= ThreadGroupCountMax) [[unlikely]]
		{
			throw std::invalid_argument("Thread group count must be less than 65536.");
		}
		if (counts[0] * count * counts[2] > ThreadGroupCountProductMax) [[unlikely]]
		{
			throw std::invalid_argument("Thread group count product exceeds 4194304.");
		}

		counts[1] = count;
	}

	std::uint32_t ThreadGroupCounts::ThreadGroupCountZ() const noexcept
	{
		return counts[2];
	}

	void ThreadGroupCounts::ThreadGroupCountZ(const std::uint32_t count)
	{
		if (count >= ThreadGroupCountMax) [[unlikely]]
		{
			throw std::invalid_argument("Thread group count must be less than 65536.");
		}
		if (counts[0] * counts[1] * count > ThreadGroupCountProductMax) [[unlikely]]
		{
			throw std::invalid_argument("Thread group count product exceeds 4194304.");
		}

		counts[2] = count;
	}

	std::span<const std::uint32_t, 3> ThreadGroupCounts::Span() const noexcept
	{
		return counts;
	}

	void ThreadGroupCounts::Set(const std::uint32_t x, const std::uint32_t y, const std::uint32_t z)
	{
		if (x >= ThreadGroupCountMax || y >= ThreadGroupCountMax || z >= ThreadGroupCountMax) [[unlikely]]
		{
			throw std::invalid_argument("Thread group count must be less than 65536.");
		}
		if (x * y * z > ThreadGroupCountProductMax) [[unlikely]]
		{
			throw std::invalid_argument("Thread group count product exceeds 4194304.");
		}

		counts[0] = x;
		counts[1] = y;
		counts[2] = z;
	}

	void ThreadGroupCounts::Set(const std::span<const std::uint32_t, 3> span)
	{
		Set(span[0], span[1], span[2]);
	}
}
