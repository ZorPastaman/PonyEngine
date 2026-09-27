/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Utility/Body.h"

export module PonyEngine.World.Hierarchy:IHierarchyService;

import std;

import PonyEngine.World;

export namespace PonyEngine::World::Hierarchy
{
	/// @brief Hierarchy service.
	class IHierarchyService
	{
		PONY_INTERFACE_BODY(IHierarchyService)

		/// @brief Removes invalid parent components.
		/// @details A parent component is invalid if it points to an invalid entity.
		/// @param world World.
		virtual void RemoveInvalidParents(IWorld& world) const = 0;

		virtual void UpdateTransforms2D(IWorld& world) const = 0;
		virtual void UpdateTransforms3D(IWorld& world) const = 0;
	};
}
