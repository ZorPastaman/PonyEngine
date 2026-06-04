/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.World.Impl:World;

import std;

import PonyEngine.Math;
import PonyEngine.Memory;
import PonyEngine.World;

import :ComponentTable;
import :ObjectTable;
import :TypeRegistry;

export namespace PonyEngine::World
{
	/// @brief World.
	class World final : public IWorld
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit World(const TypeRegistry& typeRegistry) noexcept;
		World(const World&) = delete;
		World(World&&) = delete;

		~World() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual std::size_t EntityCount() const noexcept override;
		virtual std::size_t GetEntities(std::span<Entity> entities) const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual bool AreValid(std::span<const Entity> entities) const noexcept override;
		virtual void AreValid(std::span<const Entity> entities, std::span<bool> valid) const override;
		virtual void CreateEntities(std::span<Entity> entities) override;
		virtual void DestroyEntities(std::span<const Entity> entities) override;

		virtual void AddComponents(std::span<const Entity> entities, std::type_index componentType) override;
		virtual void AddComponents(std::span<const Entity> entities, std::type_index componentType, const void* componentData) override;
		virtual void AddComponents(std::span<const Entity> entities, std::type_index componentType, std::span<void*> componentData) override;

		virtual void RemoveComponents(std::span<const Entity> entities, std::type_index componentType) override;

		[[nodiscard("Pure function")]] 
		virtual bool HasComponents(std::span<const Entity> entities, std::type_index componentType) const override;
		virtual void HasComponents(std::span<const Entity> entities, std::type_index componentType, std::span<bool> has) const override;

		[[nodiscard("Pure function")]] 
		virtual std::size_t CountComponents(std::type_index componentType) const override;

		virtual std::size_t GetEntities(std::type_index componentType, std::span<Entity> entities) const override;
		virtual std::size_t GetComponents(std::type_index componentType, std::span<void*> componentData) const override;
		virtual std::size_t GetEntitiesAndComponents(std::type_index componentType, std::span<Entity> entities, std::span<void*> componentData) const override;

		virtual void DropComponents(std::type_index componentType) override;

		[[nodiscard("Pure function")]] 
		virtual std::size_t CountQuery(const QueryParams& params) const override;
		virtual void Query(const QueryParams& params, const std::function<void(QueryItem&)>& callback) const override;

		virtual void CollectGarbage() override;

		World& operator =(const World&) = delete;
		World& operator =(World&&) = delete;

	protected:
		[[nodiscard("Weird call")]] 
		virtual TypelessObjectHandle RegisterObject(std::type_index objectType, const std::shared_ptr<void>& object) override;
		virtual void UnregisterObject(std::type_index objectType, TypelessObjectHandle handle) override;
		virtual void ReplaceObject(TypelessObjectHandle handle, std::type_index objectType, const std::shared_ptr<void>& object) override;

		[[nodiscard("Pure function")]] 
		virtual bool IsObjectValid(std::type_index objectType, TypelessObjectHandle handle) const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual const std::shared_ptr<void>& GetObject(std::type_index objectType, TypelessObjectHandle handle) const override;

	private:
		/// @brief Checks if the entity is invalid.
		/// @param entity Entity to check.
		/// @return @a True if it's invalid; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsInvalid(Entity entity) const noexcept;
		/// @brief Makes a new entity.
		/// @return Entity.
		[[nodiscard("Weird call")]]
		Entity MakeEntity() noexcept;
		/// @brief Resurrects an entity.
		/// @return Entity.
		[[nodiscard("Weird call")]]
		Entity ResurrectEntity() noexcept;
		/// @brief Kills the entity.
		/// @param entity Entity to kill.
		void KillEntity(Entity entity) noexcept;

