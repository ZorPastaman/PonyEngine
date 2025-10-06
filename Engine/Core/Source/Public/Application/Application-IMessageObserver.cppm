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

#if PONY_WINDOWS
#include "PonyEngine/Platform/Windows/Framework.h"
#endif

export module PonyEngine.Application:IMessageObserver;

#if PONY_WINDOWS
export namespace PonyEngine::Application::Windows
{
	/// @brief Message observer.
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
#endif
