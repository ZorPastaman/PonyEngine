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
		BoxCuller() noexcept;
		[[nodiscard("Pure constructor")]]
		BoxCuller(const PonyMath::Shape::AABB<float>& cameraBox, const PonyMath::Core::Matrix4x4<float>& viewMatrix) noexcept;
		[[nodiscard("Pure constructor")]]
		BoxCuller(const OrthographicParams& orthographic, const PonyMath::Core::Matrix4x4<float>& viewMatrix) noexcept;
		[[nodiscard("Pure constructor")]]
		BoxCuller(const BoxCuller& other) noexcept;
		[[nodiscard("Pure constructor")]]
		BoxCuller(BoxCuller&& other) noexcept;

		~BoxCuller() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual bool IsVisible(const PonyMath::Core::Vector3<float>& point) const noexcept override;
		[[nodiscard("Pure function")]]
		virtual bool IsVisible(const PonyMath::Shape::AABB<float>& modelBounds) const noexcept override;
		[[nodiscard("Pure function")]]
		virtual bool IsVisible(const PonyMath::Shape::AABB<float>& modelBounds, const PonyMath::Core::Quaternion<float>& rotation) const noexcept override;
		[[nodiscard("Pure function")]]
		virtual bool IsVisible(const PonyMath::Shape::AABB<float>& modelBounds, const PonyMath::Core::Matrix4x4<float>& modelMatrix) const noexcept override; // TODO: Require in docs model and view matrices to be trs.

		BoxCuller& operator =(const BoxCuller& other) noexcept = default;
		BoxCuller& operator =(BoxCuller&& other) noexcept = default;

	private:
		[[nodiscard("Pure function")]]
		static std::pair<PonyMath::Core::Vector3<float>, std::array<PonyMath::Core::Vector3<float>, 8>> GetTransformedData(const PonyMath::Shape::AABB<float>& modelBounds, const PonyMath::Core::Matrix4x4<float>& mvMatrix);
		[[nodiscard("Pure function")]]
		static void TransformPoints(PonyMath::Core::Vector3<float>& center, std::span<PonyMath::Core::Vector3<float>, 8> corners, const PonyMath::Core::Matrix4x4<float>& mvMatrix) noexcept;

		[[nodiscard("Pure function")]]
		bool IsVisible(const PonyMath::Core::Vector3<float>& center, std::span<const PonyMath::Core::Vector3<float>, 8> corners) const noexcept;

		CameraBox cameraBox;
		PonyMath::Core::Matrix4x4<float> viewMatrix;
	};
}

namespace PonyEngine::Render
{
	BoxCuller::BoxCuller() noexcept :
		viewMatrix(PonyMath::Core::Matrix4x4<float>::Predefined::Identity)
	{
	}

	BoxCuller::BoxCuller(const PonyMath::Shape::AABB<float>& cameraBox, const PonyMath::Core::Matrix4x4<float>& viewMatrix) noexcept :
		cameraBox(cameraBox),
		viewMatrix(viewMatrix)
	{
	}

	BoxCuller::BoxCuller(const OrthographicParams& orthographic, const PonyMath::Core::Matrix4x4<float>& viewMatrix) noexcept :
		cameraBox(orthographic),
		viewMatrix(viewMatrix)
	{
	}

	BoxCuller::BoxCuller(const BoxCuller& other) noexcept :
		cameraBox(other.cameraBox),
		viewMatrix(other.viewMatrix)
	{
	}

	BoxCuller::BoxCuller(BoxCuller&& other) noexcept :
		cameraBox(std::move(other.cameraBox)),
		viewMatrix(std::move(other.viewMatrix))
	{
	}

	bool BoxCuller::IsVisible(const PonyMath::Core::Vector3<float>& point) const noexcept
	{
		return cameraBox.Box().Contains(PonyMath::Core::TransformPoint(viewMatrix, point));
	}

	bool BoxCuller::IsVisible(const PonyMath::Shape::AABB<float>& modelBounds) const noexcept
	{
		PonyMath::Core::Vector3<float> center = modelBounds.Center();
		std::array<PonyMath::Core::Vector3<float>, 8> corners = modelBounds.Corners();
		TransformPoints(center, corners, viewMatrix);

		return IsVisible(center, corners);
	}

	bool BoxCuller::IsVisible(const PonyMath::Shape::AABB<float>& modelBounds, const PonyMath::Core::Quaternion<float>& rotation) const noexcept
	{
		PonyMath::Core::Vector3<float> center = modelBounds.Center();
		std::array<PonyMath::Core::Vector3<float>, 8> corners = modelBounds.Corners(rotation);
		TransformPoints(center, corners, viewMatrix);

		return IsVisible(center, corners);
	}

