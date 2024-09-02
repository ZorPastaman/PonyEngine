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

export module PonyEngine.Window.Windows.Implementation:IWindowProc;

export namespace PonyEngine::Window
{
	/// @brief Window proc manager.
	class IWindowProc
	{
	public:
		IWindowProc(const IWindowProc&) = delete;
		IWindowProc(IWindowProc&&) = delete;

		/// @brief Window proc function.
		/// @param uMsg Message.
		/// @param wParam WParam.
		/// @param lParam LParam.
		/// @return Result code.
		virtual LRESULT WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

		IWindowProc& operator =(const IWindowProc&) = delete;
		IWindowProc& operator =(IWindowProc&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IWindowProc() noexcept = default;

		~IWindowProc() noexcept = default;
	};
}
