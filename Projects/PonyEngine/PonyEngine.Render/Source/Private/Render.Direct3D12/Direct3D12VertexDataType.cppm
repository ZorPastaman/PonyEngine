/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Direct3D12.Detail:Direct3D12VertexDataType;

import <array>;
import <cmath>;
import <cstddef>;
import <cstdint>;
import <ostream>;
import <string_view>;

export namespace PonyEngine::Render
{
	/// @brief Direct3D12 vertex data type.
	enum class Direct3D12VertexDataType : std::uint8_t
	{
		Signed,
		Unsigned,
		SignedNormalized,
		UnsignedNormalized,
		Float
	};

	/// @brief Gets a string representing the @p dataType.
	/// @param dataType Vertex data type.
	/// @return String representing the @p dataType.
	[[nodiscard("Pure function")]]
	constexpr std::string_view ToString(Direct3D12VertexDataType dataType) noexcept;

	/// @brief Puts the ToString(dataType) into the @p stream.
	/// @param stream Target stream.
	/// @param dataType Vertex data type.
	/// @return @p source.
	std::ostream& operator <<(std::ostream& stream, Direct3D12VertexDataType dataType);
}

namespace PonyEngine::Render
{
	constexpr auto DataTypeNames = std::array<std::string_view, 6>
	{
		"Signed",
		"Unsigned",
		"Signed Normalized",
		"Unsigned Normalized",
		"Float",
		"Unknown"
	};

	constexpr std::string_view ToString(const Direct3D12VertexDataType dataType) noexcept
	{
		return DataTypeNames[std::min(static_cast<std::size_t>(dataType), DataTypeNames.size() - 1)];
	}

	std::ostream& operator <<(std::ostream& stream, const Direct3D12VertexDataType dataType)
	{
		return stream << ToString(dataType);
	}
}
