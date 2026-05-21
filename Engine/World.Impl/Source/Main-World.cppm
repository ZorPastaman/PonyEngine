/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Log/Log.h"

export module PonyEngine.World.Impl:World;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.Log;
import PonyEngine.Memory;
import PonyEngine.World;

import :ComponentTable;
import :TagTable;
import :TypeRegistry;

export namespace PonyEngine::World
{
	class World final : public IWorld
	{
	public:
		[[nodiscard("Pure constructor")]]
		World(Application::IApplicationContext& application, const TypeRegistry& typeRegistry) noexcept;
		World(const World&) = delete;
		World(World&&) = delete;

		~World() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual std::span<const Entity> Entities() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual bool IsValid(Entity entity) const noexcept override;
		[[nodiscard("Wierd call")]] 
		virtual Entity CreateEntity() override;
		virtual void DestroyEntity(Entity entity) override;
		[[nodiscard("Pure function")]]
		virtual bool AreValid(std::span<const Entity> entities) const override;
		virtual void AreValid(std::span<const Entity> entities, std::span<bool> valid) const override;
		virtual void CreateEntities(std::span<Entity> entities) override;
		virtual void DestroyEntities(std::span<const Entity> entities) override;

		virtual void AddComponent(Entity entity, std::type_index componentType, const void* componentData) override;
		virtual void* AddComponent(Entity entity, std::type_index componentType) override;
		virtual void AddComponents(std::span<const Entity> entities, std::type_index componentType, const void* componentData) override;
		virtual void AddComponents(std::span<const Entity> entities, std::type_index componentType, std::span<void*> componentPointers) override;

		virtual void RemoveComponent(Entity entity, std::type_index componentType) override;
		virtual void RemoveComponents(std::span<const Entity> entities, std::type_index componentType) override;

		virtual void AddTag(Entity entity, std::type_index tagType) override;
		virtual void AddTags(std::span<const Entity> entities, std::type_index tagType) override;

		virtual void RemoveTag(Entity entity, std::type_index tagType) override;
		virtual void RemoveTags(std::span<const Entity> entities, std::type_index tagType) override;

		[[nodiscard("Pure function")]] 
		virtual bool HasComponent(Entity entity, std::type_index componentType) const override;
		[[nodiscard("Pure function")]] 
		virtual bool HasComponents(std::span<const Entity> entities, std::type_index componentType) const override;
		virtual void HasComponents(std::span<const Entity> entities, std::type_index componentType, std::span<bool> has) const override;

		[[nodiscard("Pure function")]] 
		virtual bool HasTag(Entity entity, std::type_index tagType) const override;
		[[nodiscard("Pure function")]]
		virtual bool HasTags(std::span<const Entity> entities, std::type_index tagType) const override;
		virtual void HasTags(std::span<const Entity> entities, std::type_index tagType, std::span<bool> has) const override;

		virtual void DropComponents(std::type_index componentType) override;
		virtual void DropTags(std::type_index tagType) override;

		World& operator =(const World&) = delete;
		World& operator =(World&&) = delete;

	private:
		[[nodiscard("Pure function")]]
		bool IsValid(std::size_t entityIndex, Entity entity) const noexcept;
		[[nodiscard("Pure function")]]
		std::size_t FindEntityIndex(EntityID entityId, std::size_t startIndex = 0uz) const noexcept;

		[[nodiscard("Pure function")]]
		Entity CreateNewEntity() noexcept;
		[[nodiscard("Pure function")]]
		Entity ResurrectEntity() noexcept;
		[[nodiscard("Pure function")]]
		Entity CreateOrResurrectEntity();
		void ReserveEntities(std::size_t addSize);
		void InsertEntity(Entity entity);
		void InsertEntity(std::size_t index, Entity entity);
		void InsertEntities(std::span<const Entity> entities);
		void RemoveEntity(std::size_t index) noexcept;
		void RemoveEntities(std::span<const std::size_t> indices) noexcept;

