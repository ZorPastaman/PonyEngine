/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Utility/Body.h"

export module PonyEngine.RawInput:Interface;

import std;

export namespace PonyEngine::RawInput
{
	/// @brief Predefined interface names.
	struct Interface final
	{
		PONY_NON_CONSTRUCTIBLE_BODY(Interface)

		static constexpr std::string_view RawInput = "RawInput"; ///< WinAPI Raw Input interface name.
		static constexpr std::string_view XInput = "XInput"; ///< XInput interface name.
	};
}
