/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Platform/Windows/Framework.h"
#include "PonyEngine/Utility/ObjectBody.h"

export module PonyEngine.Surface.Windows:ISurfaceService;

import std;

import PonyEngine.Surface;

import :IMessageObserver;
import :IRawInputObserver;

export namespace PonyEngine::Surface::Windows
{
	/// @brief Windows surface service.
	class ISurfaceService : public Surface::ISurfaceService
	{
		INTERFACE_BODY(ISurfaceService)

		/// @brief Gets the native handle.
		/// @return Native handle.
		[[nodiscard("Pure function")]]
		virtual HWND Handle() noexcept = 0;

		/// @brief Adds the message observer.
		/// @param observer Observer to add.
		/// @param messageType Message type to observe. Examples: WM_KEYDOWN, WM_KEYUP.
		virtual void AddMessageObserver(IMessageObserver& observer, UINT messageType) = 0;
		/// @brief Adds the message observer.
		/// @param observer Observer to add.
		/// @param messageTypes Message types to observe. Examples: WM_KEYDOWN, WM_KEYUP.
		virtual void AddMessageObserver(IMessageObserver& observer, std::span<const UINT> messageTypes) = 0;
		/// @brief Removes the message observer from the specified message type.
		/// @param observer Observer to remove.
		/// @param messageType Message type to observe. Examples: WM_KEYDOWN, WM_KEYUP.
		virtual void RemoveMessageObserver(IMessageObserver& observer, UINT messageType) = 0;
		/// @brief Removes the message observer from the specified message types.
		/// @param observer Observer to remove.
		/// @param messageTypes Message types to observe. Examples: WM_KEYDOWN, WM_KEYUP.
		virtual void RemoveMessageObserver(IMessageObserver& observer, std::span<const UINT> messageTypes) = 0;
		/// @brief Removes the message observer from all the message types.
		/// @param observer Observer to remove.
		virtual void RemoveMessageObserver(IMessageObserver& observer) = 0;

		/// @brief Adds the raw input observer.
		/// @param observer Observer to add.
		/// @param rawInputType Raw input type to observe. Examples: RIM_TYPEMOUSE and RIM_TYPEKEYBOARD.
		virtual void AddRawInputObserver(IRawInputObserver& observer, DWORD rawInputType) = 0;
		/// @brief Adds the raw input observer.
		/// @param observer Observer to add.
		/// @param rawInputTypes Raw input types to observe. Examples: RIM_TYPEMOUSE and RIM_TYPEKEYBOARD.
		virtual void AddRawInputObserver(IRawInputObserver& observer, std::span<const DWORD> rawInputTypes) = 0;
		/// @brief Removes the raw input observer from the specified message type.
		/// @param observer Observer to remove.
		/// @param rawInputType Raw input type to observe. Examples: RIM_TYPEMOUSE and RIM_TYPEKEYBOARD.
		virtual void RemoveRawInputObserver(IRawInputObserver& observer, DWORD rawInputType) = 0;
		/// @brief Removes the raw input observer from the specified message types.
		/// @param observer Observer to remove.
		/// @param rawInputTypes Raw input types to observe. Examples: RIM_TYPEMOUSE and RIM_TYPEKEYBOARD.
		virtual void RemoveRawInputObserver(IRawInputObserver& observer, std::span<const DWORD> rawInputTypes) = 0;
		/// @brief Removes the raw input observer from all the message types.
		/// @param observer Observer to remove.
		virtual void RemoveRawInputObserver(IRawInputObserver& observer) = 0;
	};
}
