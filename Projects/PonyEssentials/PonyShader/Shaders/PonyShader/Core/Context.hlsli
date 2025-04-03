/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "ThreadGroupCounts.hlsli"

/// @brief Render context. It corresponds to @p PonyShader::Core::Context on the C++ side.
struct Pony_Context
{
	Pony_ThreadGroupCounts dispatchThreadGroupCounts; ///< How many thread groups are dispatched by a render pipeline.
	Pony_ThreadGroupCounts materialThreadGroupCounts; ///< How many thread groups are required by a material. It takes just the number without considering a mode declared in the material.
	Pony_ThreadGroupCounts meshThreadGroupCounts; ///< How many thread groups are required by a mesh.
	int renderQueue; ///< Render queue.
	bool isTransparent; ///< @a True if the render object is transparent; @a false otherwise.
	bool isFlipped; ///< @a True if the object is flipped (its winding order is opposite due to negative scaling); @a false otherwise. 
};
