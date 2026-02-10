/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Shader:Meshlet;

import std;

export namespace PonyEngine::Shader
{
	/// @brief Meshlet. It corresponds to @p Pony_Meshlet in PonyEngine/Meshlet.hlsli on the HLSL side.
	class Meshlet final
	{
	public:
		/// @brief Creates a zero meshlet.
		[[nodiscard("Pure constructor")]]
		constexpr Meshlet() noexcept = default;
		/// @brief Creates a meshlet.
		/// @param vertexOffset Vertex offset.
		/// @param primitiveOffset Primitive offset.
		/// @param vertexCount Vertex count.
		/// @param primitiveCount Primitive count.
		[[nodiscard("Pure constructor")]]
		constexpr Meshlet(std::uint32_t vertexOffset, std::uint32_t primitiveOffset, std::uint8_t vertexCount, std::uint8_t primitiveCount) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Meshlet(const Meshlet& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Meshlet(Meshlet&& other) noexcept = default;

		constexpr ~Meshlet() noexcept = default;

		/// @brief Gets the vertex offset.
		/// @return Vertex offset.
		[[nodiscard("Pure function")]]
		constexpr std::uint32_t& VertexOffset() noexcept;
		/// @brief Gets the vertex offset.
		/// @return Vertex offset.
		[[nodiscard("Pure function")]]
		constexpr const std::uint32_t& VertexOffset() const noexcept;

		/// @brief Gets the primitive offset.
		/// @return Primitive offset.
		[[nodiscard("Pure function")]]
		constexpr std::uint32_t& PrimitiveOffset() noexcept;
		/// @brief Gets the primitive offset.
		/// @return Primitive offset.
		[[nodiscard("Pure function")]]
		constexpr const std::uint32_t& PrimitiveOffset() const noexcept;

		/// @brief Gets the vertex count.
		/// @return Vertex count.
		[[nodiscard("Pure function")]]
		constexpr std::uint8_t& VertexCount() noexcept;
		/// @brief Gets the vertex count.
		/// @return Vertex count.
		[[nodiscard("Pure function")]]
		constexpr const std::uint8_t& VertexCount() const noexcept;

		/// @brief Gets the primitive count.
		/// @return Primitive count.
		[[nodiscard("Pure function")]]
		constexpr std::uint8_t& PrimitiveCount() noexcept;
		/// @brief Gets the primitive count.
		/// @return Primitive count.
		[[nodiscard("Pure function")]]
		constexpr const std::uint8_t& PrimitiveCount() const noexcept;

		constexpr Meshlet& operator =(const Meshlet& other) noexcept = default;
		constexpr Meshlet& operator =(Meshlet&& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Meshlet& other) const noexcept = default;

	private:
		std::uint32_t vertexOffset; ///< Vertex offset.
		std::uint32_t primitiveOffset; ///< Primitive offset.
		std::array<std::uint8_t, 4> packedCounts; ///< Packed counts: vertex count, primitive count and 2 elements for alignment with shader data.
	};
}

namespace PonyEngine::Shader
{
	constexpr Meshlet::Meshlet(const std::uint32_t vertexOffset, const std::uint32_t primitiveOffset, const std::uint8_t vertexCount, const std::uint8_t primitiveCount) noexcept :
		vertexOffset{vertexOffset},
		primitiveOffset{primitiveOffset},
		packedCounts{vertexCount, primitiveCount, 0u, 0u}
	{
	}

	constexpr std::uint32_t& Meshlet::VertexOffset() noexcept
	{
		return vertexOffset;
	}

	constexpr const std::uint32_t& Meshlet::VertexOffset() const noexcept
	{
		return vertexOffset;
	}

	constexpr std::uint32_t& Meshlet::PrimitiveOffset() noexcept
	{
		return primitiveOffset;
	}

	constexpr const std::uint32_t& Meshlet::PrimitiveOffset() const noexcept
	{
		return primitiveOffset;
	}

	constexpr std::uint8_t& Meshlet::VertexCount() noexcept
	{
		return packedCounts[0];
	}

	constexpr const std::uint8_t& Meshlet::VertexCount() const noexcept
	{
		return packedCounts[0];
	}

	constexpr std::uint8_t& Meshlet::PrimitiveCount() noexcept
	{
		return packedCounts[1];
	}

	constexpr const std::uint8_t& Meshlet::PrimitiveCount() const noexcept
	{
		return packedCounts[1];
	}
}
