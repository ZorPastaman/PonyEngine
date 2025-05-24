/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Core:CameraBox;

import <array>;
import <cstddef>;
import <span>;

import PonyMath.Core;
import PonyMath.Shape;

import PonyEngine.Render;

export namespace PonyEngine::Render
{
	/// @brief Camera box.
	class CameraBox final
	{
	public:
		/// @brief Creates a zero camera box.
		[[nodiscard("Pure constructor")]]
		CameraBox() noexcept = default;
		/// @brief Creates a camera box.
		/// @param aabb Axis-aligned bounding box.
		[[nodiscard("Pure constructor")]]
		explicit CameraBox(const PonyMath::Shape::AABB<float>& aabb) noexcept;
		/// @brief Creates a camera box.
		/// @param orthographic Orthographic projection parameters.
		[[nodiscard("Pure constructor")]]
		explicit CameraBox(const Orthographic& orthographic) noexcept;
		[[nodiscard("Pure constructor")]]
		CameraBox(const CameraBox& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		CameraBox(CameraBox&& other) noexcept = default;

		~CameraBox() noexcept = default;

		/// @brief Gets the camera box.
		/// @return Camera box.
		[[nodiscard("Pure function")]]
		const PonyMath::Shape::AABB<float>& Box() const noexcept;
		/// @brief Gets a corner by the @p index.
		/// @param index Corner index.
		/// @return Corner.
		[[nodiscard("Pure function")]]
		const PonyMath::Core::Vector3<float>& Corner(std::size_t index) const noexcept;
		/// @brief Gets the corners.
		/// @return Corners.
		[[nodiscard("Pure function")]]
		std::span<const PonyMath::Core::Vector3<float>, 8> Corners() const noexcept;

		CameraBox& operator =(const CameraBox& other) noexcept = default;
		CameraBox& operator =(CameraBox&& other) noexcept = default;

	private:
		PonyMath::Shape::AABB<float> cameraBox; ///< Camera box.
		std::array<PonyMath::Core::Vector3<float>, 8> cameraCorners; ///< Camera corners.
	};
}

namespace PonyEngine::Render
{
	CameraBox::CameraBox(const PonyMath::Shape::AABB<float>& aabb) noexcept :
		cameraBox(aabb),
		cameraCorners(cameraBox.Corners())
	{
	}

	CameraBox::CameraBox(const Orthographic& orthographic) noexcept
	{
		const auto extents = PonyMath::Core::Vector3<float>(orthographic.width, orthographic.height, orthographic.farPlane - orthographic.nearPlane) * 0.5f;
		const auto center = PonyMath::Core::Vector3<float>(0.f, 0.f, extents.Z() + orthographic.nearPlane);
		cameraBox = PonyMath::Shape::AABB<float>(center, extents);
		cameraCorners = cameraBox.Corners();
	}

	const PonyMath::Shape::AABB<float>& CameraBox::Box() const noexcept
	{
		return cameraBox;
	}

	const PonyMath::Core::Vector3<float>& CameraBox::Corner(const std::size_t index) const noexcept
	{
		return cameraCorners[index];
	}

	std::span<const PonyMath::Core::Vector3<float>, 8> CameraBox::Corners() const noexcept
	{
		return cameraCorners;
	}
}
