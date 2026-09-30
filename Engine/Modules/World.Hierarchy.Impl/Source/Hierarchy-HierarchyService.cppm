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
	/// @brief Hierarchy service.
	class HierarchyService final : public IHierarchyService
	{
	public:
		/// @brief Creates a hierarchy service.
		/// @param application Application.
		[[nodiscard("Pure constructor")]]
		explicit HierarchyService(Application::IApplication& application);
		HierarchyService(const HierarchyService&) = delete;
		HierarchyService(HierarchyService&&) = delete;

		~HierarchyService() noexcept = default;

		virtual void RemoveInvalidParents(IWorld& world) const override;
		virtual void RemoveInvalidWorldTransforms2D(IWorld& world) const override;
		virtual void RemoveInvalidWorldTransforms3D(IWorld& world) const override;

		virtual void CreateEntities(IWorld& world, std::span<Entity> entities) const override;
		virtual void CreateEntities(IWorld& world, std::span<Entity> entities, std::span<const LocalTransform2D> transforms) const override;
		virtual void CreateEntities(IWorld& world, std::span<Entity> entities, std::span<const LocalTransform3D> transforms) const override;
		virtual void CreateEntities(IWorld& world, Entity parent, std::span<Entity> children) const override;
		virtual void CreateEntities(IWorld& world, Entity parent, std::span<Entity> children, std::span<const LocalTransform2D> transforms) const override;
		virtual void CreateEntities(IWorld& world, Entity parent, std::span<Entity> children, std::span<const LocalTransform3D> transforms) const override;
		virtual void DestroyEntities(IWorld& world, std::span<const Entity> entities) const override;
		virtual void AttachChildren(IWorld& world, Entity parent, std::span<const Entity> children) const override;
		virtual void DetachChildren(IWorld& world, std::span<const Entity> entities) const override;

		virtual void AddLocalTransforms2D(IWorld& world, std::span<const Entity> entities, std::span<const LocalTransform2D> transforms) const override;
		virtual void AddLocalTransforms3D(IWorld& world, std::span<const Entity> entities, std::span<const LocalTransform3D> transforms) const override;
		virtual void RemoveTransforms2D(IWorld& world, std::span<const Entity> entities) const override;
		virtual void RemoveTransforms3D(IWorld& world, std::span<const Entity> entities) const override;

		virtual void AddDirtyTransforms(IWorld& world, std::span<const Entity> entities) const override;
		virtual void RemoveDirtyTransforms(IWorld& world, std::span<const Entity> entities, bool includeChildren) const override;
		virtual void DropDirtyTransforms(IWorld& world) const override;

		virtual void PropagateDirtyTransforms(IWorld& world) const override;
		virtual void PropagateLocalTransforms2D(IWorld& world) const override;
		virtual void PropagateLocalTransforms3D(IWorld& world) const override;
		virtual void UpdateWorldTransforms2D(IWorld& world) const override;
		virtual void UpdateWorldTransforms3D(IWorld& world) const override;
		virtual void UpdateWorldTransforms2DIfDirty(IWorld& world) const override;
		virtual void UpdateWorldTransforms3DIfDirty(IWorld& world) const override;

		HierarchyService& operator =(const HierarchyService&) = delete;
		HierarchyService& operator =(HierarchyService&&) = delete;

	private:
		/// @brief Removes components of type @p T if their entities don't have components of type @p Guard.
		/// @tparam T Type of components to remove.
		/// @tparam Guard Guard component type.
		/// @param world World.
		template<Component T, Component Guard>
		void RemoveComponentsWithoutGuards(IWorld& world) const;

		/// @brief Propagates components.
		/// @tparam T Component type.
		/// @param world World.
		/// @param componentData Component data that is added to propagated entities. If nullptr, the components are just added.
		template<Component T>
		void PropagateComponents(IWorld& world, const T* componentData = nullptr) const;
		/// @brief Finds entities for propagation.
		/// @param checkEntities Initial check entities.
		/// @param entities All entities that are potentially may be propagated.
		/// @param parents Entity parents. Synced with the @p entities by index.
		/// @param targets Target buffer.
		/// @return How many entities were moved to the @p targets.
		[[nodiscard("Must be used")]]
		static std::size_t FindEntitiesForPropagation(std::span<const Entity> checkEntities,
			std::span<Entity> entities, std::span<Parent> parents, std::span<Entity> targets) noexcept;
		/// @brief Moves the entities to targets if their parents are found among the check entities.
		/// @param checkEntities Check entities.
		/// @param entities Entities to check.
		/// @param parents Entity parents. Synced with the @p entities by index.
		/// @param targets Target buffer.
		/// @return How many entities were moved.
		[[nodiscard("Must be used")]]
		static std::size_t MoveEntitiesIfParentsFound(std::span<const Entity> checkEntities, 
			std::span<Entity> entities, std::span<Parent> parents, std::span<Entity> targets) noexcept;

		/// @brief Updates all world transforms.
		/// @tparam Size Dimension.
		/// @param world World.
		template<std::size_t Size>
		void UpdateWorldTransforms(IWorld& world) const;
		/// @brief Updates world transforms if their entities have dirty transforms.
		/// @tparam Size Dimension.
		/// @param world World.
		template<std::size_t Size>
		void UpdateWorldTransformsIfDirty(IWorld& world) const;

		Application::IApplication* application; ///< Application.
	};
}