		/// @brief Tries to find a component table.
		/// @param componentType Component type.
		/// @return Component table or @a nullptr if not found.
		[[nodiscard("Pure function")]]
		ComponentTable* FindComponentTable(std::type_index componentType);
		/// @brief Tries to find a component table.
		/// @param componentType Component type.
		/// @return Component table or @a nullptr if not found.
		[[nodiscard("Pure function")]]
		const ComponentTable* FindComponentTable(std::type_index componentType) const;
		/// @brief Gets or creates a component table.
		/// @param componentType Component type.
		/// @return Component table.
		[[nodiscard("Weird call")]]
		ComponentTable& GetOrCreateComponentTable(std::type_index componentType);
		/// @brief Adds entities and components to a component table if it doesn't have them.
		/// @param entities Entities to add.
		/// @param componentType Component type.
		/// @return Component table.
		ComponentTable& UpdateComponents(std::span<const Entity> entities, std::type_index componentType);
		/// @brief Adds components to the table.
		/// @param table Component table
		/// @param entities Entities to add.
		/// @param tableEntities Table entities cache.
		static void AddComponents(ComponentTable& table, std::span<const Entity> entities, std::span<EntityID> tableEntities);
		/// @brief Removes components from the table.
		/// @param table Component table.
		/// @param entities Entities.
		/// @param tableEntities Table entities cache.
		static void RemoveComponents(ComponentTable& table, std::span<const Entity> entities, std::span<EntityID> tableEntities) noexcept;
		/// @brief Copies entities from the table to the external array.
		/// @param table Component table.
		/// @param entities Entities.
		void CopyEntities(const ComponentTable& table, std::span<Entity> entities) const noexcept;
		/// @brief Copies component pointers from the table to the external array.
		/// @param table Component table.
		/// @param componentData Component data.
		static void CopyComponents(const ComponentTable& table, std::span<void*> componentData) noexcept;

		/// @brief Finds required tables.
		/// @param types Component types.
		/// @param requiredTables Required tables.
		/// @return @a True if all the tables found; @a false otherwise.
		[[nodiscard("Must be used")]]
		bool FindRequired(std::span<const std::type_index> types, std::span<const ComponentTable*> requiredTables) const noexcept;
		/// @brief Finds excluded tables.
		/// @param types Component types.
		/// @param excludedTables Excluded tables cache.
		/// @return Excluded tables.
		[[nodiscard("Must be used")]]
		std::span<const ComponentTable*> FindExcluded(std::span<const std::type_index> types, std::span<const ComponentTable*> excludedTables) const noexcept;
		/// @brief Finds optional tables.
		/// @param types Component types.
		/// @param optionalTables Optional tables cache.
		/// @param optionalIndices Optional table to output index map cache.
		/// @return Optional tables and table to output index map.
		[[nodiscard("Must be used")]]
		std::pair<std::span<const ComponentTable*>, std::span<std::size_t>> FindOptional(std::span<const std::type_index> types, 
			std::span<const ComponentTable*> optionalTables, std::span<std::size_t> optionalIndices) const noexcept;
		/// @brief Processes a query with required tables.
		/// @param requiredTables Required tables. Mustn't be empty.
		/// @param excludedTables Excluded tables.
		/// @param optionalTables Optional tables.
		/// @param requiredComponents Required components cache.
		/// @param optionalComponents Optional components cache.
		/// @param optionalIndices Optional table to output index map.
		/// @param callback Callback.
		void ProcessQuery(std::span<const ComponentTable* const> requiredTables, std::span<const ComponentTable* const> excludedTables,
			std::span<const ComponentTable* const> optionalTables, std::span<void*> requiredComponents, std::span<void*> optionalComponents,
			std::span<std::size_t> optionalIndices, const std::function<void(QueryItem&)>& callback) const;
		/// @brief Processes a query without required tables.
		/// @param excludedTables Excluded tables.
		/// @param optionalTables Optional tables.
		/// @param optionalComponents Optional components cache.
		/// @param optionalIndices Optional table to output index map.
		/// @param callback Callback.
		void ProcessQuery(std::span<const ComponentTable* const> excludedTables, std::span<const ComponentTable* const> optionalTables, 
			std::span<void*> optionalComponents, std::span<std::size_t> optionalIndices, const std::function<void(QueryItem&)>& callback) const;
		/// @brief Finds the smallest table.
		/// @param tables Tables.
		/// @return Smallest table.
		[[nodiscard("Pure function")]]
		static const ComponentTable* SmallestTable(std::span<const ComponentTable* const> tables) noexcept;
		/// @brief Tries to find the entity in the tables.
		/// @param tables Component tables.
		/// @param entityId Entity to find.
		/// @param excluded Required/excluded mode.
		/// @return @a True if all the tables or at least one table contain the entity (depending on the @p excluded); @a false otherwise.
		static bool FindEntity(std::span<const ComponentTable* const> tables, EntityID entityId, bool excluded) noexcept;
		/// @brief Fills required components to the output.
		/// @param entityId Entity.
		/// @param requiredTables Required tables.
		/// @param requiredComponents Required components.
		static void FillRequired(EntityID entityId, std::span<const ComponentTable* const> requiredTables, std::span<void*> requiredComponents) noexcept;
		/// @brief Fills optional components to the output.
		/// @param entityId Entity.
		/// @param optionalTables Optional tables.
		/// @param optionalIndices Optional table to output index map.
		/// @param optionalComponents Optional components.
		static void FillOptional(EntityID entityId, std::span<const ComponentTable* const> optionalTables, std::span<const std::size_t> optionalIndices,
			std::span<void*> optionalComponents) noexcept;
		/// @brief Executes the callback.
		/// @param requiredComponents Required components.
		/// @param optionalComponents Optional components.
		/// @param entityId Entity.
		/// @param callback Callback.
		/// @return @a True if the query must terminate; @a false otherwise.
		[[nodiscard("Must be used")]]
		bool ExecuteCallback(std::span<void* const> requiredComponents, std::span<void* const> optionalComponents, EntityID entityId, 
			const std::function<void(QueryItem&)>& callback) const;

