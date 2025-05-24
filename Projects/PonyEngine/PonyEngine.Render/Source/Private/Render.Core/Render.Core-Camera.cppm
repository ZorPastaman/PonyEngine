/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

export module PonyEngine.Render.Core:Camera;

import <cstdint>;
import <optional>;
import <variant>;

import PonyMath.Core;
import PonyMath.Shape;

import PonyEngine.Render;

import :BoxCuller;
import :FrustumCuller;

export namespace PonyEngine::Render::Core
{
	/// @brief Camera
	class Camera final : public ICamera
	{
	public:
		/// @brief Creates a camera.
		/// @param cameraParams Camera parameters.
		[[nodiscard("Pure constructor")]]
		explicit Camera(const CameraParams& cameraParams) noexcept;
		[[nodiscard("Pure constructor")]]
		Camera(const Camera& other) = delete;
		[[nodiscard("Pure constructor")]]
		Camera(Camera&& other) = delete;

		~Camera() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual const PonyMath::Core::Matrix4x4<float>& ViewMatrix() const noexcept override;
		virtual void ViewMatrix(const PonyMath::Core::Matrix4x4<float>& matrix) noexcept override;
		[[nodiscard("Pure function")]]
		virtual const PonyMath::Core::Matrix4x4<float>& ProjectionMatrix() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual const PonyMath::Core::Matrix4x4<float>& ViewProjectionMatrix() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual const PonyMath::Core::Matrix4x4<float>& ViewInverseMatrix() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual const PonyMath::Core::Matrix4x4<float>& ProjectionInverseMatrix() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual const PonyMath::Core::Matrix4x4<float>& ViewProjectionInverseMatrix() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual const CameraProjection& Projection() const noexcept override;
		virtual void Projection(const CameraProjection& projection) noexcept override;

		[[nodiscard("Pure function")]]
		virtual const Render::ClearValue& ClearValue() const noexcept override;
		virtual void ClearValue(const Render::ClearValue& clear) noexcept override;

		[[nodiscard("Pure function")]]
		virtual const PonyMath::Shape::Rect<float>& ViewportRect() const noexcept override;
		virtual void ViewportRect(const PonyMath::Shape::Rect<float>& rect) noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::int32_t SortingOrder() const noexcept override;
		virtual void SortingOrder(std::int32_t order) noexcept override;

		[[nodiscard("Pure function")]]
		virtual const ICuller& Culler() const noexcept override;

		Camera& operator =(const Camera&) = delete;
		Camera& operator =(Camera&&) = delete;

	private:
		/// @brief Computes a projection matrix by current parameters.
		/// @return Projection matrix.
		[[nodiscard("Pure function")]]
		PonyMath::Core::Matrix4x4<float> ComputeProjectionMatrix() const noexcept;
		/// @brief Computes a perspective projection matrix.
		/// @param params Perspective projection parameters.
		/// @return Perspective projection matrix.
		[[nodiscard("Pure function")]]
		static PonyMath::Core::Matrix4x4<float> ComputePerspectiveMatrix(const Perspective& params) noexcept;
		/// @brief Computes an orthographic projection matrix.
		/// @param params Orthographic projection parameters.
		/// @return Orthographic projection matrix.
		[[nodiscard("Pure function")]]
		static PonyMath::Core::Matrix4x4<float> ComputeOrthographicMatrix(const Orthographic& params) noexcept;

		PonyMath::Core::Matrix4x4<float> viewMatrix; ///< View matrix.
		mutable std::optional<PonyMath::Core::Matrix4x4<float>> projectionMatrix; ///< Projection matrix. It becomes std::nullopt if the projection parameters are changed.
		mutable std::optional<PonyMath::Core::Matrix4x4<float>> viewProjectionMatrix; ///< View-projection matrix. It becomes std::nullopt if the view matrix and/or the projection parameters are changed.
		mutable std::optional<PonyMath::Core::Matrix4x4<float>> viewInverseMatrix; /// Inverse of the view matrix. It becomes std::nullopt if the view matrix is changed.
		mutable std::optional<PonyMath::Core::Matrix4x4<float>> projectionInverseMatrix; /// Inverse of the projection matrix. It becomes std::nullopt if the projection parameters are changed.
		mutable std::optional<PonyMath::Core::Matrix4x4<float>> viewProjectionInverseMatrix; /// Inverse of the view-projection matrix. It becomes std::nullopt if the view matrix and/or the projection parameters are changed.

		CameraProjection projection; ///< Projection parameters.
		mutable std::optional<std::variant<FrustumCuller, BoxCuller>> culler; ///< Culler. It becomes std::nullopt if the projection parameters are changed.

		struct ClearValue clear; ///< Clear value.

		PonyMath::Shape::Rect<float> viewportRect; ///< Normalized viewport rect.

		std::int32_t sortingOrder; ///< Sorting order.
	};
}

