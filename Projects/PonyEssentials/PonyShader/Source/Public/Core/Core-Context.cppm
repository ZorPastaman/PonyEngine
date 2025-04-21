/***************************************************
* MIT License                                     *
*                                                 *
* Copyright (c) 2023-present Vladimir Popov       *
*                                                 *
* Email: zor1994@gmail.com                        *
* Repo: https://github.com/ZorPastaman/PonyEngine *
***************************************************/

export module PonyShader.Core:Context;

import <cstdint>;

import :Bool;
import :ThreadGroupCounts;

export namespace PonyShader::Core
{
	/// @brief Render context. It corresponds to @p Pony_Context in PonyShader/Core/Context.hlsli on the HLSL side.
	struct alignas(256) Context final
	{
		alignas(16) ThreadGroupCounts dispatchThreadGroupCounts; ///< How many thread groups are dispatched by a render pipeline.
		alignas(16) ThreadGroupCounts pipelineStateThreadGroupCounts; ///< How many thread groups are required by a pipeline state. It takes just the number without considering a mode declared in the pipeline state.
		alignas(16) ThreadGroupCounts meshThreadGroupCounts; ///< How many thread groups are required by a mesh.
		std::int32_t renderQueue; ///< Render queue.
		Bool isTransparent; ///< @a True if the render object is transparent; @a false otherwise.
		Bool isFlipped; ///< @a True if the object is flipped (its winding order is opposite due to negative scaling); @a false otherwise. 
	};;
}