		/// @brief Gets an arena.
		/// @return Arena.
		[[nodiscard("Pure function")]]
		static Memory::Arena& Arena();

		/// @brief Checks if the entities ara valid for world operations.
		/// @param entities Entities to check.
		void CheckIfValid(std::span<const Entity> entities) const;
		/// @brief Checks if the entities contains duplicates.
		/// @param entities Entities to check.
		static void CheckForDuplicates(std::span<const Entity> entities);

		/// @brief Checks if the types contains duplicates.
		/// @param types Types to check.
		static void CheckForDuplicates(std::span<const std::type_index> types);
		/// @brief Checks if the type spans have the same types.
		/// @param firstTypes First types.
		/// @param secondTypes Second types.
		static void CheckForDuplicates(std::span<const std::type_index> firstTypes, std::span<const std::type_index> secondTypes);

		const TypeRegistry* typeRegistry; ///< Type registry.

		std::vector<EntityGeneration> entityGenerations; ///< Entity generations.
		std::vector<EntityID> deadEntities; ///< Dead entities.

		std::vector<ComponentTable> componentTables; ///< Component tables.
		std::unordered_map<std::type_index, std::size_t> componentTablesIndices; ///< Component type to component tables index map.

		ObjectTable objectTable; ///< Object table.

		static_assert(sizeof(std::size_t) >= sizeof(EntityID), "std::size_t is less than EntityID.");
	};
}

namespace PonyEngine::World
{
	World::World(const TypeRegistry& typeRegistry) noexcept :
		typeRegistry{&typeRegistry}
	{
	}

	std::size_t World::EntityCount() const noexcept
	{
		return entityGenerations.size() - deadEntities.size();
	}

	std::size_t World::GetEntities(const std::span<Entity> entities) const noexcept
	{
		const EntityID outputCount = static_cast<EntityID>(std::min(EntityCount(), entities.size()));
		for (EntityID inputIndex = 0u, outputIndex = 0u; outputIndex < outputCount; ++inputIndex)
		{
			const EntityGeneration generation = entityGenerations[inputIndex];
			entities[outputIndex] = Entity{.id = inputIndex, .generation =  generation};
			outputIndex += Math::IsOdd(generation);
		}

		return outputCount;
	}

	bool World::AreValid(const std::span<const Entity> entities) const noexcept
	{
		for (const Entity entity : entities)
		{
			if (IsInvalid(entity))
			{
				return false;
			}
		}

		return true;
	}

	void World::AreValid(const std::span<const Entity> entities, const std::span<bool> valid) const
	{
#ifndef NDEBUG
		if (entities.size() != valid.size()) [[unlikely]]
		{
			throw std::invalid_argument("Entity and valid span sizes are mismatched");
		}
#endif

		for (std::size_t i = 0; i < entities.size(); ++i)
		{
			valid[i] = !IsInvalid(entities[i]);
		}
	}