namespace PonyEngine::World::Hierarchy
{
	HierarchyService::HierarchyService(Application::IApplication& application) :
		application{&application}
	{
		IWorldService& worldService = this->application->GetInterface<IWorldService>();
		worldService.RegisterComponent<Parent>();
		worldService.RegisterComponent<LocalTransform2D>();
		worldService.RegisterComponent<LocalTransform3D>();
		worldService.RegisterComponent<WorldTransform2D>();
		worldService.RegisterComponent<WorldTransform3D>();
		worldService.RegisterComponent<DirtyTransform>();
	}

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

		world.GetComponents<Parent>(entities, std::span(reinterpret_cast<Parent*>(parents.data()), parents.size()));

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

	void HierarchyService::RemoveInvalidWorldTransforms2D(IWorld& world) const
	{
		RemoveComponentsWithoutGuards<WorldTransform2D, LocalTransform2D>(world);
	}

	void HierarchyService::RemoveInvalidWorldTransforms3D(IWorld& world) const
	{
		RemoveComponentsWithoutGuards<WorldTransform3D, LocalTransform3D>(world);
	}

	void HierarchyService::CreateEntities(IWorld& world, const std::span<Entity> entities) const
	{
		if (entities.size() == 0uz)
		{
			return;
		}

		world.CreateEntities(entities);
	}

	void HierarchyService::CreateEntities(IWorld& world, const std::span<Entity> entities, const std::span<const LocalTransform2D> transforms) const
	{
		if (entities.size() == 0uz)
		{
			return;
		}

		world.CreateEntities(entities);
		world.AddComponents<LocalTransform2D>(entities, transforms);
	}

	void HierarchyService::CreateEntities(IWorld& world, const std::span<Entity> entities, const std::span<const LocalTransform3D> transforms) const
	{
		if (entities.size() == 0uz)
		{
			return;
		}

		world.CreateEntities(entities);
		world.AddComponents<LocalTransform3D>(entities, transforms);
	}

	void HierarchyService::CreateEntities(IWorld& world, const Entity parent, const std::span<Entity> children) const
	{
		if (children.size() == 0uz)
		{
			return;
		}

		world.CreateEntities(children);
		world.AddComponents<Parent>(children, Parent{.value = parent});
	}

	void HierarchyService::CreateEntities(IWorld& world, const Entity parent, const std::span<Entity> children, const std::span<const LocalTransform2D> transforms) const
	{
		if (children.size() == 0uz)
		{
			return;
		}

		world.CreateEntities(children);
		world.AddComponents<Parent>(children, Parent{.value = parent});
		world.AddComponents<LocalTransform2D>(children, transforms);
	}

	void HierarchyService::CreateEntities(IWorld& world, const Entity parent, const std::span<Entity> children, const std::span<const LocalTransform3D> transforms) const
	{
		if (children.size() == 0uz)
		{
			return;
		}

		world.CreateEntities(children);
		world.AddComponents<Parent>(children, Parent{.value = parent});
		world.AddComponents<LocalTransform3D>(children, transforms);
	}

