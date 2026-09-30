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

import :LocalTransform;

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
		/// @brief Removes invalid world transforms - when an entity has a world transform but doesn't have a local transform.
		/// @param world World.
		virtual void RemoveInvalidWorldTransforms2D(IWorld& world) const = 0;
		/// @brief Removes invalid world transforms - when an entity has a world transform but doesn't have a local transform.
		/// @param world World.
		virtual void RemoveInvalidWorldTransforms3D(IWorld& world) const = 0;
		
		/// @brief Creates an entity.
		/// @param world World.
		/// @return Created entity.
		Entity CreateEntity(IWorld& world) const;
		/// @brief Creates entities.
		/// @param world World.
		/// @param entities Created entities.
		virtual void CreateEntities(IWorld& world, std::span<Entity> entities) const = 0;
		/// @brief Creates an entity.
		/// @param world World.
		/// @param transform Transform to apply to the child.
		/// @return Created entity.
		Entity CreateEntity(IWorld& world, const LocalTransform2D& transform) const;
		/// @brief Creates entities.
		/// @param world World.
		/// @param entities Created entities.
		/// @param transform Transform to apply to the entities.
		void CreateEntities(IWorld& world, std::span<Entity> entities, const LocalTransform2D& transform) const;
		/// @brief Creates entities.
		/// @param world World.
		/// @param entities Created entities.
		/// @param transforms Transforms to apply to the entities. Synced with the @p entities by index.
		///                   One transform is also valid. In this case, it will be applied to all the created entities.
		virtual void CreateEntities(IWorld& world, std::span<Entity> entities, std::span<const LocalTransform2D> transforms) const = 0;
		/// @brief Creates an entity.
		/// @param world World.
		/// @param transform Transform to apply to the child.
		/// @return Created entity.
		Entity CreateEntity(IWorld& world, const LocalTransform3D& transform) const;
		/// @brief Creates entities.
		/// @param world World.
		/// @param entities Created entities.
		/// @param transform Transform to apply to the entities.
		void CreateEntities(IWorld& world, std::span<Entity> entities, const LocalTransform3D& transform) const;
		/// @brief Creates entities.
		/// @param world World.
		/// @param entities Created entities.
		/// @param transforms Transforms to apply to the entities. Synced with the @p entities by index.
		///                   One transform is also valid. In this case, it will be applied to all the created entities.
		virtual void CreateEntities(IWorld& world, std::span<Entity> entities, std::span<const LocalTransform3D> transforms) const = 0;
		/// @brief Creates an entity and adds a parent component to it that points to the @p parent.
		/// @param world World.
		/// @param parent Parent entity. Must be valid.
		/// @return Created child.
		Entity CreateEntity(IWorld& world, Entity parent) const;
		/// @brief Creates entities and adds parent components to them that point to the @p parent.
		/// @param world World.
		/// @param parent Parent entity. Must be valid.
		/// @param children Created children.
		virtual void CreateEntities(IWorld& world, Entity parent, std::span<Entity> children) const = 0;
		/// @brief Creates an entity and adds a parent component to it that points to the @p parent.
		/// @param world World.
		/// @param parent Parent entity. Must be valid.
		/// @param transform Transform to apply to the child.
		/// @return Created child.
		Entity CreateEntity(IWorld& world, Entity parent, const LocalTransform2D& transform) const;
		/// @brief Creates entities and adds parent components to them that point to the @p parent.
		/// @param world World.
		/// @param parent Parent entity. Must be valid.
		/// @param children Created children.
		/// @param transform Transform to apply to the children.
		void CreateEntities(IWorld& world, Entity parent, std::span<Entity> children, const LocalTransform2D& transform) const;
		/// @brief Creates entities and adds parent components to them that point to the @p parent.
		/// @param world World.
		/// @param parent Parent entity. Must be valid.
		/// @param children Created children.
		/// @param transforms Transforms to apply to the children. Synced with the @p children by index.
		///                   One transform is also valid. In this case, it will be applied to all the created entities.
		virtual void CreateEntities(IWorld& world, Entity parent, std::span<Entity> children, std::span<const LocalTransform2D> transforms) const = 0;
		/// @brief Creates an entity and adds a parent component to it that points to the @p parent.
		/// @param world World.
		/// @param parent Parent entity. Must be valid.
		/// @param transform Transform to apply to the child.
		/// @return Created child.
		Entity CreateEntity(IWorld& world, Entity parent, const LocalTransform3D& transform) const;
		/// @brief Creates entities and adds parent components to them that point to the @p parent.
		/// @param world World.
		/// @param parent Parent entity. Must be valid.
		/// @param children Created children.
		/// @param transform Transform to apply to the children.
		void CreateEntities(IWorld& world, Entity parent, std::span<Entity> children, const LocalTransform3D& transform) const;
		/// @brief Creates entities and adds parent components to them that point to the @p parent.
		/// @param world World.
		/// @param parent Parent entity. Must be valid.
		/// @param children Created children.
		/// @param transforms Transforms to apply to the children. Synced with the @p children by index.
		///                   One transform is also valid. In this case, it will be applied to all the created entities.
		virtual void CreateEntities(IWorld& world, Entity parent, std::span<Entity> children, std::span<const LocalTransform3D> transforms) const = 0;
		/// @brief Destroys the entity and its children.
		/// @param world World.
		/// @param entity Entity to destroy. Must be valid.
		/// @note The world mustn't have invalid parent components.
		void DestroyEntity(IWorld& world, Entity entity) const;
		/// @brief Destroys the entities and their children.
		/// @param world World.
		/// @param entities Entities to destroy. Must be valid.
		/// @note The world mustn't have invalid parent components.
		virtual void DestroyEntities(IWorld& world, std::span<const Entity> entities) const = 0;
		/// @brief Attaches the @p child to the @p parent as a child.
		/// @param world World.
		/// @param parent Parent. Must be valid.
		/// @param child Child. Must be valid.
		void AttachChild(IWorld& world, Entity parent, Entity child) const;
		/// @brief Attaches the @p children to the @p parent as children.
		/// @param world World.
		/// @param parent Parent. Must be valid.
		/// @param children Children. Must be valid.
		virtual void AttachChildren(IWorld& world, Entity parent, std::span<const Entity> children) const = 0;
		/// @brief Detaches children from the entity.
		/// @param world World.
		/// @param entity Entity to unparent. Must be valid.
		/// @note The world mustn't have invalid parent components.
		void DetachChildren(IWorld& world, Entity entity) const;
		/// @brief Detaches children from the entities.
		/// @param world World.
		/// @param entities Entities to unparent. Must be valid.
		/// @note The world mustn't have invalid parent components.
		virtual void DetachChildren(IWorld& world, std::span<const Entity> entities) const = 0;

		/// @brief Adds a local transform to the @p entity.
		/// @param world World.
		/// @param entity Entity. Must be valid.
		/// @param transform Transform to add.
		void AddLocalTransform2D(IWorld& world, Entity entity, const LocalTransform2D& transform = LocalTransform2D::Identity()) const;
		/// @brief Adds local transforms to the @p entities.
		/// @param world World.
		/// @param entities Entities.
		/// @param transform Transforms to add.
		void AddLocalTransforms2D(IWorld& world, std::span<const Entity> entities, const LocalTransform2D& transform = LocalTransform2D::Identity()) const;
		/// @brief Adds local transforms to the @p entities.
		/// @param world World.
		/// @param entities Entities.
		/// @param transforms Transforms to add. Synced with the @p entities by index.
		///                   One transform is also valid. In this case, it will be applied to all the entities.
		virtual void AddLocalTransforms2D(IWorld& world, std::span<const Entity> entities, std::span<const LocalTransform2D> transforms) const = 0;
		/// @brief Adds a local transform to the @p entity.
		/// @param world World.
		/// @param entity Entity. Must be valid.
		/// @param transform Transform to add.
		void AddLocalTransform3D(IWorld& world, Entity entity, const LocalTransform3D& transform = LocalTransform3D::Identity()) const;
		/// @brief Adds local transforms to the @p entities.
		/// @param world World.
		/// @param entities Entities.
		/// @param transform Transforms to add.
		void AddLocalTransforms3D(IWorld& world, std::span<const Entity> entities, const LocalTransform3D& transform = LocalTransform3D::Identity()) const;
		/// @brief Adds local transforms to the @p entities.
		/// @param world World.
		/// @param entities Entities.
		/// @param transforms Transforms to add. Synced with the @p entities by index.
		///                   One transform is also valid. In this case, it will be applied to all the entities.
		virtual void AddLocalTransforms3D(IWorld& world, std::span<const Entity> entities, std::span<const LocalTransform3D> transforms) const = 0;
		/// @brief Removes a local and a world transforms from the @p entity.
		/// @param world World.
		/// @param entity Entity. Must be valid.
		void RemoveTransforms2D(IWorld& world, Entity entity) const;
		/// @brief Removes local and world transforms from the @p entities.
		/// @param world World.
		/// @param entities Entities. Must be valid.
		virtual void RemoveTransforms2D(IWorld& world, std::span<const Entity> entities) const = 0;
		/// @brief Removes a local and a world transforms from the @p entity.
		/// @param world World.
		/// @param entity Entity. Must be valid.
		void RemoveTransforms3D(IWorld& world, Entity entity) const;
		/// @brief Removes local and world transforms from the @p entities.
		/// @param world World.
		/// @param entities Entities. Must be valid.
		virtual void RemoveTransforms3D(IWorld& world, std::span<const Entity> entities) const = 0;

		/// @brief Adds a dirty transform to the @p entity.
		/// @param world World.
		/// @param entity Entity. Must be valid.
		void AddDirtyTransform(IWorld& world, Entity entity) const;
		/// @brief Adds dirty transforms to the @p entities.
		/// @param world World.
		/// @param entities Entities. Must be valid.
		virtual void AddDirtyTransforms(IWorld& world, std::span<const Entity> entities) const = 0;
		/// @brief Removes a dirty transform from the @p entity.
		/// @param world World.
		/// @param entity Entity. Must be valid.
		/// @param includeChildren Should it remove dirty transforms from its children as well?
		void RemoveDirtyTransform(IWorld& world, Entity entity, bool includeChildren) const;
		/// @brief Removes dirty transforms from the @p entities.
		/// @param world World.
		/// @param entities Entities. Must be valid.
		/// @param includeChildren Should it remove dirty transforms from their children as well?
		virtual void RemoveDirtyTransforms(IWorld& world, std::span<const Entity> entities, bool includeChildren) const = 0;
		/// @brief Drops all the dirty transforms in the world.
		/// @param world World.
		virtual void DropDirtyTransforms(IWorld& world) const = 0;

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

