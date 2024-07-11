/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window.Factory:WindowParams;

import <string>;

export namespace PonyEngine::Window
{
	/// @brief Window parameters.
	struct WindowParams final
	{
		WindowParams() noexcept = default;
		WindowParams(const WindowParams& other) = default;
		WindowParams(WindowParams&& other) noexcept = default;

		~WindowParams() noexcept = default;

		WindowParams& operator =(const WindowParams& other) = default;
		WindowParams& operator =(WindowParams&& other) noexcept = default;

		std::wstring title; ///< Window title.
		int horizontalPosition; ///< Window horizontal position.
		int verticalPosition; ///< Window vertical position.
		int width; ///< Window width.
		int height; ///< Window height.
	};
}