		ComponentTable& GetOrCreateComponentTable(std::type_index componentType);
		std::pair<void*, std::size_t> GetOrCreateComponent(Entity entity, std::type_index componentType);
		std::size_t GetOrCreateComponents(std::span<const Entity> entities, std::type_index componentType, std::span<std::size_t> tableIndices,
			std::span<std::size_t> tableIndicesToCreate, std::span<EntityID> entityIdsToCreate, std::span<void*> componentPointers);
		static void RemoveComponent(ComponentTable& table, Entity entity) noexcept;
		static void RemoveComponents(ComponentTable& table, std::span<const Entity> entities, std::span<std::size_t> tableIndices) noexcept;
		void RemoveComponents(Entity entity) noexcept;
		void RemoveComponents(std::span<const Entity> entities, std::span<std::size_t> tableIndices) noexcept;

		TagTable& GetOrCreateTagTable(std::type_index tagType);
		void GetOrCreateTag(Entity entity, std::type_index tagType);
		void GetOrCreateTags(std::span<const Entity> entities, std::type_index tagType, std::span<std::size_t> tableIndices,
			std::span<std::size_t> tableIndicesToCreate, std::span<EntityID> entityIdsToCreate);
		static void RemoveTag(TagTable& table, Entity entity) noexcept;
		static void RemoveTags(TagTable& table, std::span<const Entity> entities, std::span<std::size_t> tableIndices) noexcept;
		void RemoveTags(Entity entity) noexcept;
		void RemoveTags(std::span<const Entity> entities, std::span<std::size_t> tableIndices) noexcept;

		void CheckIfValid(Entity entity) const;
		void CheckIfValid(std::size_t entityIndex, Entity entity) const;
		static void CheckIfSorted(std::span<const Entity> entities);
		void CheckIfValid(std::span<const Entity> entities) const;

		Application::IApplicationContext* application;

		const TypeRegistry* typeRegistry;

		std::vector<ComponentTable> componentTables;
		std::vector<TagTable> tagTables;
		std::unordered_map<std::type_index, std::size_t> componentTableIndices;
		std::unordered_map<std::type_index, std::size_t> tagTableIndices;

		std::vector<Entity> aliveEntities;
		std::stack<Entity> deadEntities;

		Memory::Arena arena;

		EntityID nextEntityId;
	};
}

namespace PonyEngine::World
{
	World::World(Application::IApplicationContext& application, const TypeRegistry& typeRegistry) noexcept :
		application{&application},
		typeRegistry{&typeRegistry},
		arena(512uz),
		nextEntityId{1u}
	{
	}

	std::span<const Entity> World::Entities() const noexcept
	{
		return aliveEntities;
	}

	bool World::IsValid(const Entity entity) const noexcept
	{
		return IsValid(FindEntityIndex(entity.id), entity);
	}

	Entity World::CreateEntity()
	{
		ReserveEntities(1uz);

		const Entity entity = CreateOrResurrectEntity();
		InsertEntity(entity);

		return entity;
	}

	void World::DestroyEntity(const Entity entity)
	{
		const std::size_t entityIndex = FindEntityIndex(entity.id);
		CheckIfValid(entityIndex, entity);

		RemoveComponents(entity);
		RemoveTags(entity);
		RemoveEntity(entityIndex);
	}

	bool World::AreValid(const std::span<const Entity> entities) const
	{
		CheckIfSorted(entities);

		for (std::size_t i = 0, entityIndex = 0uz; i < entities.size(); ++i)
		{
			const Entity entity = entities[i];
			entityIndex = FindEntityIndex(entity.id, entityIndex);
			
			if (!IsValid(entityIndex, entity))
			{
				return false;
			}
		}

		return true;
	}

	void World::AreValid(const std::span<const Entity> entities, const std::span<bool> valid) const
	{
		CheckIfSorted(entities);

#ifndef NDEBUG
		if (entities.size() != valid.size()) [[unlikely]]
		{
			throw std::invalid_argument("Entity and valid span sizes are mismatched");
		}
#endif

		for (std::size_t i = 0, entityIndex = 0uz; i < entities.size(); ++i)
		{
			const Entity entity = entities[i];
			entityIndex = FindEntityIndex(entity.id, entityIndex);
			valid[i] = IsValid(entityIndex, entity);
		}
	}

