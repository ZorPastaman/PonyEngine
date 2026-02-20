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
/// @param indices Index buffer.
/// @param index Point index.
/// @return Point primitive.
uint UnpackPoint(in const ByteAddressBuffer indices, in const uint index)
{
	return (indices.Load(index & ~3) >> ((index & 3) << 3)) & 0xFF;
}

/// @brief Unpacks a line primitive.
/// @param indices Index buffer.
/// @param index Line index.
/// @param isFlipped Is the line flipped?
/// @return Line primitive.
uint2 UnpackLine(in const ByteAddressBuffer indices, in const uint index, in const bool isFlipped)
{
	const uint baseIndex = index * 2;
	return uint2(UnpackPoint(indices, baseIndex + isFlipped), UnpackPoint(indices, baseIndex + !isFlipped));
}

/// @brief Unpacks a triangle primitive.
/// @param indices Index buffer.
/// @param index Triangle index.
/// @param isFlipped Is the triangle flipped?
/// @return Triangle primitive.
uint3 UnpackTriangle(in const ByteAddressBuffer indices, in const uint index, in const bool isFlipped)
{
	const uint baseIndex = index * 3;
	return uint3(UnpackPoint(indices, baseIndex), UnpackPoint(indices, baseIndex + 1 + isFlipped), UnpackPoint(indices, baseIndex + 2 - isFlipped));
}

/// @brief Unpacks a quad.
/// @param indices Index buffer.
/// @param index Quad index.
/// @param isFlipped Is the quad flipped?
/// @return Quad primitive.
uint4 UnpackQuad(in const ByteAddressBuffer indices, in const uint index, in const bool isFlipped)
{
	const uint baseIndex = index * 4;
	const uint flipShift = isFlipped * 2;
	return uint4(UnpackPoint(indices, baseIndex), UnpackPoint(indices, baseIndex + 1 + flipShift), 
		UnpackPoint(indices, baseIndex + 2), UnpackPoint(indices, baseIndex + 3 - flipShift));
}
