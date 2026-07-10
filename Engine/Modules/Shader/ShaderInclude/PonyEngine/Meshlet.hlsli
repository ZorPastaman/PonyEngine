/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

/// @brief Meshlet. It corresponds to @p PonyEngine::Shader::Meshlet on the C++ side.
struct Pony_Meshlet
{
	uint vertexOffset; ///< Vertex offset.
	uint primitiveOffset; ///< Primitive offset.
	uint packedCounts; ///< Packed vertex and primitive counts. Use @p UnpackMeshletCounts() to unpack them.

	/// @brief Unpacks a vertex count.
	/// @return Vertex count.
	uint UnpackVertexCount()
	{
		return packedCounts & 0xFF;
	}

	/// @brief Unpacks a primitive count.
	/// @return Vertex count.
	uint UnpackPrimitiveCount()
	{
		return (packedCounts >> 8) & 0xFF;
	}

	/// @brief Unpacks vertex and primitive counts.
	/// @param vertexCount Vertex count.
	/// @param primitiveCount Primitive count.
	void UnpackMeshletCounts(out uint vertexCount, out uint primitiveCount)
	{
		vertexCount = UnpackVertexCount();
		primitiveCount = UnpackPrimitiveCount();
	}
};

/// @brief Unpacks a point primitive.
/// @tparam T Uint array type.
/// @param indices Index buffer.
/// @param index Point index.
/// @return Point primitive.
template<typename T>
uint UnpackPoint(in const T indices, in const uint index)
{
	const uint mainIndex = indices[index / 4];
	const uint shift = (index % 4) * 8;
	return (mainIndex >> shift) & 0xFF;
}

/// @brief Unpacks a line primitive.
/// @tparam T Uint array type.
/// @param indices Index buffer.
/// @param index Line index.
/// @param isFlipped Is the line flipped?
/// @return Line primitive.
template<typename T>
uint2 UnpackLine(in const T indices, in const uint index, in const bool isFlipped)
{
	const uint baseIndex = index * 2;
	return uint2(UnpackPoint(indices, baseIndex + isFlipped), UnpackPoint(indices, baseIndex + !isFlipped));
}

/// @brief Unpacks a triangle primitive.
/// @tparam T Uint array type.
/// @param indices Index buffer.
/// @param index Triangle index.
/// @param isFlipped Is the triangle flipped?
/// @return Triangle primitive.
template<typename T>
uint3 UnpackTriangle(in const T indices, in const uint index, in const bool isFlipped)
{
	const uint baseIndex = index * 3;
	return uint3(UnpackPoint(indices, baseIndex), UnpackPoint(indices, baseIndex + 1 + isFlipped), UnpackPoint(indices, baseIndex + 2 - isFlipped));
}

/// @brief Unpacks a quad.
/// @tparam T Uint array type.
/// @param indices Index buffer.
/// @param index Quad index.
/// @param isFlipped Is the quad flipped?
/// @return Quad primitive.
template<typename T>
uint4 UnpackQuad(in const T indices, in const uint index, in const bool isFlipped)
{
	const uint baseIndex = index * 4;
	const uint flipShift = isFlipped * 2;
	return uint4(UnpackPoint(indices, baseIndex), UnpackPoint(indices, baseIndex + 1 + flipShift), 
		UnpackPoint(indices, baseIndex + 2), UnpackPoint(indices, baseIndex + 3 - flipShift));
}
