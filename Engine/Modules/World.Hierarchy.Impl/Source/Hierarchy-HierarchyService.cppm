/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

export module PonyEngine.World.Hierarchy.Impl:HierarchyService;

import std;

import PonyEngine.Application;
import PonyEngine.Memory;
import PonyEngine.World.Hierarchy;

export namespace PonyEngine::World::Hierarchy
{
	class HierarchyService final : public IHierarchyService
	{
	public:
		virtual void RemoveInvalidParents(IWorld& world) const override;
		virtual void RemoveInvalidChildren(IWorld& world) const override;
		virtual void UpdateChildren(IWorld& world) const override;

		virtual void DestroyEntity(IWorld& world, Entity entity) const override;
		virtual void UpdateWorldTransforms(IWorld& world) const override;

	private:
		static void AddEntitiesToRemove(IWorld& world, const Entity entity, std::span<Entity> entitiesToRemove, std::size_t& entityToRemoveCount);

		Application::IApplication* application;
	};
}

namespace PonyEngine::World::Hierarchy
{
	void HierarchyService::RemoveInvalidParents(IWorld& world) const
	{
		static_assert(sizeof(Entity) == sizeof(Parent) && alignof(Entity) == alignof(Parent), "Invalid parent component");

		const std::size_t parentCount = world.CountComponents<Parent>();
		if (parentCount == 0uz)
		{
			return;
		}

		const std::size_t bufferSize = Memory::CalculateBufferSize<Entity>(parentCount) +
			Memory::CalculateBufferSize<Entity, Entity>(parentCount) +
			Memory::CalculateBufferSize<bool, Entity>(parentCount);
		const std::shared_ptr<Application::IBuffer> buffer = application->CreateBuffer(bufferSize);
		auto arena = Memory::Arena(buffer->Span());

		const std::span<Entity> entities = arena.AllocateArray<Entity>(parentCount);
		const std::span<Entity> parents = arena.AllocateArray<Entity>(parentCount);
		const std::span<bool> areValid = arena.AllocateArray<bool>(parentCount);

		world.GetComponents(entities, std::span(reinterpret_cast<Parent*>(parents.data()), parents.size()));

		if (!world.AreValid(parents, areValid))
		{
			std::size_t invalidCount = 0uz;
			for (std::size_t i = 0uz; i < parentCount; ++i)
			{
				entities[invalidCount] = entities[i];
				invalidCount += !areValid[i];
			}

			world.RemoveComponents<Parent>(entities.subspan(0uz, invalidCount));
		}
	}

	void HierarchyService::RemoveInvalidChildren(IWorld& world) const
	{
		static_assert(sizeof(Children) == sizeof(ObjectHandle<std::vector<Entity>>) && alignof(Children) == alignof(ObjectHandle<std::vector<Entity>>), "Invalid children component");

		const std::size_t childrenCount = world.CountComponents<Children>();
		if (childrenCount == 0uz)
		{
			return;
		}

		const std::size_t bufferSize = Memory::CalculateBufferSize<Entity>(childrenCount) +
			Memory::CalculateBufferSize<ObjectHandle<std::vector<Entity>>, Entity>(childrenCount) +
			Memory::CalculateBufferSize<bool, ObjectHandle<std::vector<Entity>>>(childrenCount);
		const std::shared_ptr<Application::IBuffer> buffer = application->CreateBuffer(bufferSize);
		auto arena = Memory::Arena(buffer->Span());

		const std::span<Entity> entities = arena.AllocateArray<Entity>(childrenCount);
		const std::span<ObjectHandle<std::vector<Entity>>> children = arena.AllocateArray<ObjectHandle<std::vector<Entity>>>(childrenCount);
		const std::span<bool> areValid = arena.AllocateArray<bool>(childrenCount);

		world.GetComponents(entities, std::span(reinterpret_cast<Children*>(children.data()), children.size()));

		bool areAllValid = true;
		for (std::size_t i = 0uz; i < childrenCount; ++i)
		{
			areAllValid = (areValid[i] = world.IsObjectValid(children[i]));
		}

		if (!areAllValid)
		{
			std::size_t invalidCount = 0uz;
			for (std::size_t i = 0uz; i < childrenCount; ++i)
			{
				entities[invalidCount] = entities[i];
				invalidCount += !areValid[i];
			}

			world.RemoveComponents<Children>(entities.subspan(0uz, invalidCount));
		}
	}

