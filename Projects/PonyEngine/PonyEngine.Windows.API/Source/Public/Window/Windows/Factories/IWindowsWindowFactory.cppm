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

namespace PonyEngine::Window
{
	export class IWindowsWindowFactory : public IWindowFactory
	{
	public:
		[[nodiscard("Pure function")]]
		virtual IWindowsWindow* Create(Core::IEngine& engine) = 0;

	protected:
		inline virtual ~IWindowsWindowFactory() noexcept = default;
	};
}
