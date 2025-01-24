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

#include "PonyDebug/Log/Log.h"

export module PonyEngine.Render.Direct3D12.Detail:CameraManager;

import <memory>;
import <vector>;

import PonyDebug.Log;

import PonyEngine.Render.Direct3D12;

import :Buffer;
import :Camera;
import :ISubSystemContext;
import :ResourceManager;

export namespace PonyEngine::Render::Direct3D12
{
	class CameraManager final : public ICameraManager
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit CameraManager(ISubSystemContext& d3d12System) noexcept;
		CameraManager(const CameraManager&) = delete;
		CameraManager(CameraManager&&) = delete;

		~CameraManager() noexcept = default;

		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<ICamera> CreateCamera(const CameraParams& cameraParams) override;

		void Tick();

		void Clean() noexcept;

		CameraManager& operator =(const CameraManager&) = delete;
		CameraManager& operator =(CameraManager&&) = delete;

	private:
		ISubSystemContext* d3d12System;

		std::vector<std::shared_ptr<Camera>> cameras;
	};
}

namespace PonyEngine::Render::Direct3D12
{
	CameraManager::CameraManager(ISubSystemContext& d3d12System) noexcept :
		d3d12System{&d3d12System}
	{
	}

	std::shared_ptr<ICamera> CameraManager::CreateCamera(const CameraParams& cameraParams)
	{
		const auto camera = std::make_shared<Camera>(static_cast<PonyMath::Core::Matrix4x4<FLOAT>>(cameraParams.viewMatrix), static_cast<PonyMath::Core::Matrix4x4<FLOAT>>(cameraParams.projectionMatrix), 
			static_cast<PonyMath::Color::RGBA<FLOAT>>(cameraParams.clearColor), static_cast<PonyMath::Shape::Rect<FLOAT>>(cameraParams.viewportRect), cameraParams.sortingOrder);
		cameras.push_back(camera);
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Camera created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(camera.get()));

		return camera;
	}

	void CameraManager::Tick()
	{
		for (const std::shared_ptr<Camera>& camera : cameras)
		{
			d3d12System->GraphicsPipeline().AddCamera(*camera);
		}
	}

	void CameraManager::Clean() noexcept
	{
		for (std::size_t i = cameras.size(); i-- > 0; )
		{
			if (cameras[i].use_count() <= 1L)
			{
				PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Destroy camera at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(cameras[i].get()));
				cameras.erase(cameras.cbegin() + i);
				PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Camera destroyed.");
			}
		}
	}
}
