/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/Windows/Framework.h"
#include "PonyBase/Utility/Interface.h"

export module PonyEngine.Window.Windows:IWindowsWindowSystem;

import <span>;

import PonyEngine.Window;

import :IWindowsMessageObserver;

export namespace PonyEngine::Window
{
	/// @brief Window system for Windows.
	class IWindowsWindowSystem : public IWindowSystem
	{
		INTERFACE_BODY(IWindowsWindowSystem)

		/// @brief Gets the window handle.
		/// @return Window handle.
		[[nodiscard("Pure function")]]
		virtual HWND WindowHandle() const noexcept = 0;

		/// @brief Adds the message observer.
		/// @param observer Observer to add.
		/// @param messageTypes Message types to observe.
		virtual void AddMessageObserver(IWindowsMessageObserver& observer, std::span<UINT> messageTypes) = 0;
		/// @brief Removed the message observer.
		/// @param observer Observer to remove.
		virtual void RemoveMessageObserver(IWindowsMessageObserver& observer) noexcept = 0;
	};
}
