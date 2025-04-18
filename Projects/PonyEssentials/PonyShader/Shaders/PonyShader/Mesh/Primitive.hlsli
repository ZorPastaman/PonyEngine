/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

/// @brief Primitive. It corresponds to @p PonyShader::Mesh::Primitive on the C++ side.
struct Pony_Primitive
{
	uint indices; ///< Packed primitive indices. Use @p UnpackPoint(), @p UnpackLineFirst(), @p UnpackLineSecond(), @p UnpackLine(), @p UnpackTriangle() or @p UnpackQuad() to unpack them.
};

/// @brief Unpacks the @p primitive as a point.
/// @param primitive Primitive.
/// @param index Point index inside the pack. Must be in range [0, 3].
/// @return Unpacked primitive.
uint UnpackPoint(in Pony_Primitive primitive, in uint index)
{
	return primitive.indices >> (index * 8) & 0xFF;
}

/// @brief Unpacks the @p primitive as a line. Takes first two indices.
/// @param primitive Primitive.
/// @return Unpacked primitive.
uint2 UnpackLineFirst(in Pony_Primitive primitive)
{
	return uint2(primitive.indices & 0xFF, primitive.indices >> 8 & 0xFF);
}

/// @brief Unpacks the @p primitive as a line. Takes last two indices.
/// @param primitive Primitive.
/// @return Unpacked primitive.
uint2 UnpackLineSecond(in Pony_Primitive primitive)
{
	return uint2(primitive.indices >> 16 & 0xFF, primitive.indices >> 24 & 0xFF);
}

/// @brief Unpacks the @p primitive as a line.
/// @param primitive Primitive.
/// @param index Line index. Must be 0 or 1.
/// @return Unpacked primitive.
uint2 UnpackLine(in Pony_Primitive primitive, in uint index)
{
	uint firstIndex = (16 & -index);

	return uint2(primitive.indices >> firstIndex & 0xFF, primitive.indices >> (firstIndex + 8) & 0xFF);
}

/// @brief Unpacks the @p primitive as a triangle.
/// @param primitive Primitive.
/// @return Unpacked primitive.
uint3 UnpackTriangle(in Pony_Primitive primitive)
{
	return uint3(primitive.indices & 0xFF, primitive.indices >> 8 & 0xFF, primitive.indices >> 16 & 0xFF);
}

/// @brief Unpacks the @p primitive as a quad.
/// @param primitive Primitive.
/// @return Unpacked primitive.
uint4 UnpackQuad(in Pony_Primitive primitive)
{
	return uint4(primitive.indices & 0xFF, primitive.indices >> 8 & 0xFF, primitive.indices >> 16 & 0xFF, primitive.indices >> 24 & 0xFF);
}

/// @brief Optionally flips the line indices.
/// @param indices Indices.
/// @param flip Is flipping required?
/// @return Flipped indices if the @p flip is @a true; the same indices otherwise.
uint2 FlipLine(in uint2 indices, in bool flip)
{
	return uint2(indices[0 + flip], indices[1 - flip]);
}

/// @brief Optionally flips the triangle indices.
/// @param indices Indices.
/// @param flip Is flipping required?
/// @return Flipped indices if the @p flip is @a true; the same indices otherwise.
uint3 FlipTriangle(in uint3 indices, in bool flip)
{
	return uint3(indices[0], indices[1 + flip], indices[2 - flip]);
}

/// @brief Optionally flips the quad indices.
/// @param indices Indices.
/// @param flip Is flipping required?
/// @return Flipped indices if the @p flip is @a true; the same indices otherwise.
uint4 FlipQuad(in uint4 indices, in bool flip)
{
	uint flipShift = flip << 1;

	return uint4(indices[0], indices[1 + flipShift], indices[2], indices[3 - flipShift]);
}

/// @brief Unpacks the @p primitive as a line and optionally flips it. Takes first two indices.
/// @param primitive Primitive.
/// @param flip Is flipping required?
/// @return Unpacked primitive.
uint2 UnpackLineFirst(in Pony_Primitive primitive, in bool flip)
{
	return FlipLine(UnpackLineFirst(primitive), flip);
}

/// @brief Unpacks the @p primitive as a line and optionally flips it. Takes last two indices.
/// @param primitive Primitive.
/// @param flip Is flipping required?
/// @return Unpacked primitive.
uint2 UnpackLineSecond(in Pony_Primitive primitive, in bool flip)
{
	return FlipLine(UnpackLineSecond(primitive), flip);
}

/// @brief Unpacks the @p primitive as a line and optionally flips it.
/// @param primitive Primitive.
/// @param index Line index. Must be 0 or 1.
/// @param flip Is flipping required?
/// @return Unpacked primitive.
uint2 UnpackLine(in Pony_Primitive primitive, in uint index, in bool flip)
{
	return FlipLine(UnpackLine(primitive, index), flip);
}

/// @brief Unpacks the @p primitive as a triangle and optionally flips it.
/// @param primitive Primitive.
/// @param flip Is flipping required?
/// @return Unpacked primitive.
uint3 UnpackTriangle(in Pony_Primitive primitive, in bool flip)
{
	return FlipTriangle(UnpackTriangle(primitive), flip);
}

/// @brief Unpacks the @p primitive as a quad and optionally flips it.
/// @param primitive Primitive.
/// @param flip Is flipping required?
/// @return Unpacked primitive.
uint4 UnpackQuad(in Pony_Primitive primitive, in bool flip)
{
	return FlipQuad(UnpackQuad(primitive), flip);
}
