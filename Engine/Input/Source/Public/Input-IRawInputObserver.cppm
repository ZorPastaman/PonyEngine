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

export module PonyEngine.Input:IRawInputObserver;

import :RawInputEvent;

export namespace PonyEngine::Input
{
	/// @brief Raw input observer.
	class IRawInputObserver
	{
		INTERFACE_BODY(IRawInputObserver)

		/// @brief Invoked on raw input event.
		/// @param inputEvent Raw input event.
		virtual void OnRawInput(const RawInputEvent& inputEvent) = 0;
	};
}
