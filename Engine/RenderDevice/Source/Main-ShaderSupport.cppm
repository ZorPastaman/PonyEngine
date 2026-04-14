/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:ShaderSupport;

import std;

import PonyEngine.Meta;

import :ShaderScalarType;

export namespace PonyEngine::RenderDevice
{
	/// @brief Shader support.
	struct ShaderSupport final
	{
		std::string_view shaderIRName; ///< Shader IR name.
		Meta::Version shaderIRVersion; ///< Shader IR version.
		ShaderScalarTypeMask scalarTypes = ShaderScalarTypeMask::None; ///< Supported scalar types.
		ShaderScalarTypeMask atomicTypes = ShaderScalarTypeMask::None; ///< Supported atomic scalar types.
		ShaderScalarTypeMask groupSharedAtomicTypes = ShaderScalarTypeMask::None; ///< Supported group shared atomic scalar types.
	};
}