	void World::CreateEntities(const std::span<Entity> entities)
	{
		if (entities.size() > deadEntities.size())
		{
			const std::size_t requiredSize = entityGenerations.size() + (entities.size() - deadEntities.size());
			if (entities.size() > std::numeric_limits<EntityID>::max() || requiredSize > std::numeric_limits<EntityID>::max()) [[unlikely]]
			{
				throw std::invalid_argument("Entity count is too great");
			}


			entityGenerations.reserve(requiredSize);
		}

		std::size_t index = 0uz;
		for (std::size_t resurrectCount = std::min(deadEntities.size(), entities.size()); resurrectCount-- > 0uz; ++index)
		{
			entities[index] = ResurrectEntity();
		}
		for (; index < entities.size(); ++index)
		{
			entities[index] = MakeEntity();
		}
	}

	void World::DestroyEntities(const std::span<const Entity> entities)
	{
		CheckIfValid(entities);

		deadEntities.reserve(deadEntities.size() + entities.size());

		Memory::Arena& arena = Arena();
		arena.Free();

		const Memory::Arena::Slice<EntityID> tableEntitiesSlice = arena.Allocate<EntityID>(entities.size());
		const std::span<EntityID> tableEntities = arena.Span(tableEntitiesSlice);

		for (ComponentTable& table : componentTables)
		{
			RemoveComponents(table, entities, tableEntities);
		}

		for (const Entity entity : entities)
		{
			KillEntity(entity);
		}
	}

	void World::AddComponents(const std::span<const Entity> entities, const std::type_index componentType)
	{
		UpdateComponents(entities, componentType);
	}

	void World::AddComponents(const std::span<const Entity> entities, const std::type_index componentType, const void* const componentData)
	{
#ifndef NDEBUG
		if (!componentData) [[unlikely]]
		{
			throw std::invalid_argument("Component data is nullptr");
		}
#endif

		const ComponentTable& table = UpdateComponents(entities, componentType);

		auto byteData = static_cast<const std::byte*>(componentData);
		const std::size_t componentSize = table.ComponentSize();
		for (std::size_t i = 0uz; i < entities.size(); ++i, byteData += componentSize)
		{
			const EntityID index = table.Index(entities[i].id);
			std::memcpy(table.Component(index), byteData, componentSize);
		}
	}

	void World::AddComponents(const std::span<const Entity> entities, const std::type_index componentType, const std::span<void*> componentData)
	{
#ifndef NDEBUG
		if (entities.size() != componentData.size()) [[unlikely]]
		{
			throw std::invalid_argument("Entity and component data span sizes are mismatched");
		}
#endif

		const ComponentTable& table = UpdateComponents(entities, componentType);

		for (std::size_t i = 0uz; i < entities.size(); ++i)
		{
			const EntityID index = table.Index(entities[i].id);
			componentData[i] = table.Component(index);
		}
	}

	void World::RemoveComponents(const std::span<const Entity> entities, const std::type_index componentType)
	{
		CheckIfValid(entities);

		if (ComponentTable* const table = FindComponentTable(componentType))
		{
			Memory::Arena& arena = Arena();
			arena.Free();

			const Memory::Arena::Slice<EntityID> tableEntitiesSlice = arena.Allocate<EntityID>(entities.size());
			const std::span<EntityID> tableEntities = arena.Span(tableEntitiesSlice);

			RemoveComponents(*table, entities, tableEntities);
		}
	}

	bool World::HasComponents(const std::span<const Entity> entities, const std::type_index componentType) const
	{
		CheckIfValid(entities);

		if (const ComponentTable* const table = FindComponentTable(componentType))
		{
			for (const Entity entity : entities)
			{
				if (!table->Contains(entity.id))
				{
					return false;
				}
			}

			return true;
		}

		return false;
	}

	void World::HasComponents(const std::span<const Entity> entities, const std::type_index componentType, const std::span<bool> has) const
	{
		CheckIfValid(entities);

#ifndef NDEBUG
		if (entities.size() != has.size()) [[unlikely]]
		{
			throw std::invalid_argument("Entity and has span sizes are mismatched");
		}
#endif

		if (const ComponentTable* const table = FindComponentTable(componentType))
		{
			for (std::size_t i = 0uz; i < entities.size(); ++i)
			{
				has[i] = table->Contains(entities[i].id);
			}
		}
		else
		{
			std::ranges::fill(has, false);
		}
	}

	std::size_t World::CountComponents(const std::type_index componentType) const
	{
		if (const ComponentTable* const table = FindComponentTable(componentType))
		{
			return table->Size();
		}

		return 0uz;
	}