	void HierarchyService::DestroyEntities(IWorld& world, const std::span<const Entity> entities) const
	{
		if (entities.size() == 0uz)
		{
			return;
		}

		const std::size_t parentCount = world.CountComponents<Parent>();

		const std::size_t bufferSize = Memory::CalculateBufferSize<Entity>(parentCount) +
			Memory::CalculateBufferSize<Parent, Entity>(parentCount) +
			Memory::CalculateBufferSize<Entity, Parent>(entities.size() + parentCount);
		const std::shared_ptr<Application::IBuffer> buffer = application->CreateBuffer(bufferSize);
		auto arena = Memory::Arena(buffer->Span());

		const std::span<Entity> childEntities = arena.AllocateArray<Entity>(parentCount);
		const std::span<Parent> parents = arena.AllocateArray<Parent>(parentCount);
		const std::span<Entity> targets = arena.AllocateArray<Entity>(entities.size() + parentCount);

		world.GetComponents<Parent>(childEntities, parents);
		std::memcpy(targets.data(), entities.data(), entities.size_bytes());

		const std::size_t targetCount = FindEntitiesForPropagation(targets.subspan(0uz, entities.size()), childEntities, parents, 
			targets.subspan(entities.size(), parentCount));

		world.DestroyEntities(targets.subspan(0uz, entities.size() + targetCount));
	}

	void HierarchyService::AttachChildren(IWorld& world, const Entity parent, const std::span<const Entity> children) const
	{
		world.AddComponents<Parent>(children, Parent{.value = parent});
	}

	void HierarchyService::DetachChildren(IWorld& world, const std::span<const Entity> entities) const
	{
		const std::size_t parentCount = world.CountComponents<Parent>();
		if (parentCount == 0uz)
		{
			return;
		}

		const std::size_t bufferSize = Memory::CalculateBufferSize<Entity>(parentCount) +
			Memory::CalculateBufferSize<Parent, Entity>(parentCount);
		const std::shared_ptr<Application::IBuffer> buffer = application->CreateBuffer(bufferSize);
		auto arena = Memory::Arena(buffer->Span());

		const std::span<Entity> childEntities = arena.AllocateArray<Entity>(parentCount);
		const std::span<Parent> parents = arena.AllocateArray<Parent>(parentCount);

		world.GetComponents<Parent>(childEntities, parents);

		const std::span<const std::uint64_t> rawEntities = AsRawData(entities);
		std::size_t childCount = 0uz;
		for (std::size_t i = 0uz; i < parentCount; ++i)
		{
			childEntities[childCount] = childEntities[i];
			childCount += std::ranges::contains(rawEntities, AsRawData(parents[i].value));
		}

		if (childCount > 0uz)
		{
			world.RemoveComponents<Parent>(childEntities.subspan(0uz, childCount));
		}
	}

	void HierarchyService::AddLocalTransforms2D(IWorld& world, const std::span<const Entity> entities, const std::span<const LocalTransform2D> transforms) const
	{
		if (entities.size() == 0uz)
		{
			return;
		}

		world.AddComponents<LocalTransform2D>(entities, transforms);
	}

	void HierarchyService::AddLocalTransforms3D(IWorld& world, const std::span<const Entity> entities, const std::span<const LocalTransform3D> transforms) const
	{
		if (entities.size() == 0uz)
		{
			return;
		}

		world.AddComponents<LocalTransform3D>(entities, transforms);
	}

	void HierarchyService::RemoveTransforms2D(IWorld& world, const std::span<const Entity> entities) const
	{
		if (entities.size() == 0uz)
		{
			return;
		}

		world.RemoveComponents<WorldTransform2D>(entities);
		world.RemoveComponents<LocalTransform2D>(entities);
	}

	void HierarchyService::RemoveTransforms3D(IWorld& world, const std::span<const Entity> entities) const
	{
		if (entities.size() == 0uz)
		{
			return;
		}

		world.RemoveComponents<WorldTransform3D>(entities);
		world.RemoveComponents<LocalTransform3D>(entities);
	}

	void HierarchyService::AddDirtyTransforms(IWorld& world, const std::span<const Entity> entities) const
	{
		if (entities.size() == 0uz)
		{
			return;
		}

		world.AddComponents<DirtyTransform>(entities);
	}

