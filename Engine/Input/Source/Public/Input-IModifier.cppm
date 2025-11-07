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

export module PonyEngine.Input:IModifier;

export namespace PonyEngine::Input
{
	/// @brief Input value modifier.
	class IModifier
	{
		INTERFACE_BODY(IModifier)

		/// @brief Modifies the value.
		/// @param initial Initial not-modified value.
		/// @param current Current modified value.
		/// @return New modified value.
		[[nodiscard("Must be used")]]
		virtual float Modify(float initial, float current) noexcept = 0;
	};
}
