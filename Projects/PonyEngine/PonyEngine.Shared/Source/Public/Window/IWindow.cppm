/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window:IWindow;

import :Listeners.IKeyboardListener;

namespace PonyEngine::Window
{
	/// @brief Engine window interface.
	export class IWindow
	{
	public:
		virtual void AddKeyboardMessageListener(Listeners::IKeyboardListener* keyboardMessageListener) = 0;
		virtual void RemoveKeyboardMessageListener(Listeners::IKeyboardListener* keyboardMessageListener) = 0;

	protected:
		virtual ~IWindow() = default;
	};
}
