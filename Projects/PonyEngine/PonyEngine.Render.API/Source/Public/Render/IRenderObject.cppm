/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/Interface.h"

export module PonyEngine.Render:IRenderObject;

import PonyMath.Core;

export namespace PonyEngine::Render
{
	class IRenderObject
	{
		INTERFACE_BODY(IRenderObject)

		[[nodiscard("Pure function")]]
		virtual PonyMath::Core::Matrix4x4<float> ModelMatrix() const noexcept = 0;
		virtual void ModelMatrix(const PonyMath::Core::Matrix4x4<float>& matrix) noexcept = 0;
	};
}
