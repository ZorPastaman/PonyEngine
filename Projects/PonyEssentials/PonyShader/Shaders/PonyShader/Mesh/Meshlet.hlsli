/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

/// @brief Meshlet. It corresponds to @p PonyShader::Mesh::Meshlet on the C++ side.
struct Pony_Meshlet
{
	uint vertexOffset; ///< Vertex offset.
	uint primitiveOffset; ///< Primitive offset.
	uint packedCounts; ///< Packed vertex and primitive counts. Use @p UnpackMeshletCounts() to unpack them.
};

/// @brief Unpacks vertex and primitive counts from the @p meshlet.
/// @param meshlet Meshlet.
/// @param vertexCount Vertex count.
/// @param primitiveCount Primitive count.
void UnpackMeshletCounts(in Pony_Meshlet meshlet, out uint vertexCount, out uint primitiveCount)
{
	vertexCount = meshlet.packedCounts & 0xFF;
	primitiveCount = meshlet.packedCounts >> 8 & 0xFF;
}
