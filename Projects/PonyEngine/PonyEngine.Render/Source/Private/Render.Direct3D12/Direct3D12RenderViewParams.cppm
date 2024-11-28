/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/Direct3D12/Framework.h"

export module PonyEngine.Render.Direct3D12.Detail:Direct3D12RenderViewParams;

import PonyMath.Core;

export namespace PonyEngine::Render
{
	/// @brief Direct3D12 render view parameters.
	struct Direct3D12RenderViewParams final
	{
		PonyMath::Core::Matrix4x4<FLOAT> viewMatrix; ///< View matrix.
		PonyMath::Core::Matrix4x4<FLOAT> projectionMatrix; ///< Projection matrix.
	};
}