	void World::CreateEntities(const std::span<Entity> entities)
	{
		if (entities.size() > deadEntities.size() && 0u - nextEntityId < entities.size() - deadEntities.size()) [[unlikely]]
		{
			throw std::logic_error("No more new entities available");
		}

		ReserveEntities(entities.size());

		std::size_t index = 0uz;
		for (; index < entities.size() && !deadEntities.empty(); ++index)
		{
			entities[index] = ResurrectEntity();
		}
		std::ranges::sort(&entities[0], &entities[index]);
		for (; index < entities.size(); ++index)
		{
			entities[index] = CreateNewEntity();
		}

		InsertEntities(entities);
	}

	void World::DestroyEntities(const std::span<const Entity> entities)
	{
		CheckIfSorted(entities);

		arena.Free();

		const Memory::Arena::Slice<std::size_t> entityIndicesSlice = arena.Allocate<std::size_t>(entities.size());
		const Memory::Arena::Slice<std::size_t> tableIndicesSlice = arena.Allocate<std::size_t>(entities.size());
		const std::span<std::size_t> entityIndices = arena.Span(entityIndicesSlice);
		const std::span<std::size_t> tableIndices = arena.Span(tableIndicesSlice);

		bool isValid = true;
		for (std::size_t i = 0uz, entityIndex = 0uz; i < entities.size(); ++i)
		{
			const Entity entity = entities[i];
			entityIndex = FindEntityIndex(entity.id, entityIndex);
			entityIndices[i] = entityIndex;
			isValid &= IsValid(entityIndex, entity);
		}

#ifndef NDEBUG
		if (!isValid) [[unlikely]]
		{
			throw std::invalid_argument("Invalid entity");
		}
#endif

		RemoveComponents(entities, tableIndices);
		RemoveTags(entities, tableIndices);
		RemoveEntities(entityIndices);
	}

	void World::AddComponent(const Entity entity, const std::type_index componentType, const void* const componentData)
	{
#ifndef NDEBUG
		if (!componentData) [[unlikely]]
		{
			throw std::invalid_argument("Component data is nullptr");
		}
#endif

		const auto [component, componentSize] = GetOrCreateComponent(entity, componentType);
		std::memcpy(component, componentData, componentSize);
	}

	void* World::AddComponent(const Entity entity, const std::type_index componentType)
	{
		return GetOrCreateComponent(entity, componentType).first;
	}

	void World::AddComponents(const std::span<const Entity> entities, const std::type_index componentType, const void* const componentData)
	{
#ifndef NDEBUG
		if (!componentData) [[unlikely]]
		{
			throw std::invalid_argument("Component data is nullptr");
		}
#endif

		arena.Free();

		const Memory::Arena::Slice<std::size_t> tableIndicesSlice = arena.Allocate<std::size_t>(entities.size());
		const Memory::Arena::Slice<std::size_t> tableIndicesToCreateSlice = arena.Allocate<std::size_t>(entities.size());
		const Memory::Arena::Slice<EntityID> entityIdsToCreateSlice = arena.Allocate<EntityID>(entities.size());
		const Memory::Arena::Slice<void*> componentPointersSlice = arena.Allocate<void*>(entities.size());
		const std::span<std::size_t> tableIndices = arena.Span(tableIndicesSlice);
		const std::span<std::size_t> tableIndicesToCreate = arena.Span(tableIndicesToCreateSlice);
		const std::span<EntityID> entityIdsToCreate = arena.Span(entityIdsToCreateSlice);
		const std::span<void*> componentPointers = arena.Span(componentPointersSlice);

		const std::size_t componentSize = GetOrCreateComponents(entities, componentType, tableIndices, tableIndicesToCreate, entityIdsToCreate, componentPointers);

		auto componentDataBytes = static_cast<const std::byte*>(componentData);
		for (std::size_t i = 0uz; i < componentPointers.size(); ++i, componentDataBytes += componentSize)
		{
			std::memcpy(componentPointers[i], componentDataBytes, componentSize);
		}
	}

