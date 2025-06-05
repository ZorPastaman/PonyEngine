/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/ObjectBody.h"

export module PonyEngine.Render:ICameraManager;

import <memory>;

import :CameraParams;
import :ICamera;

export namespace PonyEngine::Render
{
	/// @brief Camera manager.
	class ICameraManager
	{
		INTERFACE_BODY(ICameraManager)

		/// @brief Creates a camera.
		/// @param cameraParams Camera parameters.
		/// @return Camera.
		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<ICamera> CreateCamera(const CameraParams& cameraParams) = 0;
	};
}
