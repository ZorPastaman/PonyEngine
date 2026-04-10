/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Type/Enum.h"

export module PonyEngine.RenderDevice:ShaderScalarType;

import std;

export namespace PonyEngine::RenderDevice
{
	/// @brief Shader scalar type.
	enum class ShaderScalarType : std::uint8_t
	{
		Int8,
		Int16,
		Int32,
		Int64,
		Float8,
		Float16,
		Float32,
		Float64
	};

	/// @brief Shader scalar type mask.
	enum class ShaderScalarTypeMask : std::uint8_t
	{
		None = 0,
		Int8 = 1 << 0,
		Int16 = 1 << 1,
		Int32 = 1 << 2,
		Int64 = 1 << 3,
		Float8 = 1 << 4,
		Float16 = 1 << 5,
		Float32 = 1 << 6,
		Float64 = 1 << 7,
		All = (1 << 8) - 1
	};

	PONY_ENUM_VALUE_MASK_FEATURES(ShaderScalarType, ShaderScalarTypeMask)
}

namespace PonyEngine::RenderDevice
{
	/// @brief Shader scalar type names.
	constexpr std::array<std::string_view, 8> ShaderScalarTypeNames
	{
		"Int8",
		"Int16",
		"Int32",
		"Int64",
		"Float8",
		"Float16",
		"Float32",
		"Float64"
	};
}

export 
{
	PONY_ENUM_VALUE_MASK_FORMATTER(PonyEngine::RenderDevice::ShaderScalarType, PonyEngine::RenderDevice::ShaderScalarTypeMask, PonyEngine::RenderDevice::ShaderScalarTypeNames)
}