	void World::AddComponents(const std::span<const Entity> entities, const std::type_index componentType, const std::span<void*> componentPointers)
	{
#ifndef NDEBUG
		if (entities.size() != componentPointers.size()) [[unlikely]]
		{
			throw std::invalid_argument("Entity and component pointer span sizes are mismatched");
		}
#endif

		arena.Free();

		const Memory::Arena::Slice<std::size_t> tableIndicesSlice = arena.Allocate<std::size_t>(entities.size());
		const Memory::Arena::Slice<std::size_t> tableIndicesToCreateSlice = arena.Allocate<std::size_t>(entities.size());
		const Memory::Arena::Slice<EntityID> entityIdsToCreateSlice = arena.Allocate<EntityID>(entities.size());
		const std::span<std::size_t> tableIndices = arena.Span(tableIndicesSlice);
		const std::span<std::size_t> tableIndicesToCreate = arena.Span(tableIndicesToCreateSlice);
		const std::span<EntityID> entityIdsToCreate = arena.Span(entityIdsToCreateSlice);
		
		GetOrCreateComponents(entities, componentType, tableIndices, tableIndicesToCreate, entityIdsToCreate, componentPointers);
	}

	void World::RemoveComponent(const Entity entity, const std::type_index componentType)
	{
		CheckIfValid(entity);

		if (const auto position = componentTableIndices.find(componentType); position != componentTableIndices.cend()) [[likely]]
		{
			RemoveComponent(componentTables[position->second], entity);
		}
#ifndef NDEBUG
		else if (!typeRegistry->IsValidComponent(componentType)) [[unlikely]]
		{
			throw std::invalid_argument("Component type is not registered");
		}
#endif
	}

	void World::RemoveComponents(const std::span<const Entity> entities, const std::type_index componentType)
	{
		CheckIfValid(entities);

		if (const auto position = componentTableIndices.find(componentType); position != componentTableIndices.cend()) [[likely]]
		{
			arena.Free();

			const Memory::Arena::Slice<std::size_t> tableIndicesSlice = arena.Allocate<std::size_t>(entities.size());
			const std::span<std::size_t> tableIndices = arena.Span(tableIndicesSlice);

			RemoveComponents(componentTables[position->second], entities, tableIndices);
		}
#ifndef NDEBUG
		else if (!typeRegistry->IsValidComponent(componentType)) [[unlikely]]
		{
			throw std::invalid_argument("Component type is not registered");
		}
#endif
	}

	void World::AddTag(const Entity entity, const std::type_index tagType)
	{
		GetOrCreateTag(entity, tagType);
	}

	void World::AddTags(const std::span<const Entity> entities, const std::type_index tagType)
	{
		arena.Free();

		const Memory::Arena::Slice<std::size_t> tableIndicesSlice = arena.Allocate<std::size_t>(entities.size());
		const Memory::Arena::Slice<std::size_t> tableIndicesToCreateSlice = arena.Allocate<std::size_t>(entities.size());
		const Memory::Arena::Slice<EntityID> entityIdsToCreateSlice = arena.Allocate<EntityID>(entities.size());
		const std::span<std::size_t> tableIndices = arena.Span(tableIndicesSlice);
		const std::span<std::size_t> tableIndicesToCreate = arena.Span(tableIndicesToCreateSlice);
		const std::span<EntityID> entityIdsToCreate = arena.Span(entityIdsToCreateSlice);

		GetOrCreateTags(entities, tagType, tableIndices, tableIndicesToCreate, entityIdsToCreate);
	}

	void World::RemoveTag(const Entity entity, const std::type_index tagType)
	{
		CheckIfValid(entity);

		if (const auto position = tagTableIndices.find(tagType); position != tagTableIndices.cend()) [[likely]]
		{
			RemoveTag(tagTables[position->second], entity);
		}
#ifndef NDEBUG
		else if (!typeRegistry->IsValidTag(tagType)) [[unlikely]]
		{
			throw std::invalid_argument("Tag type is not registered");
		}
#endif
	}

	void World::RemoveTags(const std::span<const Entity> entities, const std::type_index tagType)
	{
		CheckIfValid(entities);

		if (const auto position = tagTableIndices.find(tagType); position != tagTableIndices.cend()) [[likely]]
		{
			arena.Free();

			const Memory::Arena::Slice<std::size_t> tableIndicesSlice = arena.Allocate<std::size_t>(entities.size());
			const std::span<std::size_t> tableIndices = arena.Span(tableIndicesSlice);

			RemoveTags(tagTables[position->second], entities, tableIndices);
		}
#ifndef NDEBUG
		else if (!typeRegistry->IsValidTag(tagType)) [[unlikely]]
		{
			throw std::invalid_argument("Tag type is not registered");
		}
#endif
	}

