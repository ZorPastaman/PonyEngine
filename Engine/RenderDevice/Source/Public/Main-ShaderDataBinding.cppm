/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:ShaderDataBinding;

import std;

export namespace PonyEngine::RenderDevice
{
	/// @brief Shader data binding.
	struct ShaderDataBinding final
	{
		std::uint32_t layoutSetIndex = 0u; ///< Layout set index in a bound pipeline state.
		std::uint32_t containerIndex = 0u; ///< View index in a bound container.
	};
}
