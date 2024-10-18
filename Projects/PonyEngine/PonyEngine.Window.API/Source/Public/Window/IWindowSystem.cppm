/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window:IWindowSystem;

import PonyMath.Core;

import PonyEngine.Screen;

export namespace PonyEngine::Window
{
	/// @brief Window system.
	class IWindowSystem
	{
	public:
		IWindowSystem(const IWindowSystem&) = delete;
		IWindowSystem(IWindowSystem&&) = delete;

		/// @brief Checks if the system window is alive.
		/// @return @a True if it's alive; @a false otherwise.
		[[nodiscard("Pure function")]]
		virtual bool IsWindowAlive() const noexcept = 0;

		/// @brief Gets the window title.
		/// @return Window title.
		[[nodiscard("Pure function")]]
		virtual const wchar_t* MainTitle() const noexcept = 0;
		/// @brief Sets the window title.
		/// @param title Window title to set.
		virtual void MainTitle(const wchar_t* title) = 0;
		/// @brief Gets the window title text.
		/// @return Window title text.
		[[nodiscard("Pure function")]]
		virtual const wchar_t* SecondaryTitle() const noexcept = 0;
		/// @brief Sets the window title text.
		/// @param title Window title text to set.
		virtual void SecondaryTitle(const wchar_t* title) = 0;

		/// @brief Checks if the window is visible.
		/// @return @a True if it's visible; @a false otherwise.
		[[nodiscard("Pure function")]]
		virtual bool IsVisible() const noexcept = 0;
		/// @brief Shows the window.
		virtual void ShowWindow() = 0;
		/// @brief Hides the window.
		virtual void HideWindow() = 0;

		/// @brief Gets the window position.
		/// @return Window position.
		[[nodiscard("Pure function")]]
		virtual PonyMath::Core::Vector2<int> Position() const noexcept = 0;
		/// @brief Gets the window resolution.
		/// @return Window resolution.
		[[nodiscard("Pure function")]]
		virtual Screen::Resolution<unsigned int> Resolution() const noexcept = 0;

		/// @brief Gets the window name.
		/// @return Window name.
		[[nodiscard("Pure function")]]
		virtual const char* Name() const noexcept = 0;

		IWindowSystem& operator =(const IWindowSystem&) = delete;
		IWindowSystem& operator =(IWindowSystem&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IWindowSystem() noexcept = default;

		~IWindowSystem() noexcept = default;
	};
}
