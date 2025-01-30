/***************************************************
* MIT License                                     *
*                                                 *
* Copyright (c) 2023-present Vladimir Popov       *
*                                                 *
* Email: zor1994@gmail.com                        *
* Repo: https://github.com/ZorPastaman/PonyEngine *
***************************************************/

export module PonyShader.Mesh:Primitive;

import <array>;
import <cstddef>;
import <cstdint>;
import <span>;

export namespace PonyShader::Mesh
{
	class Primitive final
	{
	public:
		[[nodiscard("Pure constructor")]]
		Primitive() noexcept = default;
		[[nodiscard("Pure constructor")]]
		explicit Primitive(std::uint8_t i0, std::uint8_t i1 = 0u, std::uint8_t i2 = 0u, std::uint8_t i3 = 0u) noexcept;
		template<std::size_t N> [[nodiscard("Pure constructor")]]
		explicit Primitive(std::span<const std::uint8_t, N> indices) noexcept requires (N > 0 && N <= 4);
		[[nodiscard("Pure constructor")]]
		Primitive(const Primitive& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Primitive(Primitive&& other) noexcept = default;

		~Primitive() noexcept = default;

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
		std::uint8_t* Data() noexcept;
		[[nodiscard("Pure function")]]
		const std::uint8_t* Data() const noexcept;

		void Set(std::uint8_t i0, std::uint8_t i1 = 0u, std::uint8_t i2 = 0u, std::uint8_t i3 = 0u) noexcept;
		template<std::size_t N>
		void Set(std::span<const std::uint8_t, N> indicesToSet) noexcept requires (N > 0 && N <= 4);

		[[nodiscard("Pure operator")]]
		std::uint8_t& operator [](std::size_t index) noexcept;
		[[nodiscard("Pure operator")]]
		const std::uint8_t& operator [](std::size_t index) const noexcept;

		Primitive& operator =(const Primitive& other) noexcept = default;
		Primitive& operator =(Primitive&& other) noexcept = default;
		template<std::size_t N>
		Primitive& operator =(std::span<const std::uint8_t, N> otherIndices) noexcept requires (N > 0 && N <= 4);

		[[nodiscard("Pure operator")]]
		bool operator ==(const Primitive& other) const noexcept;

	private:
		std::array<std::uint8_t, 4> indices;
	};
}

namespace PonyShader::Mesh
{
	Primitive::Primitive(const std::uint8_t i0, const std::uint8_t i1, const std::uint8_t i2, const std::uint8_t i3) noexcept :
		indices{ i0, i1, i2, i3 }
	{
	}

	template<std::size_t N>
	Primitive::Primitive(const std::span<const std::uint8_t, N> indices) noexcept requires (N > 0 && N <= 4)
	{
		Set(indices);
	}

	std::uint8_t& Primitive::I0() noexcept
	{
		return indices[0];
	}

	const std::uint8_t& Primitive::I0() const noexcept
	{
		return indices[0];
	}

	std::uint8_t& Primitive::I1() noexcept
	{
		return indices[1];
	}

	const std::uint8_t& Primitive::I1() const noexcept
	{
		return indices[1];
	}

	std::uint8_t& Primitive::I2() noexcept
	{
		return indices[2];
	}

	const std::uint8_t& Primitive::I2() const noexcept
	{
		return indices[2];
	}

	std::uint8_t& Primitive::I3() noexcept
	{
		return indices[3];
	}

	const std::uint8_t& Primitive::I3() const noexcept
	{
		return indices[3];
	}

	std::uint8_t* Primitive::Data() noexcept
	{
		return indices.data();
	}

	const std::uint8_t* Primitive::Data() const noexcept
	{
		return indices.data();
	}

	void Primitive::Set(const std::uint8_t i0, const std::uint8_t i1, const std::uint8_t i2, const std::uint8_t i3) noexcept
	{
		indices[0] = i0;
		indices[1] = i1;
		indices[2] = i2;
		indices[3] = i3;
	}

	template<std::size_t N>
	void Primitive::Set(const std::span<const std::uint8_t, N> indicesToSet) noexcept requires (N > 0 && N <= 4)
	{
		std::ranges::copy(indicesToSet, indices.begin());
	}

	std::uint8_t& Primitive::operator [](const std::size_t index) noexcept
	{
		return indices[index];
	}

	const std::uint8_t& Primitive::operator [](const std::size_t index) const noexcept
	{
		return indices[index];
	}

	template<std::size_t N>
	Primitive& Primitive::operator =(const std::span<const std::uint8_t, N> otherIndices) noexcept requires (N > 0 && N <= 4)
	{
		Set(otherIndices);

		return *this;
	}

	bool Primitive::operator ==(const Primitive& other) const noexcept
	{
		return indices == other.indices;
	}
}
