/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Detail:BoxCuller;

import <utility>;

import PonyMath.Core;
import PonyMath.Shape;

import PonyEngine.Render;

export namespace PonyEngine::Render
{
	class BoxCuller final : public ICuller
	{
	public:
		[[nodiscard("Pure constructor")]]
		BoxCuller() noexcept;
		[[nodiscard("Pure constructor")]]
		BoxCuller(const PonyMath::Shape::Box<float>& box, const PonyMath::Core::Matrix4x4<float>& viewMatrix) noexcept;
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
		virtual bool IsVisible(const PonyMath::Shape::Box<float>& box) const noexcept override;

		BoxCuller& operator =(const BoxCuller& other) noexcept = default;
		BoxCuller& operator =(BoxCuller&& other) noexcept = default;

	private:
		PonyMath::Shape::Box<float> box;
		PonyMath::Core::Matrix4x4<float> viewMatrix;
	};
}

namespace PonyEngine::Render
{
	BoxCuller::BoxCuller() noexcept :
		viewMatrix(PonyMath::Core::Matrix4x4<float>::Predefined::Identity)
	{
	}

	BoxCuller::BoxCuller(const PonyMath::Shape::Box<float>& box, const PonyMath::Core::Matrix4x4<float>& viewMatrix) noexcept :
		box(box),
		viewMatrix(viewMatrix)
	{
	}

	BoxCuller::BoxCuller(const OrthographicParams& orthographic, const PonyMath::Core::Matrix4x4<float>& viewMatrix) noexcept :
		box(PonyMath::Core::Vector3<float>(-orthographic.width * 0.5f, -orthographic.height * 0.5f, orthographic.nearPlane), 
			PonyMath::Core::Vector3<float>(orthographic.width, orthographic.height, orthographic.farPlane - orthographic.nearPlane)),
		viewMatrix(viewMatrix)
	{
	}

	BoxCuller::BoxCuller(const BoxCuller& other) noexcept :
		box(other.box),
		viewMatrix(other.viewMatrix)
	{
	}

	BoxCuller::BoxCuller(BoxCuller&& other) noexcept :
		box(std::move(other.box)),
		viewMatrix(std::move(other.viewMatrix))
	{
	}

	bool BoxCuller::IsVisible(const PonyMath::Core::Vector3<float>& point) const noexcept
	{
		return box.Contains(PonyMath::Core::TransformPoint(viewMatrix, point));
	}

	bool BoxCuller::IsVisible(const PonyMath::Shape::Box<float>& box) const noexcept
	{
		return true;
	}
}
