/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

/// @brief Transform. It corresponds to @p PonyShader::Space::Transform on the C++ side.
struct Pony_Transform
{
	float4x4 modelMatrix; ///< Model matrix.
	float4x4 viewMatrix; ///< View matrix.
	float4x4 projectionMatrix; ///< Projection matrix.
	float4x4 mvpMatrix; ///< Model-view-projection matrix.
};
