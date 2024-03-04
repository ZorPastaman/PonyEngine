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
	/// @brief Window interface used by an engine.
	export class IEngineWindow : public IWindow
	{
	public:
		inline virtual ~IEngineWindow() noexcept = default;

		/// @brief Shows a window.
		virtual void ShowWindow() = 0;

		/// @brief Ticks a window message queue.
		virtual void Tick() = 0;
	};
}
