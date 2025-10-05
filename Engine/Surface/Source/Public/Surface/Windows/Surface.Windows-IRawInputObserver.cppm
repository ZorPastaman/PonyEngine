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
	/// @brief Window raw input observer.
	class IRawInputObserver
	{
		INTERFACE_BODY(IRawInputObserver)

		/// @brief Observes raw input.
		/// @param input Raw input to observe.
		virtual void Observe(const RAWINPUT& input) = 0;
	};
}
