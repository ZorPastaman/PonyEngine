/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/Interface.h"

export module PonyEngine.Screen:IScreenSystem;

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
		virtual PonyMath::Utility::Resolution<unsigned int> DisplayResolution() const noexcept = 0;
	};
}
