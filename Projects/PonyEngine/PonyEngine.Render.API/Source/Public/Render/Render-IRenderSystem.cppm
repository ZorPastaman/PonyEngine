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

export module PonyEngine.Render:IRenderSystem;

import :ICameraManager;
import :IRenderObjectManager;

export namespace PonyEngine::Render
{
	/// @brief Render system.
	class IRenderSystem
	{
		INTERFACE_BODY(IRenderSystem)

		/// @brief Gets the camera manager.
		/// @return Camera manager.
		[[nodiscard("Pure function")]]
		virtual ICameraManager& CameraManager() noexcept = 0;
		/// @brief Gets the camera manager.
		/// @return Camera manager.
		[[nodiscard("Pure function")]]
		virtual const ICameraManager& CameraManager() const noexcept = 0;

		/// @brief Gets the render object manager.
		/// @return Render object manager.
		[[nodiscard("Pure function")]]
		virtual IRenderObjectManager& RenderObjectManager() noexcept = 0;
		/// @brief Gets the render object manager.
		/// @return Render object manager.
		[[nodiscard("Pure function")]]
		virtual const IRenderObjectManager& RenderObjectManager() const noexcept = 0;
	};
}
