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
#include "PonyEngine/RawInput/Brand.h"

export module PonyEngine.RawInput:Style;

import std;

export namespace PonyEngine::RawInput
{
	/// @brief Predefined styles.
	struct Style final
	{
		PONY_NON_CONSTRUCTIBLE_BODY(Style)

		static constexpr std::string_view None = "None"; ///< No style.
		static constexpr std::string_view Xbox = PONY_INPUT_XBOX; ///< Xbox brand.
		static constexpr std::string_view PlayStation = PONY_INPUT_PLAYSTATION; ///< PlayStation brand.
	};
}
