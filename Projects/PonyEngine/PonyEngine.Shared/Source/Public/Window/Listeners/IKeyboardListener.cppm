/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window:Listeners.IKeyboardListener;

import PonyEngine.Utility;

import :Messages.KeyboardMessage;

namespace PonyEngine::Window::Listeners
{
	export class IKeyboardListener : public Utility::INamed
	{
	public:
		virtual void Listen(Messages::KeyboardMessage keyboardMessage) noexcept = 0;

	protected:
		inline virtual ~IKeyboardListener() noexcept = default;
	};
}
