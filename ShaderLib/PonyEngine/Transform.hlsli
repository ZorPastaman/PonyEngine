/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

/// @brief Transform. It corresponds to @p PonyEngine::Shader::Transform on the C++ side.
struct Pony_Transform
{
	float4x4 m; ///< Model matrix.
	float4x4 v; ///< View matrix.
	float4x4 p; ///< Projection matrix.
	float4x4 mv; ///< Model-view matrix.
	float4x4 vp; ///< View-projection matrix.
	float4x4 mvp; ///< Model-view-projection matrix.
	float4x4 mInv; ///< Inverse of the model matrix.
	float4x4 vInv; ///< Inverse of the view matrix.
	float4x4 pInv; ///< Inverse of the projection matrix.
	float4x4 mvInv; ///< Inverse of the model-view matrix.
	float4x4 vpInv; ///< Inverse of the view-projection matrix.
	float4x4 mvpInv; ///< Inverse of the model-view-projection matrix.
	
	float mDet; ///< Model matrix determinant.
	float vDet; ///< View matrix determinant.
	float pDet; ///< Projection matrix determinant.
	float mvDet; ///< Model-view matrix determinant.
	float vpDet; ///< View-projection matrix determinant.
	float mvpDet; ///< Model-view-projection matrix determinant.
	float mInvDet; ///< Inverse of the model matrix determinant.
	float vInvDet; ///< Inverse of the view matrix determinant.
	float pInvDet; ///< Inverse of the projection matrix determinant.
	float mvInvDet; ///< Inverse of the model-view matrix determinant.
	float vpInvDet; ///< Inverse of the view-projection matrix determinant.
	float mvpInvDet; ///< Inverse of the model-view-projection matrix determinant.
};
