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

export module PonyEngine.Window.Windows:IMessageObserver;

export namespace PonyEngine::Window::Windows
{
	/// @brief Windows message observer.
	class IMessageObserver
	{
		INTERFACE_BODY(IMessageObserver)

		/// @brief Observes a message.
		/// @param uMsg Message type.
		/// @param wParam wParam.
		/// @param lParam lParam.
		virtual void Observe(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
	};
}
