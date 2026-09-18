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

export module PonyEngine.World.Impl:ComponentTable;

import std;

import PonyEngine.World;

export namespace PonyEngine::World
{
	/// @brief Component table.
	class ComponentTable final
	{
	public:
		/// @brief Creates a component table.
		/// @param componentSize Component size.
		/// @param componentAlignment Component alignment.
		[[nodiscard("Pure constructor")]]
		ComponentTable(std::size_t componentSize, std::size_t componentAlignment) noexcept;
		ComponentTable(const ComponentTable&) = delete;
		[[nodiscard("Pure constructor")]]
		ComponentTable(ComponentTable&& other) noexcept = default;

		~ComponentTable() noexcept = default;

		/// @brief Gets a component size.
		/// @return Component size.
		[[nodiscard("Pure function")]]
		std::size_t ComponentSize() const noexcept;
		/// @brief Gets a component alignment.
		/// @return Component alignment.
		[[nodiscard("Pure function")]]
		std::size_t ComponentAlignment() const noexcept;

		/// @brief Gets the table size.
		/// @return Table size.
		[[nodiscard("Pure function")]]
		EntityID Size() const noexcept;
		/// @brief Checks if the table contains the entity.
		/// @param entity Entity to check.
		/// @return @a True if it contains; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool Contains(EntityID entity) const noexcept;
		/// @brief Gets the entity index.
		/// @param entity Entity. Must be contained in the table.
		/// @return Entity index.
		[[nodiscard("Pure function")]]
		EntityID Index(EntityID entity) const noexcept;
		/// @brief Gets an entity at the index.
		/// @param index Entity index. Must be valid.
		/// @return Entity.
		[[nodiscard("Pure function")]]
		EntityID Entity(EntityID index) const noexcept;
		/// @brief Gets an entity component at the index.
		/// @param index Entity index. Must be valid.
		/// @return Entity component.
		[[nodiscard("Pure function")]]
		void* Component(EntityID index) const noexcept;
		/// @brief Adds the entities to the table.
		/// @param entitiesToAdd Entities to add. The table mustn't contain the entities.
		void Add(std::span<const EntityID> entitiesToAdd);
		/// @brief Removes the entities from the table.
		/// @param entitiesToRemove Entities to remove. The table must contain the entities.
		void Remove(std::span<const EntityID> entitiesToRemove) noexcept;
		/// @brief Clears the table.
		void Clear() noexcept;

		ComponentTable& operator =(const ComponentTable&) = delete;
		ComponentTable& operator =(ComponentTable&& other) noexcept = default;

	private:
		/// @brief Extends the sparse array if needed.
		/// @param maxEntityToAdd Max entity that will be added.
		void EnsureSparse(EntityID maxEntityToAdd);
		/// @brief Extends the dense arrays if needed.
		/// @param addCount How many entities will be added.
		void EnsureDense(EntityID addCount);

		/// @brief Calculates a maximum entity.
		/// @param entities Entities.
		/// @return Maximum entity.
		[[nodiscard("Pure function")]]
		static EntityID MaxEntity(std::span<const EntityID> entities) noexcept;

		/// @brief Component data deleter.
		struct ComponentDeleter final
		{
			std::size_t alignment; ///< Component data alignment.

			/// @brief Deletes the component data array.
			/// @param ptr Component data array.
			void operator ()(std::byte* ptr) const noexcept;
		};

		std::unique_ptr<EntityID[]> sparse; ///< Sparse.
		std::unique_ptr<EntityID[]> entities; ///< Entities dense.
		std::unique_ptr<std::byte[], ComponentDeleter> components; ///< Component data dense.

		EntityID sparseCapacity; ///< Sparse capacity.
		EntityID denseSize; ///< Dense size.
		EntityID denseCapacity; ///< Dense capacity.

		std::size_t componentSize; ///< Component size.
		std::size_t componentAlignment; ///< Component alignment.

		static_assert(sizeof(std::size_t) >= sizeof(EntityID), "std::size_t is less than EntityID.");
	};
}

namespace PonyEngine::World
{
	ComponentTable::ComponentTable(const std::size_t componentSize, const std::size_t componentAlignment) noexcept :
		sparseCapacity{0u},
		denseSize{0u},
		denseCapacity{0u},
		componentSize{componentSize},
		componentAlignment{componentAlignment}
	{
	}

	std::size_t ComponentTable::ComponentSize() const noexcept
	{
		return componentSize;
	}

	std::size_t ComponentTable::ComponentAlignment() const noexcept
	{
		return componentAlignment;
	}

