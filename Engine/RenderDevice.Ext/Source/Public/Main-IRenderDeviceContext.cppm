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
	/// @brief Render device context.
	class IRenderDeviceContext
	{
		PONY_INTERFACE_BODY(IRenderDeviceContext)

		/// @brief Gets the application context.
		/// @return Application context.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual Application::IApplicationContext& Application() noexcept = 0;
		/// @brief Gets the application context.
		/// @return Application context.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual const Application::IApplicationContext& Application() const noexcept = 0;

		/// @brief Gets the logger.
		/// @return Logger.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual Log::ILogger& Logger() noexcept = 0;
		/// @brief Gets the logger.
		/// @return Logger.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual const Log::ILogger& Logger() const noexcept = 0;

		/// @brief Gets a texture format ID.
		/// @param textureFormat Texture format.
		/// @return Texture format ID.
		/// @note This function mustn't be called on different threads at the same time.
		/// @note This function mustn't be called while @p TextureFormat(TextureFormatId) or @p IsValid(TextureFormatId) is executing.
		/// @note It's recommended that the backend get all texture format ids on its initialization.
		[[nodiscard("Wierd call")]]
		virtual struct TextureFormatID TextureFormatId(std::string_view textureFormat) = 0;
		/// @brief Gets a texture format.
		/// @param textureFormatId Texture format ID.
		/// @return Texture format.
		/// @note The function mustn't be called concurrently with the @p TextureFormatId().
		[[nodiscard("Pure function")]]
		virtual std::string_view TextureFormat(struct TextureFormatID textureFormatId) const = 0;
		/// @brief Checks if the texture format ID is valid.
		/// @param textureFormatId Texture format ID.
		/// @return @a True if it's valid; @a false otherwise.
		/// @note The function mustn't be called concurrently with the @p TextureFormatId().
		[[nodiscard("Pure function")]]
		virtual bool IsValid(struct TextureFormatID textureFormatId) const noexcept = 0;
	};
}
