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
	struct ShaderSupport final
	{
		std::string_view shaderIRName;
		Meta::Version version;
		ShaderScalarTypeMask scalarTypes = ShaderScalarTypeMask::None;
		ShaderScalarTypeMask atomicTypes = ShaderScalarTypeMask::None;
		ShaderScalarTypeMask groupSharedAtomicTypes = ShaderScalarTypeMask::None;
	};
}