	void HierarchyService::UpdateChildren(IWorld& world) const
	{
		static_assert(sizeof(Entity) == sizeof(Parent) && alignof(Entity) == alignof(Parent), "Invalid parent component");

		const std::size_t childrenCount = world.CountComponents<Children>();
		const std::size_t parentCount = world.CountComponents<Parent>();

		if (childrenCount == 0uz && parentCount == 0uz)
		{
			return;
		}

		const std::size_t childrenClearBufferSize = Memory::CalculateBufferSize<Children*>(childrenCount);
		const std::size_t childrenUpdateBufferSize = Memory::CalculateBufferSize<Entity>(parentCount) +
			Memory::CalculateBufferSize<Entity, Entity>(parentCount) +
			Memory::CalculateBufferSize<Entity, Entity>(parentCount) +
			Memory::CalculateBufferSize<std::size_t, Entity>(parentCount) +
			Memory::CalculateBufferSize<Children*, std::size_t>(parentCount) +
			Memory::CalculateBufferSize<Entity, Children*>(parentCount) +
			Memory::CalculateBufferSize<bool, Entity>(parentCount);
		const std::size_t bufferSize = std::max(childrenClearBufferSize, childrenUpdateBufferSize);
		const std::shared_ptr<Application::IBuffer> buffer = application->CreateBuffer(bufferSize);
		auto arena = Memory::Arena(buffer->Span());

		const Memory::Arena::Marker marker = arena.GetMarker();

		if (childrenCount > 0uz)
		{
			const std::span<Children> children = arena.AllocateArray<Children>(childrenCount);
			world.GetComponents(children);

			for (const auto& [childrenObject] : children)
			{
				world.GetObject(childrenObject)->clear();
			}
		}

		if (parentCount > 0uz)
		{
			arena.Rewind(marker);
			const std::span<Entity> entities = arena.AllocateArray<Entity>(parentCount);
			const std::span<Entity> parents = arena.AllocateArray<Entity>(parentCount);
			const std::span<Entity> uniqueParentsProto = arena.AllocateArray<Entity>(parentCount);
			const std::span<std::size_t> parentToUniqueParent = arena.AllocateArray<std::size_t>(parentCount);

			world.GetComponents(entities, std::span(reinterpret_cast<Parent*>(parents.data()), parents.size()));

			std::size_t uniqueParentCount = 0uz;
			for (std::size_t i = 0uz; i < parentCount; ++i)
			{
				const std::size_t parentIndex = std::ranges::find(uniqueParentsProto.subspan(0uz, i), parents[i]) - uniqueParentsProto.cbegin();
				uniqueParentsProto[uniqueParentCount] = parents[i];
				parentToUniqueParent[i] = uniqueParentCount;
				uniqueParentCount += parentIndex == i;
			}

			const std::span<Entity> uniqueParents = uniqueParentsProto.subspan(0uz, uniqueParentCount);
			const std::span<Children*> childContainers = arena.AllocateArray<Children*>(uniqueParentCount);
			const std::span<Entity> newParents = arena.AllocateArray<Entity>(uniqueParentCount);
			const std::span<bool> haveChildrenContainers = arena.AllocateArray<bool>(uniqueParentCount);

			if (!world.HasComponents<Children>(uniqueParents, haveChildrenContainers))
			{
				std::size_t newParentCount = 0uz;
				for (std::size_t i = 0uz; i < uniqueParents.size(); ++i)
				{
					newParents[newParentCount] = uniqueParents[i];
					newParentCount += !haveChildrenContainers[i];
				}

				const std::span<Children*> newChildContainers = childContainers.subspan(0uz, newParentCount);
				world.AddComponents(newParents.subspan(0uz, newParentCount), newChildContainers);

				for (Children* const newChildContainer : newChildContainers)
				{
					newChildContainer->value = world.RegisterObject(std::make_shared<std::vector<Entity>>());
				}
			}

			world.GetComponents(uniqueParents, childContainers);

			for (std::size_t i = 0uz; i < entities.size(); ++i)
			{
				const std::size_t uniqueParentIndex = parentToUniqueParent[i];
				Children* const children = childContainers[uniqueParentIndex];
				world.GetObject(children->value)->push_back(entities[i]);
			}
		}
	}

