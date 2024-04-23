/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window:IWindow;

import <string>;

import PonyEngine.Utility;

import :IKeyboardObserver;

export namespace PonyEngine::Window
{
	/// @brief Engine window interface.
	class IWindow : public Utility::INamed
	{
	public:
		/// @brief Gets a window title.
		/// @return Window title.
		[[nodiscard("Pure function")]]
		virtual const wchar_t* GetTitle() const noexcept = 0;
		/// @brief Sets a window title.
		/// @param title Window title to set.
		virtual void SetTitle(const wchar_t* title) = 0;

		/// @brief Adds a keyboard input observer.
		/// @param keyboardMessageObserver Keyboard input observer. Mustn't be nullptr.
		virtual void AddKeyboardMessageObserver(IKeyboardObserver* keyboardMessageObserver) = 0;
		/// @brief Removes a keyboard input observer.
		/// @param keyboardMessageObserver Keyboard input observer.
		virtual void RemoveKeyboardMessageObserver(IKeyboardObserver* keyboardMessageObserver) = 0;

		/// @brief Shows a window.
		virtual void ShowWindow() = 0;

		/// @brief Ticks a window message queue.
		virtual void Tick() = 0;

	protected:
		~IWindow() noexcept = default;
	};
}
