/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyDebug/Log/Log.h"

export module PonyEngine.Render.Direct3D12.Detail:CameraManager;

import <cstdint>;
import <memory>;
import <vector>;

import PonyDebug.Log;

import PonyEngine.Render.Direct3D12;

import :Camera;
import :ISubSystemContext;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 camera manager.
	class CameraManager final : public ICameraManager
	{
	public:
		/// @brief Creates a camera manager.
		/// @param d3d12System Direct3D12 system context.
		[[nodiscard("Pure constructor")]]
		explicit CameraManager(ISubSystemContext& d3d12System) noexcept;
		CameraManager(const CameraManager&) = delete;
		CameraManager(CameraManager&&) = delete;

		~CameraManager() noexcept = default;

		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<ICamera> CreateCamera(const CameraParams& cameraParams) override;

		/// @brief Cleans out of dead cameras.
		void Clean() noexcept;

		CameraManager& operator =(const CameraManager&) = delete;
		CameraManager& operator =(CameraManager&&) = delete;

	private:
		ISubSystemContext* d3d12System; ///< Direct3D12 system context.

		std::vector<std::shared_ptr<Camera>> cameras; ///< Cameras.
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
		const auto camera = std::make_shared<Camera>(cameraParams);
		cameras.push_back(camera);
		d3d12System->GraphicsPipeline().AddCamera(*camera);
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Camera created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(camera.get()));

		return camera;
	}

	void CameraManager::Clean() noexcept
	{
		for (std::size_t i = cameras.size(); i-- > 0; )
		{
			if (const std::shared_ptr<Camera>& camera = cameras[i]; camera.use_count() <= 1L)
			{
				PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Destroy camera at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(camera.get()));
				d3d12System->GraphicsPipeline().RemoveCamera(*camera);
				cameras.erase(cameras.cbegin() + i);
				PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Camera destroyed.");
			}
		}
	}
}