	EntityID ComponentTable::Size() const noexcept
	{
		return denseSize;
	}

	bool ComponentTable::Contains(const EntityID entity) const noexcept
	{
		return entity < sparseCapacity && sparse[entity] < denseSize && entities[sparse[entity]] == entity;
	}

	EntityID ComponentTable::Index(const EntityID entity) const noexcept
	{
		assert(entity < sparseCapacity && "Out of range.");
		return sparse[entity];
	}

	EntityID ComponentTable::Entity(const EntityID index) const noexcept
	{
		assert(index < denseSize && "Out of range.");
		return entities[index];
	}

	void* ComponentTable::Component(const EntityID index) const noexcept
	{
		assert(index < denseSize && "Out of range.");
		return &components[index * componentSize];
	}

	void ComponentTable::Add(const std::span<const EntityID> entitiesToAdd)
	{
		EnsureSparse(MaxEntity(entitiesToAdd));
		EnsureDense(static_cast<EntityID>(entitiesToAdd.size()));

		for (const EntityID entity : entitiesToAdd)
		{
			assert(!Contains(entity) && "The entity was already added.");
			sparse[entity] = denseSize;
			entities[denseSize] = entity;
			++denseSize;
		}
	}

	void ComponentTable::Remove(const std::span<const EntityID> entitiesToRemove) noexcept
	{
		for (const EntityID entity : entitiesToRemove)
		{
			assert(Contains(entity) && "The entity wasn't added.");

			if (const EntityID denseIndexToRemove = sparse[entity]; denseIndexToRemove != --denseSize) [[likely]]
			{
				const EntityID lastEntity = entities[denseSize];
				entities[denseIndexToRemove] = lastEntity;
				std::memcpy(Component(denseIndexToRemove), Component(denseSize), componentSize);
				sparse[lastEntity] = denseIndexToRemove;
			}

			sparse[entity] = std::numeric_limits<EntityID>::max();
		}
	}

	void ComponentTable::Clear() noexcept
	{
		denseSize = 0u;
		std::memset(sparse.get(), -1, sparseCapacity * sizeof(EntityID));
	}

	void ComponentTable::EnsureSparse(const EntityID maxEntityToAdd)
	{
		if (maxEntityToAdd < sparseCapacity) [[likely]]
		{
			return;
		}

		const EntityID requiredCapacity = maxEntityToAdd + 1u;
		const EntityID newCapacity = requiredCapacity > 1u << (std::numeric_limits<EntityID>::digits - 1) 
			? std::numeric_limits<EntityID>::max() 
			: std::bit_ceil(requiredCapacity);
		auto newSparse = std::make_unique<EntityID[]>(newCapacity);

		std::memcpy(newSparse.get(), sparse.get(), sparseCapacity * sizeof(EntityID));
		std::memset(newSparse.get() + sparseCapacity, -1, (newCapacity - sparseCapacity) * sizeof(EntityID));

		sparse = std::move(newSparse);
		sparseCapacity = newCapacity;
	}

	void ComponentTable::EnsureDense(const EntityID addCount)
	{
		const EntityID requiredCapacity = denseSize + addCount;
		if (requiredCapacity <= denseCapacity) [[likely]]
		{
			return;
		}

		const EntityID newCapacity = requiredCapacity > 1u << (std::numeric_limits<EntityID>::digits - 1)
			? std::numeric_limits<EntityID>::max()
			: std::bit_ceil(requiredCapacity);
		const std::size_t newComponentCapacity = newCapacity * componentSize;
		auto newEntities = std::make_unique<EntityID[]>(newCapacity);
		auto newComponents = std::unique_ptr<std::byte[], ComponentDeleter>(static_cast<std::byte*>(
			operator new[](newComponentCapacity, std::align_val_t{componentAlignment})), ComponentDeleter{.alignment = componentAlignment});

		std::memcpy(newEntities.get(), entities.get(), denseSize * sizeof(EntityID));
		std::memcpy(newComponents.get(), components.get(), denseSize * componentSize);

		entities = std::move(newEntities);
		components = std::move(newComponents);
		denseCapacity = newCapacity;
	}

	EntityID ComponentTable::MaxEntity(const std::span<const EntityID> entities) noexcept
	{
		EntityID maxEntity = 0u;
		for (const EntityID entity : entities)
		{
			maxEntity = std::max(maxEntity, entity);
		}

		return maxEntity;
	}

	void ComponentTable::ComponentDeleter::operator ()(std::byte* const ptr) const noexcept
	{
		operator delete[](ptr, std::align_val_t{alignment});
	}
}
