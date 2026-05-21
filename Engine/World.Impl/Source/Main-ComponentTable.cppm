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
		std::size_t Size() const noexcept;
		[[nodiscard("Pure function")]]
		std::size_t Find(EntityID entity, std::size_t startIndex = 0uz) const noexcept;
		[[nodiscard("Pure function")]]
		bool IsValid(std::size_t index, EntityID entity) const noexcept;

		[[nodiscard("Pure function")]]
		EntityID GetEntity(std::size_t index) const noexcept;
		[[nodiscard("Pure function")]]
		void* GetComponent(std::size_t index) const noexcept;

		void Reserve(std::size_t addSize);
		void Insert(std::size_t index, EntityID entity);
		void Remove(std::size_t index) noexcept;
		void Clear() noexcept;

		ComponentTable& operator =(const ComponentTable&) = delete;
		ComponentTable& operator =(ComponentTable&& other) noexcept = default;

	private:
		struct DataDeleter final
		{
			std::size_t alignment;

			void operator ()(std::byte* ptr) const noexcept;
		};

		std::unique_ptr<EntityID[]> entities;
		std::unique_ptr<std::byte[], DataDeleter> components;
		std::size_t size;
		std::size_t capacity;

		std::size_t componentSize;
		std::size_t componentAlignment;
	};
}

namespace PonyEngine::World
{
	ComponentTable::ComponentTable(const std::size_t componentSize, const std::size_t componentAlignment) noexcept :
		size{0uz},
		capacity{0uz},
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

	std::size_t ComponentTable::Size() const noexcept
	{
		return size;
	}

	std::size_t ComponentTable::Find(const EntityID entity, const std::size_t startIndex) const noexcept
	{
		return std::lower_bound(entities.get() + startIndex, entities.get() + size, entity) - entities.get();
	}

	bool ComponentTable::IsValid(const std::size_t index, const EntityID entity) const noexcept
	{
		return index < size && entities[index] == entity;
	}

	EntityID ComponentTable::GetEntity(const std::size_t index) const noexcept
	{
		assert(index < size && "Out of range.");
		return entities[index];
	}

	void* ComponentTable::GetComponent(const std::size_t index) const noexcept
	{
		assert(index < size && "Out of range.");
		return &components[index * componentSize];
	}

	void ComponentTable::Reserve(const std::size_t addSize)
	{
		if (capacity - size < addSize)
		{
			const std::size_t newCapacity = std::bit_ceil(size + addSize);
			auto newEntities = std::make_unique<EntityID[]>(newCapacity);
			auto newComponents = std::unique_ptr<std::byte[], DataDeleter>(static_cast<std::byte*>(operator new[](newCapacity * componentSize, 
				std::align_val_t{componentAlignment})), DataDeleter{.alignment = componentAlignment});

			std::memcpy(newEntities.get(), entities.get(), size * sizeof(EntityID));
			std::memcpy(newComponents.get(), components.get(), size * componentSize);

			entities = std::move(newEntities);
			components = std::move(newComponents);
			capacity = newCapacity;
		}
	}

	void ComponentTable::Insert(const std::size_t index, const EntityID entity)
	{
		assert(index <= size && "Out of range.");

		Reserve(1uz);

		const std::size_t count = size - index;
		std::memmove(&entities[index + 1], &entities[index], count * sizeof(EntityID));
		std::memmove(&components[(index + 1) * componentSize], &components[index * componentSize], count * componentSize);

		entities[index] = entity;
		++size;
	}

	void ComponentTable::Remove(const std::size_t index) noexcept
	{
		assert(index < size && "Out of range.");

		const std::size_t count = size - index - 1uz;
		std::memmove(&entities[index], &entities[index + 1], count * sizeof(EntityID));
		std::memmove(&components[index * componentSize], &components[(index + 1) * componentSize], count * componentSize);

		--size;
	}

	void ComponentTable::Clear() noexcept
	{
		size = 0uz;
	}

	void ComponentTable::DataDeleter::operator ()(std::byte* const ptr) const noexcept
	{
		operator delete[](ptr, std::align_val_t{alignment});
	}
}
