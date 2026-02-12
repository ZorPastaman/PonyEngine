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

export module PonyEngine.RenderDevice:IRenderDeviceServiceObserver;

import std;

export namespace PonyEngine::RenderDevice
{
	class IRenderDeviceServiceObserver
	{
		PONY_INTERFACE_BODY(IRenderDeviceServiceObserver)

		virtual void OnBeforeBackendSwitch(std::optional<std::size_t> fromBackendIndex, std::optional<std::size_t> toBackendIndex) {}
		virtual void OnAfterBackendSwitch(std::optional<std::size_t> fromBackendIndex, std::optional<std::size_t> toBackendIndex) {}
	};
}
