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

import :WindowsWindowSystemParams;

export namespace PonyEngine::Window
{
	/// @brief Window system for Windows factory.
	class IWindowsWindowSystemFactory : public IWindowSystemFactory
	{
	public:
		IWindowsWindowSystemFactory(const IWindowsWindowSystemFactory&) = delete;
		IWindowsWindowSystemFactory(IWindowsWindowSystemFactory&&) = delete;

		[[nodiscard("Pure function")]]
		virtual WindowsWindowSystemParams& SystemParams() noexcept override = 0;
		[[nodiscard("Pure function")]]
		virtual const WindowsWindowSystemParams& SystemParams() const noexcept override = 0;

		IWindowsWindowSystemFactory& operator =(const IWindowsWindowSystemFactory&) = delete;
		IWindowsWindowSystemFactory& operator =(IWindowsWindowSystemFactory&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IWindowsWindowSystemFactory() noexcept = default;

		~IWindowsWindowSystemFactory() noexcept = default;
	};
}
