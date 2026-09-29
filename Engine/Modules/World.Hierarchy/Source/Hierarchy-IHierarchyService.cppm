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

		/// @brief Propagates dirty transform components to children.
		/// @param world World.
		/// @note The world mustn't have invalid parent components.
		virtual void PropagateDirtyTransforms(IWorld& world) const = 0;
		/// @brief Propagates a local transform 2D to all children of parents that have a local transform 2D. The added transforms are identity.
		/// @param world World.
		/// @note The world mustn't have invalid parent components.
		virtual void PropagateLocalTransforms2D(IWorld& world) const = 0;
		/// @brief Propagates a local transform 3D to all children of parents that have a local transform 3D. The added transforms are identity.
		/// @param world World.
		/// @note The world mustn't have invalid parent components.
		virtual void PropagateLocalTransforms3D(IWorld& world) const = 0;
		/// @brief Updates world transforms 2D.
		/// @param world World.
		/// @note The world mustn't have invalid parent components.
		virtual void UpdateWorldTransforms2D(IWorld& world) const = 0;
		/// @brief Updates world transforms 3D.
		/// @param world World.
		/// @note The world mustn't have invalid parent components.
		virtual void UpdateWorldTransforms3D(IWorld& world) const = 0;
		/// @brief Updates world transforms 2D if their entities have dirty transform components.
		/// @param world World.
		/// @note The world mustn't have invalid parent components.
		virtual void UpdateWorldTransforms2DIfDirty(IWorld& world) const = 0;
		/// @brief Updates world transforms 3D if their entities have dirty transform components.
		/// @param world World.
		/// @note The world mustn't have invalid parent components.
		virtual void UpdateWorldTransforms3DIfDirty(IWorld& world) const = 0;
	};
}
