/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "Platform/Windows/Framework.h"

export module PonyEngine.Window.Windows.Implementation:WindowParams;

import <string>;

namespace PonyEngine::Window
{
	/// @brief Window parameters.
	export struct WindowParams final
	{
	public:
		WindowParams() = default;
		WindowParams(const WindowParams& other) = default;
		WindowParams(WindowParams&& other) = default;

		~WindowParams() noexcept = default;

		WindowParams& operator =(const WindowParams& other) = default;
		WindowParams& operator =(WindowParams&& other) = default;

		std::wstring title; /// @brief Window title.
		int cmdShow = SW_NORMAL; /// @brief Window cmdShow.
	};
}