	bool World::HasComponent(const Entity entity, const std::type_index componentType) const
	{
		CheckIfValid(entity);

		if (const auto position = componentTableIndices.find(componentType); position != componentTableIndices.cend()) [[likely]]
		{
			const ComponentTable& table = componentTables[position->second];
			const std::size_t tableIndex = table.Find(entity.id);
			return table.IsValid(tableIndex, entity.id);
		}
#ifndef NDEBUG
		if (!typeRegistry->IsValidComponent(componentType)) [[unlikely]]
		{
			throw std::invalid_argument("Component type is not registered");
		}
#endif

		return false;
	}

	bool World::HasComponents(const std::span<const Entity> entities, const std::type_index componentType) const
	{
		CheckIfValid(entities);

		if (const auto position = componentTableIndices.find(componentType); position != componentTableIndices.cend()) [[likely]]
		{
			const ComponentTable& table = componentTables[position->second];

			for (std::size_t i = 0uz, tableIndex = 0uz; i < entities.size(); ++i)
			{
				const EntityID entityId = entities[i].id;
				tableIndex = table.Find(entityId, tableIndex);

				if (!table.IsValid(tableIndex, entityId))
				{
					return false;
				}
			}

			return true;
		}
#ifndef NDEBUG
		if (!typeRegistry->IsValidComponent(componentType)) [[unlikely]]
		{
			throw std::invalid_argument("Component type is not registered");
		}
#endif

		return entities.empty();
	}

	void World::HasComponents(const std::span<const Entity> entities, const std::type_index componentType, const std::span<bool> has) const
	{
#ifndef NDEBUG
		if (entities.size() != has.size()) [[unlikely]]
		{
			throw std::invalid_argument("Entity and has span sizes are mismatched");
		}
#endif

		CheckIfValid(entities);

		if (const auto position = componentTableIndices.find(componentType); position != componentTableIndices.cend()) [[likely]]
		{
			const ComponentTable& table = componentTables[position->second];
			
			for (std::size_t i = 0uz, tableIndex = 0uz; i < entities.size(); ++i)
			{
				const EntityID entityId = entities[i].id;
				tableIndex = table.Find(entityId, tableIndex);
				has[i] = table.IsValid(tableIndex, entityId);
			}
		}
#ifndef NDEBUG
		else if (!typeRegistry->IsValidComponent(componentType)) [[unlikely]]
		{
			throw std::invalid_argument("Component type is not registered");
		}
#endif
	}

	bool World::HasTag(const Entity entity, const std::type_index tagType) const
	{
		CheckIfValid(entity);

		if (const auto position = tagTableIndices.find(tagType); position != tagTableIndices.cend()) [[likely]]
		{
			const TagTable& table = tagTables[position->second];
			const std::size_t tableIndex = table.Find(entity.id);
			return table.IsValid(tableIndex, entity.id);
		}
#ifndef NDEBUG
		if (!typeRegistry->IsValidTag(tagType)) [[unlikely]]
		{
			throw std::invalid_argument("Tag type is not registered");
		}
#endif

		return false;
	}

	bool World::HasTags(const std::span<const Entity> entities, const std::type_index tagType) const
	{
		CheckIfValid(entities);

		if (const auto position = tagTableIndices.find(tagType); position != tagTableIndices.cend()) [[likely]]
		{
			const TagTable& table = tagTables[position->second];

			for (std::size_t i = 0uz, tableIndex = 0uz; i < entities.size(); ++i)
			{
				const EntityID entityId = entities[i].id;
				tableIndex = table.Find(entityId, tableIndex);

				if (!table.IsValid(tableIndex, entityId))
				{
					return false;
				}
			}

			return true;
		}
#ifndef NDEBUG
		if (!typeRegistry->IsValidTag(tagType)) [[unlikely]]
		{
			throw std::invalid_argument("Tag type is not registered");
		}
#endif

		return entities.empty();
	}

