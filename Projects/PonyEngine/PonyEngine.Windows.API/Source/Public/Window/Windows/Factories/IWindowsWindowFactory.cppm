/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window.Windows.Factories:IWindowsWindowFactory;

import PonyEngine.Core;
import PonyEngine.Window.Factories;
import PonyEngine.Window.Windows;

export namespace PonyEngine::Window
{
	/// @brief Windows window factory.
	class IWindowsWindowFactory : public IWindowFactory
	{
	public:
		/// @brief Gets a cmdShow of the next window.
		/// @return CmdShow.
		[[nodiscard("Pure function")]]
		virtual int GetCmdShow() const noexcept = 0;
		/// @brief Sets a cmdShow of the next window.
		/// @param cmdShow CmdShow.
		virtual void SetCmdShow(int cmdShow) noexcept = 0;

	protected:
		~IWindowsWindowFactory() noexcept = default;
	};
}