	std::size_t World::GetEntities(const std::type_index componentType, const std::span<Entity> entities) const
	{
		if (const ComponentTable* const table = FindComponentTable(componentType))
		{
			const EntityID count = static_cast<EntityID>(std::min(static_cast<std::size_t>(table->Size()), entities.size()));
			CopyEntities(*table, entities.subspan(0uz, count));

			return count;
		}

		return 0uz;
	}

	std::size_t World::GetComponents(const std::type_index componentType, const std::span<void*> componentData) const
	{
		if (const ComponentTable* const table = FindComponentTable(componentType))
		{
			const EntityID count = static_cast<EntityID>(std::min(static_cast<std::size_t>(table->Size()), componentData.size()));
			CopyComponents(*table, componentData.subspan(0uz, count));

			return count;
		}

		return 0uz;
	}

	std::size_t World::GetEntitiesAndComponents(const std::type_index componentType, const std::span<Entity> entities, const std::span<void*> componentData) const
	{
#ifndef NDEBUG
		if (entities.size() != componentData.size())
		{
			throw std::invalid_argument("Entity and component data span sizes are mismatched");
		}
#endif

		if (const ComponentTable* const table = FindComponentTable(componentType))
		{
			const EntityID count = static_cast<EntityID>(std::min(static_cast<std::size_t>(table->Size()), entities.size()));
			CopyEntities(*table, entities.subspan(0uz, count));
			CopyComponents(*table, componentData.subspan(0uz, count));

			return count;
		}

		return 0uz;
	}

	void World::DropComponents(const std::type_index componentType)
	{
		if (ComponentTable* const table = FindComponentTable(componentType))
		{
			table->Clear();
		}
	}

	std::size_t World::CountQuery(const QueryParams& params) const
	{
		std::size_t count = EntityCount();
		for (const std::type_index tableType : params.requiredComponentTypes)
		{
			count = std::min(count, CountComponents(tableType));
		}

		return count;
	}

	void World::Query(const QueryParams& params, const std::function<void(QueryItem&)>& callback) const
	{
		CheckForDuplicates(params.requiredComponentTypes);
		CheckForDuplicates(params.excludedComponentTypes);
		CheckForDuplicates(params.optionalComponentTypes);
		CheckForDuplicates(params.requiredComponentTypes, params.excludedComponentTypes);
		CheckForDuplicates(params.requiredComponentTypes, params.optionalComponentTypes);
		CheckForDuplicates(params.excludedComponentTypes, params.optionalComponentTypes);

#ifndef NDEBUG
		if (!callback) [[unlikely]]
		{
			throw std::invalid_argument("Callback is nullptr");
		}
#endif

		Memory::Arena& arena = Arena();
		arena.Free();

		const Memory::Arena::Slice<const ComponentTable*> requiredComponentTablesSlice = arena.Allocate<const ComponentTable*>(params.requiredComponentTypes.size());
		const Memory::Arena::Slice<const ComponentTable*> excludedComponentTablesSlice = arena.Allocate<const ComponentTable*>(params.excludedComponentTypes.size());
		const Memory::Arena::Slice<const ComponentTable*> optionalComponentTablesSlice = arena.Allocate<const ComponentTable*>(params.optionalComponentTypes.size());
		const Memory::Arena::Slice<std::size_t> optionalOutputIndicesSlice = arena.Allocate<std::size_t>(params.optionalComponentTypes.size());
		const Memory::Arena::Slice<void*> requiredComponentsSlice = arena.Allocate<void*>(params.requiredComponentTypes.size());
		const Memory::Arena::Slice<void*> optionalComponentsSlice = arena.Allocate<void*>(params.optionalComponentTypes.size());

		const std::span<const ComponentTable*> requiredComponentTables = arena.Span(requiredComponentTablesSlice);
		if (!FindRequired(params.requiredComponentTypes, requiredComponentTables))
		{
			return;
		}

		const std::span<const ComponentTable*> excludedComponentTables = FindExcluded(params.excludedComponentTypes, arena.Span(excludedComponentTablesSlice));
		const auto [optionalComponentTables, optionalOutputIndices] = FindOptional(params.optionalComponentTypes, arena.Span(optionalComponentTablesSlice),
			arena.Span(optionalOutputIndicesSlice));

		const std::span<void*> requiredComponents = arena.Span(requiredComponentsSlice);
		const std::span<void*> optionalComponents = arena.Span(optionalComponentsSlice);
		std::ranges::fill(optionalComponents, nullptr);

		if (requiredComponentTables.empty())
		{
			ProcessQuery(excludedComponentTables, optionalComponentTables, optionalComponents, optionalOutputIndices, callback);
		}
		else
		{
			ProcessQuery(requiredComponentTables, excludedComponentTables, optionalComponentTables,
				requiredComponents, optionalComponents, optionalOutputIndices, callback);
		}
	}

