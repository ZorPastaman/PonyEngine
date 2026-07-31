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

export module PonyEngine.WinAPIInput.Windows:IRawInputObserver;

export namespace PonyEngine::WinAPIInput
{
	/// @brief Raw input observer.
	class IRawInputObserver
	{
		PONY_INTERFACE_BODY(IRawInputObserver)

		/// @brief Invoked on an input event.
		/// @param rawInput Raw input.
		/// @note The function is always called on a main thread.
		virtual void OnInput(const RAWINPUT& rawInput) {}
		/// @brief Invoked on a device connection change.
		/// @param device Device handle.
		/// @param isConnected Is the device connected?
		/// @note The function is always called on a main thread.
		virtual void OnDeviceConnectionChanged(HANDLE device, bool isConnected) {}
	};
}
