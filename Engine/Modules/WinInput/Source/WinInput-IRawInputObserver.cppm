/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Utility/Body.h"

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

export module PonyEngine.WinInput:IRawInputObserver;

export namespace PonyEngine::WinInput
{
	/// @brief Raw input observer.
	class IRawInputObserver
	{
		PONY_INTERFACE_BODY(IRawInputObserver)

		/// @brief Invoked on an input event.
		/// @param rawInput Raw input.
		/// @note The function is always called on a main thread.
		/// @note It's called inside message pump queue.
		virtual void OnInput(const RAWINPUT& rawInput) {}
		/// @brief Invoked on a device connection change.
		/// @param device Device handle.
		/// @param isConnected Is the device connected?
		/// @note The function is always called on a main thread.
		/// @remark It's called inside message pump queue.
		/// @remark It may be called on subscription for already connected devices.
		virtual void OnDeviceConnectionChanged(HANDLE device, bool isConnected) {}
	};
}
