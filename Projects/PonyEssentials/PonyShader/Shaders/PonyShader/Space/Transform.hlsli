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
	float4x4 model; ///< Model matrix.
	float4x4 view; ///< View matrix.
	float4x4 projection; ///< Projection matrix.
	float4x4 mv; ///< Model-view matrix.
	float4x4 vp; ///< View-projection matrix.
	float4x4 mvp; ///< Model-view-projection matrix.
	float4x4 modelInv; ///< Inverse of the model matrix.
	float4x4 viewInv; ///< Inverse of the view matrix.
	float4x4 projectionInv; ///< Inverse of the projection matrix.
	float4x4 mvInv; ///< Inverse of the model-view matrix.
	float4x4 vpInv; ///< Inverse of the view-projection matrix.
	float4x4 mvpInv; ///< Inverse of the model-view-projection matrix.
};
