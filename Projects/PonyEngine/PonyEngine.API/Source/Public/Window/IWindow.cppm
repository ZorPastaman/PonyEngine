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

export namespace PonyEngine::Window
{
	/// @brief Engine window.
	class IWindow
	{
	public:
		/// @brief Checks if the system window is alive.
		/// @return @a True if it's alive; @a false otherwise.
		[[nodiscard("Pure function")]]
		virtual bool IsWindowAlive() const noexcept = 0;

		/// @brief Gets the window title.
		/// @return Window title.
		[[nodiscard("Pure function")]]
		virtual const wchar_t* GetTitle() const = 0;
		/// @brief Sets the window title.
		/// @param title Window title to set.
		virtual void SetTitle(const wchar_t* title) = 0;

		/// @brief Gets the window name.
		/// @return Window name.
		[[nodiscard("Pure function")]]
		virtual const char* GetName() const noexcept = 0;

		/// @brief Shows the window.
		virtual void ShowWindow() = 0;
		/// @brief Hides the window.
		virtual void HideWindow() = 0;

	protected:
		~IWindow() noexcept = default;
	};
}
