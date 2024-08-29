/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window.Windows.Factory:IWindowsWindowSystemFactory;

import PonyEngine.Window.Factory;

import :WindowsWindowParams;

export namespace PonyEngine::Window
{
	/// @brief Window system for Windows factory.
	class IWindowsWindowSystemFactory : public IWindowSystemFactory
	{
	public:
		IWindowsWindowSystemFactory(const IWindowsWindowSystemFactory&) = delete;
		IWindowsWindowSystemFactory(IWindowsWindowSystemFactory&&) = delete;

		/// @brief Gets the next Windows window params.
		/// @return Next Windows window params.
		[[nodiscard("Pure function")]]
		virtual WindowsWindowParams NextWindowsWindowParams() const noexcept = 0;
		/// @brief Sets the next Windows window params.
		/// @param params Next Windows window params to set.
		virtual void NextWindowsWindowParams(const WindowsWindowParams& params) noexcept = 0;

		IWindowsWindowSystemFactory& operator =(const IWindowsWindowSystemFactory&) = delete;
		IWindowsWindowSystemFactory& operator =(IWindowsWindowSystemFactory&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IWindowsWindowSystemFactory() noexcept = default;

		~IWindowsWindowSystemFactory() noexcept = default;
	};
}
