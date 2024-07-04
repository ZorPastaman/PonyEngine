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

export namespace PonyEngine::Window
{
	/// @brief Engine window interface.
	class IWindow : public Utility::INamed
	{
	public:
		/// @brief Checks if the system window is alive.
		/// @return @a True if it's alive; @a false otherwise.
		[[nodiscard("Pure function")]]
		virtual bool IsWindowAlive() const noexcept = 0;

		/// @brief Gets a window title.
		/// @return Window title.
		[[nodiscard("Pure function")]]
		virtual const wchar_t* GetTitle() const = 0;
		/// @brief Sets a window title.
		/// @param title Window title to set.
		virtual void SetTitle(const wchar_t* title) = 0;

		/// @brief Shows a window.
		virtual void ShowWindow() = 0;
		/// @brief Hides a window.
		virtual void HideWindow() = 0;

	protected:
		~IWindow() noexcept = default;
	};
}
