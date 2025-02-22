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
import <variant>;

import PonyMath.Color;
import PonyMath.Core;
import PonyMath.Shape;

import :Clear;
import :Common;
import :ICuller;

export namespace PonyEngine::Render
{
	class ICamera
	{
		INTERFACE_BODY(ICamera)

		[[nodiscard("Pure function")]]
		virtual const PonyMath::Core::Matrix4x4<float>& ViewMatrix() const noexcept = 0;
		virtual void ViewMatrix(const PonyMath::Core::Matrix4x4<float>& matrix) noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual const PonyMath::Core::Matrix4x4<float>& ProjectionMatrix() const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual const PonyMath::Core::Matrix4x4<float>& ViewProjectionMatrix() const noexcept = 0;

		[[nodiscard("Pure function")]]
		virtual const CameraProjection& Projection() const noexcept = 0;
		virtual void Projection(const CameraProjection& projection) noexcept = 0;

		[[nodiscard("Pure function")]]
		virtual const PonyMath::Color::RGBA<float>& ClearColor() const noexcept = 0;
		virtual void ClearColor(const PonyMath::Color::RGBA<float>& color) noexcept = 0;

		[[nodiscard("Pure function")]]
		virtual Clear ClearFlags() const noexcept = 0;
		virtual void ClearFlags(Clear clear) noexcept = 0;

		[[nodiscard("Pure function")]]
		virtual const PonyMath::Shape::Rect<float>& ViewportRect() const noexcept = 0;
		virtual void ViewportRect(const PonyMath::Shape::Rect<float>& rect) noexcept = 0;

		[[nodiscard("Pure function")]]
		virtual std::int32_t SortingOrder() const noexcept = 0;
		virtual void SortingOrder(std::int32_t order) noexcept = 0;

		[[nodiscard("Pure function")]]
		virtual const ICuller& Culler() const noexcept = 0;
	};
}