	void HierarchyService::RemoveDirtyTransforms(IWorld& world, const std::span<const Entity> entities, const bool includeChildren) const
	{
		if (entities.size() == 0uz)
		{
			return;
		}

		if (includeChildren)
		{
			const std::size_t childCount = world.CountComponents<Parent>();
			if (childCount == 0uz)
			{
				world.RemoveComponents<DirtyTransform>(entities);
				return;
			}

			const std::size_t bufferSize = Memory::CalculateBufferSize<Entity>(childCount) +
				Memory::CalculateBufferSize<Parent, Entity>(childCount) +
				Memory::CalculateBufferSize<Entity, Parent>(entities.size() + childCount);
			const std::shared_ptr<Application::IBuffer> buffer = application->CreateBuffer(bufferSize);
			auto arena = Memory::Arena(buffer->Span());

			const std::span<Entity> childEntities = arena.AllocateArray<Entity>(childCount);
			const std::span<Parent> parents = arena.AllocateArray<Parent>(childCount);
			const std::span<Entity> targets = arena.AllocateArray<Entity>(entities.size() + childCount);

			world.GetComponents<Parent>(childEntities, parents);
			std::memcpy(targets.data(), entities.data(), entities.size_bytes());

			const std::size_t targetCount = FindEntitiesForPropagation(targets.subspan(0uz, entities.size()), childEntities, parents,
				targets.subspan(entities.size(), childCount));

			world.RemoveComponents<DirtyTransform>(targets.subspan(0uz, entities.size() + targetCount));
		}
		else
		{
			world.RemoveComponents<DirtyTransform>(entities);
		}
	}

	void HierarchyService::DropDirtyTransforms(IWorld& world) const
	{
		world.DropComponents<DirtyTransform>();
	}

	void HierarchyService::PropagateDirtyTransforms(IWorld& world) const
	{
		PropagateComponents<DirtyTransform>(world);
	}

	void HierarchyService::PropagateLocalTransforms2D(IWorld& world) const
	{
		PropagateComponents<LocalTransform2D>(world, &LocalTransform2D::Identity());
	}

	void HierarchyService::PropagateLocalTransforms3D(IWorld& world) const
	{
		PropagateComponents<LocalTransform3D>(world, &LocalTransform3D::Identity());
	}

	void HierarchyService::UpdateWorldTransforms2D(IWorld& world) const
	{
		UpdateWorldTransforms<2>(world);
	}

	void HierarchyService::UpdateWorldTransforms3D(IWorld& world) const
	{
		UpdateWorldTransforms<3>(world);
	}

	void HierarchyService::UpdateWorldTransforms2DIfDirty(IWorld& world) const
	{
		UpdateWorldTransformsIfDirty<2>(world);
	}

	void HierarchyService::UpdateWorldTransforms3DIfDirty(IWorld& world) const
	{
		UpdateWorldTransformsIfDirty<3>(world);
	}

	template<Component T, Component Guard>
	void HierarchyService::RemoveComponentsWithoutGuards(IWorld& world) const
	{
		constexpr auto query = MakeQuery(Required<T>(), Excluded<Guard>());

		const std::size_t queryCount = world.CountQuery(query.QueryParams);
		if (queryCount == 0uz)
		{
			return;
		}

		const std::size_t bufferSize = Memory::CalculateBufferSize<Entity>(queryCount);
		const std::shared_ptr<Application::IBuffer> buffer = application->CreateBuffer(bufferSize);
		auto arena = Memory::Arena(buffer->Span());

		const std::span<Entity> entities = arena.AllocateArray<Entity>(queryCount);
		std::size_t entityCount = 0uz;
		world.Query(query.QueryParams, [&](const QueryItem& item) noexcept
		{
			entities[entityCount++] = item.entity;
		});

		if (entityCount > 0uz)
		{
			world.RemoveComponents<T>(entities.subspan(0uz, entityCount));
		}
	}