namespace PonyEngine::World::Hierarchy
{
	Entity IHierarchyService::CreateEntity(IWorld& world) const
	{
		Entity entity;
		CreateEntities(world, std::span(&entity, 1uz));
		return entity;
	}

	Entity IHierarchyService::CreateEntity(IWorld& world, const LocalTransform2D& transform) const
	{
		Entity entity;
		CreateEntities(world, std::span(&entity, 1uz), std::span(&transform, 1uz));
		return entity;
	}

	void IHierarchyService::CreateEntities(IWorld& world, const std::span<Entity> entities, const LocalTransform2D& transform) const
	{
		CreateEntities(world, entities, std::span(&transform, 1uz));
	}

	Entity IHierarchyService::CreateEntity(IWorld& world, const LocalTransform3D& transform) const
	{
		Entity entity;
		CreateEntities(world, std::span(&entity, 1uz), std::span(&transform, 1uz));
		return entity;
	}

	void IHierarchyService::CreateEntities(IWorld& world, const std::span<Entity> entities, const LocalTransform3D& transform) const
	{
		CreateEntities(world, entities, std::span(&transform, 1uz));
	}

	Entity IHierarchyService::CreateEntity(IWorld& world, const Entity parent) const
	{
		Entity child;
		CreateEntities(world, parent, std::span(&child, 1uz));
		return child;
	}

