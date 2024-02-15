/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window.Implementation:IEngineWindow;

import PonyEngine.Window;

namespace PonyEngine::Window
{
	export class IEngineWindow : public IWindow
	{
	public:
		virtual ~IEngineWindow() noexcept = default;

		virtual void ShowWindow() = 0;
	};
}
