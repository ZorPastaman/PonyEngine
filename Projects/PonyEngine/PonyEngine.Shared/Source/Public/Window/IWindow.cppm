/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window:IWindow;

import :MessageListeners.IKeyboardMessageListener;

namespace PonyEngine::Window
{
	/// @brief Engine window interface.
	export class IWindow
	{
	public:
		virtual void AddKeyboardMessageListener(MessageListeners::IKeyboardMessageListener& keyboardMessageListener) = 0;
		virtual void RemoveKeyboardMessageListener(MessageListeners::IKeyboardMessageListener& keyboardMessageListener) = 0;

	protected:
		virtual ~IWindow() = default;
	};
}
