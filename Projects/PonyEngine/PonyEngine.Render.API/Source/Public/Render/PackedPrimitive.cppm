/***************************************************
* MIT License                                     *
*                                                 *
* Copyright (c) 2023-present Vladimir Popov       *
*                                                 *
* Email: zor1994@gmail.com                        *
* Repo: https://github.com/ZorPastaman/PonyEngine *
***************************************************/

export module PonyEngine.Render:PackedPrimitive;

import <array>;
import <cstddef>;
import <cstdint>;
import <span>;

export namespace PonyEngine::Render
{
	class PackedPrimitive final
	{
	public:
		[[nodiscard("Pure constructor")]]
		PackedPrimitive() noexcept = default;
		[[nodiscard("Pure constructor")]]
		explicit PackedPrimitive(std::uint8_t i0, std::uint8_t i1 = 0u, std::uint8_t i2 = 0u, std::uint8_t i3 = 0u) noexcept;
		[[nodiscard("Pure constructor")]]
		explicit PackedPrimitive(std::uint32_t value) noexcept;
		template<std::size_t N> [[nodiscard("Pure constructor")]]
		explicit PackedPrimitive(std::span<const std::uint8_t, N> indices) noexcept requires (N > 0 && N <= 4);
		[[nodiscard("Pure constructor")]]
		PackedPrimitive(const PackedPrimitive& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		PackedPrimitive(PackedPrimitive&& other) noexcept = default;

		~PackedPrimitive() noexcept = default;

		[[nodiscard("Pure function")]]
		std::uint8_t& I0() noexcept;
		[[nodiscard("Pure function")]]
		const std::uint8_t& I0() const noexcept;
		[[nodiscard("Pure function")]]
		std::uint8_t& I1() noexcept;
		[[nodiscard("Pure function")]]
		const std::uint8_t& I1() const noexcept;
		[[nodiscard("Pure function")]]
		std::uint8_t& I2() noexcept;
		[[nodiscard("Pure function")]]
		const std::uint8_t& I2() const noexcept;
		[[nodiscard("Pure function")]]
		std::uint8_t& I3() noexcept;
		[[nodiscard("Pure function")]]
		const std::uint8_t& I3() const noexcept;
		[[nodiscard("Pure function")]]
		std::uint32_t& Value() noexcept;
		[[nodiscard("Pure function")]]
		const std::uint32_t& Value() const noexcept;
		[[nodiscard("Pure function")]]
		std::uint8_t* Data() noexcept;
		[[nodiscard("Pure function")]]
		const std::uint8_t* Data() const noexcept;

		void Set(std::uint8_t i0, std::uint8_t i1 = 0u, std::uint8_t i2 = 0u, std::uint8_t i3 = 0u) noexcept;
		void Set(std::uint32_t value) noexcept;
		template<std::size_t N>
		void Set(std::span<const std::uint8_t, N> indicesToSet) noexcept requires (N > 0 && N <= 4);

		[[nodiscard("Pure operator")]]
		std::uint8_t& operator [](std::size_t index) noexcept;
		[[nodiscard("Pure operator")]]
		const std::uint8_t& operator [](std::size_t index) const noexcept;

		PackedPrimitive& operator =(const PackedPrimitive& other) noexcept = default;
		PackedPrimitive& operator =(PackedPrimitive&& other) noexcept = default;
		template<std::size_t N>
		PackedPrimitive& operator =(std::span<const std::uint8_t, N> otherIndices) noexcept requires (N > 0 && N <= 4);

		[[nodiscard("Pure operator")]]
		bool operator ==(const PackedPrimitive& other) const noexcept;

	private:
		std::array<std::uint8_t, 4> indices;
	};
}

namespace PonyEngine::Render
{
	PackedPrimitive::PackedPrimitive(const std::uint8_t i0, const std::uint8_t i1, const std::uint8_t i2, const std::uint8_t i3) noexcept :
		indices{ i0, i1, i2, i3 }
	{
	}

	PackedPrimitive::PackedPrimitive(const std::uint32_t value) noexcept
	{
		Set(value);
	}

	template<std::size_t N>
	PackedPrimitive::PackedPrimitive(const std::span<const std::uint8_t, N> indices) noexcept requires (N > 0 && N <= 4)
	{
		Set(indices);
	}

	std::uint8_t& PackedPrimitive::I0() noexcept
	{
		return indices[0];
	}

	const std::uint8_t& PackedPrimitive::I0() const noexcept
	{
		return indices[0];
	}

	std::uint8_t& PackedPrimitive::I1() noexcept
	{
		return indices[1];
	}

	const std::uint8_t& PackedPrimitive::I1() const noexcept
	{
		return indices[1];
	}

	std::uint8_t& PackedPrimitive::I2() noexcept
	{
		return indices[2];
	}

	const std::uint8_t& PackedPrimitive::I2() const noexcept
	{
		return indices[2];
	}

	std::uint8_t& PackedPrimitive::I3() noexcept
	{
		return indices[3];
	}

	const std::uint8_t& PackedPrimitive::I3() const noexcept
	{
		return indices[3];
	}

	std::uint32_t& PackedPrimitive::Value() noexcept
	{
		return *reinterpret_cast<std::uint32_t*>(indices.data());
	}

	const std::uint32_t& PackedPrimitive::Value() const noexcept
	{
		return *reinterpret_cast<const std::uint32_t*>(indices.data());
	}

	std::uint8_t* PackedPrimitive::Data() noexcept
	{
		return indices.data();
	}

	const std::uint8_t* PackedPrimitive::Data() const noexcept
	{
		return indices.data();
	}

	void PackedPrimitive::Set(const std::uint8_t i0, const std::uint8_t i1, const std::uint8_t i2, const std::uint8_t i3) noexcept
	{
		indices[0] = i0;
		indices[1] = i1;
		indices[2] = i2;
		indices[3] = i3;
	}

	void PackedPrimitive::Set(const std::uint32_t value) noexcept
	{
		*reinterpret_cast<uint32_t*>(indices.data()) = value;
	}

	template<std::size_t N>
	void PackedPrimitive::Set(const std::span<const std::uint8_t, N> indicesToSet) noexcept requires (N > 0 && N <= 4)
	{
		std::ranges::copy(indicesToSet, indices.begin());
	}

	std::uint8_t& PackedPrimitive::operator [](const std::size_t index) noexcept
	{
		return indices[index];
	}

	const std::uint8_t& PackedPrimitive::operator [](const std::size_t index) const noexcept
	{
		return indices[index];
	}

	template<std::size_t N>
	PackedPrimitive& PackedPrimitive::operator =(const std::span<const std::uint8_t, N> otherIndices) noexcept requires (N > 0 && N <= 4)
	{
		Set(otherIndices);

		return *this;
	}

	bool PackedPrimitive::operator ==(const PackedPrimitive& other) const noexcept
	{
		return indices == other.indices;
	}
}
