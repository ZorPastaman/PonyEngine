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
	/// @brief Render device service observer.
	class IRenderDeviceServiceObserver
	{
		PONY_INTERFACE_BODY(IRenderDeviceServiceObserver)

		/// @brief Invoked before switching a backend.
		/// @details You must release all the backend-dependent resources on this event.
		/// @param fromBackendIndex Previous backend index.
		/// @param toBackendIndex Next backend index.
		virtual void OnBeforeBackendSwitch(std::optional<std::size_t> fromBackendIndex, std::optional<std::size_t> toBackendIndex) {}
		/// @brief Invoked after switching a backend.
		/// @param fromBackendIndex Previous backend index.
		/// @param toBackendIndex Next backend index.
		virtual void OnAfterBackendSwitch(std::optional<std::size_t> fromBackendIndex, std::optional<std::size_t> toBackendIndex) {}
	};
}
