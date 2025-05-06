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

export module PonyEngine.Render:IShaderManager;

import <memory>;

import :IShader;
import :ShaderParams;

export namespace PonyEngine::Render
{
	/// @brief Shader manager.
	class IShaderManager
	{
		INTERFACE_BODY(IShaderManager)

		/// @brief Creates a shader.
		/// @param params Shader parameters.
		/// @return Shader.
		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<IShader> CreateShader(const ShaderParams& params) = 0;
	};
}