	void HierarchyService::DestroyEntity(IWorld& world, const Entity entity) const
	{
		const std::size_t entityCount = world.EntityCount();

		const std::size_t bufferSize = Memory::CalculateBufferSize<Entity>(entityCount);
		const std::shared_ptr<Application::IBuffer> buffer = application->CreateBuffer(bufferSize);
		auto arena = Memory::Arena(buffer->Span());

		const std::span<Entity> entitiesToRemove = arena.AllocateArray<Entity>(entityCount);

		std::size_t entityToRemoveCount = 0uz;
		AddEntitiesToRemove(world, entity, entitiesToRemove, entityToRemoveCount);
		world.DestroyEntities(entitiesToRemove.subspan(0uz, entityToRemoveCount));
	}

	void HierarchyService::UpdateWorldTransforms(IWorld& world) const
	{
		const std::size_t localTransformCount = world.CountComponents<LocalTransform3D<float>>();
		if (localTransformCount == 0uz)
		{
			return;
		}

		const std::size_t bufferSize = Memory::CalculateBufferSize<Entity>(localTransformCount) +
			Memory::CalculateBufferSize<LocalTransform3D<float>, Entity>(localTransformCount) +
			Memory::CalculateBufferSize<WorldTransform3D<float>*, LocalTransform3D<float>>(localTransformCount) +
			Memory::CalculateBufferSize<Parent*, WorldTransform3D<float>*>(localTransformCount) +
			Memory::CalculateBufferSize<std::size_t, Parent*>(localTransformCount);
		const std::shared_ptr<Application::IBuffer> buffer = application->CreateBuffer(bufferSize);
		auto arena = Memory::Arena(buffer->Span());

		const std::span<Entity> entities = arena.AllocateArray<Entity>(localTransformCount);
		const std::span<LocalTransform3D<float>> localTransforms = arena.AllocateArray<LocalTransform3D<float>>(localTransformCount);
		const std::span<WorldTransform3D<float>*> worldTransforms = arena.AllocateArray<WorldTransform3D<float>*>(localTransformCount);
		const std::span<Parent*> parents = arena.AllocateArray<Parent*>(localTransformCount);
		const std::span<std::size_t> indices = arena.AllocateArray<std::size_t>(localTransformCount);

		world.GetComponents(entities, localTransforms);
		world.AddComponents(entities, worldTransforms);
		world.TryGetComponents(entities, parents);
		std::ranges::iota(indices, 0uz);
		std::ranges::sort(indices, [&](const std::size_t lhs, const std::size_t rhs) { return !parents[lhs] || parents[lhs]->value != entities[rhs]; });

		for (const std::size_t index : indices)
		{
		}
	}

	void HierarchyService::AddEntitiesToRemove(IWorld& world, const Entity entity, std::span<Entity> entitiesToRemove,
		std::size_t& entityToRemoveCount)
	{
		entitiesToRemove[entityToRemoveCount++] = entity;

		if (Children children; world.TryGetComponent(entity, children))
		{
			for (const Entity child : *world.GetObject(children.value))
			{
				AddEntitiesToRemove(world, child, entitiesToRemove, entityToRemoveCount);
			}
		}
	}
}