	template<Component T>
	void HierarchyService::PropagateComponents(IWorld& world, const T* const componentData) const
	{
		constexpr auto childQuery = MakeQuery(Required<Parent>(), Excluded<T>());

		const std::size_t propagationCount = world.CountComponents<T>();
		const std::size_t childCount = world.CountQuery(childQuery.QueryParams);
		if (propagationCount == 0uz || childCount == 0uz)
		{
			return;
		}

		const std::size_t bufferSize = Memory::CalculateBufferSize<Entity>(propagationCount) +
			Memory::CalculateBufferSize<Entity, Entity>(childCount) +
			Memory::CalculateBufferSize<Parent, Entity>(childCount) +
			Memory::CalculateBufferSize<Entity, Parent>(childCount);
		const std::shared_ptr<Application::IBuffer> buffer = application->CreateBuffer(bufferSize);
		auto arena = Memory::Arena(buffer->Span());

		const std::span<Entity> propagationEntities = arena.AllocateArray<Entity>(propagationCount);
		const std::span<Entity> childEntities = arena.AllocateArray<Entity>(childCount);
		const std::span<Parent> parents = arena.AllocateArray<Parent>(childCount);
		const std::span<Entity> targets = arena.AllocateArray<Entity>(childCount);

		world.GetComponents<T>(propagationEntities);

		std::size_t checkChildCount = 0uz;
		world.Query(childQuery.QueryParams, [&](const QueryItem& item) noexcept
		{
			childEntities[checkChildCount] = item.entity;
			parents[checkChildCount] = childQuery.template GetRequired<Parent>(item);
			++checkChildCount;
		});

		const std::size_t targetCount = FindEntitiesForPropagation(propagationEntities, 
			childEntities.subspan(0uz, checkChildCount), parents.subspan(0uz, checkChildCount), targets);

		if (targetCount > 0uz)
		{
			const std::span<const Entity> targetEntities = targets.subspan(0uz, targetCount);
			if (componentData)
			{
				world.AddComponents<T>(targetEntities, *componentData);
			}
			else
			{
				world.AddComponents<T>(targetEntities);
			}
		}
	}

	std::size_t HierarchyService::FindEntitiesForPropagation(std::span<const Entity> checkEntities, 
		std::span<Entity> entities, std::span<Parent> parents, std::span<Entity> targets) noexcept
	{
		assert(entities.size() == parents.size() && "Entity and parent span sizes are mismatched.");
		assert(targets.size() >= entities.size() && "Not enough target size.");

		std::size_t targetCount = 0uz;
		std::size_t movedCount;
		do
		{
			movedCount = MoveEntitiesIfParentsFound(checkEntities, entities, parents, targets);

			checkEntities = targets.subspan(0uz, movedCount);
			const std::size_t entityCount = entities.size() - movedCount;
			entities = entities.subspan(0uz, entityCount);
			parents = parents.subspan(0uz, entityCount);
			targets = targets.subspan(movedCount, targets.size() - movedCount);

			targetCount += movedCount;
		} while (movedCount > 0uz);

		return targetCount;
	}

	std::size_t HierarchyService::MoveEntitiesIfParentsFound(const std::span<const Entity> checkEntities,
		const std::span<Entity> entities, const std::span<Parent> parents, const std::span<Entity> targets) noexcept
	{
		assert(entities.size() == parents.size() && "Entity and parent span sizes are mismatched.");
		assert(targets.size() >= entities.size() && "Not enough target size.");

		const std::span<const std::uint64_t> rawCheckEntities = AsRawData(checkEntities);

		std::size_t movedCount = 0uz;
		for (std::size_t i = 0uz; i < entities.size(); ++i)
		{
			const Entity entity = entities[i];
			const Parent parent = parents[i];
			const std::size_t index = i - movedCount;
			entities[index] = entity;
			parents[index] = parent;
			targets[movedCount] = entity;
			movedCount += std::ranges::contains(rawCheckEntities, AsRawData(parent.value));
		}

		return movedCount;
	}

