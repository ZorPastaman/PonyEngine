/***************************************************
* MIT License                                     *
*                                                 *
* Copyright (c) 2023-present Vladimir Popov       *
*                                                 *
* Email: zor1994@gmail.com                        *
* Repo: https://github.com/ZorPastaman/PonyEngine *
***************************************************/

export module PonyEngine.Render:Meshlet;

import <array>;
import <cstdint>;

export namespace PonyEngine::Render
{
	class Meshlet final
	{
	public:
		[[nodiscard("Pure constructor")]]
		Meshlet() noexcept = default;
		[[nodiscard("Pure constructor")]]
		Meshlet(std::uint32_t vertexOffset, std::uint32_t primitiveOffset, std::uint8_t vertexCount, std::uint8_t primitiveCount) noexcept;
		[[nodiscard("Pure constructor")]]
		Meshlet(const Meshlet& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Meshlet(Meshlet&& other) noexcept = default;

		~Meshlet() noexcept = default;

		[[nodiscard("Pure function")]]
		std::uint32_t& VertexOffset() noexcept;
		[[nodiscard("Pure function")]]
		const std::uint32_t& VertexOffset() const noexcept;

		[[nodiscard("Pure function")]]
		std::uint32_t& PrimitiveOffset() noexcept;
		[[nodiscard("Pure function")]]
		const std::uint32_t& PrimitiveOffset() const noexcept;

		[[nodiscard("Pure function")]]
		std::uint8_t& VertexCount() noexcept;
		[[nodiscard("Pure function")]]
		const std::uint8_t& VertexCount() const noexcept;

		[[nodiscard("Pure function")]]
		std::uint8_t& PrimitiveCount() noexcept;
		[[nodiscard("Pure function")]]
		const std::uint8_t& PrimitiveCount() const noexcept;

		void Set(std::uint32_t vertexOffsetToSet, std::uint32_t primitiveOffsetToSet, std::uint8_t vertexCount, std::uint8_t primitiveCount) noexcept;

		Meshlet& operator =(const Meshlet& other) noexcept = default;
		Meshlet& operator =(Meshlet&& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		bool operator ==(const Meshlet& other) const noexcept = default;

	private:
		std::uint32_t vertexOffset;
		std::uint32_t primitiveOffset;
		std::array<std::uint8_t, 4> packedCounts; ///< Packed counts: vertex count, primitive count and 2 elements for alignment with shader data.
	};
}

namespace PonyEngine::Render
{
	Meshlet::Meshlet(const std::uint32_t vertexOffset, const std::uint32_t primitiveOffset, const std::uint8_t vertexCount, const std::uint8_t primitiveCount) noexcept :
		vertexOffset{vertexOffset},
		primitiveOffset{primitiveOffset},
		packedCounts{ vertexCount, primitiveCount, 0u, 0u }
	{
	}

	std::uint32_t& Meshlet::VertexOffset() noexcept
	{
		return vertexOffset;
	}

	const std::uint32_t& Meshlet::VertexOffset() const noexcept
	{
		return vertexOffset;
	}

	std::uint32_t& Meshlet::PrimitiveOffset() noexcept
	{
		return primitiveOffset;
	}

	const std::uint32_t& Meshlet::PrimitiveOffset() const noexcept
	{
		return primitiveOffset;
	}

	std::uint8_t& Meshlet::VertexCount() noexcept
	{
		return packedCounts[0];
	}

	const std::uint8_t& Meshlet::VertexCount() const noexcept
	{
		return packedCounts[0];
	}

	std::uint8_t& Meshlet::PrimitiveCount() noexcept
	{
		return packedCounts[1];
	}

	const std::uint8_t& Meshlet::PrimitiveCount() const noexcept
	{
		return packedCounts[1];
	}

	void Meshlet::Set(const std::uint32_t vertexOffsetToSet, const std::uint32_t primitiveOffsetToSet, const std::uint8_t vertexCount, const std::uint8_t primitiveCount) noexcept
	{
		vertexOffset = vertexOffsetToSet;
		primitiveOffset = primitiveOffsetToSet;
		packedCounts[0] = vertexCount;
		packedCounts[1] = primitiveCount;
	}
}
