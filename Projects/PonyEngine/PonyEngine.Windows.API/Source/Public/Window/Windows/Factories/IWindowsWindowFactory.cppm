/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window.Windows.Factories:IWindowsWindowFactory;

import PonyEngine.Window.Factory;

import :WindowsWindowParams;

export namespace PonyEngine::Window
{
	/// @brief Windows window factory.
	class IWindowsWindowFactory : public IWindowFactory
	{
	public:
		IWindowsWindowFactory(const IWindowsWindowFactory&) = delete;
		IWindowsWindowFactory(IWindowsWindowFactory&&) = delete;

		/// @brief Gets the next Windows window params.
		/// @return Next Windows window params.
		[[nodiscard("Pure function")]]
		virtual WindowsWindowParams& NextWindowsWindowParams() noexcept = 0;
		/// @brief Gets the next Windows window params.
		/// @return Next Windows window params.
		[[nodiscard("Pure function")]]
		virtual const WindowsWindowParams& NextWindowsWindowParams() const noexcept = 0;

		IWindowsWindowFactory& operator =(const IWindowsWindowFactory&) = delete;
		IWindowsWindowFactory& operator =(IWindowsWindowFactory&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IWindowsWindowFactory() noexcept = default;

		~IWindowsWindowFactory() noexcept = default;
	};
}
