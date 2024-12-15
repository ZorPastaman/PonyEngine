/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/DXGI/Framework.h"
#include "PonyBase/Utility/ObjectBody.h"

export module PonyEngine.Render.DXGI.Detail:IDXGISystemContext;

import PonyDebug.Log;

export namespace PonyEngine::Render
{
	/// @brief DXGI system context.
	class IDXGISystemContext
	{
		INTERFACE_BODY(IDXGISystemContext)

		/// @brief Gets the logger.
		/// @return Logger.
		[[nodiscard("Pure function")]]
		virtual PonyDebug::Log::ILogger& Logger() noexcept = 0;
		/// @brief Gets the logger.
		/// @return Logger.
		[[nodiscard("Pure function")]]
		virtual const PonyDebug::Log::ILogger& Logger() const noexcept = 0;

		/// @brief Gets the DXGI factory.
		/// @return Factory.
		[[nodiscard("Pure function")]]
		virtual IDXGIFactory7& Factory() noexcept = 0;
		/// @brief Gets the DXGI factory.
		/// @return Factory.
		[[nodiscard("Pure function")]]
		virtual const IDXGIFactory7& Factory() const noexcept = 0;

		/// @brief Gets the graphics device.
		/// @return Graphics device.
		[[nodiscard("Pure function")]]
		virtual IUnknown& Device() noexcept = 0;
		/// @brief Gets the graphics device.
		/// @return Graphics device.
		[[nodiscard("Pure function")]]
		virtual const IUnknown& Device() const noexcept = 0;
	};
}
