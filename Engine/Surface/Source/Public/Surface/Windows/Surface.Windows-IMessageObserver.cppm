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

export module PonyEngine.Surface.Windows:IMessageObserver;

export namespace PonyEngine::Surface::Windows
{
	/// @brief Window message observer.
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
