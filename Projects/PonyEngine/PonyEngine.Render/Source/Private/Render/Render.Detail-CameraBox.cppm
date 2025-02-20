/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Detail:CameraBox;

import <array>;
import <span>;

import PonyMath.Core;
import PonyMath.Shape;

import PonyEngine.Render;

export namespace PonyEngine::Render
{
	class CameraBox final
	{
	public:
		static constexpr std::array<PonyMath::Core::Vector3<float>, 3> BoxAxes =
		{
			PonyMath::Core::Vector3<float>::Predefined::Right,
			PonyMath::Core::Vector3<float>::Predefined::Up,
			PonyMath::Core::Vector3<float>::Predefined::Forward
		};

		[[nodiscard("Pure constructor")]]
		CameraBox() noexcept = default;
		[[nodiscard("Pure constructor")]]
		explicit CameraBox(const PonyMath::Shape::AABB<float>& aabb) noexcept;
		[[nodiscard("Pure constructor")]]
		explicit CameraBox(const OrthographicParams& orthographic) noexcept;
		[[nodiscard("Pure constructor")]]
		CameraBox(const CameraBox& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		CameraBox(CameraBox&& other) noexcept = default;

		~CameraBox() noexcept = default;

		[[nodiscard("Pure function")]]
		const PonyMath::Shape::AABB<float>& Box() const noexcept;
		[[nodiscard("Pure function")]]
		const PonyMath::Core::Vector3<float>& Corner(std::size_t index) const noexcept;
		[[nodiscard("Pure function")]]
		std::span<const PonyMath::Core::Vector3<float>, 8> Corners() const noexcept;
		[[nodiscard("Pure function")]]
		const PonyMath::Core::Vector3<float>& Edge(std::size_t index) const noexcept;
		[[nodiscard("Pure function")]]
		std::span<const PonyMath::Core::Vector3<float>, 3> Edges() const noexcept;

		CameraBox& operator =(const CameraBox& other) noexcept = default;
		CameraBox& operator =(CameraBox&& other) noexcept = default;

	private:
		void UpdateCache() noexcept;

		PonyMath::Shape::AABB<float> cameraBox;
		std::array<PonyMath::Core::Vector3<float>, 8> cameraCorners;
		std::array<PonyMath::Core::Vector3<float>, 3> cameraEdges;
	};
}

namespace PonyEngine::Render
{
	CameraBox::CameraBox(const PonyMath::Shape::AABB<float>& aabb) noexcept :
		cameraBox(aabb)
	{
		UpdateCache();
	}

	CameraBox::CameraBox(const OrthographicParams& orthographic) noexcept
	{
		const auto extents = PonyMath::Core::Vector3<float>(orthographic.width * 0.5f, orthographic.height * 0.5f, (orthographic.farPlane - orthographic.nearPlane) * 0.5f);
		const auto center = PonyMath::Core::Vector3<float>(0.f, 0.f, extents.Z() + orthographic.nearPlane);
		cameraBox = PonyMath::Shape::AABB<float>(center, extents);

		UpdateCache();
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

	const PonyMath::Core::Vector3<float>& CameraBox::Edge(const std::size_t index) const noexcept
	{
		return cameraEdges[index];
	}

	std::span<const PonyMath::Core::Vector3<float>, 3> CameraBox::Edges() const noexcept
	{
		return cameraEdges;
	}

	void CameraBox::UpdateCache() noexcept
	{
		cameraCorners = cameraBox.Corners();
		cameraEdges =
		{
			cameraCorners[1] - cameraCorners[0],
			cameraCorners[2] - cameraCorners[0],
			cameraCorners[4] - cameraCorners[0]
		};
	}
}
