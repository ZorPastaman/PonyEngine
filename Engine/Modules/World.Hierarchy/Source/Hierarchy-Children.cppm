/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.World.Hierarchy:Children;

import std;

import PonyEngine.World;

export namespace PonyEngine::World::Hierarchy
{
	/// @brief Children component.
	struct Children final
	{
		ObjectHandle<std::vector<Entity>> value; ///< Children.
	};
}
