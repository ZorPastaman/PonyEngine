/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Detail:BoxCuller;

import <algorithm>;
import <array>;
import <cstddef>;
import <utility>;

import PonyMath.Core;
import PonyMath.Shape;

import PonyEngine.Render;

import :CameraBox;

export namespace PonyEngine::Render
{
	/// @brief Box culler.
	class BoxCuller final : public ICuller
	{
	public:
		/// @brief Creates a zero box culler.
		[[nodiscard("Pure constructor")]]
		BoxCuller() noexcept = default;
		/// @brief Creates a box culler.
		/// @param cameraBox Camera bounding box.
		[[nodiscard("Pure constructor")]]
		explicit BoxCuller(const PonyMath::Shape::AABB<float>& cameraBox) noexcept;
		/// @brief Creates a box culler.
		/// @param orthographic Orthographic projection parameters.
		[[nodiscard("Pure constructor")]]
		explicit BoxCuller(const Orthographic& orthographic) noexcept;
		[[nodiscard("Pure constructor")]]
		BoxCuller(const BoxCuller& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		BoxCuller(BoxCuller&& other) noexcept = default;

		~BoxCuller() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual bool IsVisible(const PonyMath::Core::Vector3<float>& point) const noexcept override;
		[[nodiscard("Pure function")]]
		virtual bool IsVisible(const PonyMath::Shape::OBB<float>& obb) const noexcept override;

		BoxCuller& operator =(const BoxCuller& other) noexcept = default;
		BoxCuller& operator =(BoxCuller&& other) noexcept = default;

	private:
		CameraBox cameraBox; ///< Camera box.
	};
}

namespace PonyEngine::Render
{
	BoxCuller::BoxCuller(const PonyMath::Shape::AABB<float>& cameraBox) noexcept :
		cameraBox(cameraBox)
	{
	}

	BoxCuller::BoxCuller(const Orthographic& orthographic) noexcept :
		cameraBox(orthographic)
	{
	}

	bool BoxCuller::IsVisible(const PonyMath::Core::Vector3<float>& point) const noexcept
	{
		return cameraBox.Box().Contains(point);
	}

	bool BoxCuller::IsVisible(const PonyMath::Shape::OBB<float>& obb) const noexcept
	{
		// Check by center.
		if (cameraBox.Box().Contains(obb.Center()))
		{
			return true;
		}

		// Check by bounding sphere.
		const float radiusSqr = PonyMath::Core::Vector3<float>(obb.Extents()).MagnitudeSquared();
		if (const PonyMath::Core::Vector3<float> closestPoint = cameraBox.Box().ClosestPoint(obb.Center()); (closestPoint - obb.Center()).MagnitudeSquared() > radiusSqr)
		{
			return false;
		}

		const std::array<PonyMath::Core::Vector3<float>, PonyMath::Shape::AABB<float>::CornerCount> obbCorners = obb.Corners();

		// Check by corners.
		for (const PonyMath::Core::Vector3<float>& corner : obbCorners)
		{
			if (cameraBox.Box().Contains(corner))
			{
				return true;
			}
		}

		// Check by SAT (first step).
		for (std::size_t axisIndex = 0; axisIndex < PonyMath::Shape::AABB<float>::Axes.size(); ++axisIndex)
		{
			const PonyMath::Core::Vector3<float>& axis = PonyMath::Shape::AABB<float>::Axes[axisIndex];
			const float extent = cameraBox.Box().Extent(axisIndex);

			std::array<float, PonyMath::Shape::AABB<float>::CornerCount> projections;
			for (std::size_t cornerIndex = 0; cornerIndex < PonyMath::Shape::AABB<float>::CornerCount; ++cornerIndex)
			{
				projections[cornerIndex] = PonyMath::Core::Dot(axis, obbCorners[cornerIndex] - cameraBox.Box().Center());
			}

			const auto [min, max] = std::ranges::minmax_element(projections);
			if (*min > extent || *max < -extent)
			{
				return false;
			}
		}

		// Check by SAT (second step).
		for (std::size_t axisIndex = 0; axisIndex < PonyMath::Shape::AABB<float>::Axes.size(); ++axisIndex)
		{
			const PonyMath::Core::Vector3<float>& axis = obb.Axis(axisIndex);
			const float extent = obb.Extent(axisIndex);

			std::array<float, PonyMath::Shape::AABB<float>::CornerCount> projections;
			for (std::size_t cornerIndex = 0; cornerIndex < PonyMath::Shape::AABB<float>::CornerCount; ++cornerIndex)
			{
				projections[cornerIndex] = PonyMath::Core::Dot(axis, cameraBox.Corner(cornerIndex) - obb.Center());
			}

			const auto [min, max] = std::ranges::minmax_element(projections);
			if (*min > extent || *max < -extent)
			{
				return false;
			}
		}

		// Check by SAT (third step).
		for (const PonyMath::Core::Vector3<float>& cameraAxis : PonyMath::Shape::AABB<float>::Axes)
		{
			for (const PonyMath::Core::Vector3<float>& objectAxis : obb.Axes())
			{
				const PonyMath::Core::Vector3<float> axis = PonyMath::Core::Cross(cameraAxis, objectAxis);

				std::array<float, PonyMath::Shape::AABB<float>::CornerCount> cameraProjections;
				std::array<float, PonyMath::Shape::AABB<float>::CornerCount> obbProjections;
				for (std::size_t cornerIndex = 0; cornerIndex < PonyMath::Shape::AABB<float>::CornerCount; ++cornerIndex)
				{
					cameraProjections[cornerIndex] = PonyMath::Core::Dot(axis, cameraBox.Corner(cornerIndex));
					obbProjections[cornerIndex] = PonyMath::Core::Dot(axis, obbCorners[cornerIndex]);
				}

				const auto [cameraMin, cameraMax] = std::ranges::minmax_element(cameraProjections);
				const auto [objectMin, objectMax] = std::ranges::minmax_element(obbProjections);
				if (*cameraMin > *objectMax || *cameraMax < *objectMin)
				{
					return false;
				}
			}
		}

		return true;
	}
}
