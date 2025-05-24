/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/Windows/Framework.h"

export module PonyEngine.Screen.Windows.Detail:Utility;

import <cstdint>;

import PonyMath.Utility;

export namespace PonyEngine::Screen::Windows
{
	/// @brief Gets a current display resolution.
	/// @return Display resolution.
	[[nodiscard("Pure function")]]
	PonyMath::Utility::Resolution<std::uint32_t> GetDisplayResolution() noexcept;
}

namespace PonyEngine::Screen::Windows
{
	PonyMath::Utility::Resolution<std::uint32_t> GetDisplayResolution() noexcept
	{
		PonyMath::Utility::Resolution<std::uint32_t> resolution;
		resolution.Width() = static_cast<std::uint32_t>(GetSystemMetrics(SM_CXSCREEN));
		resolution.Height() = static_cast<std::uint32_t>(GetSystemMetrics(SM_CYSCREEN));

		return resolution;
	}
}
