/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input:IKeyboardObserver;

import :KeyboardMessage;

export namespace PonyEngine::Input
{
	/// @brief Keyboard input observer.
	class IKeyboardObserver
	{
	public:
		IKeyboardObserver(const IKeyboardObserver&) = delete;
		IKeyboardObserver(IKeyboardObserver&&) = delete;

		/// @brief Receives a keyboard input.
		/// @param keyboardMessage Keyboard message.
		virtual void Observe(const KeyboardMessage& keyboardMessage) = 0;

		/// @brief Gets the observer name.
		/// @return Observer name.
		[[nodiscard("Pure function")]]
		virtual const char* GetName() const noexcept = 0;

		IKeyboardObserver& operator =(const IKeyboardObserver&) = delete;
		IKeyboardObserver& operator =(IKeyboardObserver&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IKeyboardObserver() noexcept = default;

		~IKeyboardObserver() noexcept = default;
	};
}
