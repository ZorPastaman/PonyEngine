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

export module PonyEngine.Window.Windows.Implementation:CreateWindowParams;

import <string>;

export namespace PonyEngine::Window
{
	/// @brief Window parameters.
	struct CreateWindowParams final
	{
		CreateWindowParams() = default;
		CreateWindowParams(const CreateWindowParams& other) = default;
		CreateWindowParams(CreateWindowParams&& other) = default;

		~CreateWindowParams() noexcept = default;

		CreateWindowParams& operator =(const CreateWindowParams& other) = default;
		CreateWindowParams& operator =(CreateWindowParams&& other) = default;

		std::wstring title; ///< Window title.
		DWORD style; ///< Window style.
		DWORD extendedStyle; ///< Extended window style.
		int horizontalPosition; ///< Horizontal window position.
		int verticalPosition; ///< Vertical window position.
		int width; ///< Window width.
		int height; ///< Window height.
		int cmdShow; ///< Window cmdShow.
	};
}
