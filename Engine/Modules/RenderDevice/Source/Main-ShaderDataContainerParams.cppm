/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:ShaderDataContainerParams;

import std;

export namespace PonyEngine::RenderDevice
{
	/// @brief Shader data container parameters.
	struct ShaderDataContainerParams final
	{
		std::uint32_t size = 1u; ///< Container size.
		bool shaderVisible = false; ///< Is it shader visible?
	};
}
