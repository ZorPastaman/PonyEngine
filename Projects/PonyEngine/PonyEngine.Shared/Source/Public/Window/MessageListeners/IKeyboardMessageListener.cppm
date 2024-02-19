/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window:MessageListeners.IKeyboardMessageListener;

import :Messages.KeyboardMessage;

namespace PonyEngine::Window::MessageListeners
{
	export class IKeyboardMessageListener
	{
	public:
		virtual ~IKeyboardMessageListener() noexcept = default;

		virtual void Listen(Messages::KeyboardMessage keyboardMessage) noexcept = 0;
	};
}
