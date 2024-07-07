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

export module PonyEngine.Window.Windows.Factories:WindowClassParams;

import <string>;

export namespace PonyEngine::Window
{
	/// @brief Window class parameters. They are used in RegisterClass() function.
	struct WindowClassParams final
	{
		WindowClassParams() noexcept = default;
		WindowClassParams(const WindowClassParams& other) = default;
		WindowClassParams(WindowClassParams&& other) noexcept = default;

		~WindowClassParams() noexcept = default;

		WindowClassParams& operator =(const WindowClassParams& other) = default;
		WindowClassParams& operator =(WindowClassParams&& other) noexcept = default;

		std::wstring className; ///< Class name. Must be unique.
		HICON icon; ///< Class icon. The default icon is used if it's NULL.
		HCURSOR cursor; ///< Class cursor. The default cursor is used if it's NULL.
		int classStyle; ///< Class style;
	};
}

