/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "Platform/Windows/Framework.h"

export module PonyEngine.Window.Windows.Implementation:IWindowProc;

namespace PonyEngine::Window
{
	/// @brief Window proc manager.
	export class IWindowProc
	{
	public:
		/// @brief Window proc function.
		/// @param uMsg Message.
		/// @param wParam WParam.
		/// @param lParam LParam.
		/// @return Result code.
		virtual LRESULT WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

	protected:
		inline virtual ~IWindowProc() noexcept = default;
	};
}