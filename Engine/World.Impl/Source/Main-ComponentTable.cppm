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
	class ComponentTable final
	{
	public:
		[[nodiscard("Pure constructor")]]
		ComponentTable(std::size_t componentSize, std::size_t componentAlignment) noexcept;
		ComponentTable(const ComponentTable&) = delete;
		[[nodiscard("Pure constructor")]]
		ComponentTable(ComponentTable&& other) noexcept = default;

		~ComponentTable() noexcept = default;

		[[nodiscard("Pure function")]]
		std::size_t ComponentSize() const noexcept;
		[[nodiscard("Pure function")]]
		std::size_t ComponentAlignment() const noexcept;

		[[nodiscard("Pure function")]]
		EntityID Size() const noexcept;
		[[nodiscard("Pure function")]]
		bool Contains(EntityID entity) const noexcept;
		[[nodiscard("Pure function")]]
		EntityID Index(EntityID entity) const noexcept;
		[[nodiscard("Pure function")]]
		EntityID Entity(EntityID index) const noexcept;
		[[nodiscard("Pure function")]]
		void* Component(EntityID index) const noexcept;
		void Add(std::span<const EntityID> entitiesToAdd);
		void Remove(std::span<const EntityID> entitiesToRemove) noexcept;
		void Clear() noexcept;

		ComponentTable& operator =(const ComponentTable&) = delete;
		ComponentTable& operator =(ComponentTable&& other) noexcept = default;

	private:
		void EnsureSparse(EntityID maxEntityToAdd);
		void EnsureDense(std::span<const EntityID> entitiesToAdd);

		[[nodiscard("Pure function")]]
		static EntityID MaxEntity(std::span<const EntityID> entities) noexcept;

		struct ComponentDeleter final
		{
			std::size_t alignment;

			void operator ()(std::byte* ptr) const noexcept;
		};

		std::unique_ptr<EntityID[]> sparse;
		std::unique_ptr<EntityID[]> entities;
		std::unique_ptr<std::byte[], ComponentDeleter> components;

		EntityID sparseCapacity;
		EntityID denseSize;
		EntityID denseCapacity;

		std::size_t componentSize;
		std::size_t componentAlignment;
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
		return sparse[entity];
	}

	EntityID ComponentTable::Entity(const EntityID index) const noexcept
	{
		return entities[index];
	}

	void* ComponentTable::Component(const EntityID index) const noexcept
	{
		return &components[index * componentSize];
	}

	void ComponentTable::Add(const std::span<const EntityID> entitiesToAdd)
	{
		EnsureSparse(MaxEntity(entitiesToAdd));
		EnsureDense(entitiesToAdd);

		for (const EntityID entity : entitiesToAdd)
		{
			sparse[entity] = denseSize;
			entities[denseSize] = entity;
			++denseSize;
		}
	}

	void ComponentTable::Remove(const std::span<const EntityID> entitiesToRemove) noexcept
	{
		for (const EntityID entity : entitiesToRemove)
		{
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
		std::fill_n(sparse.get(), sparseCapacity, std::numeric_limits<EntityID>::max());
	}

	void ComponentTable::EnsureSparse(const EntityID maxEntityToAdd)
	{
		if (maxEntityToAdd < sparseCapacity) [[likely]]
		{
			return;
		}

		const EntityID newCapacity = std::bit_ceil(maxEntityToAdd + 1u);
		auto newSparse = std::make_unique<EntityID[]>(newCapacity);
		std::memcpy(newSparse.get(), sparse.get(), sparseCapacity * sizeof(EntityID));
		std::fill_n(newSparse.get() + sparseCapacity, newCapacity - sparseCapacity, std::numeric_limits<EntityID>::max());
		sparse = std::move(newSparse);
		sparseCapacity = newCapacity;
	}

	void ComponentTable::EnsureDense(const std::span<const EntityID> entitiesToAdd)
	{
		if (denseSize + entitiesToAdd.size() <= denseCapacity) [[likely]]
		{
			return;
		}

		const EntityID newCapacity = static_cast<EntityID>(std::bit_ceil(denseSize + entitiesToAdd.size()));
		const std::size_t newComponentSize = newCapacity * componentSize;
		auto newEntities = std::make_unique<EntityID[]>(newCapacity);
		auto newComponents = std::unique_ptr<std::byte[], ComponentDeleter>(static_cast<std::byte*>(
			operator new[](newComponentSize, std::align_val_t{componentAlignment})), ComponentDeleter{.alignment = componentAlignment});
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
