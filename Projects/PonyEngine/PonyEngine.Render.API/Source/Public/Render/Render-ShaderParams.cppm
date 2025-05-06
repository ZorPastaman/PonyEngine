/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:ShaderParams;

import <filesystem>;
import <string>;

export namespace PonyEngine::Render
{
	/// @brief Shader parameters.
	struct ShaderParams final
	{
		std::filesystem::path shaderPath; ///< Path to a shader file.

		std::string name; ///< Shader name.
	};
}
