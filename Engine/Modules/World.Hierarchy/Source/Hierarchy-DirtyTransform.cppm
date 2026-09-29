/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.World.Hierarchy:DirtyTransform;

export namespace PonyEngine::World::Hierarchy
{
	/// @brief Tag component that tells that a world transform of its entity must be updated.
	struct DirtyTransform final
	{
	};
}
