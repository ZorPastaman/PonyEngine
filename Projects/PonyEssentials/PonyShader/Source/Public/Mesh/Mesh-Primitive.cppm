/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyShader.Mesh:Primitive;

import <algorithm>;
import <array>;
import <cstddef>;
import <cstdint>;
import <span>;

export namespace PonyShader::Mesh
{
	/// @brief Primitive. It corresponds to @p Pony_Primitive in PonyShader/Mesh/Primitive.hlsli on the HLSL side.
	/// @details. It may store up to 4 point indices, up to 2 line indices (first two and last two indices), up to 1 triangle (first three indices) and up to 1 quad.
	class Primitive final
	{
	public:
		/// @brief Creates a zero primitive.
		[[nodiscard("Pure constructor")]]
		constexpr Primitive() noexcept = default;
		/// @brief Creates a primitive.
		/// @param i0 Index 0.
		/// @param i1 Index 1.
		/// @param i2 Index 2.
		/// @param i3 Index 3.
		[[nodiscard("Pure constructor")]]
		explicit constexpr Primitive(std::uint8_t i0, std::uint8_t i1 = 0u, std::uint8_t i2 = 0u, std::uint8_t i3 = 0u) noexcept;
		/// @brief Creates a primitive.
		/// @tparam N Index count.
		/// @param indices Indices.
		template<std::size_t N> [[nodiscard("Pure constructor")]]
		explicit constexpr Primitive(std::span<const std::uint8_t, N> indices) noexcept requires (N > 0 && N <= 4);
		[[nodiscard("Pure constructor")]]
		constexpr Primitive(const Primitive& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Primitive(Primitive&& other) noexcept = default;

		constexpr ~Primitive() noexcept = default;

		/// @brief Gets the index 0.
		/// @return Index 0.
		[[nodiscard("Pure function")]]
		constexpr std::uint8_t& I0() noexcept;
		/// @brief Gets the index 0.
		/// @return Index 0.
		[[nodiscard("Pure function")]]
		constexpr const std::uint8_t& I0() const noexcept;
		/// @brief Gets the index 1.
		/// @return Index 1.
		[[nodiscard("Pure function")]]
		constexpr std::uint8_t& I1() noexcept;
		/// @brief Gets the index 1.
		/// @return Index 1.
		[[nodiscard("Pure function")]]
		constexpr const std::uint8_t& I1() const noexcept;
		/// @brief Gets the index 2.
		/// @return Index 2.
		[[nodiscard("Pure function")]]
		constexpr std::uint8_t& I2() noexcept;
		/// @brief Gets the index 2.
		/// @return Index 2.
		[[nodiscard("Pure function")]]
		constexpr const std::uint8_t& I2() const noexcept;
		/// @brief Gets the index 3.
		/// @return Index 3.
		[[nodiscard("Pure function")]]
		constexpr std::uint8_t& I3() noexcept;
		/// @brief Gets the index 3.
		/// @return Index 3.
		[[nodiscard("Pure function")]]
		constexpr const std::uint8_t& I3() const noexcept;
		/// @brief Gets the index span.
		/// @return Index span.
		[[nodiscard("Pure function")]]
		constexpr std::span<std::uint8_t, 4> Span() noexcept;
		/// @brief Gets the index span.
		/// @return Index span.
		[[nodiscard("Pure function")]]
		constexpr std::span<const std::uint8_t, 4> Span() const noexcept;

		/// @brief Gets a primitive index by the @p index.
		/// @param index Primitive index index.
		/// @return Primitive index.
		[[nodiscard("Pure operator")]]
		constexpr std::uint8_t& operator [](std::size_t index) noexcept;
		/// @brief Gets a primitive index by the @p index.
		/// @param index Primitive index index.
		/// @return Primitive index.
		[[nodiscard("Pure operator")]]
		constexpr const std::uint8_t& operator [](std::size_t index) const noexcept;

		constexpr Primitive& operator =(const Primitive& other) noexcept = default;
		constexpr Primitive& operator =(Primitive&& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Primitive& other) const noexcept;

	private:
		std::array<std::uint8_t, 4> indices; ///< Indices.
	};
}

namespace PonyShader::Mesh
{
	constexpr Primitive::Primitive(const std::uint8_t i0, const std::uint8_t i1, const std::uint8_t i2, const std::uint8_t i3) noexcept :
		indices{ i0, i1, i2, i3 }
	{
	}

	template<std::size_t N>
	constexpr Primitive::Primitive(const std::span<const std::uint8_t, N> indices) noexcept requires (N > 0 && N <= 4) :
		Primitive()
	{
		std::ranges::copy(indices, this->indices.data());
	}

	constexpr std::uint8_t& Primitive::I0() noexcept
	{
		return indices[0];
	}

	constexpr const std::uint8_t& Primitive::I0() const noexcept
	{
		return indices[0];
	}

	constexpr std::uint8_t& Primitive::I1() noexcept
	{
		return indices[1];
	}

	constexpr const std::uint8_t& Primitive::I1() const noexcept
	{
		return indices[1];
	}

	constexpr std::uint8_t& Primitive::I2() noexcept
	{
		return indices[2];
	}

	constexpr const std::uint8_t& Primitive::I2() const noexcept
	{
		return indices[2];
	}

	constexpr std::uint8_t& Primitive::I3() noexcept
	{
		return indices[3];
	}

	constexpr const std::uint8_t& Primitive::I3() const noexcept
	{
		return indices[3];
	}

	constexpr std::span<std::uint8_t, 4> Primitive::Span() noexcept
	{
		return indices;
	}

	constexpr std::span<const std::uint8_t, 4> Primitive::Span() const noexcept
	{
		return indices;
	}

	constexpr std::uint8_t& Primitive::operator [](const std::size_t index) noexcept
	{
		return indices[index];
	}

	constexpr const std::uint8_t& Primitive::operator [](const std::size_t index) const noexcept
	{
		return indices[index];
	}

	constexpr bool Primitive::operator ==(const Primitive& other) const noexcept
	{
		return indices == other.indices;
	}
}
