/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

export module PonyTools.Memory:ByteWriter;

import PonyEngine.Utility;

import :Utility;

export namespace PonyTools::Memory
{
	class ByteWriter final
	{
	public:
		[[nodiscard("Pure constructor")]]
		ByteWriter(std::span<std::byte> data, bool isTargetBigEndian) noexcept;
		ByteWriter(const ByteWriter&) = delete;
		ByteWriter(ByteWriter&&) = delete;

		~ByteWriter() noexcept = default;

		template<PonyEngine::Utility::Arithmetic T>
		void Write(T value) noexcept;

		void Skip(std::size_t count) noexcept;

		ByteWriter& operator =(const ByteWriter&) = delete;
		ByteWriter& operator =(ByteWriter&&) = delete;

	private:
		std::byte* current;
		const std::byte* end;
		bool shouldSwap;
	};
}

namespace PonyTools::Memory
{
	ByteWriter::ByteWriter(const std::span<std::byte> data, const bool isTargetBigEndian) noexcept :
		current{data.data()},
		end{data.data() + data.size()},
		shouldSwap{isTargetBigEndian != IsHostBigEndian}
	{
	}

	template<PonyEngine::Utility::Arithmetic T>
	void ByteWriter::Write(const T value) noexcept
	{
		if constexpr (std::is_floating_point_v<T>)
		{
			static_assert(sizeof(T) == sizeof(std::uint32_t) || sizeof(T) == sizeof(std::uint64_t), "Unsupported type");
			using IntType = std::conditional_t<sizeof(T) == sizeof(std::uint32_t), std::uint32_t, std::uint64_t>;
			Write(std::bit_cast<IntType>(value));
		}
		else
		{
			assert(static_cast<std::size_t>(end - current) >= sizeof(T) && "Out of range.");

			const T data = shouldSwap ? std::byteswap(value) : value;
			std::memcpy(current, &data, sizeof(T));
			current += sizeof(T);
		}
	}

	void ByteWriter::Skip(const std::size_t count) noexcept
	{
		assert(static_cast<std::size_t>(end - current) <= count && "Out of range.");
		current += count;
	}
}