	bool BoxCuller::IsVisible(const PonyMath::Shape::AABB<float>& modelBounds, const PonyMath::Core::Matrix4x4<float>& modelMatrix) const noexcept
	{
		PonyMath::Core::Vector3<float> center = modelBounds.Center();
		std::array<PonyMath::Core::Vector3<float>, 8> corners = modelBounds.Corners();
		TransformPoints(center, corners, viewMatrix * modelMatrix);

		return IsVisible(center, corners);
	}

	std::pair<PonyMath::Core::Vector3<float>, std::array<PonyMath::Core::Vector3<float>, 8>> BoxCuller::GetTransformedData(const PonyMath::Shape::AABB<float>& modelBounds, const PonyMath::Core::Matrix4x4<float>& mvMatrix)
	{
		std::pair<PonyMath::Core::Vector3<float>, std::array<PonyMath::Core::Vector3<float>, 8>> data;

		data.first = PonyMath::Core::TransformPoint(mvMatrix, modelBounds.Center());

		const PonyMath::Core::Vector3<float> extentsX = PonyMath::Core::TransformDirection(mvMatrix, PonyMath::Core::Vector3<float>())
	}

	void BoxCuller::TransformPoints(PonyMath::Core::Vector3<float>& center, const std::span<PonyMath::Core::Vector3<float>, 8> corners, const PonyMath::Core::Matrix4x4<float>& mvMatrix) noexcept
	{
		center = PonyMath::Core::TransformPoint(mvMatrix, center);

		for (PonyMath::Core::Vector3<float>& corner : corners)
		{
			corner = PonyMath::Core::TransformPoint(mvMatrix, corner);
		}
	}

	bool BoxCuller::IsVisible(const PonyMath::Core::Vector3<float>& center, const std::span<const PonyMath::Core::Vector3<float>, 8> corners) const noexcept
	{
		for (std::size_t axisIndex = 0; axisIndex < CameraBox::BoxAxes.size(); ++axisIndex)
		{
			const PonyMath::Core::Vector3<float>& normal = CameraBox::BoxAxes[axisIndex];
			const float extent = cameraBox.Box().Extent(axisIndex);

			std::array<float, 8> modelProjections;
			for (std::size_t cornerIndex = 0; cornerIndex < modelProjections.size(); ++cornerIndex)
			{
				modelProjections[cornerIndex] = PonyMath::Core::Dot(normal, corners[cornerIndex] - cameraBox.Box().Center());
			}

			const auto [min, max] = std::ranges::minmax_element(modelProjections);
			if (*min > extent || *max < -extent)
			{
				return false;
			}
		}

		const std::array<PonyMath::Core::Vector3<float>, 3> modelEdges =
		{
			corners[1] - corners[0],
			corners[2] - corners[0],
			corners[4] - corners[0]
		};
		for (const PonyMath::Core::Vector3<float>& modelEdge : modelEdges)
		{
			const float edgeLength = modelEdge.Magnitude();
			if (edgeLength < 0.0001f)
			{
				continue;
			}
			const float halfEdgeLength = edgeLength * 0.5f;
			const PonyMath::Core::Vector3<float> normal = modelEdge * (1.f / edgeLength);

			std::array<float, 8> cameraProjections;
			for (std::size_t cornerIndex = 0; cornerIndex < 8; ++cornerIndex)
			{
				cameraProjections[cornerIndex] = PonyMath::Core::Dot(normal, cameraBox.Corner(cornerIndex) - center);
			}

			const auto [min, max] = std::ranges::minmax_element(cameraProjections);
			if (*min > halfEdgeLength || *max < -halfEdgeLength)
			{
				return false;
			}
		}

		for (const PonyMath::Core::Vector3<float>& cameraEdge : cameraBox.Edges())
		{
			for (const PonyMath::Core::Vector3<float>& modelEdge : modelEdges)
			{
				PonyMath::Core::Vector3<float> normal = PonyMath::Core::Cross(cameraEdge, modelEdge);
				const float normalMagnitude = normal.Magnitude();
				if (normalMagnitude < 0.0001f)
				{
					continue;
				}
				normal *= 1.f / normalMagnitude;

				std::array<float, 8> cameraProjections;
				std::array<float, 8> modelProjections;
				for (std::size_t i = 0; i < 8; ++i)
				{
					cameraProjections[i] = PonyMath::Core::Dot(normal, cameraBox.Corner(i));
					modelProjections[i] = PonyMath::Core::Dot(normal, corners[i]);
				}

				const auto [cameraMin, cameraMax] = std::ranges::minmax_element(cameraProjections);
				const auto [modelMin, modelMax] = std::ranges::minmax_element(modelProjections);
				if (*cameraMin > *modelMax || *cameraMax < *modelMin)
				{
					return false;
				}
			}
		}

		return true;
	}
}