	void World::HasTags(const std::span<const Entity> entities, const std::type_index tagType, const std::span<bool> has) const
	{
#ifndef NDEBUG
		if (entities.size() != has.size()) [[unlikely]]
		{
			throw std::invalid_argument("Entity and has span sizes are mismatched");
		}
#endif

		CheckIfValid(entities);

		if (const auto position = tagTableIndices.find(tagType); position != tagTableIndices.cend()) [[likely]]
		{
			const TagTable& table = tagTables[position->second];

			for (std::size_t i = 0uz, tableIndex = 0uz; i < entities.size(); ++i)
			{
				const EntityID entityId = entities[i].id;
				tableIndex = table.Find(entityId, tableIndex);
				has[i] = table.IsValid(tableIndex, entityId);
			}
		}
#ifndef NDEBUG
		else if (!typeRegistry->IsValidTag(tagType)) [[unlikely]]
		{
			throw std::invalid_argument("Tag type is not registered");
		}
#endif
	}

	void World::DropComponents(const std::type_index componentType)
	{
		if (const auto position = componentTableIndices.find(componentType); position != componentTableIndices.cend()) [[likely]]
		{
			componentTables[position->second].Clear();
		}
#ifndef NDEBUG
		else if (!typeRegistry->IsValidComponent(componentType)) [[unlikely]]
		{
			throw std::invalid_argument("Component type is not registered");
		}
#endif
	}

	void World::DropTags(const std::type_index tagType)
	{
		if (const auto position = tagTableIndices.find(tagType); position != tagTableIndices.cend()) [[likely]]
		{
			tagTables[position->second].Clear();
		}
#ifndef NDEBUG
		else if (!typeRegistry->IsValidTag(tagType)) [[unlikely]]
		{
			throw std::invalid_argument("Tag type is not registered");
		}
#endif
	}

	bool World::IsValid(const std::size_t entityIndex, const Entity entity) const noexcept
	{
		return entityIndex < aliveEntities.size() && aliveEntities[entityIndex] == entity;
	}

	std::size_t World::FindEntityIndex(const EntityID entityId, const std::size_t startIndex) const noexcept
	{
		return std::lower_bound(aliveEntities.cbegin() + startIndex, aliveEntities.cend(), entityId, 
			[](const Entity& entity, const EntityID& value) { return entity.id < value; }) - aliveEntities.begin();
	}

	Entity World::CreateNewEntity() noexcept
	{
		return Entity{.id = nextEntityId++};
	}

	Entity World::ResurrectEntity() noexcept
	{
		Entity entity = deadEntities.top();
		deadEntities.pop();
		++entity.generation;

		return entity;
	}

	Entity World::CreateOrResurrectEntity()
	{
		if (deadEntities.empty())
		{
			if (nextEntityId == 0u) [[unlikely]]
			{
				throw std::logic_error("No more new entities available");
			}

			return CreateNewEntity();
		}

		return ResurrectEntity();
	}

	void World::ReserveEntities(const std::size_t addSize)
	{
		aliveEntities.reserve(aliveEntities.size() + addSize);
	}

	void World::InsertEntity(const Entity entity)
	{
		InsertEntity(FindEntityIndex(entity.id), entity);
	}

	void World::InsertEntity(const std::size_t index, const Entity entity)
	{
		aliveEntities.insert(aliveEntities.cbegin() + index, entity);
	}

	void World::InsertEntities(const std::span<const Entity> entities)
	{
		for (const Entity entity : entities)
		{
			InsertEntity(entity);
		}
	}

	void World::RemoveEntity(const std::size_t index) noexcept
	{
		const auto entity = aliveEntities[index];
		aliveEntities.erase(aliveEntities.cbegin() + index);

		try
		{
			deadEntities.push(entity);
		}
		catch (...)
		{
			PONY_LOG_X(application->Logger(), std::current_exception(), "On pushing entity to dead entities.");
		}
	}

	void World::RemoveEntities(const std::span<const std::size_t> indices) noexcept
	{
		for (std::size_t i = indices.size(); i-- > 0uz; )
		{
			RemoveEntity(indices[i]);
		}
	}

