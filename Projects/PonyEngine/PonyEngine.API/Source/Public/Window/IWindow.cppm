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

import :IKeyboardListener;

namespace PonyEngine::Window
{
	/// @brief Engine window interface.
	export class IWindow
	{
	public:
		/// @brief Gets a window title.
		/// @return Window title.
		[[nodiscard("Pure function")]]
		virtual std::wstring GetTitle() const = 0;
		/// @brief Sets a window title.
		/// @param title Window title to set.
		/// @return @a True if the procedure is successful; @a false otherwise.
		virtual bool SetTitle(const std::wstring& title) = 0;

		/// @brief Adds a keyboard input listener.
		/// @param keyboardMessageListener Keyboard input listener. Mustn't be nullptr.
		virtual void AddKeyboardMessageListener(IKeyboardListener* keyboardMessageListener) = 0;
		/// @brief Removes a keyboard input listener.
		/// @param keyboardMessageListener Keyboard input listener.
		virtual void RemoveKeyboardMessageListener(IKeyboardListener* keyboardMessageListener) = 0;

		/// @brief Shows a window.
		virtual void ShowWindow() = 0;

		/// @brief Ticks a window message queue.
		virtual void Tick() = 0;

	protected:
		inline virtual ~IWindow() noexcept = default;
	};
}
