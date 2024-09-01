/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Platform/Windows/Framework.h"

export module PonyEngine.Window.Windows:IWindowsWindowSystem;

import PonyEngine.Window;

export namespace PonyEngine::Window
{
	/// @brief Window system for Windows.
	class IWindowsWindowSystem : public IWindowSystem
	{
	public:
		IWindowsWindowSystem(const IWindowsWindowSystem&) = delete;
		IWindowsWindowSystem(IWindowsWindowSystem&&) = delete;

		/// @brief Gets the window handle.
		/// @return Window handle.
		[[nodiscard("Pure function")]]
		virtual HWND WindowHandle() const noexcept = 0;

		IWindowsWindowSystem& operator =(const IWindowsWindowSystem&) = delete;
		IWindowsWindowSystem& operator =(IWindowsWindowSystem&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IWindowsWindowSystem() noexcept = default;

		~IWindowsWindowSystem() noexcept = default;
	};
}
