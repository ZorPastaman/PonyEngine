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
import <span>;
import <utility>;

import PonyMath.Core;
import PonyMath.Shape;

import PonyEngine.Render;

import :CameraBox;

export namespace PonyEngine::Render
{
	class BoxCuller final : public ICuller
	{
	public:
		[[nodiscard("Pure constructor")]]
		BoxCuller() noexcept = default;
		[[nodiscard("Pure constructor")]]
		explicit BoxCuller(const PonyMath::Shape::AABB<float>& cameraBox) noexcept;
		[[nodiscard("Pure constructor")]]
		explicit BoxCuller(const OrthographicParams& orthographic) noexcept;
		[[nodiscard("Pure constructor")]]
		BoxCuller(const BoxCuller& other) noexcept;
		[[nodiscard("Pure constructor")]]
		BoxCuller(BoxCuller&& other) noexcept;

		~BoxCuller() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual bool IsVisible(const PonyMath::Core::Vector3<float>& point) const noexcept override;
		[[nodiscard("Pure function")]]
		virtual bool IsVisible(const PonyMath::Shape::OBB<float>& obb) const noexcept override;

		BoxCuller& operator =(const BoxCuller& other) noexcept = default;
		BoxCuller& operator =(BoxCuller&& other) noexcept = default;

	private:
		[[nodiscard("Pure function")]]
		bool CheckVisibility(const PonyMath::Shape::OBB<float>& obb) const noexcept;

		CameraBox cameraBox;
	};
}

namespace PonyEngine::Render
{
	BoxCuller::BoxCuller(const PonyMath::Shape::AABB<float>& cameraBox) noexcept :
		cameraBox(cameraBox)
	{
	}

	BoxCuller::BoxCuller(const OrthographicParams& orthographic) noexcept :
		cameraBox(orthographic)
	{
	}

	BoxCuller::BoxCuller(const BoxCuller& other) noexcept :
		cameraBox(other.cameraBox)
	{
	}

	BoxCuller::BoxCuller(BoxCuller&& other) noexcept :
		cameraBox(std::move(other.cameraBox))
	{
	}

	bool BoxCuller::IsVisible(const PonyMath::Core::Vector3<float>& point) const noexcept
	{
		return cameraBox.Box().Contains(point);
	}

	bool BoxCuller::IsVisible(const PonyMath::Shape::OBB<float>& obb) const noexcept
	{
		return CheckVisibility(obb);
	}

	bool BoxCuller::CheckVisibility(const PonyMath::Shape::OBB<float>& obb) const noexcept
	{
		const std::array<PonyMath::Core::Vector3<float>, 8> objectCorners = obb.Corners();
		for (std::size_t axisIndex = 0; axisIndex < PonyMath::Shape::AABB<float>::Axes.size(); ++axisIndex)
		{
			const PonyMath::Core::Vector3<float>& axis = PonyMath::Shape::AABB<float>::Axes[axisIndex];
			const float extent = cameraBox.Box().Extent(axisIndex);

			std::array<float, 8> projections;
			for (std::size_t cornerIndex = 0; cornerIndex < 8; ++cornerIndex)
			{
				projections[cornerIndex] = PonyMath::Core::Dot(axis, objectCorners[cornerIndex] - cameraBox.Box().Center());
			}

			const auto [min, max] = std::ranges::minmax_element(projections);
			if (*min > extent || *max < -extent)
			{
				return false;
			}
		}

		for (std::size_t axisIndex = 0; axisIndex < objectCorners.size(); ++axisIndex)
		{
			const PonyMath::Core::Vector3<float>& axis = obb.Axis(axisIndex);
			const float extent = obb.Extent(axisIndex);

			std::array<float, 8> projections;
			for (std::size_t cornerIndex = 0; cornerIndex < 8; ++cornerIndex)
			{
				projections[cornerIndex] = PonyMath::Core::Dot(axis, cameraBox.Corner(cornerIndex) - obb.Center());
			}

			const auto [min, max] = std::ranges::minmax_element(projections);
			if (*min > extent || *max < -extent)
			{
				return false;
			}
		}

		for (const PonyMath::Core::Vector3<float>& cameraAxis : PonyMath::Shape::AABB<float>::Axes)
		{
			for (const PonyMath::Core::Vector3<float>& objectAxis : obb.Axes())
			{
				const PonyMath::Core::Vector3<float> axis = PonyMath::Core::Cross(cameraAxis, objectAxis);

				std::array<float, 8> cameraProjections;
				std::array<float, 8> objectProjections;
				for (std::size_t cornerIndex = 0; cornerIndex < 8; ++cornerIndex)
				{
					cameraProjections[cornerIndex] = PonyMath::Core::Dot(axis, cameraBox.Corner(cornerIndex));
					objectProjections[cornerIndex] = PonyMath::Core::Dot(axis, objectCorners[cornerIndex]);
				}

				const auto [cameraMin, cameraMax] = std::ranges::minmax_element(cameraProjections);
				const auto [objectMin, objectMax] = std::ranges::minmax_element(objectProjections);
				if (*cameraMin > *objectMax || *cameraMax < *objectMin)
				{
					return false;
				}
			}
		}

		return true;
	}
}
