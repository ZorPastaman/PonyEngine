/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Platform/Windows/Framework.h"

export module PonyEngine.Window.Windows.Implementation:WindowParams;

import <string>;

export namespace PonyEngine::Window
{
	// TODO: move this window params to platform independent.

	/// @brief Window parameters.
	struct WindowParams final
	{
		WindowParams() = default;
		WindowParams(const WindowParams& other) = default;
		WindowParams(WindowParams&& other) = default;

		~WindowParams() noexcept = default;

		WindowParams& operator =(const WindowParams& other) = default;
		WindowParams& operator =(WindowParams&& other) = default;

		std::wstring title; ///< Window title.
		int cmdShow = SW_NORMAL; ///< Window cmdShow.
	};
}
