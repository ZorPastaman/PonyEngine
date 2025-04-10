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
	/// @brief Culler.
	class ICuller
	{
		INTERFACE_BODY(ICuller)

		/// @brief Checks if the point is visible.
		/// @param point Point to check.
		/// @return @a True if it's visible; @a false otherwise.
		[[nodiscard("Pure function")]]
		virtual bool IsVisible(const PonyMath::Core::Vector3<float>& point) const noexcept = 0;
		/// @brief Checks if the oriented bounding box is visible.
		/// @param obb Oriented bounding box to check.
		/// @return @a True if it's visible; @a false otherwise.
		[[nodiscard("Pure function")]]
		virtual bool IsVisible(const PonyMath::Shape::OBB<float>& obb) const noexcept = 0;
	};
}