	void World::CollectGarbage()
	{
		objectTable.CollectGarbage(*typeRegistry, componentTables, componentTablesIndices, Arena());
	}

	TypelessObjectHandle World::RegisterObject(const std::type_index objectType, const std::shared_ptr<void>& object)
	{
		return objectTable.RegisterObject(objectType, object);
	}

	void World::UnregisterObject(const std::type_index objectType, const TypelessObjectHandle handle)
	{
		objectTable.UnregisterObject(objectType, handle);
	}

	void World::ReplaceObject(const TypelessObjectHandle handle, const std::type_index objectType, const std::shared_ptr<void>& object)
	{
		objectTable.ReplaceObject(handle, objectType, object);
	}

	bool World::IsObjectValid(const std::type_index objectType, const TypelessObjectHandle handle) const noexcept
	{
		return objectTable.IsObjectValid(objectType, handle);
	}

	const std::shared_ptr<void>& World::GetObject(const std::type_index objectType, const TypelessObjectHandle handle) const
	{
		return objectTable.GetObject(objectType, handle);
	}

	bool World::IsInvalid(const Entity entity) const noexcept
	{
		return Math::IsEven(entity.generation) || entity.id >= entityGenerations.size() || entityGenerations[entity.id] != entity.generation;
	}

	Entity World::MakeEntity() noexcept
	{
		const EntityID entityId = static_cast<EntityID>(entityGenerations.size());

		constexpr EntityGeneration entityGeneration = 1u;
		entityGenerations.push_back(entityGeneration);

		return Entity{.id = entityId, .generation = entityGeneration};
	}

	Entity World::ResurrectEntity() noexcept
	{
		const EntityID entityId = deadEntities.back();
		deadEntities.pop_back();

		const EntityGeneration entityGeneration = ++entityGenerations[entityId];

		return Entity{.id = entityId, .generation = entityGeneration};
	}

	void World::KillEntity(const Entity entity) noexcept
	{
		++entityGenerations[entity.id];
		deadEntities.push_back(entity.id);
	}

	ComponentTable* World::FindComponentTable(const std::type_index componentType)
	{
		return const_cast<ComponentTable*>(const_cast<const World*>(this)->FindComponentTable(componentType));
	}

	const ComponentTable* World::FindComponentTable(const std::type_index componentType) const
	{
		if (const auto position = componentTablesIndices.find(componentType); position != componentTablesIndices.cend())
		{
			return &componentTables[position->second];
		}
#ifndef NDEBUG
		if (!typeRegistry->IsValidComponent(componentType)) [[unlikely]]
		{
			throw std::invalid_argument("Component type is not registered");
		}
#endif

		return nullptr;
	}

	ComponentTable& World::GetOrCreateComponentTable(const std::type_index componentType)
	{
		if (const auto position = componentTablesIndices.find(componentType); position != componentTablesIndices.cend()) [[likely]]
		{
			return componentTables[position->second];
		}
		
		ComponentTable table = typeRegistry->CreateComponentTable(componentType);
		componentTables.push_back(std::move(table));
		try
		{
			componentTablesIndices[componentType] = componentTables.size() - 1uz;
		}
		catch (...)
		{
			componentTables.pop_back();
			throw;
		}

		return componentTables.back();
	}

	ComponentTable& World::UpdateComponents(const std::span<const Entity> entities, const std::type_index componentType)
	{
		CheckIfValid(entities);

		Memory::Arena& arena = Arena();
		arena.Free();

		const Memory::Arena::Slice<EntityID> tableEntitiesSlice = arena.Allocate<EntityID>(entities.size());
		const std::span<EntityID> tableEntities = arena.Span(tableEntitiesSlice);

		ComponentTable& table = GetOrCreateComponentTable(componentType);
		AddComponents(table, entities, tableEntities);

		return table;
	}

