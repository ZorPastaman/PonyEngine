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

export module PonyEngine.Render.Direct3D12.Detail:IShaderManager;

import <memory>;
import <string_view>;

import :Shader;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 shader manager.
	class IShaderManager
	{
		INTERFACE_BODY(IShaderManager)

		/// @brief Creates a shader.
		/// @param shaderPath Shader path without extension.
		/// @return Shader.
		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<Shader> CreateShader(std::string_view shaderPath) = 0;
	};
}
