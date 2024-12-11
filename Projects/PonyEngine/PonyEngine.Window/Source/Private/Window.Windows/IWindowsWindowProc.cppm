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

export module PonyEngine.Window.Windows.Detail:IWindowsWindowProc;

export namespace PonyEngine::Window
{
	/// @brief Windows window proc manager.
	class IWindowsWindowProc
	{
		INTERFACE_BODY(IWindowsWindowProc)

		/// @brief Window proc function.
		/// @param uMsg Message.
		/// @param wParam WParam.
		/// @param lParam LParam.
		/// @return Result code.
		virtual LRESULT WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
	};
}