	ComponentTable& World::GetOrCreateComponentTable(const std::type_index componentType)
	{
		if (const auto position = componentTableIndices.find(componentType); position != componentTableIndices.cend()) [[likely]]
		{
			return componentTables[position->second];
		}

		componentTables.push_back(typeRegistry->CreateComponentTable(componentType));
		try
		{
			componentTableIndices[componentType] = componentTables.size() - 1uz;
		}
		catch (...)
		{
			componentTables.pop_back();
			throw;
		}

		return componentTables.back();
	}

	std::pair<void*, std::size_t> World::GetOrCreateComponent(const Entity entity, const std::type_index componentType)
	{
		CheckIfValid(entity);

		ComponentTable& table = GetOrCreateComponentTable(componentType);
		const std::size_t tableIndex = table.Find(entity.id);
		if (!table.IsValid(tableIndex, entity.id))
		{
			table.Insert(tableIndex, entity.id);
		}

		return std::pair(table.GetComponent(tableIndex), table.ComponentSize());
	}

	std::size_t World::GetOrCreateComponents(const std::span<const Entity> entities, const std::type_index componentType, const std::span<std::size_t> tableIndices,
		const std::span<std::size_t> tableIndicesToCreate, const std::span<EntityID> entityIdsToCreate, const std::span<void*> componentPointers)
	{
		CheckIfValid(entities);

		ComponentTable& table = GetOrCreateComponentTable(componentType);
		std::size_t entitiesToCreateCount = 0uz;

		for (std::size_t i = 0uz, tableIndex = 0uz; i < entities.size(); ++i)
		{
			const EntityID entityId = entities[i].id;
			tableIndex = table.Find(entityId, tableIndex);
			const bool isValid = table.IsValid(tableIndex, entityId);

			const std::size_t fixedTableIndex = tableIndex + entitiesToCreateCount;
			tableIndices[i] = fixedTableIndex;
			tableIndicesToCreate[entitiesToCreateCount] = fixedTableIndex;
			entityIdsToCreate[entitiesToCreateCount] = entityId;
			entitiesToCreateCount += !isValid;
		}

		table.Reserve(entitiesToCreateCount);
		for (std::size_t i = 0uz; i < entitiesToCreateCount; ++i)
		{
			table.Insert(tableIndicesToCreate[i], entityIdsToCreate[i]);
		}

		for (std::size_t i = 0uz; i < tableIndices.size(); ++i)
		{
			componentPointers[i] = table.GetComponent(tableIndices[i]);
		}

		return table.ComponentSize();
	}

	void World::RemoveComponent(ComponentTable& table, const Entity entity) noexcept
	{
		if (const std::size_t targetIndex = table.Find(entity.id); table.IsValid(targetIndex, entity.id))
		{
			table.Remove(targetIndex);
		}
	}

	void World::RemoveComponents(ComponentTable& table, const std::span<const Entity> entities, const std::span<std::size_t> tableIndices) noexcept
	{
		std::size_t tableDestroyCount = 0uz;

		for (std::size_t tableIndex = 0uz; const Entity entity : entities)
		{
			tableIndex = table.Find(entity.id, tableIndex);
			const bool isValidEntity = table.IsValid(tableIndex, entity.id);
			tableIndices[tableDestroyCount] = tableIndex;
			tableDestroyCount += isValidEntity;
		}

		for (std::size_t i = tableDestroyCount; i-- > 0uz; )
		{
			table.Remove(tableIndices[i]);
		}
	}

	void World::RemoveComponents(const Entity entity) noexcept
	{
		for (ComponentTable& table : componentTables)
		{
			RemoveComponent(table, entity);
		}
	}

	void World::RemoveComponents(const std::span<const Entity> entities, const std::span<std::size_t> tableIndices) noexcept
	{
		for (ComponentTable& table : componentTables)
		{
			RemoveComponents(table, entities, tableIndices);
		}
	}

