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

export namespace PonyEngine::Render
{
	class IRenderDeviceModuleContext
	{
		PONY_INTERFACE_BODY(IRenderDeviceModuleContext)

		[[nodiscard("Must be used to remove")]]
		virtual BackendHandle AddBackend(const std::function<std::shared_ptr<IBackend>(IRenderDeviceContext&)>& factory) = 0;
		virtual void RemoveBackend(BackendHandle backendHandle) = 0;
	};
}
