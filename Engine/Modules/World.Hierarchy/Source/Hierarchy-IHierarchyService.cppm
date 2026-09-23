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
		/// @brief Removes invalid children components.
		/// @details A children component is invalid if it points to an invalid object.
		/// @param world World.
		virtual void RemoveInvalidChildren(IWorld& world) const = 0;
		/// @brief Updates children components.
		/// @param world World.
		/// @note All the parent and children components in the world must be valid.
		virtual void UpdateChildren(IWorld& world) const = 0;

		/// @brief Destroys the entity and all its children.
		/// @param world World.
		/// @param entity Entity. Must be valid.
		/// @note The hierarchy must be valid.
		virtual void DestroyEntity(IWorld& world, Entity entity) const = 0;
		/// @brief Updates world transforms.
		/// @param world World.
		/// @note The hierarchy must be valid.
		virtual void UpdateWorldTransforms(IWorld& world) const = 0;
	};
}
