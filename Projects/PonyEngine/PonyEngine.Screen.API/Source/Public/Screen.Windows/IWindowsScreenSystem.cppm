/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Screen.Windows:IWindowsScreenSystem;

import PonyEngine.Screen;

export namespace PonyEngine::Screen
{
	class IWindowsScreenSystem : public IScreenSystem
	{
	public:
		IWindowsScreenSystem(const IWindowsScreenSystem&) = delete;
		IWindowsScreenSystem(IWindowsScreenSystem&&) = delete;

		IWindowsScreenSystem& operator =(const IWindowsScreenSystem&) = delete;
		IWindowsScreenSystem& operator =(IWindowsScreenSystem&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IWindowsScreenSystem() noexcept = default;

		~IWindowsScreenSystem() noexcept = default;
	};
}
