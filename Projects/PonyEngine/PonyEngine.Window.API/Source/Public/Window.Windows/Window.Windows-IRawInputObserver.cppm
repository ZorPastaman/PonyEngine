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

export module PonyEngine.Window.Windows:IRawInputObserver;

export namespace PonyEngine::Window::Windows
{
	/// @brief Windows raw input observer.
	class IRawInputObserver
	{
		INTERFACE_BODY(IRawInputObserver)

		/// @brief Observes raw input.
		/// @param input Raw input to observe.
		virtual void Observe(const RAWINPUT& input) = 0;
	};
}
