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

export module PonyEngine.Surface.Windows:ISurfaceService;

import std;

import PonyEngine.Math;
import PonyEngine.Surface;

import :IRawInputObserver;

export namespace PonyEngine::Surface::Windows
{
	/// @brief Windows surface service.
	class ISurfaceService : public Surface::ISurfaceService
	{
		PONY_INTERFACE_BODY(ISurfaceService)

		/// @brief Gets the native handle.
		/// @return Native handle.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual HWND Handle() noexcept = 0;

		/// @brief Gets a last message time.
		/// @return Last message time.
		/// @note Must be called on a main thread only.
		[[nodiscard("Pure function")]]
		virtual std::chrono::time_point<std::chrono::steady_clock> LastMessageTime() const noexcept = 0;
		/// @brief Gets the cursor position of the last message.
		/// @return Cursor position in the screen coordinates of the last message.
		/// @note Must be called on a main thread only.
		[[nodiscard("Pure function")]]
		virtual Math::Vector2<std::int32_t> LastMessageCursorPosition() const noexcept = 0;

		/// @brief Adds the raw input observer.
		/// @param observer Observer to add.
		/// @param usagePage Usage page.
		/// @param usage Usage.
		/// @note Must be called on a main thread only.
		virtual void AddRawInputObserver(IRawInputObserver& observer, USHORT usagePage, USHORT usage) = 0;
		/// @brief Adds the raw input observer.
		/// @param observer Observer to add.
		/// @param rawInputUsages Pairs of usage page and usage.
		/// @note Must be called on a main thread only.
		virtual void AddRawInputObserver(IRawInputObserver& observer, std::span<const std::pair<USHORT, USHORT>> rawInputUsages) = 0;
		/// @brief Removes the raw input observer from the specified message type.
		/// @param observer Observer to remove.
		/// @param usagePage Usage page.
		/// @param usage Usage.
		/// @note Must be called on a main thread only.
		virtual void RemoveRawInputObserver(IRawInputObserver& observer, USHORT usagePage, USHORT usage) noexcept = 0;
		/// @brief Removes the raw input observer from the specified message types.
		/// @param observer Observer to remove.
		/// @param rawInputUsages Pairs of usage page and usage.
		/// @note Must be called on a main thread only.
		virtual void RemoveRawInputObserver(IRawInputObserver& observer, std::span<const std::pair<USHORT, USHORT>> rawInputUsages) noexcept = 0;
		/// @brief Removes the raw input observer from all the message types.
		/// @param observer Observer to remove.
		/// @note Must be called on a main thread only.
		virtual void RemoveRawInputObserver(IRawInputObserver& observer) noexcept = 0;
	};
}
