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
	/// @brief Windows window factory.
	export class IWindowsWindowFactory : public IWindowFactory
	{
	public:
		/// @brief Creates a windows window.
		/// @param engine Engine that owns the window.
		/// @return Created windows window.
		[[nodiscard("Pure function")]]
		virtual IWindowsWindow* Create(Core::IEngine& engine) override = 0;

	protected:
		inline virtual ~IWindowsWindowFactory() noexcept = default;
	};
}
