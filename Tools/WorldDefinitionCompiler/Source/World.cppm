/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyTools.World;

import std;

export namespace PonyTools::World
{
	class WorldDefinition final
	{
	public:
		[[nodiscard("Pure constructor")]]
		WorldDefinition() noexcept = default;
		[[nodiscard("Pure constructor")]]
		WorldDefinition(const WorldDefinition& other) = default;
		[[nodiscard("Pure constructor")]]
		WorldDefinition(WorldDefinition&& other) noexcept = default;

		~WorldDefinition() noexcept = default;

		[[nodiscard("Pure function")]]
		std::uint64_t GetEntity(std::string_view entityId) const;
		[[nodiscard("Pure function")]]
		std::vector<std::byte>& GetComponentData(std::size_t tableIndex) noexcept;

		std::uint64_t AddEntity(std::string_view entityId);
		std::size_t AddComponent(std::uint64_t entityIndex, std::string_view componentType);
		std::uint64_t AddObject(std::string_view objectId, std::string_view objectType, std::span<const std::byte> objectData);

		WorldDefinition& operator =(const WorldDefinition& other);
		WorldDefinition& operator =(WorldDefinition&& other) noexcept = default;

	private:
		struct ComponentTable final
		{
			std::string type;
			std::vector<std::uint64_t> entities;
			std::vector<std::byte> data;
		};
		struct Object final
		{
			std::string type;
			std::vector<std::byte> data;
		};

		[[nodiscard("Weird call")]]
		std::size_t GetOrCreateTable(std::string_view componentType);

		std::vector<std::string> entityIds;
		std::vector<ComponentTable> componentTables;
		std::vector<Object> objects;
		std::vector<std::string> objectIds;
	};
}

namespace PonyTools::World
{
	std::uint64_t WorldDefinition::GetEntity(const std::string_view entityId) const
	{
		if (const auto position = std::ranges::find(entityIds, entityId); position != entityIds.cend()) [[likely]]
		{
			return static_cast<std::uint64_t>(position - entityIds.cbegin());
		}

		throw std::invalid_argument("Entity not found");
	}

	std::vector<std::byte>& WorldDefinition::GetComponentData(const std::size_t tableIndex) noexcept
	{
		return componentTables[tableIndex].data;
	}

	std::uint64_t WorldDefinition::AddEntity(const std::string_view entityId)
	{
		if (std::ranges::contains(entityIds, entityId)) [[unlikely]]
		{
			throw std::invalid_argument(std::format("Entity with the same id '{}' is already added", entityId));
		}

		if (entityIds.size() >= std::numeric_limits<std::uint64_t>::max()) [[unlikely]]
		{
			throw std::overflow_error("Too many entities");
		}

		entityIds.push_back(std::string(entityId));
		return static_cast<std::uint64_t>(entityIds.size() - 1uz);
	}

	std::size_t WorldDefinition::AddComponent(const std::uint64_t entityIndex, const std::string_view componentType)
	{
		std::size_t tableIndex = GetOrCreateTable(componentType);
		ComponentTable& table = componentTables[tableIndex];

		if (std::ranges::contains(table.entities, entityIndex)) [[unlikely]]
		{
			throw std::invalid_argument("Entity already has component of this type");
		}

		table.entities.push_back(entityIndex);
		return tableIndex;
	}

	std::uint64_t WorldDefinition::AddObject(const std::string_view objectId, const std::string_view objectType, const std::span<const std::byte> objectData)
	{
		if (std::ranges::contains(objectIds, objectId)) [[unlikely]]
		{
			throw std::invalid_argument("Object with the same id is already added");
		}

		objects.push_back(Object{.type = std::string(objectType), .data = std::vector(objectData.cbegin(), objectData.cend())});
		objectIds.push_back(std::string(objectId));
		return static_cast<std::uint64_t>(objects.size() - 1uz);
	}

	std::size_t WorldDefinition::GetOrCreateTable(const std::string_view componentType)
	{
		const auto position = std::ranges::find_if(componentTables, [&](const ComponentTable& table) { return table.type == componentType; });
		const std::size_t index = position - componentTables.cbegin();
		if (index == componentTables.size())
		{
			componentTables.push_back(ComponentTable{.type = std::string(componentType)});
		}

		return index;
	}

	WorldDefinition& WorldDefinition::operator =(const WorldDefinition& other)
	{
		WorldDefinition definition = other;
		return *this = std::move(definition);
	}
}
