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

export module PonyEngine.WinAPIInput.Windows:IInputDispatcher;

import :IRawInputObserver;

export namespace PonyEngine::WinAPIInput
{
	/// @brief Input dispatcher.
	class IInputDispatcher
	{
		PONY_INTERFACE_BODY(IInputDispatcher)

		/// @brief Adds the observer.
		/// @param observer Observer to add.
		/// @param usagePage Raw input usage page.
		/// @param usage Raw input usage.
		/// @note Must be called on a main thread.
		virtual void AddObserver(IRawInputObserver& observer, USHORT usagePage, USHORT usage) = 0;
		/// @brief Removes the observer.
		/// @param observer Observer to remove.
		/// @param usagePage Raw input usage page.
		/// @param usage Raw input usage.
		/// @note Must be called on a main thread.
		virtual void RemoveObserver(IRawInputObserver& observer, USHORT usagePage, USHORT usage) = 0;
	};
}