	void World::AddComponents(ComponentTable& table, const std::span<const Entity> entities, const std::span<EntityID> tableEntities)
	{
		std::size_t tableEntityCount = 0uz;

		for (const Entity entity : entities)
		{
			tableEntities[tableEntityCount] = entity.id;
			tableEntityCount += !table.Contains(entity.id);
		}

		table.Add(tableEntities.subspan(0uz, tableEntityCount));
	}

	void World::RemoveComponents(ComponentTable& table, const std::span<const Entity> entities, const std::span<EntityID> tableEntities) noexcept
	{
		std::size_t tableEntityCount = 0uz;

		for (const Entity entity : entities)
		{
			tableEntities[tableEntityCount] = entity.id;
			tableEntityCount += table.Contains(entity.id);
		}

		table.Remove(tableEntities.subspan(0uz, tableEntityCount));
	}

	void World::CopyEntities(const ComponentTable& table, const std::span<Entity> entities) const noexcept
	{
		for (EntityID i = 0u; i < entities.size(); ++i)
		{
			const EntityID entityId = table.Entity(i);
			entities[i] = Entity{.id = entityId, .generation = entityGenerations[entityId]};
		}
	}

	void World::CopyComponents(const ComponentTable& table, const std::span<void*> componentData) noexcept
	{
		for (EntityID i = 0u; i < componentData.size(); ++i)
		{
			componentData[i] = table.Component(i);
		}
	}

	bool World::FindRequired(const std::span<const std::type_index> types, const std::span<const ComponentTable*> requiredTables) const noexcept
	{
		for (std::size_t i = 0uz; i < requiredTables.size(); ++i)
		{
			if (!((requiredTables[i] = FindComponentTable(types[i]))))
			{
				return false;
			}
		}

		return true;
	}

	std::span<const ComponentTable*> World::FindExcluded(const std::span<const std::type_index> types, const std::span<const ComponentTable*> excludedTables) const noexcept
	{
		std::size_t excludedComponentTableCount = 0uz;
		for (const std::type_index componentType : types)
		{
			const bool found = (excludedTables[excludedComponentTableCount] = FindComponentTable(componentType));
			excludedComponentTableCount += found;
		}

		return excludedTables.subspan(0uz, excludedComponentTableCount);
	}

	std::pair<std::span<const ComponentTable*>, std::span<std::size_t>> World::FindOptional(const std::span<const std::type_index> types, 
		const std::span<const ComponentTable*> optionalTables, const std::span<std::size_t> optionalIndices) const noexcept
	{
		std::size_t optionalComponentTableCount = 0uz;
		for (std::size_t i = 0uz; i < types.size(); ++i)
		{
			const bool found = (optionalTables[optionalComponentTableCount] = FindComponentTable(types[i]));
			optionalIndices[optionalComponentTableCount] = i;
			optionalComponentTableCount += found;
		}

		return std::pair(optionalTables.subspan(0uz, optionalComponentTableCount), optionalIndices.subspan(0uz, optionalComponentTableCount));
	}

	void World::ProcessQuery(const std::span<const ComponentTable* const> requiredTables, const std::span<const ComponentTable* const> excludedTables, 
		const std::span<const ComponentTable* const> optionalTables, const std::span<void*> requiredComponents, const std::span<void*> optionalComponents,
		const std::span<std::size_t> optionalIndices, const std::function<void(QueryItem&)>& callback) const
	{
		const ComponentTable* const mainTable = SmallestTable(requiredTables);
		for (EntityID mainIndex = 0uz; mainIndex < mainTable->Size(); ++mainIndex)
		{
			const EntityID entityId = mainTable->Entity(mainIndex);

			if (!FindEntity(requiredTables, entityId, false) || FindEntity(excludedTables, entityId, true))
			{
				continue;
			}

			FillRequired(entityId, requiredTables, requiredComponents);
			FillOptional(entityId, optionalTables, optionalIndices, optionalComponents);

			if (ExecuteCallback(requiredComponents, optionalComponents, entityId, callback)) [[unlikely]]
			{
				break;
			}
		}
	}

