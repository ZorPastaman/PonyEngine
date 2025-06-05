/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/ObjectBody.h"

export module PonyEngine.Screen:IScreenSystem;

import <cstdint>;

import PonyMath.Utility;

export namespace PonyEngine::Screen
{
	/// @brief Screen system.
	class IScreenSystem
	{
		INTERFACE_BODY(IScreenSystem)

		/// @brief Gets a display resolution.
		/// @return Display resolution.
		[[nodiscard("Pure function")]]
		virtual PonyMath::Utility::Resolution<std::uint32_t> DisplayResolution() const noexcept = 0;
	};
}
