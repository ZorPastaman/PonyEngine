/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyShader.Space:Transform;

import PonyMath.Core;

export namespace PonyShader::Space
{
	/// @brief Render transform. It corresponds to @p Pony_Transform in PonyShader/Space/Transform.hlsli on the HLSL side.
	struct alignas(256) Transform final
	{
		PonyMath::Core::Matrix4x4<float> model; ///< Model matrix.
		PonyMath::Core::Matrix4x4<float> view; ///< View matrix.
		PonyMath::Core::Matrix4x4<float> projection; ///< Projection matrix.
		PonyMath::Core::Matrix4x4<float> mv; ///< MV matrix.
		PonyMath::Core::Matrix4x4<float> vp; ///< VP matrix.
		PonyMath::Core::Matrix4x4<float> mvp; ///< MVP matrix.
		PonyMath::Core::Matrix4x4<float> modelInv; ///< Inverse of the model matrix.
		PonyMath::Core::Matrix4x4<float> viewInv; ///< Inverse of the view matrix.
		PonyMath::Core::Matrix4x4<float> projectionInv; ///< Inverse of the projection matrix.
		PonyMath::Core::Matrix4x4<float> mvInv; ///< Inverse of the model-view matrix.
		PonyMath::Core::Matrix4x4<float> vpInv; ///< Inverse of the view-projection matrix.
		PonyMath::Core::Matrix4x4<float> mvpInv; ///< Inverse of the model-view-projection matrix.
	};
}
