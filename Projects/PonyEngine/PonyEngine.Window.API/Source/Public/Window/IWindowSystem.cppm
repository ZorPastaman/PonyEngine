/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window:IWindowSystem;

import <string_view>;

import PonyMath.Core;
import PonyMath.Utility;

import PonyEngine.Core;

export namespace PonyEngine::Window
{
	/// @brief Window system.
	class IWindowSystem : public Core::ISystem
	{
	public:
		IWindowSystem(const IWindowSystem&) = delete;
		IWindowSystem(IWindowSystem&&) = delete;

		/// @brief Gets the window title.
		/// @return Window title.
		[[nodiscard("Pure function")]]
		virtual std::wstring_view MainTitle() const noexcept = 0;
		/// @brief Sets the window title.
		/// @param title Window title to set.
		virtual void MainTitle(std::wstring_view title) = 0;
		/// @brief Gets the window title text.
		/// @return Window title text.
		[[nodiscard("Pure function")]]
		virtual std::wstring_view SecondaryTitle() const noexcept = 0;
		/// @brief Sets the window title text.
		/// @param title Window title text to set.
		virtual void SecondaryTitle(std::wstring_view title) = 0;

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
		virtual PonyMath::Utility::Resolution<unsigned int> Resolution() const noexcept = 0;

		IWindowSystem& operator =(const IWindowSystem&) = delete;
		IWindowSystem& operator =(IWindowSystem&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IWindowSystem() noexcept = default;

		~IWindowSystem() noexcept = default;
	};
}
