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

export module PonyEngine.Render:SlotNames;

import <string_view>;

export namespace PonyEngine::Render
{
	/// @brief Engine specific data slot names.
	/// @details The engine passes specific data values to slots if they have these names.
	struct SlotNames final
	{
		NON_CONSTRUCTIBLE_BODY(SlotNames)

		static constexpr std::string_view Context = "Pony_Context"; ///< Engine context slot name. Bound to @p Pony_Context from @p PonyShader/Core/Context.hlsli.
		static constexpr std::string_view Transform = "Pony_Transform"; ///< Engine transform slot name. Bound to @p Pony_Transform from @p PonyShader/Space/Transform.hlsli.
	};
}
