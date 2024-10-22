/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Screen.Windows.Factory:IWindowsScreenSystemFactory;

import PonyEngine.Screen.Factory;

import :WindowsScreenSystemParams;

export namespace PonyEngine::Screen
{
	class IWindowsScreenSystemFactory : public IScreenSystemFactory
	{
	public:
		IWindowsScreenSystemFactory(const IWindowsScreenSystemFactory&) = delete;
		IWindowsScreenSystemFactory(IWindowsScreenSystemFactory&&) = delete;

		[[nodiscard("Pure function")]]
		virtual WindowsScreenSystemParams& SystemParams() noexcept override = 0;
		[[nodiscard("Pure function")]]
		virtual const WindowsScreenSystemParams& SystemParams() const noexcept override = 0;

		IWindowsScreenSystemFactory& operator =(const IWindowsScreenSystemFactory&) = delete;
		IWindowsScreenSystemFactory& operator =(IWindowsScreenSystemFactory&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IWindowsScreenSystemFactory() noexcept = default;

		~IWindowsScreenSystemFactory() noexcept = default;
	};
}
