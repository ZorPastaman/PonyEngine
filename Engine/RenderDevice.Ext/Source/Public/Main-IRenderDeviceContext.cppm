/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Object/Body.h"

export module PonyEngine.RenderDevice.Ext:IRenderDeviceContext;

import PonyEngine.Application.Ext;
import PonyEngine.Log;
import PonyEngine.RenderDevice;

export namespace PonyEngine::RenderDevice
{
	class IRenderDeviceContext
	{
		PONY_INTERFACE_BODY(IRenderDeviceContext)

		/// @brief Gets the application context.
		/// @return Application context.
		[[nodiscard("Pure function")]]
		virtual Application::IApplicationContext& Application() noexcept = 0;
		/// @brief Gets the application context.
		/// @return Application context.
		[[nodiscard("Pure function")]]
		virtual const Application::IApplicationContext& Application() const noexcept = 0;

		/// @brief Gets the logger.
		/// @return Logger.
		[[nodiscard("Pure function")]]
		virtual Log::ILogger& Logger() noexcept = 0;
		/// @brief Gets the logger.
		/// @return Logger.
		[[nodiscard("Pure function")]]
		virtual const Log::ILogger& Logger() const noexcept = 0;

		[[nodiscard("Wierd call")]]
		virtual struct TextureFormatId TextureFormatId(std::string_view textureFormat) = 0;
		[[nodiscard("Pure function")]]
		virtual std::string_view TextureFormat(struct TextureFormatId textureFormatId) const = 0;
		[[nodiscard("Pure function")]]
		virtual bool IsValid(struct TextureFormatId textureFormatId) const noexcept = 0;
	};
}