	TagTable& World::GetOrCreateTagTable(const std::type_index tagType)
	{
		if (const auto position = tagTableIndices.find(tagType); position != tagTableIndices.cend()) [[likely]]
		{
			return tagTables[position->second];
		}

		tagTables.push_back(typeRegistry->CreateTagTable(tagType));
		try
		{
			tagTableIndices[tagType] = tagTables.size() - 1uz;
		}
		catch (...)
		{
			tagTables.pop_back();
			throw;
		}

		return tagTables.back();
	}

	void World::GetOrCreateTag(const Entity entity, const std::type_index tagType)
	{
		CheckIfValid(entity);

		TagTable& table = GetOrCreateTagTable(tagType);
		const std::size_t tableIndex = table.Find(entity.id);
		if (!table.IsValid(tableIndex, entity.id))
		{
			table.Insert(tableIndex, entity.id);
		}
	}

	void World::GetOrCreateTags(const std::span<const Entity> entities, const std::type_index tagType, const std::span<std::size_t> tableIndices, 
		const std::span<std::size_t> tableIndicesToCreate, const std::span<EntityID> entityIdsToCreate)
	{
		CheckIfValid(entities);

		TagTable& table = GetOrCreateTagTable(tagType);
		std::size_t entitiesToCreateCount = 0uz;

		for (std::size_t i = 0uz, tableIndex = 0uz; i < entities.size(); ++i)
		{
			const EntityID entityId = entities[i].id;
			tableIndex = table.Find(entityId, tableIndex);
			const bool isValid = table.IsValid(tableIndex, entityId);

			const std::size_t fixedTableIndex = tableIndex + entitiesToCreateCount;
			tableIndices[i] = fixedTableIndex;
			tableIndicesToCreate[entitiesToCreateCount] = fixedTableIndex;
			entityIdsToCreate[entitiesToCreateCount] = entityId;
			entitiesToCreateCount += !isValid;
		}

		table.Reserve(entitiesToCreateCount);
		for (std::size_t i = 0uz; i < entitiesToCreateCount; ++i)
		{
			table.Insert(tableIndicesToCreate[i], entityIdsToCreate[i]);
		}
	}

	void World::RemoveTag(TagTable& table, const Entity entity) noexcept
	{
		if (const std::size_t targetIndex = table.Find(entity.id); table.IsValid(targetIndex, entity.id))
		{
			table.Remove(targetIndex);
		}
	}

	void World::RemoveTags(TagTable& table, const std::span<const Entity> entities, const std::span<std::size_t> tableIndices) noexcept
	{
		std::size_t tableDestroyCount = 0uz;

		for (std::size_t tableIndex = 0uz; const Entity entity : entities)
		{
			tableIndex = table.Find(entity.id, tableIndex);
			const bool isValidEntity = table.IsValid(tableIndex, entity.id);
			tableIndices[tableDestroyCount] = tableIndex;
			tableDestroyCount += isValidEntity;
		}

		for (std::size_t i = tableDestroyCount; i-- > 0uz; )
		{
			table.Remove(tableIndices[i]);
		}
	}

	void World::RemoveTags(const Entity entity) noexcept
	{
		for (TagTable& table : tagTables)
		{
			RemoveTag(table, entity);
		}
	}

	void World::RemoveTags(const std::span<const Entity> entities, const std::span<std::size_t> tableIndices) noexcept
	{
		for (TagTable& table : tagTables)
		{
			RemoveTags(table, entities, tableIndices);
		}
	}

	void World::CheckIfValid(const Entity entity) const
	{
#ifndef NDEBUG
		if (!IsValid(entity)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid entity");
		}
#endif
	}

	void World::CheckIfValid(const std::size_t entityIndex, const Entity entity) const
	{
#ifndef NDEBUG
		if (!IsValid(entityIndex, entity)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid entity");
		}
#endif
	}

	void World::CheckIfSorted(const std::span<const Entity> entities)
	{
#ifndef NDEBUG
		for (std::size_t i = 1uz; i < entities.size(); ++i)
		{
			if (entities[i] <= entities[i - 1uz]) [[unlikely]]
			{
				throw std::invalid_argument("Entities are not sorted");
			}
		}
#endif
	}

	void World::CheckIfValid(const std::span<const Entity> entities) const
	{
#ifndef NDEBUG
		if (!AreValid(entities)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid entity");
		}
#endif
	}
}
