/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Object/Body.h"

export module PonyEngine.RawInput.Ext:ExitCodes;

export namespace PonyEngine::Input
{
	/// @brief Exit codes of the input sub-systems.
	struct ExitCodes final
	{
		NON_CONSTRUCTIBLE_BODY(ExitCodes)

		static constexpr int InputError = -5000; ///< Main input error.
	};
}
