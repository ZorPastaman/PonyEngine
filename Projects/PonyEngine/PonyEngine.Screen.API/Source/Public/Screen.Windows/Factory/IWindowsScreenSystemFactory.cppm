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

export namespace PonyEngine::Screen
{
	class IWindowsScreenSystemFactory : public IScreenSystemFactory
	{
	public:
		IWindowsScreenSystemFactory(const IWindowsScreenSystemFactory&) = delete;
		IWindowsScreenSystemFactory(IWindowsScreenSystemFactory&&) = delete;

		IWindowsScreenSystemFactory& operator =(const IWindowsScreenSystemFactory&) = delete;
		IWindowsScreenSystemFactory& operator =(IWindowsScreenSystemFactory&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IWindowsScreenSystemFactory() noexcept = default;

		~IWindowsScreenSystemFactory() noexcept = default;
	};
}
