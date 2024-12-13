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
#include "PonyBase/Utility/ObjectBody.h"

export module PonyEngine.Window.Windows:IWindowsRawInputManager;

import <span>;

import :IWindowsRawInputObserver;

export namespace PonyEngine::Window
{
	class IWindowsRawInputManager
	{
		INTERFACE_BODY(IWindowsRawInputManager)

		/// @brief Adds the raw input observer.
		/// @note It's not supported to add the same raw input observer twice in a row. If you need to update its raw input types, you should remove it first.
		/// @param observer Observer to add.
		/// @param rawInputTypes Raw input types. RIM_TYPEMOUSE and RIM_TYPEKEYBOARD are supported only.
		virtual void AddRawInputObserver(IWindowsRawInputObserver& observer, std::span<const DWORD> rawInputTypes) = 0;
		/// @brief Removes the raw input observer.
		/// @param observer Observer to remove.
		virtual void RemoveRawInputObserver(IWindowsRawInputObserver& observer) noexcept = 0;
	};
}
