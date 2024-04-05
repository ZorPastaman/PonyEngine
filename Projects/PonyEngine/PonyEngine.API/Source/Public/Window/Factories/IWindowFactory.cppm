/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window.Factories:IWindowFactory;

import <string>;

import PonyEngine.Core;
import PonyEngine.Window;

namespace PonyEngine::Window
{
	/// @brief Window factory.
	export class IWindowFactory
	{
	public:
		/// @brief Creates a window.
		/// @param engine Engine that owns the window.
		/// @return Created window.
		[[nodiscard("Pure function")]]
		virtual IWindow* Create(Core::IEngine& engine) = 0;
		/// @brief Destroys a previously created window.
		/// @param window Window to destroy.
		virtual void Destroy(IWindow* window) noexcept = 0;

		/// @brief Gets a title of the next created window.
		/// @return Window title.
		[[nodiscard("Pure function")]]
		virtual const wchar_t* GetTitle() const noexcept = 0;
		/// @brief Sets a title of the next created window.
		/// @param title Window title.
		virtual void SetTitle(const wchar_t* title) noexcept = 0;

		/// @brief Gets a window class name.
		/// @return Window class name.
		[[nodiscard("Pure function")]]
		virtual const char* GetWindowName() const noexcept = 0; // TODO: add a test

	protected:
		inline virtual ~IWindowFactory() noexcept = default;
	};
}
