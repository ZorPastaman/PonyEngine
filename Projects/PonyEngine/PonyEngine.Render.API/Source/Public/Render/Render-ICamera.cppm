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

export module PonyEngine.Render:ICamera;

import <cstdint>;

import PonyMath.Color;
import PonyMath.Core;
import PonyMath.Shape;

import :ClearParams;
import :Common;
import :ICuller;

export namespace PonyEngine::Render
{
	/// @brief Render camera.
	class ICamera
	{
		INTERFACE_BODY(ICamera)

		/// @brief Gets the view matrix.
		/// @return View matrix.
		[[nodiscard("Pure function")]]
		virtual const PonyMath::Core::Matrix4x4<float>& ViewMatrix() const noexcept = 0;
		/// @brief Sets the view matrix.
		/// @param matrix View matrix to set.
		virtual void ViewMatrix(const PonyMath::Core::Matrix4x4<float>& matrix) noexcept = 0;
		/// @brief Gets the projection matrix.
		/// @return Projection matrix.
		[[nodiscard("Pure function")]]
		virtual const PonyMath::Core::Matrix4x4<float>& ProjectionMatrix() const noexcept = 0;
		/// @brief Gets the view-projection matrix.
		/// @return View-projection matrix.
		[[nodiscard("Pure function")]]
		virtual const PonyMath::Core::Matrix4x4<float>& ViewProjectionMatrix() const noexcept = 0;

		/// @brief Gets the projection parameters.
		/// @return Projection parameters.
		[[nodiscard("Pure function")]]
		virtual const CameraProjection& Projection() const noexcept = 0;
		/// @brief Sets the projection parameters.
		/// @param projection Projection parameters to set.
		virtual void Projection(const CameraProjection& projection) noexcept = 0;

		/// @brief Gets the clear parameters.
		/// @return Clear parameters.
		[[nodiscard("Pure function")]]
		virtual const ClearParams& Clear() const noexcept = 0;
		/// @brief Sets the clear parameters.
		/// @param clear Clear parameters to set.
		virtual void Clear(const ClearParams& clear) noexcept = 0;

		/// @brief Gets the normalized viewport rect.
		/// @return Normalized viewport rect.
		[[nodiscard("Pure function")]]
		virtual const PonyMath::Shape::Rect<float>& ViewportRect() const noexcept = 0;
		/// @brief Sets the normalized viewport rect.
		/// @param rect Normalized viewport rect to set.
		virtual void ViewportRect(const PonyMath::Shape::Rect<float>& rect) noexcept = 0;

		/// @brief Gets the sorting order.
		/// @return Sorting order.
		[[nodiscard("Pure function")]]
		virtual std::int32_t SortingOrder() const noexcept = 0;
		/// @brief Sets the sorting order.
		/// @param order Sorting order.
		virtual void SortingOrder(std::int32_t order) noexcept = 0;

		/// @brief Gets the camera culler.
		/// @details Culler is recreated each time when the camera projection is changed.
		/// @return Camera culler.
		[[nodiscard("Pure function")]]
		virtual const ICuller& Culler() const noexcept = 0;
	};
}
