/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window.Windows.Factory:IWindowsWindowSystemFactory;

import :WindowsWindowParams;

export namespace PonyEngine::Window
{
	/// @brief Window system for Windows factory.
	class IWindowsWindowSystemFactory
	{
	public:
		IWindowsWindowSystemFactory(const IWindowsWindowSystemFactory&) = delete;
		IWindowsWindowSystemFactory(IWindowsWindowSystemFactory&&) = delete;

		/// @brief Gets the next window params.
		/// @return Next window params.
		[[nodiscard("Pure function")]]
		virtual WindowsWindowParams& WindowParams() noexcept = 0;
		/// @brief Gets the next window params.
		/// @return Next window params.
		[[nodiscard("Pure function")]]
		virtual const WindowsWindowParams& WindowParams() const noexcept = 0;

		IWindowsWindowSystemFactory& operator =(const IWindowsWindowSystemFactory&) = delete;
		IWindowsWindowSystemFactory& operator =(IWindowsWindowSystemFactory&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IWindowsWindowSystemFactory() noexcept = default;

		~IWindowsWindowSystemFactory() noexcept = default;
	};
}
