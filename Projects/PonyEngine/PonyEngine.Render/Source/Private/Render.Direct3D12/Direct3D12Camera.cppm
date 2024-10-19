/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/Direct3D12/Framework.h"

export module PonyEngine.Render.Direct3D12.Implementation:Direct3D12Camera;

import PonyMath.Core;

import PonyEngine.Screen;

import :Direct3D12CameraParams;

export namespace PonyEngine::Render
{
	class Direct3D12Camera final
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit Direct3D12Camera(const Direct3D12CameraParams& cameraParams, const Screen::Resolution<UINT>& resolution) noexcept;
		[[nodiscard("Pure constructor")]]
		Direct3D12Camera(const Direct3D12Camera& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Direct3D12Camera(Direct3D12Camera&& other) noexcept = default;

		~Direct3D12Camera() noexcept = default;

		[[nodiscard("Pure function")]]
		const Direct3D12CameraParams& CameraParams() const noexcept;
		void CameraParams(const Direct3D12CameraParams& cameraParams) noexcept;

		[[nodiscard("Pure function")]]
		const D3D12_VIEWPORT& ViewPort() const noexcept;
		[[nodiscard("Pure function")]]
		const D3D12_RECT& ViewRect() const noexcept;

		[[nodiscard("Pure function")]]
		PonyMath::Core::Matrix4x4<float>& TrsMatrix() noexcept; // TODO: Use float instead of FLOAT everywhere it's possible
		[[nodiscard("Pure function")]]
		const PonyMath::Core::Matrix4x4<float>& TrsMatrix() const noexcept;
		[[nodiscard("Pure function")]]
		const PonyMath::Core::Matrix4x4<float>& ProjectionMatrix() const noexcept;

		Direct3D12Camera& operator =(const Direct3D12Camera& other) noexcept = default;
		Direct3D12Camera& operator =(Direct3D12Camera&& other) noexcept = default;

	private:
		Screen::Resolution<UINT> resolution;
		Direct3D12CameraParams cameraParams;

		D3D12_VIEWPORT viewPort;
		D3D12_RECT viewRect;

		PonyMath::Core::Matrix4x4<FLOAT> trsMatrix;
		PonyMath::Core::Matrix4x4<FLOAT> projectionMatrix;
	};
}

namespace PonyEngine::Render
{
	Direct3D12Camera::Direct3D12Camera(const Direct3D12CameraParams& cameraParams, const Screen::Resolution<UINT>& resolution) noexcept :
		resolution(resolution),
		cameraParams(cameraParams),
		viewPort{.TopLeftX = 0.f, .TopLeftY = 0.f, .Width = static_cast<FLOAT>(resolution.Width()), .Height = static_cast<FLOAT>(resolution.Height()), .MinDepth = D3D12_MIN_DEPTH, .MaxDepth = D3D12_MAX_DEPTH},
		viewRect{.left = 0L, .top = 0L, .right = static_cast<LONG>(resolution.Width()), .bottom = static_cast<LONG>(resolution.Height())},
		trsMatrix(PonyMath::Core::Matrix4x4<float>::Predefined::Identity),
		projectionMatrix(PonyMath::Core::PerspectiveMatrix(cameraParams.fov, resolution.Aspect<FLOAT>(), cameraParams.nearPlane, cameraParams.farPlane))
	{
	}

	const Direct3D12CameraParams& Direct3D12Camera::CameraParams() const noexcept
	{
		return cameraParams;
	}

	void Direct3D12Camera::CameraParams(const Direct3D12CameraParams& cameraParams) noexcept
	{
		this->cameraParams = cameraParams;
		projectionMatrix = PonyMath::Core::PerspectiveMatrix(cameraParams.fov, resolution.Aspect<FLOAT>(), cameraParams.nearPlane, cameraParams.farPlane);
	}

	const D3D12_VIEWPORT& Direct3D12Camera::ViewPort() const noexcept
	{
		return viewPort;
	}

	const D3D12_RECT& Direct3D12Camera::ViewRect() const noexcept
	{
		return viewRect;
	}

	PonyMath::Core::Matrix4x4<float>& Direct3D12Camera::TrsMatrix() noexcept
	{
		return trsMatrix;
	}

	const PonyMath::Core::Matrix4x4<float>& Direct3D12Camera::TrsMatrix() const noexcept
	{
		return trsMatrix;
	}

	const PonyMath::Core::Matrix4x4<float>& Direct3D12Camera::ProjectionMatrix() const noexcept
	{
		return projectionMatrix;
	}
}