	template<std::size_t Size>
	void HierarchyService::UpdateWorldTransforms(IWorld& world) const
	{
		using LTransform = LocalTransform<Size>;
		using WTransform = WorldTransform<Size>;

		const std::size_t transformCount = world.CountComponents<LTransform>();
		if (transformCount == 0uz)
		{
			return;
		}

		const std::size_t bufferSize = Memory::CalculateBufferSize<Entity>(transformCount) +
			Memory::CalculateBufferSize<Parent*, Entity>(transformCount) + 
			Memory::CalculateBufferSize<LTransform, Parent*>(transformCount) +
			Memory::CalculateBufferSize<WTransform*, LTransform>(transformCount) +
			Memory::CalculateBufferSize<std::size_t, WTransform*>(transformCount) +
			Memory::CalculateBufferSize<std::size_t, std::size_t>(transformCount) +
			Memory::CalculateBufferSize<std::size_t, std::size_t>(transformCount);
		const std::shared_ptr<Application::IBuffer> buffer = application->CreateBuffer(bufferSize);
		auto arena = Memory::Arena(buffer->Span());

		const std::span<Entity> entities = arena.AllocateArray<Entity>(transformCount);
		const std::span<Parent*> parents = arena.AllocateArray<Parent*>(transformCount);
		const std::span<LTransform> localTransforms = arena.AllocateArray<LTransform>(transformCount);
		const std::span<WTransform*> worldTransforms = arena.AllocateArray<WTransform*>(transformCount);
		const std::span<std::size_t> parentIndices = arena.AllocateArray<std::size_t>(transformCount);
		const std::span<std::size_t> depths = arena.AllocateArray<std::size_t>(transformCount);
		const std::span<std::size_t> updateIndices = arena.AllocateArray<std::size_t>(transformCount);

		world.GetComponents<LTransform>(entities, localTransforms);
		world.TryGetComponents<Parent>(entities, parents);
		world.AddComponents<WTransform>(entities, worldTransforms);

		const std::span<std::uint64_t> rawEntities = AsRawData(entities);
		for (std::size_t i = 0uz; i < transformCount; ++i)
		{
			const Parent* const parent = parents[i];
			parentIndices[i] = parent ? std::ranges::find(rawEntities, AsRawData(parent->value)) - rawEntities.cbegin() : std::numeric_limits<std::size_t>::max();
		}

		std::size_t rootCount = 0uz;
		for (std::size_t i = 0uz; i < transformCount; ++i)
		{
			std::size_t& depth = depths[i] = 0uz;
			std::size_t index = i;
			while (parentIndices[index] < transformCount)
			{
				++depth;
				index = parentIndices[index];
				assert(index != i && "Cycled parent hierarchy detected.");
			}
			rootCount += depth == 0uz;
		}

		std::ranges::iota(updateIndices, 0uz);
		std::ranges::sort(updateIndices, [&](const std::size_t lhs, const std::size_t rhs) noexcept { return depths[lhs] < depths[rhs]; });

		for (std::size_t i = 0uz; i < rootCount; ++i)
		{
			const std::size_t index = updateIndices[i];
			*worldTransforms[index] = WTransform(localTransforms[index]);
		}
		for (std::size_t i = rootCount; i < transformCount; ++i)
		{
			const std::size_t index = updateIndices[i];
			*worldTransforms[index] = Combine(*worldTransforms[parentIndices[index]], localTransforms[index]);
		}
	}

