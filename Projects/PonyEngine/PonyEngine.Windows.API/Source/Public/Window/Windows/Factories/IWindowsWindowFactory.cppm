/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window.Windows.Factories:IWindowsWindowFactory;

import PonyEngine.Window.Factories;

import :WindowsWindowParams;

export namespace PonyEngine::Window
{
	/// @brief Windows window factory.
	class IWindowsWindowFactory : public IWindowFactory
	{
	public:
		/// @brief Gets a next Windows window params.
		/// @return Next Windows window params.
		[[nodiscard("Pure function")]]
		virtual WindowsWindowParams& NextWindowsWindowParams() noexcept = 0;
		/// @brief Gets a next Windows window params.
		/// @return Next Windows window params.
		[[nodiscard("Pure function")]]
		virtual const WindowsWindowParams& NextWindowsWindowParams() const noexcept = 0;

	protected:
		~IWindowsWindowFactory() noexcept = default;
	};
}