	void World::ProcessQuery(const std::span<const ComponentTable* const> excludedTables, const std::span<const ComponentTable* const> optionalTables, 
		const std::span<void*> optionalComponents, const std::span<std::size_t> optionalIndices, const std::function<void(QueryItem&)>& callback) const
	{
		for (EntityID entityId = 0u; entityId < entityGenerations.size(); ++entityId)
		{
			if (Math::IsEven(entityGenerations[entityId]) || FindEntity(excludedTables, entityId, true))
			{
				continue;
			}

			FillOptional(entityId, optionalTables, optionalIndices, optionalComponents);

			if (ExecuteCallback(std::span<void* const>(), optionalComponents, entityId, callback)) [[unlikely]]
			{
				break;
			}
		}
	}

	const ComponentTable* World::SmallestTable(const std::span<const ComponentTable* const> tables) noexcept
	{
		std::size_t smallestIndex = 0uz;
		std::size_t smallestSize = tables[smallestIndex]->Size();
		for (std::size_t i = 1uz; i < tables.size(); ++i)
		{
			if (const std::size_t size = tables[i]->Size(); size < smallestSize)
			{
				smallestSize = size;
				smallestIndex = i;
			}
		}

		return tables[smallestIndex];
	}

	bool World::FindEntity(const std::span<const ComponentTable* const> tables, const EntityID entityId, const bool excluded) noexcept
	{
		bool found = !excluded;
		for (std::size_t i = 0uz; i < tables.size() && found ^ excluded; ++i)
		{
			found = tables[i]->Contains(entityId);
		}

		return found;
	}

	void World::FillRequired(const EntityID entityId, const std::span<const ComponentTable* const> requiredTables, const std::span<void*> requiredComponents) noexcept
	{
		for (std::size_t requiredIndex = 0uz; requiredIndex < requiredTables.size(); ++requiredIndex)
		{
			const ComponentTable* const table = requiredTables[requiredIndex];
			requiredComponents[requiredIndex] = table->Component(table->Index(entityId));
		}
	}

	void World::FillOptional(const EntityID entityId, const std::span<const ComponentTable* const> optionalTables, const std::span<const std::size_t> optionalIndices,
		const std::span<void*> optionalComponents) noexcept
	{
		for (std::size_t i = 0uz; i < optionalTables.size(); ++i)
		{
			const ComponentTable* const table = optionalTables[i];
			optionalComponents[optionalIndices[i]] = table->Contains(entityId) ? table->Component(table->Index(entityId)) : nullptr;
		}
	}

	bool World::ExecuteCallback(const std::span<void* const> requiredComponents, const std::span<void* const> optionalComponents, const EntityID entityId,
		const std::function<void(QueryItem&)>& callback) const
	{
		auto queryItem = QueryItem
		{
			.requiredComponents = requiredComponents,
			.optionalComponents = optionalComponents,
			.entity = Entity{.id = entityId, .generation = entityGenerations[entityId]},
			.terminate = false
		};
		callback(queryItem);

		return queryItem.terminate;
	}

	Memory::Arena& World::Arena()
	{
		thread_local auto arena = Memory::Arena(0uz, 256uz);
		return arena;
	}

	void World::CheckIfValid(const std::span<const Entity> entities) const
	{
		CheckForDuplicates(entities);

#ifndef NDEBUG
		if (!AreValid(entities)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid entity");
		}
#endif
	}

	void World::CheckForDuplicates(const std::span<const Entity> entities)
	{
#ifndef NDEBUG
		for (std::size_t i = 1uz; i < entities.size(); ++i)
		{
			for (std::size_t j = 0uz; j < i; ++j)
			{
				if (entities[i].id == entities[j].id) [[unlikely]]
				{
					throw std::invalid_argument("Duplicate entity");
				}
			}
		}
#endif
	}

	void World::CheckForDuplicates(const std::span<const std::type_index> types)
	{
#ifndef NDEBUG
		for (std::size_t i = 1uz; i < types.size(); ++i)
		{
			for (std::size_t j = 0uz; j < i; ++j)
			{
				if (types[i] == types[j]) [[unlikely]]
				{
					throw std::invalid_argument("Duplicate type");
				}
			}
		}
#endif
	}

	void World::CheckForDuplicates(const std::span<const std::type_index> firstTypes, const std::span<const std::type_index> secondTypes)
	{
#ifndef NDEBUG
		for (const std::type_index firstType : firstTypes)
		{
			for (const std::type_index secondType : secondTypes)
			{
				if (firstType == secondType) [[unlikely]]
				{
					throw std::invalid_argument("Duplicate type");
				}
			}
		}
#endif
	}
}
