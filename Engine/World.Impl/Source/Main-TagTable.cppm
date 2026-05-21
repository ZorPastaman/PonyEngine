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

export module PonyEngine.World.Impl:TagTable;

import std;

import PonyEngine.World;

export namespace PonyEngine::World
{
	class TagTable final
	{
	public:
		[[nodiscard("Pure constructor")]]
		TagTable() noexcept = default;
		TagTable(const TagTable&) = delete;
		[[nodiscard("Pure constructor")]]
		TagTable(TagTable&& other) noexcept = default;

		~TagTable() noexcept = default;

		[[nodiscard("Pure function")]]
		std::size_t Size() const noexcept;
		[[nodiscard("Pure function")]]
		std::size_t Find(EntityID entity, std::size_t startIndex = 0uz) const noexcept;
		[[nodiscard("Pure function")]]
		bool IsValid(std::size_t index, EntityID entity) const noexcept;

		[[nodiscard("Pure function")]]
		EntityID GetEntity(std::size_t index) const noexcept;

		void Reserve(std::size_t addSize);
		void Insert(std::size_t index, EntityID entity);
		void Remove(std::size_t index) noexcept;
		void Clear() noexcept;

		TagTable& operator =(const TagTable&) = delete;
		TagTable& operator =(TagTable&& other) noexcept = default;

	private:
		std::vector<EntityID> entities;
	};
}

namespace PonyEngine::World
{
	std::size_t TagTable::Size() const noexcept
	{
		return entities.size();
	}

	std::size_t TagTable::Find(const EntityID entity, const std::size_t startIndex) const noexcept
	{
		return std::lower_bound(entities.cbegin() + startIndex, entities.cend(), entity) - entities.begin();
	}

	bool TagTable::IsValid(const std::size_t index, const EntityID entity) const noexcept
	{
		return index < entities.size() && entities[index] == entity;
	}

	EntityID TagTable::GetEntity(const std::size_t index) const noexcept
	{
		return entities[index];
	}

	void TagTable::Reserve(const std::size_t addSize)
	{
		entities.reserve(std::bit_ceil(entities.size() + addSize));
	}

	void TagTable::Insert(const std::size_t index, const EntityID entity)
	{
		entities.insert(entities.cbegin() + index, entity);
	}

	void TagTable::Remove(const std::size_t index) noexcept
	{
		entities.erase(entities.cbegin() + index);
	}

	void TagTable::Clear() noexcept
	{
		entities.clear();
	}
}
