/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/ObjectBody.h"

export module PonyEngine.Render:ICuller;

import PonyMath.Core;
import PonyMath.Shape;

export namespace PonyEngine::Render
{
	class ICuller
	{
		INTERFACE_BODY(ICuller)

		[[nodiscard("Pure function")]]
		virtual bool IsVisible(const PonyMath::Core::Vector3<float>& point) const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual bool IsVisible(const PonyMath::Shape::AABB<float>& modelBounds) const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual bool IsVisible(const PonyMath::Shape::AABB<float>& modelBounds, const PonyMath::Core::Quaternion<float>& rotation) const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual bool IsVisible(const PonyMath::Shape::AABB<float>& modelBounds, const PonyMath::Core::Matrix4x4<float>& modelMatrix) const noexcept = 0;
	};
}
