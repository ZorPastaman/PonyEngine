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

export module PonyEngine.Window.Windows.Detail:IWindowProc;

export namespace PonyEngine::Window
{
	/// @brief Window proc manager.
	class IWindowProc // TODO: The interface must be public for custom WindowsClasses.
	{
		INTERFACE_BODY(IWindowProc)

		/// @brief Window proc function.
		/// @param uMsg Message.
		/// @param wParam WParam.
		/// @param lParam LParam.
		/// @return Result code.
		virtual LRESULT WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
	};
}
