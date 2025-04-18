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

export module PonyEngine.Render:DataTypes;

import <string_view>;

export namespace PonyEngine::Render
{
	/// @brief Engine special data types.
	/// @details The engine passes special data to slots if they have these types.
	/// @remark All the data will be transferred to shader b-buffers.
	struct DataTypes final
	{
		NON_CONSTRUCTIBLE_BODY(DataTypes)

		static constexpr std::string_view Data = "Pony_Data"; ///< Engine data type. It's a shortcut to include all the engine data in the order: Context, Transform. Don't use with other types.
		static constexpr std::string_view Context = "Pony_Context"; ///< Engine context data type. Bound to @p Pony_Context from @p PonyShader/Core/Context.hlsli.
		static constexpr std::string_view Transform = "Pony_Transform"; ///< Engine transform data type. Bound to @p Pony_Transform from @p PonyShader/Space/Transform.hlsli.
	};
}
