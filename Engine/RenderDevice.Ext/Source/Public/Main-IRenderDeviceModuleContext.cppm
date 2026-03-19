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

export module PonyEngine.RenderDevice.Ext:IRenderDeviceModuleContext;

import std;

import :BackendHandle;
import :IBackend;
import :IRenderDeviceContext;

export namespace PonyEngine::RenderDevice
{
	/// @brief Render device module context.
	class IRenderDeviceModuleContext
	{
		PONY_INTERFACE_BODY(IRenderDeviceModuleContext)

		/// @brief Adds a backend.
		/// @param factory Backend factory.
		/// @return Backend handle. Must be used to remove a backend before a destruction of the render device.
		/// @note The function must be called on a main thread.
		[[nodiscard("Must be used to remove")]]
		virtual BackendHandle AddBackend(const std::function<std::shared_ptr<IBackend>(IRenderDeviceContext&)>& factory) = 0;
		/// @brief Removes a backend.
		/// @param backendHandle Backend handle.
		/// @note The function must be called on a main thread.
		virtual void RemoveBackend(BackendHandle backendHandle) = 0;
	};
}
