/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window.Factories:IWindowFactory;

import PonyEngine.Core;
import PonyEngine.Window;

namespace PonyEngine::Window
{
	export class IWindowFactory
	{
	public:
		[[nodiscard("Pure function")]]
		virtual IWindow* Create(Core::IEngine& engine) = 0;
		virtual void Destroy(IWindow* window) = 0;

	protected:
		inline virtual ~IWindowFactory() noexcept = default;
	};
}