	Entity IHierarchyService::CreateEntity(IWorld& world, const Entity parent, const LocalTransform2D& transform) const
	{
		Entity child;
		CreateEntities(world, parent, std::span(&child, 1uz), std::span(&transform, 1uz));
		return child;
	}

	void IHierarchyService::CreateEntities(IWorld& world, const Entity parent, const std::span<Entity> children, const LocalTransform2D& transform) const
	{
		CreateEntities(world, parent, children, std::span(&transform, 1uz));
	}

	Entity IHierarchyService::CreateEntity(IWorld& world, const Entity parent, const LocalTransform3D& transform) const
	{
		Entity child;
		CreateEntities(world, parent, std::span(&child, 1uz), std::span(&transform, 1uz));
		return child;
	}

	void IHierarchyService::CreateEntities(IWorld& world, const Entity parent, const std::span<Entity> children, const LocalTransform3D& transform) const
	{
		CreateEntities(world, parent, children, std::span(&transform, 1uz));
	}

	void IHierarchyService::DestroyEntity(IWorld& world, const Entity entity) const
	{
		DestroyEntities(world, std::span(&entity, 1uz));
	}

	void IHierarchyService::AttachChild(IWorld& world, const Entity parent, const Entity child) const
	{
		AttachChildren(world, parent, std::span(&child, 1uz));
	}

	void IHierarchyService::DetachChildren(IWorld& world, const Entity entity) const
	{
		DetachChildren(world, std::span(&entity, 1uz));
	}

	void IHierarchyService::AddLocalTransform2D(IWorld& world, const Entity entity, const LocalTransform2D& transform) const
	{
		AddLocalTransforms2D(world, std::span(&entity, 1uz), std::span(&transform, 1uz));
	}

	void IHierarchyService::AddLocalTransforms2D(IWorld& world, const std::span<const Entity> entities, const LocalTransform2D& transform) const
	{
		AddLocalTransforms2D(world, entities, std::span(&transform, 1uz));
	}

	void IHierarchyService::AddLocalTransform3D(IWorld& world, const Entity entity, const LocalTransform3D& transform) const
	{
		AddLocalTransforms3D(world, std::span(&entity, 1uz), std::span(&transform, 1uz));
	}

	void IHierarchyService::AddLocalTransforms3D(IWorld& world, const std::span<const Entity> entities, const LocalTransform3D& transform) const
	{
		AddLocalTransforms3D(world, entities, std::span(&transform, 1uz));
	}

	void IHierarchyService::RemoveTransforms2D(IWorld& world, const Entity entity) const
	{
		RemoveTransforms2D(world, std::span(&entity, 1uz));
	}

	void IHierarchyService::RemoveTransforms3D(IWorld& world, const Entity entity) const
	{
		RemoveTransforms3D(world, std::span(&entity, 1uz));
	}

	void IHierarchyService::AddDirtyTransform(IWorld& world, const Entity entity) const
	{
		AddDirtyTransforms(world, std::span(&entity, 1uz));
	}

	void IHierarchyService::RemoveDirtyTransform(IWorld& world, const Entity entity, const bool includeChildren) const
	{
		RemoveDirtyTransforms(world, std::span(&entity, 1uz), includeChildren);
	}
}
