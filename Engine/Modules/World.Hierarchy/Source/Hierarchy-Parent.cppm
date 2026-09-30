/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.World.Hierarchy:Parent;

import PonyEngine.World;

export namespace PonyEngine::World::Hierarchy
{
	/// @brief Parent component.
	struct Parent final
	{
		Entity value; ///< Parent entity.
	};
}