namespace PonyEngine::Render::Core
{
	Camera::Camera(const CameraParams& cameraParams) noexcept :
		viewMatrix(cameraParams.viewMatrix),
		projection(cameraParams.projection),
		clear(cameraParams.clearValue),
		viewportRect(cameraParams.viewportRect),
		sortingOrder{cameraParams.sortingOrder}
	{
	}

	const PonyMath::Core::Matrix4x4<float>& Camera::ViewMatrix() const noexcept
	{
		return viewMatrix;
	}

	void Camera::ViewMatrix(const PonyMath::Core::Matrix4x4<float>& matrix) noexcept
	{
		viewMatrix = matrix;
		viewProjectionMatrix = std::nullopt;
		viewInverseMatrix = std::nullopt;
		viewProjectionInverseMatrix = std::nullopt;
	}

	const PonyMath::Core::Matrix4x4<float>& Camera::ProjectionMatrix() const noexcept
	{
		if (!projectionMatrix)
		{
			projectionMatrix = ComputeProjectionMatrix();
		}

		return projectionMatrix.value();
	}

	const PonyMath::Core::Matrix4x4<float>& Camera::ViewProjectionMatrix() const noexcept
	{
		if (!viewProjectionMatrix)
		{
			viewProjectionMatrix = ProjectionMatrix() * ViewMatrix();
		}

		return viewProjectionMatrix.value();
	}

	const PonyMath::Core::Matrix4x4<float>& Camera::ViewInverseMatrix() const noexcept
	{
		if (!viewInverseMatrix)
		{
			viewInverseMatrix = viewMatrix.Inverse();
		}

		return viewInverseMatrix.value();
	}

	const PonyMath::Core::Matrix4x4<float>& Camera::ProjectionInverseMatrix() const noexcept
	{
		if (!projectionInverseMatrix)
		{
			projectionInverseMatrix = ProjectionMatrix().Inverse();
		}

		return projectionInverseMatrix.value();
	}

	const PonyMath::Core::Matrix4x4<float>& Camera::ViewProjectionInverseMatrix() const noexcept
	{
		if (!viewProjectionInverseMatrix)
		{
			viewProjectionInverseMatrix = ViewInverseMatrix() * ProjectionInverseMatrix();
		}

		return viewProjectionInverseMatrix.value();
	}

	const CameraProjection& Camera::Projection() const noexcept
	{
		return projection;
	}

	void Camera::Projection(const CameraProjection& projection) noexcept
	{
		this->projection = projection;
		projectionMatrix = std::nullopt;
		viewProjectionMatrix = std::nullopt;
		projectionInverseMatrix = std::nullopt;
		viewProjectionInverseMatrix = std::nullopt;
		culler = std::nullopt;
	}

	const struct ClearValue& Camera::ClearValue() const noexcept
	{
		return clear;
	}

	void Camera::ClearValue(const struct ClearValue& clear) noexcept
	{
		this->clear = clear;
	}

	const PonyMath::Shape::Rect<float>& Camera::ViewportRect() const noexcept
	{
		return viewportRect;
	}

	void Camera::ViewportRect(const PonyMath::Shape::Rect<float>& rect) noexcept
	{
		viewportRect = rect;
	}

	std::int32_t Camera::SortingOrder() const noexcept
	{
		return sortingOrder;
	}

	void Camera::SortingOrder(const std::int32_t order) noexcept
	{
		sortingOrder = order;
	}

	const ICuller& Camera::Culler() const noexcept
	{
		if (!culler)
		{
			switch (projection.index())
			{
			case 0:
				culler = FrustumCuller(std::get<0>(projection));
				break;
			case 1:
				culler = BoxCuller(std::get<1>(projection));
				break;
			default: [[unlikely]]
				assert(false && "Unsupported projection type.");
				culler = BoxCuller(PonyMath::Shape::AABB<float>::Predefined::Zero);
				break;
			}
		}

		return culler->index() == 0
			? static_cast<const ICuller&>(std::get<0>(culler.value()))
			: std::get<1>(culler.value());
	}

	PonyMath::Core::Matrix4x4<float> Camera::ComputeProjectionMatrix() const noexcept
	{
		switch (projection.index())
		{
		case 0:
			return ComputePerspectiveMatrix(std::get<0>(projection));
		case 1:
			return ComputeOrthographicMatrix(std::get<1>(projection));
		default: [[unlikely]]
			assert(false && "Unsupported projection type.");
			return PonyMath::Core::Matrix4x4<float>::Predefined::Identity;
		}
	}

	PonyMath::Core::Matrix4x4<float> Camera::ComputePerspectiveMatrix(const Perspective& params) noexcept
	{
		return PonyMath::Core::PerspectiveMatrix(params.fov, params.aspect, params.nearPlane, params.farPlane);
	}

	PonyMath::Core::Matrix4x4<float> Camera::ComputeOrthographicMatrix(const Orthographic& params) noexcept
	{
		return PonyMath::Core::OrthographicMatrix(params.width, params.height, params.nearPlane, params.farPlane);
	}
}
