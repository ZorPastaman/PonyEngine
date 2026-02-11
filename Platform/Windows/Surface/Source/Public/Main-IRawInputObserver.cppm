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
#include "PonyEngine/Platform/Windows/Framework.h"

export module PonyEngine.Surface.Windows:IRawInputObserver;

export namespace PonyEngine::Surface::Windows
{
	/// @brief Windows raw input observer.
	/// @note All the observer functions are always called on a main thread.
	class IRawInputObserver
	{
		PONY_INTERFACE_BODY(IRawInputObserver)

		/// @brief Observes raw input.
		/// @param rawInput Raw input to observe.
		virtual void Observe(const RAWINPUT& rawInput) {}

		/// @brief Invoked on a device connection change.
		/// @param device Device handle.
		/// @param isConnected Is the device connected?
		virtual void OnDeviceConnectionChanged(HANDLE device, bool isConnected) {}
	};
}
