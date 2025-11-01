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

export module PonyEngine.Input:IInputObserver;

import :InputEvent;

export namespace PonyEngine::Input
{
	/// @brief Input observer.
	class IInputObserver
	{
		INTERFACE_BODY(IInputObserver)

		/// @brief Invoked on each tick.
		/// @param inputEvent Input event.
		virtual void OnInput(const InputEvent& inputEvent) = 0;
	};
}