	template<std::size_t Size>
	void HierarchyService::UpdateWorldTransformsIfDirty(IWorld& world) const
	{
		using LTransform = LocalTransform<Size>;
		using WTransform = WorldTransform<Size>;

		constexpr auto transformQuery = MakeQuery(Required<LTransform, DirtyTransform>(), Optional<Parent>());

		const std::size_t transformCount = world.CountQuery(transformQuery.QueryParams);
		if (transformCount == 0uz)
		{
			return;
		}

		const std::size_t bufferSize = Memory::CalculateBufferSize<Entity>(transformCount) +
			Memory::CalculateBufferSize<Parent*, Entity>(transformCount) +
			Memory::CalculateBufferSize<LTransform*, Parent*>(transformCount) +
			Memory::CalculateBufferSize<WTransform*, LTransform*>(transformCount) +
			Memory::CalculateBufferSize<std::size_t, WTransform*>(transformCount) +
			Memory::CalculateBufferSize<bool, std::size_t>(transformCount) +
			Memory::CalculateBufferSize<std::size_t, bool>(transformCount) +
			Memory::CalculateBufferSize<std::size_t, std::size_t>(transformCount) +
			Memory::CalculateBufferSize<Entity, std::size_t>(transformCount) +
			Memory::CalculateBufferSize<WTransform*, Entity>(transformCount);
		const std::shared_ptr<Application::IBuffer> buffer = application->CreateBuffer(bufferSize);
		auto arena = Memory::Arena(buffer->Span());

		const std::span<Entity> entitiesProto = arena.AllocateArray<Entity>(transformCount);
		const std::span<Parent*> parentsProto = arena.AllocateArray<Parent*>(transformCount);
		const std::span<LTransform*> localTransformsProto = arena.AllocateArray<LTransform*>(transformCount);

		std::size_t entityCount = 0uz;
		world.Query(transformQuery.QueryParams, [&](const QueryItem& item) noexcept
		{
			entitiesProto[entityCount] = item.entity;
			parentsProto[entityCount] = transformQuery.template GetOptional<Parent>(item);
			localTransformsProto[entityCount] = &transformQuery.template GetRequired<LTransform>(item);
			++entityCount;
		});

		const std::span<Entity> entities = entitiesProto.subspan(0uz, entityCount);
		const std::span<Parent*> parents = parentsProto.subspan(0uz, entityCount);
		const std::span<LTransform*> localTransforms = localTransformsProto.subspan(0uz, entityCount);
		const std::span<WTransform*> worldTransforms = arena.AllocateArray<WTransform*>(entityCount);
		const std::span<std::size_t> parentIndices = arena.AllocateArray<std::size_t>(entityCount);
		const std::span<bool> isOuterParent = arena.AllocateArray<bool>(entityCount);
		const std::span<std::size_t> depths = arena.AllocateArray<std::size_t>(entityCount);
		const std::span<std::size_t> updateIndices = arena.AllocateArray<std::size_t>(entityCount);
		const std::span<Entity> outerParentEntitiesProto = arena.AllocateArray<Entity>(entityCount);

		world.AddComponents<WTransform>(entities, worldTransforms);

		const std::span<std::uint64_t> rawEntities = AsRawData(entities);
		const std::span<std::uint64_t> rawOuterParentEntitiesProto = AsRawData(outerParentEntitiesProto);
		std::size_t outerParentCount = 0uz;
		for (std::size_t i = 0uz; i < entityCount; ++i)
		{
			if (const Parent* const parent = parents[i])
			{
				if (std::size_t index = std::ranges::find(rawEntities, AsRawData(parent->value)) - rawEntities.cbegin(); index < rawEntities.size())
				{
					parentIndices[i] = index;
					isOuterParent[i] = false;
				}
				else
				{
					index = std::ranges::find(rawOuterParentEntitiesProto.subspan(0uz, outerParentCount), AsRawData(parent->value)) - rawOuterParentEntitiesProto.cbegin();
					parentIndices[i] = index;
					isOuterParent[i] = true;
					outerParentEntitiesProto[outerParentCount] = parent->value;
					outerParentCount += index == outerParentCount;
				}
			}
			else
			{
				parentIndices[i] = std::numeric_limits<std::size_t>::max();
				isOuterParent[i] = false;
			}
		}

		const std::span<Entity> outerParentEntities = outerParentEntitiesProto.subspan(0uz, outerParentCount);
		const std::span<WTransform*> outerParentWorldTransforms = arena.AllocateArray<WTransform*>(outerParentCount);
		world.TryGetComponents<WTransform>(outerParentEntities, outerParentWorldTransforms);

		std::size_t rootCount = 0uz;
		for (std::size_t i = 0uz; i < entityCount; ++i)
		{
			std::size_t& depth = depths[i] = isOuterParent[i];
			std::size_t index = i;
			while (!isOuterParent[index] && parentIndices[index] < entityCount)
			{
				++depth;
				index = parentIndices[index];
				assert(index != i && "Cycled parent hierarchy detected.");
			}
			rootCount += depth == 0uz;
		}

		std::ranges::iota(updateIndices, 0uz);
		std::ranges::sort(updateIndices, [&](const std::size_t lhs, const std::size_t rhs) noexcept { return depths[lhs] < depths[rhs]; });

		for (std::size_t i = 0uz; i < rootCount; ++i)
		{
			const std::size_t index = updateIndices[i];
			*worldTransforms[index] = WTransform(*localTransforms[index]);
		}
		for (std::size_t i = rootCount; i < transformCount; ++i)
		{
			const std::size_t index = updateIndices[i];
			const std::span<WTransform*> parentTransforms = isOuterParent[index] ? outerParentWorldTransforms : worldTransforms;
			const WTransform* const parentTransform = parentTransforms[parentIndices[index]];
			*worldTransforms[index] = Combine(parentTransform ? *parentTransform : WTransform::Identity(), *localTransforms[index]);
		}
	}
}
