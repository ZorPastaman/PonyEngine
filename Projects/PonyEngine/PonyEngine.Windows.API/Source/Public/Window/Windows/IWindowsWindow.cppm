/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window.Windows:IWindowsWindow;

import <windows.h>;

import PonyEngine.Window;

namespace PonyEngine::Window
{
	export class IWindowsWindow : public IWindow
	{
	public:
		virtual HWND GetWindowHandle() const noexcept = 0;

	protected:
		inline virtual ~IWindowsWindow() noexcept = default;
	};
}
