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

#include "PonyDebug/Log/Log.h"

export module PonyEngine.Render.Detail:CameraManager;

import <cstddef>;
import <cstdint>;
import <memory>;
import <vector>;

import PonyDebug.Log;

import PonyEngine.Render;

import :Camera;
import :IPipeline;
import :IRenderSystemContext;

export namespace PonyEngine::Render
{
	/// @brief Camera manager.
	class CameraManager final : public ICameraManager
	{
	public:
		/// @brief Creates a camera manager.
		/// @param renderSystem Render system context.
		[[nodiscard("Pure constuctor")]]
		explicit CameraManager(IRenderSystemContext& renderSystem) noexcept;
		CameraManager(const CameraManager&) = delete;
		CameraManager(CameraManager&&) = delete;

		~CameraManager() noexcept = default;

		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<ICamera> CreateCamera(const CameraParams& cameraParams) override;

		/// @brief Ticks the camera manager.
		void Tick();
		/// @brief Cleans out dead cameras.
		void Clean() noexcept;

		CameraManager& operator =(const CameraManager&) = delete;
		CameraManager& operator =(CameraManager&&) = delete;

	private:
		/// @brief Submits cameras to a pipeline.
		void Submit();

		IRenderSystemContext* renderSystem; ///< Render system context.

		std::vector<std::shared_ptr<Camera>> cameras; ///< Cameras.
	};
}

namespace PonyEngine::Render
{
	CameraManager::CameraManager(IRenderSystemContext& renderSystem) noexcept :
		renderSystem{&renderSystem}
	{
	}

	std::shared_ptr<ICamera> CameraManager::CreateCamera(const CameraParams& cameraParams)
	{
		const auto camera = std::make_shared<Camera>(cameraParams);
		cameras.push_back(camera);

		return camera;
	}

	void CameraManager::Tick()
	{
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Verbose, "Submit.");
		Submit();
	}

	void CameraManager::Clean() noexcept
	{
		for (std::size_t i = cameras.size(); i-- > 0; )
		{
			if (cameras[i].use_count() <= 1L)
			{
				cameras.erase(cameras.cbegin() + i);
			}
		}
	}

	void CameraManager::Submit()
	{
		for (const std::shared_ptr<Camera>& camera : cameras)
		{
			renderSystem->Pipeline().Submit(*camera);
		}
	}
}
